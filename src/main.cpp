#include <iostream>
#include <mcl/bn256.hpp>

auto main() -> int {
  try {
    mcl::bn256::initPairing();
  } catch (...) {
    std::cout << "An error occurred!" << std::endl;
  }
  std::cout << "Hello from the Pairings World!" << std::endl;
  return 0;
}