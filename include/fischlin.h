#pragma once

#include <functional>
#include <mcl/bn256.hpp>
#include <vector>

#include "bls.h"

struct SAS {
  mcl::bn256::G1 aggSig;
  mcl::bn256::G2 pk;
  std::string c;
  mcl::bn256::G1 s;
};

/* Fischlin, Marc, Anja Lehmann, and Dominique Schröder
 * "History-free sequential aggregate signatures"
 * International Conference on Security and Cryptography for Networks
 * Springer, Berlin, Heidelberg, 2012
 */
class HistoryFreeSAS : public BLS {
 public:
  HistoryFreeSAS();
  auto aggregate(SAS& agg, const mcl::bn256::G2& pk, const mcl::bn256::Fr& sk,
                 const std::string& msg) -> bool;
  auto aggregateVerify(const SAS& agg, const std::vector<mcl::bn256::G2>& pks,
                       const std::vector<std::string>& msgs) -> bool;
  const std::string emptyHash_;
  auto emptyPK() -> mcl::bn256::G2;

 private:
  static auto computeHashchain(const mcl::bn256::Fp12& e, const std::string& m,
                        const mcl::bn256::G2& pk, const std::string& c)
      -> std::string;
  mcl::bn256::G2 emptyPK_;
};