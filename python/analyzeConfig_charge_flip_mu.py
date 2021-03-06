import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.analyzeConfig_charge_flip import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_charge_flip_mu(analyzeConfig_charge_flip):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, configDir, outputDir, executable_analyze, samples, lepton_selections, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
               histograms_to_fit = [], select_rle_output = False, executable_prep_dcard="prepareDatacard"):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "charge_flip", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      histograms_to_fit)

    self.samples = samples
    
    self.prep_dcard_processesToCopy = ["data_obs", "DY", "DY_fake", "WJets", "TTbar", "Singletop", "Diboson"]
    self.prep_dcard_signals = [ "DY" ]
    
    self.lepton_selections = lepton_selections
    
    #self.hadTau_selection = hadTau_selection

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_selection in self.lepton_selections:
          key_dir = getKey(sample_name, lepton_selection)  
          for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_RLES  ]:
            initDict(self.dirs, [ key_dir, dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
              self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                "_".join([ lepton_selection ]), process_name)
            else:
              self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                "_".join([ lepton_selection ]), process_name)
    ##print "self.dirs = ", self.dirs

    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_charge_flip_cfg.py")
    self.cfgFile_prep_dcard_original = os.path.join(self.workingDir, "prepareDatacards_cfg.py")
    #self.histogramDir_prep_dcard = "charge_flip_SS_Tight"
    self.select_rle_output = select_rle_output

  def createCfg_prep_dcard(self, jobOptions):
    """Fills the template of python configuration file for datacard preparation
       Args:
         histogramToFit: name of the histogram used for signal extraction
    """
    category_output = self.channel
    if jobOptions['label']:
        category_output += "_%s" % jobOptions['label']
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])
    lines.append("process.prepareDatacards.processesToCopy = cms.vstring(%s)" % self.prep_dcard_processesToCopy)
    lines.append("process.prepareDatacards.signals = cms.vstring(%s)" % self.prep_dcard_signals)
    lines.append("process.prepareDatacards.makeSubDir = cms.bool(True)")
    lines.append("process.prepareDatacards.categories = cms.VPSet(")
    for charge in ["OS", "SS"]:
      for ptEtaBin in ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML","BE_MM",  "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"]:
        lines.append("    cms.PSet(")
        lines.append("        input = cms.string('%s/%s')," % (charge, ptEtaBin))
        lines.append("        output = cms.string('ttH_%s_%s_%s')" % (self.channel, charge, ptEtaBin))
        lines.append("    ),")
    lines.append(")")
    lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
    lines.append("""process.prepareDatacards.sysShifts = cms.vstring(
     "CMS_ttHl_muonERUp",
     "CMS_ttHl_muonERDown",
     "CMS_ttHl_muonESBarrel1Up",
     "CMS_ttHl_muonESBarrel1Down",
     "CMS_ttHl_muonESBarrel2Up",
     "CMS_ttHl_muonESBarrel2Down",
     "CMS_ttHl_muonESEndcap1Down",
     "CMS_ttHl_muonESEndcap1Up",
     "CMS_ttHl_muonESEndcap2Down",
     "CMS_ttHl_muonESEndcap2Up"
    )""")
    create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)



  def create(self):
    analyzeConfig_charge_flip.create(self)

