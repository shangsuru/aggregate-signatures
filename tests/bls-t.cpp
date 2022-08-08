#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "bls.h"

using namespace mcl::bn256;

TEST_CASE("Accepts signature") {
  BLS bls = BLS();
  std::string m = "msg";
  G1 sig;
  bls.sign(sig, m);
  CHECK(bls.verify(sig, m));
}

TEST_CASE("Accepts signature on empty message") {
  BLS bls = BLS();
  std::string m;
  G1 sig;
  bls.sign(sig, m);
  CHECK(bls.verify(sig, m));
}

TEST_CASE("Neglects signature on different message") {
  BLS bls = BLS();
  std::string m = "msg";
  G1 sig;
  bls.sign(sig, m);
  CHECK(!bls.verify(sig, "other"));
}