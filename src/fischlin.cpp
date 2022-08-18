#include "fischlin.h"

using namespace mcl::bn256;
using std::string;
using std::to_string;
using std::vector;

HistoryFreeSAS::HistoryFreeSAS()  {
  hashAndMapToG2(emptyPK_, "0");
}

auto HistoryFreeSAS::emptyPK() -> mcl::bn256::G2 { return emptyPK_; }

auto HistoryFreeSAS::aggregate(SAS& agg, const G2& pk, const Fr& sk,
                               const string& msg) -> bool {
  // Add message into the hashchain
  Fp12 e = 1;
  G2 old_pk = emptyPK_;
  if (!agg.aggSig.isZero()) {
    pairing(e, agg.aggSig, g_);
    old_pk = agg.pk;
  }
  string new_c = computeHashchain(e, msg, old_pk, agg.c);

  // Verify signature on old hashchain
  if (BLS::verify(agg.s, agg.c, old_pk) ||
      (old_pk == emptyPK_ && agg.c == emptyHash_ && agg.s.isZero())) {
    // Sign new hashchain
    G1 new_s;
    sign(new_s, new_c, sk);
    // Add signature into aggregate
    G1 new_agg;
    G1::add(new_agg, agg.aggSig, new_s);

    // Output new aggregate signature
    agg.aggSig = new_agg;
    agg.c = new_c;
    agg.pk = pk;
    agg.s = new_s;

    return true;
  }

  return false;  // Aggregation failed
}

auto HistoryFreeSAS::aggregateVerify(const SAS& agg, const vector<G2>& pks,
                                     const vector<string>& msgs) -> bool {
  vector<string> hashchains;
  Fp12 product = 1;
  for (int i = 0; i < msgs.size(); i++) {
    // Recompute all intermediate hashchain values
    if (i == 0) {
      hashchains.push_back(computeHashchain(product, msgs[i], emptyPK_, emptyHash_));
    } else {
      hashchains.push_back(computeHashchain(product, msgs[i], pks[i - 1], hashchains[i - 1]));
    }

    Fp12 tmp;
    G1 hash;
    BLS::hash(hash, hashchains[i]);
    pairing(tmp, hash, pks[i]);
    Fp12::mul(product, product, tmp);
  }

  Fp12 e;
  pairing(e, agg.aggSig, g_);
  return e == product;
}

auto HistoryFreeSAS::computeHashchain(const Fp12& e, const string& m,
                                      const G2& pk, const string& c) -> string {
  std::hash<string> hashchain;
  return to_string(
      hashchain(e.serializeToHexStr() + m + pk.serializeToHexStr() + c));
}