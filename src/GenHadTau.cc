#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau, GenParticle

GenHadTau::GenHadTau(Double_t pt,
		     Double_t eta,
		     Double_t phi,
		     Double_t mass,
		     Int_t charge)
  : GenParticle(pt, eta, phi, mass)
  , charge_(charge)
{}
