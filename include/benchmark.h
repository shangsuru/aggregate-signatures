#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

#include "bgls.h"
#include "bls.h"
#include "fischlin.h"

class SignatureScheme {
 public:
  inline static const std::string kBLS = "BLS";
  inline static const std::string kBGLS = "BGLS";
  inline static const std::string kFischlin = "FISCHLIN";
};

struct ExperimentData {
  std::string signatureScheme;
  size_t numberOfMessages;
  double signatureSizeKB;
  double publicKeySizeKB;
  double privateKeySizeKB;
  std::chrono::milliseconds timeToSign;
  std::chrono::milliseconds timeToVerify;
};

auto operator<<(std::ostream &strm, const ExperimentData &d) -> std::ostream& {
  return strm << d.signatureScheme << "," <<  d.numberOfMessages << "," << d.signatureSizeKB << "," 
              << d.publicKeySizeKB << "," << d.privateKeySizeKB << "," << d.timeToSign.count() << "," 
              << d.timeToVerify.count();
}