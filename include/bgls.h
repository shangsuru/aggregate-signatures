#pragma once

#include <cassert>
#include <mcl/bn256.hpp>
#include <vector>

#include "bls.h"

/* Boneh, Dan, et al
 * "Aggregate and verifiably encrypted signatures from bilinear maps"
 * International conference on the theory and applications of cryptographic
 * techniques Springer, Berlin, Heidelberg, 2003
 */
class BGLS : public BLS {
 public:
  static void aggregate(mcl::bn256::G1& agg,
                        const std::vector<mcl::bn256::G1>& sigs);
  auto aggregateVerify(const mcl::bn256::G1& agg,
                       const std::vector<mcl::bn256::G2>& pks,
                       const std::vector<std::string>& msgs) -> bool;
};
