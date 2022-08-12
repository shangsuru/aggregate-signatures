#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "bls.h"
#include "doctest.h"

using namespace mcl::bn256;
using std::string;

auto signAndVerify(const string& msgToSign, const string& msgToVerify) -> bool {
  BLS bls = BLS();
  G1 sig;
  G2 pk;
  Fr sk;
  bls.generateKeys(pk, sk);

  BLS::sign(sig, msgToSign, sk);
  return bls.verify(sig, msgToVerify, pk);
}

TEST_CASE("Accepts signature") {
  CHECK(signAndVerify("msg", "msg"));
}

TEST_CASE("Accepts signature on empty message") {
  CHECK(signAndVerify("", ""));
}

TEST_CASE("Rejects signature on different message") {
  CHECK(!signAndVerify("msg", "other"));
}