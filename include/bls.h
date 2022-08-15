#pragma once

#include <mcl/bn256.hpp>

/* Boneh, Dan, Ben Lynn, and Hovav Shacham
 * "Short signatures from the Weil pairing"
 * International conference on the theory and application of cryptology and
 * information security
 * Springer, Berlin, Heidelberg, 2001
 */
class BLS {
 public:
  BLS();
  void generateKeys(mcl::bn256::G2& pk, mcl::bn256::Fr& sk);
  static void sign(mcl::bn256::G1& sig, const std::string& m,
                   const mcl::bn256::Fr& sk);
  auto verify(const mcl::bn256::G1& sig, const std::string& m,
              const mcl::bn256::G2& pk) -> bool;

 protected:
  static void hash(mcl::bn256::G1& p, const std::string& m);
  mcl::bn256::G2 g_;
};