#include <iostream>
#include "bls.h"
#include "bgls.h"

using namespace mcl::bn256;
using namespace std;

void runBLS() {
  string m = "Hello World";
  G1 sig;
  G2 pk;
  Fr sk;
  BLS bls = BLS();
  bls.generateKeys(pk, sk);
  BLS::sign(sig, m, sk);
  if (bls.verify(sig, m, pk)) {
    cout << "BLS: SUCCESS" << endl;
  } else {
    cout << "BLS: FAILURE" << endl;
  }
}

void runBGLS() {
  BGLS bgls = BGLS();
  vector<string> msgs = {"hello1", "hello2", "hello3"};
  vector<G2> pks;
  vector<Fr> sks;
  vector<G1> sigs;
  G2 pk;
  Fr sk;
  G1 sig;
  G1 agg;
  for (int i = 0; i < 3; i++) {
    bgls.generateKeys(pk, sk);
    pks.push_back(pk);
    sks.push_back(sk);
    BGLS::sign(sig, msgs[i], sk);
    sigs.push_back(sig);
    assert(bgls.verify(sig, msgs[i], pk));
  }
  BGLS::aggregate(agg, sigs);
  if (bgls.aggregateVerify(agg, pks, msgs)) {
    cout << "BGLS: SUCCESS" << endl;
  } else {
    cout << "BGLS: FAILURE" << endl;
  }
}

auto main() -> int {
  runBLS();
  runBGLS();
  return 0;
}