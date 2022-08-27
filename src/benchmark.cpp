#include "benchmark.h"

using namespace mcl::bn256;
using namespace std;
using namespace std::chrono;

auto generateMessages(int numberOfMessages) -> vector<string> {
  vector<string> msgs;
  for (int i = 1; i <= numberOfMessages; i++) {
    msgs.push_back("msg" + to_string(i));
  }
  return msgs;
}

auto runBLS(const vector<string>& msgs) -> ExperimentData {
  G1 sig;
  G2 pk;
  Fr sk;
  BLS bls = BLS();
  bls.generateKeys(pk, sk);

  auto start = high_resolution_clock::now();
  for (const string& m : msgs) {
    BLS::sign(sig, m, sk);
  }
  auto stop = high_resolution_clock::now();
  auto time_to_sign = duration_cast<milliseconds>(stop - start);

  start = high_resolution_clock::now();
  for (const string& m : msgs) {
    bls.verify(sig, m, pk);
  }
  stop = high_resolution_clock::now();
  auto time_to_verify = duration_cast<milliseconds>(stop -start);

  return ExperimentData{
      SignatureScheme::kBLS, msgs.size(), sizeof(sig) / 1000.0 * msgs.size(), sizeof(pk) / 1000.0 * msgs.size(), sizeof(sk) / 1000.0 * msgs.size(),
      time_to_sign, time_to_verify,
  };
}

auto runBGLS(const vector<string>& msgs) -> ExperimentData {
  BGLS bgls = BGLS();
  G1 agg;
  vector<G2> pks;
  vector<Fr> sks;
  vector<G1> sigs;
  G2 pk;
  Fr sk;
  G1 sig;

  // Generate keys
  for (int i = 0; i < msgs.size(); i++) {
    bgls.generateKeys(pk, sk);
    pks.push_back(pk);
    sks.push_back(sk);
  }

  // Sign messages and aggregate them into a single signature
  auto start = high_resolution_clock::now();
  for (int i = 0; i < msgs.size(); i++) {
    BGLS::sign(sig, msgs[i], sks[i]);
    sigs.push_back(sig);
    bgls.verify(sig, msgs[i], pks[i]);
  }
  BGLS::aggregate(agg, sigs);
  auto stop = high_resolution_clock::now();
  auto time_to_sign = duration_cast<milliseconds>(stop - start);

  start = high_resolution_clock::now();
  bgls.aggregateVerify(agg, pks, msgs);
  stop = high_resolution_clock::now();
  auto time_to_verify = duration_cast<milliseconds>(stop -start);

  return ExperimentData{
      SignatureScheme::kBLS, msgs.size(), sizeof(agg) / 1000.0 , sizeof(pk) / 1000.0 * msgs.size(), sizeof(sk) / 1000.0 * msgs.size(),
      time_to_sign, time_to_verify,
  };
}

auto runFischlin(const vector<string>& msgs) -> ExperimentData {
  HistoryFreeSAS fischlin = HistoryFreeSAS();
  auto sas = SAS();
  vector<G2> pks;
  vector<Fr> sks;
  G2 pk;
  Fr sk;

  // Generate keys
  for (int i = 0; i < msgs.size(); i++) {
    fischlin.generateKeys(pk, sk);
    pks.push_back(pk);
    sks.push_back(sk);
  }

  // Compute aggregate
  auto start = high_resolution_clock::now();
  for (int i = 0; i < msgs.size(); i++) {
    fischlin.aggregate(sas, pks[i], sks[i], msgs[i]);
  }
  auto stop = high_resolution_clock::now();
  auto time_to_sign = duration_cast<milliseconds>(stop - start);

  // Verify the aggregate
  start = high_resolution_clock::now();
  fischlin.aggregateVerify(sas, pks, msgs);
  stop = high_resolution_clock::now();
  auto time_to_verify = duration_cast<milliseconds>(stop - start);

  return ExperimentData{
      SignatureScheme::kFischlin, msgs.size(), sizeof(sas) / 1000.0, sizeof(pk) / 1000.0 * msgs.size(), sizeof(sk) / 1000.0 * msgs.size(),
      time_to_sign, time_to_verify,
  };
}

void writeToCSV(const vector<ExperimentData>& collectedDatapoints) {
  ofstream f;
  f.open("results/aggsig.csv");

  string csv_header =
      "scheme,N,signatureSizeKB,publicKeySizeKB,privateKeySizeKB,timeToSign,"
      "timeToVerify";
  f << csv_header << endl;

  for (const ExperimentData& data : collectedDatapoints) {
    f << data << endl;
  }

  f.close();
}

auto main() -> int {
  vector<int> number_of_messages = {10, 100, 1000, 10000, 100000};
  vector<ExperimentData> data;
  for (int n : number_of_messages) {
    vector<string> msgs = generateMessages(n);
    cout << "Running BLS with N=" << n << endl;
    data.push_back(runBLS(msgs));
    cout << "Running BGLS with N=" << n << endl;
    data.push_back(runBGLS(msgs));
    cout << "Running Fischlin with N=" << n << endl;
    data.push_back(runFischlin(msgs));
  }

  writeToCSV(data);
  return 0;
}