#ifndef tthAnalysis_HiggsToTauTau_GenLepton_h
#define tthAnalysis_HiggsToTauTau_GenLepton_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle

class GenLepton
  : public GenParticle
{
 public:
  GenLepton() = default;
  GenLepton(Double_t pt,
            Double_t eta,
            Double_t phi,
            Double_t mass,
            Int_t pdgId);
  GenLepton(const math::PtEtaPhiMLorentzVector & p4,
            Int_t pdgId);

  /**
   * @brief Funtions to access data-members
   * @return Values of data-members
   */
  Int_t pdgId() const { return pdgId_; }
  Int_t charge() const { return charge_; }

 protected:
  Int_t pdgId_;  ///< PDG id of the lepton (signed)
  Int_t charge_; ///< charge of lepton (either +1 or -1, depending on pdgId)
};

std::ostream& operator<<(std::ostream& stream, const GenLepton& lepton);

#endif // tthAnalysis_HiggsToTauTau_GenLepton_h
