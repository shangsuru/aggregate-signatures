#include "bgls.h"

using namespace mcl::bn256;
using namespace std;

void BGLS::aggregate(G1& agg, const vector<G1>& sigs) {
  agg = sigs[0];
  for (int i = 1; i < sigs.size(); i++) {
    G1::add(agg, agg, sigs[i]);
  }
}

auto BGLS::aggregateVerify(const G1& agg, const vector<G2>& pks,
                           const vector<string>& msgs) -> bool {
  assert(pks.size() == msgs.size());
  Fp12 e1;
  Fp12 e2;
  Fp12 tmp;
  G1 hash;

  pairing(e1, agg, g_);

  BLS::hash(hash, msgs[0]);
  pairing(tmp, hash, pks[0]);
  e2 = tmp;
  for (int i = 1; i < pks.size(); i++) {
    BLS::hash(hash, msgs[i]);
    pairing(tmp, hash, pks[i]);
    Fp12::mul(e2, e2, tmp);
  }

  return e1 == e2;
}