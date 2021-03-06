#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_3l_1tau_h

/** \class EvtHistManager_3l_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 3l_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_3l_1tau.h" // MEMOutput_3l_1tau

class EvtHistManager_3l_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_3l_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_3l_1tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium, 
		      double mvaOutput_3l_ttV, double mvaOutput_3l_ttbar, double mvaDiscr_3l, double mvaOutput_3l_1tau_ttV, double mvaOutput_3l_1tau_ttbar, double mvaDiscr_3l_1tau, 
		      double mTauTauVis1, double mTauTauVis2, 
		      const MEMOutput_3l_1tau* memOutput_3l_1tau, double evtWeight);

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  int era_;

  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_3l_ttV_;
  TH1* histogram_mvaOutput_3l_ttbar_;
  TH1* histogram_mvaDiscr_3l_;

  TH1* histogram_mvaOutput_3l_1tau_ttV_;
  TH1* histogram_mvaOutput_3l_1tau_ttbar_;
  TH1* histogram_mvaDiscr_3l_1tau_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_memOutput_isValid_;
  TH1* histogram_memOutput_errorFlag_;
  TH1* histogram_memOutput_type_;
  TH1* histogram_memOutput_logWeight_ttH_;
  TH1* histogram_memOutput_logWeight_ttZ_;
  TH1* histogram_memOutput_logWeight_ttH_hww_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_mem_logCPUTime_;
  TH1* histogram_mem_logRealTime_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
