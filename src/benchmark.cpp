#include <iostream>
#include "bls.h"

using namespace mcl::bn256;

auto main() -> int {
  std::string m = "Hello World";
  G1 sig;
  G2 pk;
  Fr sk;
  BLS bls = BLS();
  bls.generateKeys(pk, sk);
  bls.sign(sig, m, sk);
  if (bls.verify(sig, m, pk)) {
    std::cout << "Verification successful" << std::endl;
  } else {
    std::cout << "Verification failed" << std::endl;
  }
  
  return 0;
}