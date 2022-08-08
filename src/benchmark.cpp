#include <iostream>
#include "bls.h"

using namespace mcl::bn256;

auto main() -> int {
  std::string m = "Hello World";
  G1 sig;
  BLS bls = BLS();
  bls.sign(sig, m);
  if (bls.verify(sig, m)) {
    std::cout << "Verification successful" << std::endl;
  } else {
    std::cout << "Verification failed" << std::endl;
  }
  
  return 0;
}