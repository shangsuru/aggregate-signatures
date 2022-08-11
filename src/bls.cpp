#include "bls.h"

using namespace mcl::bn256;

BLS::BLS() {
  initPairing();
  mapToG2(g_, 1);
}

void BLS::generateKeys(G2& pk, Fr& sk) {
  sk.setRand();
  G2::mul(pk, g_, sk);
}

void BLS::sign(G1& sig, const std::string& m, const Fr& sk) {
  G1 hash;
  BLS::hash(hash, m);
  G1::mul(sig, hash, sk);
}

auto BLS::verify(const G1& sig, const std::string& m, const G2& pk) -> bool {
  Fp12 e1;
  Fp12 e2;
  G1 hash;
  BLS::hash(hash, m);
  pairing(e1, sig, g_);
  pairing(e2, hash, pk);
  return e1 == e2;
}

void BLS::hash(G1& p, const std::string& m) {
  Fp t;
  t.setHashOf(m);
  mapToG1(p, t);
}