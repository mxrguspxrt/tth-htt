import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_mcClosure_cfg import process

process.makePlots_mcClosure.processesBackground = cms.vstring(
    ##"TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "fakes_data"
)
process.makePlots_mcClosure.processSignal = cms.string("signal")

process.makePlots_mcClosure.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("0l_3tau_OS_Fakeable_mcClosure_wFakeRateWeights"),
        label = cms.string("0l_3tau")
    )
)

process.makePlots_mcClosure.distributions.extend([
    cms.PSet(
        histogramName = cms.string('sel/leadHadTau/$PROCESS/pt'),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string('leading #tau_{h} p_{T} [GeV]'),
        yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/leadHadTau/$PROCESS/eta'),
        xAxisTitle = cms.string('leading #tau_{h} #eta'),
        yAxisTitle = cms.string('dN/d#eta')
    ),
    cms.PSet(
        histogramName = cms.string('sel/subleadHadTau/$PROCESS/pt'),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string('subleading #tau_{h} p_{T} [GeV]'),
        yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/subleadHadTau/$PROCESS/eta'),
        xAxisTitle = cms.string('subleading #tau_{h} #eta'),
        yAxisTitle = cms.string('dN/d#eta')
    ),
    cms.PSet(
        histogramName = cms.string('sel/thirdHadTau/$PROCESS/pt'),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string('third #tau_{h} p_{T} [GeV]'),
        yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/thirdHadTau/$PROCESS/eta'),
        xAxisTitle = cms.string('third #tau_{h} #eta'),
        yAxisTitle = cms.string('dN/d#eta')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mTauTauVis'),
        xAxisTitle = cms.string('m_{#tau#tau}^{vis} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#tau#tau}^{vis} [1/GeV]')
    )
])

