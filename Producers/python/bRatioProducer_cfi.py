import FWCore.ParameterSet.Config as cms 


GenJetBCEnergyRatio = cms.EDAnalyzer('GenJetBCEnergyRatio',
    genParticleTag = cms.InputTag("genParticles"),
    genJetTag = cms.InputTag("ak5GenJets"),
)

