
#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TError.h> // gErrorAbortLevel, kError

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 1l_2tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE 
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_3tau.h" // EvtHistManager_0l_3tau
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager_0l_3tau.h" // CutFlowTableHistManager_0l_3tau
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_bTagWeight, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_3tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_setBranchAddresses, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface.h" // Data_to_MC_CorrectionInterface
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_3tau_trigger.h" // Data_to_MC_CorrectionInterface_0l_3tau_trigger
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

#define EPS 1E-2

typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_3tau };

const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString = {
  { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
  { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
  { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
};

//const int hadTauSelection_antiElectron_lead = 1; // vLoose
//const int hadTauSelection_antiMuon_lead = 1; // Loose 
//const int hadTauSelection_antiElectron_sublead = 2; // Loose
//const int hadTauSelection_antiMuon_sublead = 1; // Loose
//const int hadTauSelection_antiElectron_third = 2; // Loose
//const int hadTauSelection_antiMuon_third = 1; // Loose
const int hadTauSelection_antiElectron_lead = -1; // not applied
const int hadTauSelection_antiMuon_lead = -1; // not applied
const int hadTauSelection_antiElectron_sublead = -1; // not applied
const int hadTauSelection_antiMuon_sublead = -1; // not applied
const int hadTauSelection_antiElectron_third = -1; // not applied
const int hadTauSelection_antiMuon_third = -1; // not applied

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};

int min(int value1, int value2, int value3)
{
  int min12 = std::min(value1, value2);
  return std::min(min12, value3);
} 

/**
 * @brief Produce datacard and control plots for 0l_3tau category.
 */
int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_0l_3tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_0l_3tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("analyze_0l_3tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_0l_3tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  int era = -1;
  if      ( era_string == "2015" ) era = kEra_2015;
  else if ( era_string == "2016" ) era = kEra_2016;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  vstring triggerNames_2tau = cfg_analyze.getParameter<vstring>("triggers_2tau");
  std::vector<hltPath*> triggers_2tau = create_hltPaths(triggerNames_2tau);
  bool use_triggers_2tau = cfg_analyze.getParameter<bool>("use_triggers_2tau");

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  int hadTauSelection = -1;
  if      ( hadTauSelection_part1 == "Loose"                                                     ) hadTauSelection = kLoose;
  else if ( hadTauSelection_part1 == "Fakeable" || hadTauSelection_part1 == "Fakeable_mcClosure" ) hadTauSelection = kFakeable;
  else if ( hadTauSelection_part1 == "Tight"                                                     ) hadTauSelection = kTight;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_string << " !!\n";
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_3tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  enum { kOS, kSS };
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS" ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS" ) hadTauChargeSelection = kSS;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  bool use_HIP_mitigation_bTag = cfg_analyze.getParameter<bool>("use_HIP_mitigation_bTag"); 
  std::cout << "use_HIP_mitigation_bTag = " << use_HIP_mitigation_bTag << std::endl;
  bool use_HIP_mitigation_mediumMuonId = cfg_analyze.getParameter<bool>("use_HIP_mitigation_mediumMuonId"); 
  std::cout << "use_HIP_mitigation_mediumMuonId = " << use_HIP_mitigation_mediumMuonId << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC"); 
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight"); 
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits"); 

  bool isDEBUG = ( cfg_analyze.exists("isDEBUG") ) ? cfg_analyze.getParameter<bool>("isDEBUG") : false; 
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  std::string jet_btagWeight_branch;
  if ( isMC ) {
    if      ( era == kEra_2015 ) jet_btagWeight_branch = "Jet_bTagWeight";
    else if ( era == kEra_2016 ) jet_btagWeight_branch = "Jet_btagWeightCSV";
    else assert(0);
  }

  int jetPt_option = RecoJetReader::kJetPt_central;
  int hadTauPt_option = RecoHadTauReader::kHadTauPt_central;
  int jetToTauFakeRate_option = kFRjt_central;
  int lheScale_option = kLHE_scale_central;
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("analyze_0l_3tau")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_btag") ) {
      if ( isMC ) jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
      else cms::Exception("analyze_0l_3tau")
	<< "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_JES") ) {
      if ( isMC ) {
	jet_btagWeight_branch = getBranchName_bTagWeight(era, central_or_shift);
	if      ( shiftUp_or_Down == "Up"   ) jetPt_option = RecoJetReader::kJetPt_jecUp;
	else if ( shiftUp_or_Down == "Down" ) jetPt_option = RecoJetReader::kJetPt_jecDown;
	else assert(0);
      } else cms::Exception("analyze_0l_3tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_tauES") ) {
      if ( isMC ) {
	if      ( shiftUp_or_Down == "Up"   ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
	else if ( shiftUp_or_Down == "Down" ) hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
	else assert(0);
      } else cms::Exception("analyze_0l_3tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_FRjt") ) {
      if      ( central_or_shift_tstring.EndsWith("normUp")    ) jetToTauFakeRate_option = kFRjt_normUp;
      else if ( central_or_shift_tstring.EndsWith("normDown")  ) jetToTauFakeRate_option = kFRjt_normDown;
      else if ( central_or_shift_tstring.EndsWith("shapeUp")   ) jetToTauFakeRate_option = kFRjt_shapeUp;
      else if ( central_or_shift_tstring.EndsWith("shapeDown") ) jetToTauFakeRate_option = kFRjt_shapeDown;
      else assert(0);
    } else if ( central_or_shift_tstring.BeginsWith("CMS_ttHl_thu_shape") ) {
      if ( isMC ) {
	if      ( central_or_shift_tstring.EndsWith("x1Down") ) lheScale_option = kLHE_scale_xDown;
	else if ( central_or_shift_tstring.EndsWith("x1Up")   ) lheScale_option = kLHE_scale_xUp;
	else if ( central_or_shift_tstring.EndsWith("y1Down") ) lheScale_option = kLHE_scale_yDown;
	else if ( central_or_shift_tstring.EndsWith("y1Up")   ) lheScale_option = kLHE_scale_yUp;
	else assert(0);
      } else cms::Exception("analyze_0l_3tau")
	  << "Configuration parameter 'central_or_shift' = " << central_or_shift << " not supported for data !!\n";
    } else if ( !(central_or_shift_tstring.BeginsWith("CMS_ttHl_FRet") || 
		  central_or_shift_tstring.BeginsWith("CMS_ttHl_FRmt")) ) {
      throw cms::Exception("analyze_0l_3tau")
	<< "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    }
  }

  edm::ParameterSet cfg_dataToMCcorrectionInterface;  
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_lead", hadTauSelection_antiElectron_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_lead", hadTauSelection_antiMuon_lead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_sublead", hadTauSelection_antiElectron_sublead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_sublead", hadTauSelection_antiMuon_sublead);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron_third", hadTauSelection_antiElectron_third);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon_third", hadTauSelection_antiMuon_third);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  //cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", false);
  Data_to_MC_CorrectionInterface* dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface(cfg_dataToMCcorrectionInterface);
  edm::ParameterSet cfg_triggerSF_2tau = cfg_analyze.getParameter<edm::ParameterSet>("triggerSF_2tau");
  cfg_dataToMCcorrectionInterface.addParameter<edm::ParameterSet>("triggerSF_2tau", cfg_triggerSF_2tau);
  Data_to_MC_CorrectionInterface_0l_3tau_trigger* dataToMCcorrectionInterface_0l_3tau_trigger = new Data_to_MC_CorrectionInterface_0l_3tau_trigger(cfg_dataToMCcorrectionInterface);
  
  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "3tau"     ) applyFakeRateWeights = kFR_3tau;
  else throw cms::Exception("analyze_0l_3tau") 
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";
  
  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_3tau ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }
  
  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons1 = cfg_analyze.getParameter<std::string>("branchName_genLeptons1");
  std::string branchName_genLeptons2 = cfg_analyze.getParameter<std::string>("branchName_genLeptons2");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfg_runLumiEventSelector;
    cfg_runLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfg_runLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfg_runLumiEventSelector);
  }
  
  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  const bool selectBDT = [&cfg_analyze]() -> bool
  {
    if(cfg_analyze.exists("selectBDT"))
      return cfg_analyze.getParameter<bool>("selectBDT");
    return false;
  }();

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TChain* inputTree = new TChain(treeName.data());
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("analyze_0l_3tau") 
      << "Failed to identify input Tree !!\n";
  }
  
  std::cout << "input Tree contains " << inputTree->GetEntries() << " Entries in " << inputTree->GetListOfFiles()->GetEntries() << " files." << std::endl;

//--- declare event-level variables
  RUN_TYPE run;
  inputTree->SetBranchAddress(RUN_KEY, &run);
  LUMI_TYPE lumi;
  inputTree->SetBranchAddress(LUMI_KEY, &lumi);
  EVT_TYPE event;
  inputTree->SetBranchAddress(EVT_KEY, &event);
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode;
  if ( isSignal ) {
    inputTree->SetBranchAddress(GENHIGGSDECAYMODE_KEY, &genHiggsDecayMode);
  }

  hltPaths_setBranchAddresses(inputTree, triggers_2tau);

  GENWEIGHT_TYPE genWeight = 1.;
  PUWEIGHT_TYPE pileupWeight = 1.;
  if ( isMC ) {
    inputTree->SetBranchAddress(GENWEIGHT_KEY, &genWeight);
    inputTree->SetBranchAddress(PUWEIGHT_KEY, &pileupWeight);
  }

//--- declare particle collections
  RecoMuonReader* muonReader = new RecoMuonReader(era, Form("n%s", branchName_muons.data()), branchName_muons);
  if ( use_HIP_mitigation_mediumMuonId ) muonReader->enable_HIP_mitigation();
  else muonReader->disable_HIP_mitigation();
  muonReader->setBranchAddresses(inputTree);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, Form("n%s", branchName_electrons.data()), branchName_electrons);
  electronReader->setBranchAddresses(inputTree);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  fakeableElectronSelector.disable_offline_e_trigger_cuts();
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  tightElectronSelector.disable_offline_e_trigger_cuts();

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, Form("n%s", branchName_hadTaus.data()), branchName_hadTaus);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  hadTauReader->setBranchAddresses(inputTree);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(min(hadTauSelection_antiElectron_lead, hadTauSelection_antiElectron_sublead, hadTauSelection_antiElectron_third));
  preselHadTauSelector.set_min_antiMuon(min(hadTauSelection_antiMuon_lead, hadTauSelection_antiMuon_sublead, hadTauSelection_antiMuon_third));
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_lead(era, 0);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector_lead.set(hadTauSelection_part2);
  fakeableHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  fakeableHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_sublead(era, 1);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector_sublead.set(hadTauSelection_part2);
  fakeableHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  fakeableHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector_third(era, 2);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector_third.set(hadTauSelection_part2);
  fakeableHadTauSelector_third.set_min_antiElectron(hadTauSelection_antiElectron_third);
  fakeableHadTauSelector_third.set_min_antiMuon(hadTauSelection_antiMuon_third);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_lead(era, 0);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_lead.set(hadTauSelection_part2);
  tightHadTauSelector_lead.set_min_antiElectron(hadTauSelection_antiElectron_lead);
  tightHadTauSelector_lead.set_min_antiMuon(hadTauSelection_antiMuon_lead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_sublead(era, 1);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_sublead.set(hadTauSelection_part2);
  tightHadTauSelector_sublead.set_min_antiElectron(hadTauSelection_antiElectron_sublead);
  tightHadTauSelector_sublead.set_min_antiMuon(hadTauSelection_antiMuon_sublead);
  RecoHadTauCollectionSelectorTight tightHadTauSelector_third(era, 2);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector_third.set(hadTauSelection_part2);
  tightHadTauSelector_third.set_min_antiElectron(hadTauSelection_antiElectron_third);
  tightHadTauSelector_third.set_min_antiMuon(hadTauSelection_antiMuon_third);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, Form("n%s", branchName_jets.data()), branchName_jets);
  if ( use_HIP_mitigation_bTag ) jetReader->enable_HIP_mitigation();
  else jetReader->disable_HIP_mitigation();
  jetReader->setJetPt_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(inputTree);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);  
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, branchName_met);
  metReader->setBranchAddresses(inputTree);

  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    genLeptonReader = new GenLeptonReader(Form("n%s", branchName_genLeptons1.data()), branchName_genLeptons1, Form("n%s", branchName_genLeptons2.data()), branchName_genLeptons2); 
    genLeptonReader->setBranchAddresses(inputTree);
    genHadTauReader = new GenHadTauReader(Form("n%s", branchName_genHadTaus.data()), branchName_genHadTaus);
    genHadTauReader->setBranchAddresses(inputTree);
    genJetReader = new GenJetReader(Form("n%s", branchName_genJets.data()), branchName_genJets);
    genJetReader->setBranchAddresses(inputTree);
    lheInfoReader = new LHEInfoReader();
    lheInfoReader->setBranchAddresses(inputTree);
  }

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;

//--- declare histograms
  struct preselHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    HadTauHistManager* leadHadTau_;
    HadTauHistManager* subleadHadTau_;
    HadTauHistManager* thirdHadTau_;
    JetHistManager* jets_;
    JetHistManager* BJets_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    EvtHistManager_0l_3tau* evt_;
  };
  std::map<int, preselHistManagerType*> preselHistManagers;
  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    MuonHistManager* muons_;
    HadTauHistManager* hadTaus_;
    std::map<std::string, HadTauHistManager*> hadTaus_in_categories_;
    HadTauHistManager* leadHadTau_;
    std::map<std::string, HadTauHistManager*> leadHadTau_in_categories_;
    HadTauHistManager* subleadHadTau_;
    std::map<std::string, HadTauHistManager*> subleadHadTau_in_categories_;
    HadTauHistManager* thirdHadTau_;
    std::map<std::string, HadTauHistManager*> thirdHadTau_in_categories_;
    JetHistManager* jets_;
    JetHistManager* leadJet_;
    JetHistManager* subleadJet_;
    JetHistManager* BJets_loose_;
    JetHistManager* leadBJet_loose_;
    JetHistManager* subleadBJet_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    EvtHistManager_0l_3tau* evt_;
    std::map<std::string, EvtHistManager_0l_3tau*> evt_in_decayModes_;
    std::map<std::string, EvtHistManager_0l_3tau*> evt_in_categories_;
    WeightHistManager* weights_;
  };
  std::map<int, selHistManagerType*> selHistManagers;
  for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
	hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

    std::string process_and_genMatch = process_string;
    if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

    int idxHadTau = hadTauGenMatch_definition->idx_;
    
    preselHistManagerType* preselHistManager = new preselHistManagerType();
    preselHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/electrons", histogramDir.data()), central_or_shift));
    preselHistManager->electrons_->bookHistograms(fs);
    preselHistManager->muons_ =  new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/muons", histogramDir.data()), central_or_shift));
    preselHistManager->muons_->bookHistograms(fs);
    preselHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/hadTaus", histogramDir.data()), central_or_shift));
    preselHistManager->hadTaus_->bookHistograms(fs);
    preselHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/leadHadTau", histogramDir.data()), central_or_shift));
    preselHistManager->leadHadTau_->bookHistograms(fs);
    preselHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/subleadHadTau", histogramDir.data()), central_or_shift));
    preselHistManager->subleadHadTau_->bookHistograms(fs);
    preselHistManager->thirdHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/thirdHadTau", histogramDir.data()), central_or_shift));
    preselHistManager->thirdHadTau_->bookHistograms(fs);
    preselHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/jets", histogramDir.data()), central_or_shift));
    preselHistManager->jets_->bookHistograms(fs);
    preselHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/BJets_loose", histogramDir.data()), central_or_shift));
    preselHistManager->BJets_loose_->bookHistograms(fs);
    preselHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/BJets_medium", histogramDir.data()), central_or_shift));
    preselHistManager->BJets_medium_->bookHistograms(fs);
    preselHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/met", histogramDir.data()), central_or_shift));
    preselHistManager->met_->bookHistograms(fs);
    preselHistManager->evt_ = new EvtHistManager_0l_3tau(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/presel/evt", histogramDir.data()), central_or_shift));
    preselHistManager->evt_->bookHistograms(fs);
    preselHistManagers[idxHadTau] = preselHistManager;

    selHistManagerType* selHistManager = new selHistManagerType();
    selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/electrons", histogramDir.data()), central_or_shift));
    selHistManager->electrons_->bookHistograms(fs);
    selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/muons", histogramDir.data()), central_or_shift));
    selHistManager->muons_->bookHistograms(fs);
    selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/hadTaus", histogramDir.data()), central_or_shift));
    selHistManager->hadTaus_->bookHistograms(fs);
    selHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/leadHadTau", histogramDir.data()), central_or_shift));
    selHistManager->leadHadTau_->bookHistograms(fs);
    selHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/subleadHadTau", histogramDir.data()), central_or_shift));
    selHistManager->subleadHadTau_->bookHistograms(fs);
    selHistManager->thirdHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/thirdHadTau", histogramDir.data()), central_or_shift));
    selHistManager->thirdHadTau_->bookHistograms(fs);
    vstring categories_tau = {
      "0l_3tau_bloose", "0l_3tau_btight"
    };
    for ( vstring::const_iterator category = categories_tau.begin();
	  category != categories_tau.end(); ++category ) {
      TString histogramDir_category = histogramDir.data();
      histogramDir_category.ReplaceAll("0l_3tau", category->data());
      selHistManager->hadTaus_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/hadTaus", histogramDir_category.Data()), central_or_shift));
      selHistManager->hadTaus_in_categories_[*category]->bookHistograms(fs);
      selHistManager->leadHadTau_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/leadHadTau", histogramDir_category.Data()), central_or_shift));
      selHistManager->leadHadTau_in_categories_[*category]->bookHistograms(fs);
      selHistManager->subleadHadTau_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/subleadHadTau", histogramDir_category.Data()), central_or_shift));
      selHistManager->subleadHadTau_in_categories_[*category]->bookHistograms(fs);
      selHistManager->thirdHadTau_in_categories_[*category] = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/thirdHadTau", histogramDir_category.Data()), central_or_shift));
      selHistManager->thirdHadTau_in_categories_[*category]->bookHistograms(fs);
    }
    selHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/jets", histogramDir.data()), central_or_shift));
    selHistManager->jets_->bookHistograms(fs);
    selHistManager->leadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/leadJet", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadJet_->bookHistograms(fs);
    selHistManager->subleadJet_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/subleadJet", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadJet_->bookHistograms(fs);
    selHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/BJets_loose", histogramDir.data()), central_or_shift));
    selHistManager->BJets_loose_->bookHistograms(fs);
    selHistManager->leadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/leadBJet_loose", histogramDir.data()), central_or_shift, 0));
    selHistManager->leadBJet_loose_->bookHistograms(fs);
    selHistManager->subleadBJet_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/subleadBJet_loose", histogramDir.data()), central_or_shift, 1));
    selHistManager->subleadBJet_loose_->bookHistograms(fs);
    selHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/BJets_medium", histogramDir.data()), central_or_shift));
    selHistManager->BJets_medium_->bookHistograms(fs);
    selHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/met", histogramDir.data()), central_or_shift));
    selHistManager->met_->bookHistograms(fs);
    selHistManager->evt_ = new EvtHistManager_0l_3tau(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/evt", histogramDir.data()), central_or_shift));
    selHistManager->evt_->bookHistograms(fs);      
    vstring decayModes_evt;
    decayModes_evt.reserve(decayMode_idString.size());
    boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes_evt));
    if ( isSignal ) {
      for ( vstring::const_iterator decayMode = decayModes_evt.begin();
	    decayMode != decayModes_evt.end(); ++decayMode) {

	std::string decayMode_and_genMatch = (*decayMode);
	if ( apply_hadTauGenMatching ) decayMode_and_genMatch += hadTauGenMatch_definition->name_;

	selHistManager->evt_in_decayModes_[*decayMode] = new EvtHistManager_0l_3tau(makeHistManager_cfg(decayMode_and_genMatch,
          Form("%s/sel/evt", histogramDir.data()), central_or_shift));
	selHistManager->evt_in_decayModes_[*decayMode]->bookHistograms(fs);
      }
    }
    vstring categories_evt = { 
      "0l_3tau_bloose", "0l_3tau_btight"
    };
    for ( vstring::const_iterator category = categories_evt.begin();
	  category != categories_evt.end(); ++category ) {
      TString histogramDir_category = histogramDir.data();
      histogramDir_category.ReplaceAll("0l_3tau", category->data());
      selHistManager->evt_in_categories_[*category] = new EvtHistManager_0l_3tau(makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evt", histogramDir_category.Data()), central_or_shift));
      selHistManager->evt_in_categories_[*category]->bookHistograms(fs);
    }      
    selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch, 
      Form("%s/sel/weights", histogramDir.data()), central_or_shift));
    selHistManager->weights_->bookHistograms(fs, 
      { "genWeight", "pileupWeight", "data_to_MC_correction", "triggerWeight", "leptonEff", "hadTauEff", "fakeRate" });
    selHistManagers[idxHadTau] = selHistManager;
  }

  GenEvtHistManager* genEvtHistManager_beforeCuts = 0;
  GenEvtHistManager* genEvtHistManager_afterCuts = 0;
  LHEInfoHistManager* lheInfoHistManager = 0;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("%s/unbiased/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    genEvtHistManager_afterCuts = new GenEvtHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/genEvt", histogramDir.data()), central_or_shift));
    genEvtHistManager_afterCuts->bookHistograms(fs);
     lheInfoHistManager = new LHEInfoHistManager(makeHistManager_cfg(process_string, 
      Form("%s/sel/lheInfo", histogramDir.data()), central_or_shift));
    lheInfoHistManager->bookHistograms(fs);
  }

  NtupleFillerBDT<float, int> * bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type   int_type;
  if(selectBDT)
  {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), central_or_shift)
    );
    bdt_filler -> register_variable<float_type>(
      "mindr_tau1_jet", "mindr_tau2_jet", "mindr_tau3_jet", 
      "avg_dr_jet", "ptmiss", "htmiss", "tau1_mva", "tau2_mva", "tau3_mva", "tau1_pt", "tau2_pt", "tau3_pt",
      "tau1_eta", "tau2_eta", "tau3_eta", "dr_tau12", "dr_tau13", "dr_tau23", "mT_tau1", "mT_tau2", "mT_tau3", "mTauTauVis1", "mTauTauVis2",
      "lumiScale", "genWeight", "evtWeight"
    );
    bdt_filler -> register_variable<int_type>(
      "nJet", "nBJetLoose", "nBJetMedium"
    );
    bdt_filler -> bookTree(fs);
  }
  
  int numEntries = inputTree->GetEntries();
  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  CutFlowTableHistManager_0l_3tau* cutFlowHistManager = new CutFlowTableHistManager_0l_3tau(makeHistManager_cfg(process_string, 
    Form("%s/sel/cutFlow", histogramDir.data()), central_or_shift));
  cutFlowHistManager->bookHistograms(fs);
  for ( int idxEntry = 0; idxEntry < numEntries && (maxEvents == -1 || idxEntry < maxEvents); ++idxEntry ) {
    if ( idxEntry > 0 && (idxEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << idxEntry << " (" << selectedEntries << " Entries selected)" << std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    inputTree->GetEntry(idxEntry);

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(run, lumi, event) ) continue;
    cutFlowTable.update("run:ls:event selection");
    cutFlowHistManager->fillHistograms("run:ls:event selection", lumiScale);

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry " << idxEntry << ":"
		<< " run = " << run << ", lumi = " << lumi << ", event = " << event << std::endl;
      if ( inputTree->GetFile() ) std::cout << "input File = " << inputTree->GetFile()->GetName() << std::endl;
    }

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
    	    genLepton != genLeptons.end(); ++genLepton ) {
	int abs_pdgId = std::abs(genLepton->pdgId());
	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }

    if ( isMC ) {
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
    }
    
    bool isTriggered_2tau = hltPaths_isTriggered(triggers_2tau) || (isMC && !apply_trigger_bits);

    bool selTrigger_2tau = use_triggers_2tau && isTriggered_2tau;
    if ( !selTrigger_2tau ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS trigger selection." << std::endl; 
	std::cout << " (selTrigger_2tau = " << selTrigger_2tau << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, fakeableMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_lead = fakeableHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus_sublead = hadTauCleaner(fakeableHadTauSelector_sublead(preselHadTaus), fakeableHadTaus_lead);
    std::vector<const RecoHadTau*> fakeableHadTaus_third = hadTauCleaner(fakeableHadTauSelector_third(preselHadTaus), fakeableHadTaus_lead, fakeableHadTaus_sublead);
    assert(fakeableHadTaus_lead.size() <= 1 && fakeableHadTaus_sublead.size() <= 1 && fakeableHadTaus_third.size() <= 1);
    std::vector<const RecoHadTau*> fakeableHadTaus;
    if ( fakeableHadTaus_lead.size()    >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_lead[0]);
    if ( fakeableHadTaus_sublead.size() >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_sublead[0]);
    if ( fakeableHadTaus_third.size()   >= 1 ) fakeableHadTaus.push_back(fakeableHadTaus_third[0]);
    std::vector<const RecoHadTau*> tightHadTaus_lead = tightHadTauSelector_lead(preselHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus_sublead = hadTauCleaner(tightHadTauSelector_sublead(preselHadTaus), tightHadTaus_lead);
    std::vector<const RecoHadTau*> tightHadTaus_third = hadTauCleaner(tightHadTauSelector_third(preselHadTaus), tightHadTaus_lead, tightHadTaus_sublead);
    assert(tightHadTaus_lead.size() <= 1 && tightHadTaus_sublead.size() <= 1 && tightHadTaus_third.size() <= 1);
    std::vector<const RecoHadTau*> tightHadTaus;
    if ( tightHadTaus_lead.size()    >= 1 ) tightHadTaus.push_back(tightHadTaus_lead[0]);
    if ( tightHadTaus_sublead.size() >= 1 ) tightHadTaus.push_back(tightHadTaus_sublead[0]);
    if ( tightHadTaus_third.size()   >= 1 ) tightHadTaus.push_back(tightHadTaus_third[0]);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);
    selHadTaus = pickFirstNobjects(selHadTaus, 3);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, selHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);    

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if ( isMC && !fillGenEvtHistograms ) {
      genLeptons = genLeptonReader->read();
      for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
    	    genLepton != genLeptons.end(); ++genLepton ) {
    	int abs_pdgId = std::abs(genLepton->pdgId());
    	if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
    	else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
      }
      genHadTaus = genHadTauReader->read();
      genJets = genJetReader->read();
    }

//--- match reconstructed to generator level particles
    if ( isMC ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(preselHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());
    std::sort(preselLeptons.begin(), preselLeptons.end(), isHigherConePt);

    // require presence of at least two hadronic taus passing loose preselection criteria
    // (do not veto events with more than two loosely selected hadronic tau candidates,
    //  as sample of hadronic tau candidates passing loose preselection criteria contains significant contamination from jets)
    std::sort(preselHadTaus.begin(), preselHadTaus.end(), isHigherPt);
    if ( !(preselHadTaus.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 presel taus");
    cutFlowHistManager->fillHistograms(">= 3 presel taus", lumiScale);
    const RecoHadTau* preselHadTau_lead = preselHadTaus[0];
    const RecoHadTau* preselHadTau_sublead = preselHadTaus[1];
    const RecoHadTau* preselHadTau_third = preselHadTaus[2];
    const hadTauGenMatchEntry& preselHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, preselHadTau_lead, preselHadTau_sublead, preselHadTau_third);
    int idxPreselHadTau_genMatch = preselHadTau_genMatch.idx_;
    assert(idxPreselHadTau_genMatch != kGen_HadTauUndefined3);

    int preselHadTau_chargeSum = preselHadTau_lead->charge() + preselHadTau_sublead->charge() + preselHadTau_third->charge();
    const RecoHadTau* preselHadTau1_SS = 0;
    const RecoHadTau* preselHadTau2_SS = 0;
    const RecoHadTau* preselHadTau_OS  = 0;
    for ( int idxPreselHadTau = 0; idxPreselHadTau < 3; ++idxPreselHadTau ) {
      const RecoHadTau* preselHadTau = preselHadTaus[idxPreselHadTau];
      if ( preselHadTau->charge()*preselHadTau_chargeSum > 0 ) {
	if      ( !preselHadTau1_SS ) preselHadTau1_SS = preselHadTau;
	else if ( !preselHadTau2_SS ) preselHadTau2_SS = preselHadTau;
      } else {
	if ( !preselHadTau_OS ) preselHadTau_OS = preselHadTau;
      }
    }
    double mTauTauVis1_presel = ( preselHadTau1_SS && preselHadTau_OS ) ? (preselHadTau1_SS->p4() + preselHadTau_OS->p4()).mass() : -1.;
    double mTauTauVis2_presel = ( preselHadTau2_SS && preselHadTau_OS ) ? (preselHadTau2_SS->p4() + preselHadTau_OS->p4()).mass() : -1.;

    // apply requirement on jets (incl. b-tagged jets) on preselection level
    if ( !(selJets.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 jets");
    cutFlowHistManager->fillHistograms(">= 2 jets", lumiScale);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (1)");
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (1)", lumiScale);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- fill histograms with events passing preselection
    preselHistManagerType* preselHistManager = preselHistManagers[idxPreselHadTau_genMatch];
    assert(preselHistManager != 0);
    preselHistManager->electrons_->fillHistograms(preselElectrons, 1.);
    preselHistManager->muons_->fillHistograms(preselMuons, 1.);
    preselHistManager->hadTaus_->fillHistograms(preselHadTaus, 1.);
    preselHistManager->leadHadTau_->fillHistograms({ preselHadTau_lead }, 1.);
    preselHistManager->subleadHadTau_->fillHistograms({ preselHadTau_sublead }, 1.);
    preselHistManager->thirdHadTau_->fillHistograms({ preselHadTau_third }, 1.);
    preselHistManager->jets_->fillHistograms(selJets, 1.);
    preselHistManager->BJets_loose_->fillHistograms(selBJets_loose, 1.);
    preselHistManager->BJets_medium_->fillHistograms(selBJets_medium, 1.);
    preselHistManager->met_->fillHistograms(met, mht_p4, met_LD, 1.);
    preselHistManager->evt_->fillHistograms(preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mTauTauVis1_presel, mTauTauVis2_presel, 1.);

//--- apply final event selection 
    // require presence of at least three hadronic taus passing tight selection criteria of final event selection
    if ( !(selHadTaus.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 sel taus", lumiScale);
    cutFlowHistManager->fillHistograms(">= 3 sel taus", lumiScale);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const RecoHadTau* selHadTau_third = selHadTaus[2];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead, selHadTau_third);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined3);
    
    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= sgn(genWeight);
      evtWeight *= pileupWeight;
      if ( lheScale_option != kLHE_scale_central ) {	
	if      ( lheScale_option == kLHE_scale_xDown ) evtWeight *= lheInfoReader->getWeight_scale_xDown();
	else if ( lheScale_option == kLHE_scale_xUp   ) evtWeight *= lheInfoReader->getWeight_scale_xUp();
	else if ( lheScale_option == kLHE_scale_yDown ) evtWeight *= lheInfoReader->getWeight_scale_yDown();
	else if ( lheScale_option == kLHE_scale_yUp   ) evtWeight *= lheInfoReader->getWeight_scale_yUp();
      }
      double btagWeight = 1.;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	btagWeight *= (*jet)->BtagWeight();
      }
      evtWeight *= btagWeight;
      if ( isDEBUG ) {
	std::cout << "lumiScale = " << lumiScale << std::endl;
	if ( apply_genWeight ) std::cout << "genWeight = " << sgn(genWeight) << std::endl;
	std::cout << "pileupWeight = " << pileupWeight << std::endl;
	std::cout << "btagWeight = " << btagWeight << std::endl;
      }
    }

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    double weight_leptonEff = 1.;
    double weight_hadTauEff = 1.;
    if ( isMC ) {
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
      int selHadTau_third_genPdgId = getHadTau_genPdgId(selHadTau_third);

      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(),
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(),
	selHadTau_third_genPdgId, selHadTau_third->pt(), selHadTau_third->eta());

      dataToMCcorrectionInterface_0l_3tau_trigger->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->decayMode(),
	selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->decayMode(),
	selHadTau_third_genPdgId, selHadTau_third->pt(), selHadTau_third->eta(), selHadTau_third->decayMode());
      dataToMCcorrectionInterface_0l_3tau_trigger->setTriggerBits(isTriggered_2tau);

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
	triggerWeight = dataToMCcorrectionInterface_0l_3tau_trigger->getWeight_triggerEff();
	if ( isDEBUG ) {
	  std::cout << "triggerWeight = " << triggerWeight << std::endl;
	}
	evtWeight *= triggerWeight;
      }

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface_0l_3tau_trigger->getSF_triggerEff();
      if ( isDEBUG ) {
	std::cout << "sf_triggerEff = " << sf_triggerEff << std::endl;
      }
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

//--- apply data/MC corrections for hadronic tau identification efficiency 
//    and for e->tau and mu->tau misidentification rates     
      double sf_hadTauEff = 1.;
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      sf_hadTauEff *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      if ( isDEBUG ) { 
	std::cout << "sf_hadTauEff = " << sf_hadTauEff << std::endl;
      }
      weight_hadTauEff *= sf_hadTauEff;
      weight_data_to_MC_correction *= sf_hadTauEff;

      if ( isDEBUG ) {
	std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }
      evtWeight *= weight_data_to_MC_correction;
    }       
    
    // veto events that contain leptons passing tight selection criteria, to avoid overlap with other channels
    std::vector<const RecoLepton*> tightLeptons;    
    tightLeptons.reserve(tightElectrons.size() + tightMuons.size());
    tightLeptons.insert(tightLeptons.end(), tightElectrons.begin(), tightElectrons.end());
    tightLeptons.insert(tightLeptons.end(), tightMuons.begin(), tightMuons.end());
    std::sort(tightLeptons.begin(), tightLeptons.end(), isHigherPt);
    if ( !(tightLeptons.size() <= 0) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS tightLeptons selection." << std::endl;
	printLeptonCollection("tightLeptons", tightLeptons);
      }
      continue;
    }
    cutFlowTable.update("no tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("no tight leptons", evtWeight);

    double weight_fakeRate = 1.;
    if ( applyFakeRateWeights == kFR_3tau) {
      double prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTaus);
      double prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTaus);
      double prob_fake_hadTau_third = jetToTauFakeRateInterface->getWeight_third(selHadTau_third->pt(), selHadTau_third->absEta());
      bool passesTight_hadTau_third = isMatched(*selHadTau_third, tightHadTaus);
      weight_fakeRate = getWeight_3L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead, 
	prob_fake_hadTau_sublead, passesTight_hadTau_sublead, 
	prob_fake_hadTau_third, passesTight_hadTau_third);
      if ( isDEBUG ) {
	std::cout << "weight_fakeRate = " << weight_fakeRate << std::endl;
      }
      evtWeight *= weight_fakeRate;
    }    
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }

    int selHadTau_chargeSum = selHadTau_lead->charge() + selHadTau_sublead->charge() + selHadTau_third->charge();
    const RecoHadTau* selHadTau1_SS = 0;
    const RecoHadTau* selHadTau2_SS = 0;
    const RecoHadTau* selHadTau_OS  = 0;
    for ( int idxSelHadTau = 0; idxSelHadTau < 3; ++idxSelHadTau ) {
      const RecoHadTau* selHadTau = selHadTaus[idxSelHadTau];
      if ( selHadTau->charge()*selHadTau_chargeSum > 0 ) {
	if      ( !selHadTau1_SS ) selHadTau1_SS = selHadTau;
	else if ( !selHadTau2_SS ) selHadTau2_SS = selHadTau;
      } else {
	if ( !selHadTau_OS ) selHadTau_OS = selHadTau;
      }
    }
    double mTauTauVis1 = ( selHadTau1_SS && selHadTau_OS ) ? (selHadTau1_SS->p4() + selHadTau_OS->p4()).mass() : -1.;
    double mTauTauVis2 = ( selHadTau2_SS && selHadTau_OS ) ? (selHadTau2_SS->p4() + selHadTau_OS->p4()).mass() : -1.;

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 3) ) continue;
    cutFlowTable.update(">= 3 jets", evtWeight);
    cutFlowHistManager->fillHistograms(">= 3 jets", evtWeight);
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) continue;
    cutFlowTable.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
    cutFlowHistManager->fillHistograms(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);
 
    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptons.begin();
	  lepton1 != preselLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != preselLeptons.end(); ++lepton2 ) {
	double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	if ( mass < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    if ( !(selHadTau_lead->pt() > 40. && selHadTau_lead->absEta() < 2.1) ) continue;
    cutFlowTable.update("lead hadTau pT > 40 GeV && abs(eta) < 2.1", evtWeight);
    cutFlowHistManager->fillHistograms("lead hadTau pT > 40 GeV && abs(eta) < 2.1", evtWeight);

    if ( !(selHadTau_sublead->pt() > 40. && selHadTau_sublead->absEta() < 2.1) ) continue;
    cutFlowTable.update("sublead hadTau pT > 40 GeV && abs(eta) < 2.1", evtWeight);
    cutFlowHistManager->fillHistograms("sublead hadTau pT > 40 GeV && abs(eta) < 2.1", evtWeight);

    if ( !(selHadTau_third->pt() > 20. && selHadTau_third->absEta() < 2.1) ) continue;
    cutFlowTable.update("third hadTau pT > 20 GeV && abs(eta) < 2.1", evtWeight);
    cutFlowHistManager->fillHistograms("third hadTau pT > 20 GeV && abs(eta) < 2.1", evtWeight);

    bool isCharge_OS = std::abs(selHadTau_lead->charge() + selHadTau_sublead->charge() + selHadTau_third->charge()) <= 1;
    bool isCharge_SS = !isCharge_OS;
    if ( (hadTauChargeSelection == kOS && isCharge_SS) || (hadTauChargeSelection == kSS && isCharge_OS) ) {
      if ( run_lumi_eventSelector ) {
	std::cout << "event FAILS lepton+tau charge selection." << std::endl;	
	std::cout << " (leading selHadTau charge = " << selHadTau_lead->charge() 
		  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() 
		  << ", third selHadTau charge = " << selHadTau_third->charge() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("tau charge sum", evtWeight);
    cutFlowHistManager->fillHistograms("tau charge sum", evtWeight);
    
    if ( hadTauSelection == kFakeable ) {
      if ( tightHadTaus_lead.size() >= 1 && tightHadTaus_sublead.size() >= 1 && tightHadTaus_third.size() >= 1 ) continue; // CV: avoid overlap with signal region
      cutFlowTable.update("signal region veto", evtWeight);
      cutFlowHistManager->fillHistograms("signal region veto", evtWeight);
    }

//--- fill histograms with events passing final selection 
    selHistManagerType* selHistManager = selHistManagers[idxSelHadTau_genMatch];
    assert(selHistManager != 0);
    selHistManager->electrons_->fillHistograms(preselElectrons, evtWeight);
    selHistManager->muons_->fillHistograms(preselMuons, evtWeight);
    selHistManager->hadTaus_->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
    selHistManager->leadHadTau_->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->thirdHadTau_->fillHistograms({ selHadTau_third }, evtWeight);
    selHistManager->jets_->fillHistograms(selJets, evtWeight);
    selHistManager->leadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->subleadJet_->fillHistograms(selJets, evtWeight);
    selHistManager->BJets_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->leadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->subleadBJet_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->BJets_medium_->fillHistograms(selBJets_medium, evtWeight);
    selHistManager->met_->fillHistograms(met, mht_p4, met_LD, evtWeight);
    selHistManager->evt_->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mTauTauVis1, mTauTauVis2, evtWeight);
    if ( isSignal ) {
      for ( const auto & kv: decayMode_idString ) {
        if ( std::fabs(genHiggsDecayMode - kv.second) < EPS ) {
          selHistManager->evt_in_decayModes_[kv.first]->fillHistograms(
            preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
            selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
	    mTauTauVis1, mTauTauVis2, evtWeight);
          break;
        }
      }
    }
    selHistManager->weights_->fillHistograms("genWeight", genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", pileupWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("leptonEff", weight_leptonEff);
    selHistManager->weights_->fillHistograms("hadTauEff", weight_hadTauEff);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);

    std::string category;
    if   ( selBJets_medium.size() >= 1 ) category = "0l_3tau_btight"; 
    else                                 category = "0l_3tau_bloose";  
    selHistManager->hadTaus_in_categories_[category]->fillHistograms({ selHadTau_lead, selHadTau_sublead }, evtWeight);
    selHistManager->leadHadTau_in_categories_[category]->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_in_categories_[category]->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->thirdHadTau_in_categories_[category]->fillHistograms({ selHadTau_third }, evtWeight);
    selHistManager->evt_in_categories_[category]->fillHistograms(
      preselElectrons.size(), preselMuons.size(), selHadTaus.size(), 
      selJets.size(), selBJets_loose.size(), selBJets_medium.size(),
      mTauTauVis1, mTauTauVis2, evtWeight);

    if ( isMC ) {
      genEvtHistManager_afterCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genJets);
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeight);
    }

    if ( selEventsFile ) {
      (*selEventsFile) << run << ":" << lumi << ":" << event << std::endl;
    }

    if(bdt_filler)
    {
      bdt_filler -> operator()({ run, lumi, event })
          ("mindr_tau1_jet", TMath::Min(10., comp_mindr_hadTau1_jet(*selHadTau_lead, selJets)))
          ("mindr_tau2_jet", TMath::Min(10., comp_mindr_hadTau2_jet(*selHadTau_sublead, selJets)))
	  ("mindr_tau3_jet", TMath::Min(10., comp_mindr_hadTau3_jet(*selHadTau_third, selJets)))
          ("avg_dr_jet",     comp_avg_dr_jet(selJets))
          ("ptmiss",         met.pt())
          ("htmiss",         mht_p4.pt())
          ("tau1_mva",       selHadTau_lead -> raw_mva_dR03())
          ("tau2_mva",       selHadTau_sublead -> raw_mva_dR03())
          ("tau3_mva",       selHadTau_third -> raw_mva_dR03())
          ("tau1_pt",        selHadTau_lead -> pt())
          ("tau2_pt",        selHadTau_sublead -> pt())
          ("tau3_pt",        selHadTau_third -> pt())
          ("tau1_eta",       selHadTau_lead -> eta())
          ("tau2_eta",       selHadTau_sublead -> eta())
          ("tau3_eta",       selHadTau_third -> eta())
          ("dr_taus12",      deltaR(selHadTau_lead -> p4(), selHadTau_sublead -> p4()))
          ("dr_taus13",      deltaR(selHadTau_lead -> p4(), selHadTau_third -> p4()))
          ("dr_taus23",      deltaR(selHadTau_sublead -> p4(), selHadTau_third -> p4()))
   	  ("mT_tau1",        comp_MT_met_hadTau1(*selHadTau_lead, met.pt(), met.phi()))
          ("mT_tau2",        comp_MT_met_hadTau2(*selHadTau_sublead, met.pt(), met.phi()))
          ("mT_tau3",        comp_MT_met_hadTau3(*selHadTau_third, met.pt(), met.phi()))
          ("mTauTauVis1",    mTauTauVis1)
          ("mTauTauVis2",    mTauTauVis2)
          ("lumiScale",      lumiScale)
          ("genWeight",      genWeight)
          ("evtWeight",      evtWeight)
          ("nJet",           selJets.size())
          ("nBJetLoose",     selBJets_loose.size())
          ("nBJetMedium",    selBJets_medium.size())
        .fill()
      ;
    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "num. Entries = " << numEntries << std::endl;
  std::cout << " analyzed = " << analyzedEntries << std::endl;
  std::cout << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")" << std::endl;
  std::cout << std::endl;

  std::cout << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  std::cout << "sel. Entries by gen. matching:" << std::endl;
  for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
	hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

    std::string process_and_genMatch = process_string;
    if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

    int idxHadTau = hadTauGenMatch_definition->idx_;

    const TH1* histogram_EventCounter = selHistManagers[idxHadTau]->evt_->getHistogram_EventCounter();
    std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries() << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
  }
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete jetToTauFakeRateInterface;
  
  delete run_lumi_eventSelector;

  delete selEventsFile;
  delete bdt_filler;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete cutFlowHistManager;

  hltPaths_delete(triggers_2tau);

  clock.Show("analyze_0l_3tau");

  return EXIT_SUCCESS;
}

