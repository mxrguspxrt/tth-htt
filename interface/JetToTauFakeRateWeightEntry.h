#ifndef tthAnalysis_HiggsToTauTau_JetToTauFakeRateWeightEntry_h
#define tthAnalysis_HiggsToTauTau_JetToTauFakeRateWeightEntry_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include <TFile.h> // TFile
#include <TGraphAsymmErrors.h> // TGraphAsymmErrors
#include <TF1.h> // TF1

#include <string>

enum { kFRjt_central, kFRjt_normUp, kFRjt_normDown, kFRjt_shapeUp, kFRjt_shapeDown };

class JetToTauFakeRateWeightEntry
{
 public:
  JetToTauFakeRateWeightEntry(double absEtaMin, double absEtaMax, const std::string& hadTauSelection,
			      TFile* inputFile, const edm::ParameterSet& cfg, int central_or_shift);
  ~JetToTauFakeRateWeightEntry();

  // jet->tau fake-rates (product of fake-rates in MC, determined in bins of tau candidate pT and eta, and data/MC scale factors)
  double getWeight(double pt) const;

  // jet->tau fake-rate scale factors (ratio of jet->tau fake-rates in data and MC simulation);
  // to be applied to simulated events in case data-driven "fake" background estimation is applied to leptons only
  double getSF(double pt) const;
    
  double absEtaMin() const { return absEtaMin_; }
  double absEtaMax() const { return absEtaMax_; }

 private:
  double absEtaMin_;
  double absEtaMax_;
  std::string hadTauSelection_;
  std::string graphName_;
  TGraphAsymmErrors* graph_;
  bool applyGraph_;
  std::string fitFunctionName_;
  TF1* fitFunction_;
  bool applyFitFunction_;
};

#endif
