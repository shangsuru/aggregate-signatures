#pragma once

#include <mcl/bn256.hpp>

/* BLS signature scheme according to the paper
 * "Short signatures from the Weil pairing." 
 * Boneh, Dan, Ben Lynn, and Hovav Shacham.
 * International conference on the theory and application of cryptology and information security. 
 * Springer, Berlin, Heidelberg, 2001.
 */
class BLS {
 public:
  BLS();
  void sign(mcl::bn256::G1& sig, const std::string& m);
  auto verify(const mcl::bn256::G1& sig, const std::string& m) -> bool;

 private:
  static void hash(mcl::bn256::G1& p, const std::string& m);
  mcl::bn256::G2 g_;
  mcl::bn256::Fr sk_;
  mcl::bn256::G2 pk_;
};