#ifndef tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_3tau_trigger_h
#define tthAnalysis_HiggsToTauTau_Data_to_MC_CorrectionInterface_0l_3tau_trigger_h

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase

#include <string>
#include <map>
#include <assert.h> // assert

class Data_to_MC_CorrectionInterface_0l_3tau_trigger
{
 public:
  Data_to_MC_CorrectionInterface_0l_3tau_trigger(const edm::ParameterSet& cfg);
  ~Data_to_MC_CorrectionInterface_0l_3tau_trigger();

  //-----------------------------------------------------------------------------
  // set HLT trigger bits
  // (to be called once per event, before calling any of the getSF.. functions)
  void setTriggerBits(bool isTriggered_2tau);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // set hadTau pT, eta and decay mode
  // (to be called once per event, before calling any of the getSF.. functions)
  void setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode, 
		  int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode,
		  int hadTau3_genPdgId, double hadTau3_pt, double hadTau3_eta, int hadTau3_decayMode);
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // trigger efficiency turn-on curves for Spring16 non-reHLT MC (not yet implemented)
  double getWeight_triggerEff() const { assert(0); }
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // data/MC correction for trigger efficiency 
  double getSF_triggerEff() const;
  //-----------------------------------------------------------------------------

 private:

  //-----------------------------------------------------------------------------
  // data/MC corrections for trigger efficiencies in 2016 ReReco data and Summer16 MC

  std::map<int, vLutWrapperBase> effTrigger_2tau_perLeg_data_gentau_;  // key = reconstructed tau decay mode 
  std::map<int, vLutWrapperBase> effTrigger_2tau_perLeg_data_faketau_; // key = reconstructed tau decay mode 
  std::map<int, vLutWrapperBase> effTrigger_2tau_perLeg_mc_gentau_;    // key = reconstructed tau decay mode 
  std::map<int, vLutWrapperBase> effTrigger_2tau_perLeg_mc_faketau_;   // key = reconstructed tau decay mode 
  //-----------------------------------------------------------------------------

  std::map<std::string, TFile*> inputFiles_;

  int era_;
  std::string hadTauSelection_;
  bool isDEBUG_;

  bool isTriggered_2tau_;

  int hadTau1_genPdgId_;
  double hadTau1_pt_;
  double hadTau1_eta_;
  int hadTau1_decayMode_;
  int hadTau2_genPdgId_;
  double hadTau2_pt_;
  double hadTau2_eta_;
  int hadTau2_decayMode_;
  int hadTau3_genPdgId_;
  double hadTau3_pt_;
  double hadTau3_eta_;
  int hadTau3_decayMode_;
};

#endif // tthAnalysis_HiggsToTauTau_data_to_MC_corrections_0l_3tau_trigger_h
