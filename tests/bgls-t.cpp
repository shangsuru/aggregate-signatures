#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "bgls.h"
#include "doctest.h"

using namespace mcl::bn256;
using namespace std;

void computeAggregate(BGLS& bgls, G1& agg, vector<G2>& pks,
                      const vector<string>& msgs) {
  vector<Fr> sks;
  vector<G1> sigs;
  G2 pk;
  Fr sk;
  G1 sig;

  // Generate keys and sign messages individually
  for (const auto& msg : msgs) {
    bgls.generateKeys(pk, sk);
    pks.push_back(pk);
    sks.push_back(sk);
    BGLS::sign(sig, msg, sk);
    sigs.push_back(sig);
    assert(bgls.verify(sig, msg, pk));
  }

  BGLS::aggregate(agg, sigs);
}

auto verifyAggregate(const vector<string>& msgs) -> bool {
  BGLS bgls = BGLS();
  G1 agg;
  vector<G2> pks;
  computeAggregate(bgls, agg, pks, msgs);
  return bgls.aggregateVerify(agg, pks, msgs);
}

TEST_CASE("Accepts aggregate signature of 3 messages") {
  CHECK(verifyAggregate({"msg1", "msg2", "msg3"}));
}

TEST_CASE("Accepts aggregate signature of 1 message") {
  CHECK(verifyAggregate({"msg1"}));
}

TEST_CASE("Accepts aggregate signature of 10000 messages") {
  vector<string> msgs;
  const int number_of_messages = 10000;
  for (int i = 1; i <= number_of_messages; i++) {
    msgs.push_back("msg" + to_string(i));
  }
  CHECK(verifyAggregate(msgs));
}

TEST_CASE("Rejects aggregate signature with wrong message list") {
  BGLS bgls = BGLS();
  G1 agg;
  vector<G2> pks;
  vector<string> msgs = {"msg1", "msg2", "msg3"};
  computeAggregate(bgls, agg, pks, msgs);
  CHECK(!bgls.aggregateVerify(agg, pks, {"msg1", "msg2", "WRONG"}));
}

TEST_CASE("Order of the messages does not matter") {
  BGLS bgls = BGLS();
  G1 agg;
  vector<G2> pks;
  vector<string> msgs = {"msg1", "msg2", "msg3"};
  computeAggregate(bgls, agg, pks, msgs);

  // Swap the order of messages and corresponding public keys in the
  // verification step
  auto tmp = pks[2];
  pks[2] = pks[1];
  pks[1] = tmp;
  CHECK(bgls.aggregateVerify(agg, pks, {"msg1", "msg3", "msg2"}));
}