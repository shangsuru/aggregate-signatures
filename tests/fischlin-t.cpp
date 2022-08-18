#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "fischlin.h"

using namespace mcl::bn256;
using namespace std;

void computeAggregate(HistoryFreeSAS& fischlin, SAS& sas, vector<G2>& pks) {
  vector<string> msgs = {"msg1", "msg2", "msg3"};
  G2 pk;
  Fr sk;

  // Generate keys and compute aggregate
  for (auto & msg : msgs) {
    fischlin.generateKeys(pk, sk);
    CHECK(fischlin.aggregate(sas, pk, sk, msg));
    pks.push_back(pk);
  }
}

void verifyAggregate(const vector<string>& msgs) {
  HistoryFreeSAS fischlin = HistoryFreeSAS();
  auto sas = SAS();
  vector<G2> pks;
  G2 pk;
  Fr sk;

  // Generate keys and compute aggregate
  for (const auto & msg : msgs) {
    fischlin.generateKeys(pk, sk);
    CHECK(fischlin.aggregate(sas, pk, sk, msg));
    pks.push_back(pk);
  }
  // Verify the aggregate
  CHECK(fischlin.aggregateVerify(sas, pks, msgs));
}

TEST_CASE("Accepts aggregate signature of 1 message") {
  verifyAggregate({"msg1"});
}

TEST_CASE("Accepts aggregate signature of 3 messages") {
  verifyAggregate({"msg1", "msg2", "msg3"});
}

TEST_CASE("Accepts aggregate signature of 10000 messages") {
  vector<string> msgs;
  const int number_of_messages = 10000;
  for (int i = 1; i <= number_of_messages; i++) {
    msgs.push_back("msg" + to_string(i));
  }
  verifyAggregate(msgs);
}

TEST_CASE("Rejects aggregate signature when one message is wrong") {
  HistoryFreeSAS fischlin = HistoryFreeSAS();
  auto sas = SAS();
  vector<G2> pks;
  computeAggregate(fischlin, sas, pks);
  // Includes a wrong message at the verification step
  CHECK(!fischlin.aggregateVerify(sas, pks, {"msg1", "msg2", "WRONG"}));
}

TEST_CASE("Swapping the order of messages makes the verification fail") {
  HistoryFreeSAS fischlin = HistoryFreeSAS();
  SAS sas = SAS();
  vector<G2> pks;
  computeAggregate(fischlin, sas, pks);

  // Swap the order of messages and corresponding public keys in the
  // verification step
  auto tmp = pks[2];
  pks[2] = pks[1];
  pks[1] = tmp;
  CHECK(!fischlin.aggregateVerify(sas, pks, {"msg1", "msg3", "msg2"}));
}