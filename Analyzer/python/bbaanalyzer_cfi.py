import FWCore.ParameterSet.Config as cms

#define a parameter set to be passed to all modules that utilize GenTauDecayID for signal taus
commonGenTauDecayIDPSet = cms.PSet(momPDGID = cms.vint32(36),
                                   chargedHadronPTMin = cms.double(0.0),
                                   neutralHadronPTMin = cms.double(0.0),
                                   chargedLeptonPTMin = cms.double(0.0),
                                   totalPTMin = cms.double(0.0))

BBAAnalyzer = cms.EDAnalyzer('BBAAnalyzer',
    outFileName = cms.string('BBAAnalyzer_Histo_a30_v1.root'),
    genParticleTag = cms.InputTag("genParticles"),
    genJetTag = cms.InputTag("a5kGenJets"),
    bRatioTag = cms.InputTag("bRatioCollection"),
    genTauDecayIDPSet = commonGenTauDecayIDPSet,
)
