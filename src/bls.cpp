#include "bls.h"

using namespace mcl::bn256;

BLS::BLS() {
  initPairing();
  mapToG2(g_, 1);
  sk_.setRand();
  G2::mul(pk_, g_, sk_);
}

void BLS::sign(G1& sig, const std::string& m) {
  G1 hash;
  BLS::hash(hash, m);
  G1::mul(sig, hash, sk_);
}

auto BLS::verify(const G1& sig, const std::string& m) -> bool {
  Fp12 e1;
  Fp12 e2;
  G1 hash;
  BLS::hash(hash, m);
  pairing(e1, sig, g_);
  pairing(e2, hash, pk_);
  return e1 == e2;
}

void BLS::hash(G1& p, const std::string& m) {
  Fp t;
  t.setHashOf(m);
  mapToG1(p, t);
}