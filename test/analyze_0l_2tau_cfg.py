import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    fileNames = cms.vstring('/afs/cern.ch/user/k/kaehatah/public/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_0l_2tau.root')
)

process.analyze_0l_2tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    histogramDir = cms.string('0l_2tau_OS_Tight'),

    era = cms.string('2015'),

    triggers_2tau = cms.vstring(""),
    use_triggers_2tau = cms.bool(True),   
        
    hadTauSelection = cms.string('Tight|dR03mvaTight'),
    hadTauChargeSelection = cms.string('OS'),
    apply_hadTauGenMatching = cms.bool(False),

    applyFakeRateWeights = cms.string("disabled"), # either "disabled", or "2tau"
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        ),
        sublead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        )
    ),

    triggerSF_2tau = cms.PSet(),

    use_HIP_mitigation_bTag = cms.bool(False),
    use_HIP_mitigation_mediumMuonId = cms.bool(False),
        
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(True),

    fillGenEvtHistograms = cms.bool(False),

    branchName_electrons = cms.string('selLeptons'),
    branchName_muons = cms.string('selLeptons'),
    branchName_hadTaus = cms.string('TauGood'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),

    branchName_genLeptons1 = cms.string('GenLep'),
    branchName_genLeptons2 = cms.string('GenLepFromTau'),
    branchName_genHadTaus = cms.string('GenHadTaus'),
    branchName_genJets = cms.string('GenJet'),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    selectBDT = cms.bool(False),
)

#--------------------------------------------------------------------------------
# CV: add data/MC corrections for efficiency of DoubleTau trigger
jsonFileName = os.path.expandvars("$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_tt.json")
jsonFile = open(jsonFileName)
import json
jsonData = json.load(jsonFile)
##print "jsonData:"
##print jsonData
for fit, parameters in jsonData.items():
    ##print "fit = %s:" % fit
    pset = cms.PSet()
    for parameterName, parameterValue in parameters.items():
        ##print " %s = %1.2f" % (parameterName, parameterValue)
        setattr(pset, parameterName, cms.double(parameterValue))
    setattr(process.analyze_0l_2tau.triggerSF_2tau, fit, pset)
#--------------------------------------------------------------------------------

##processDumpFile = open('analyze_0l_2tau.dump', 'w')
##print >> processDumpFile, process.dumpPython()
