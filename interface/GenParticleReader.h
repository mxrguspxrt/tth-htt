#ifndef tthAnalysis_HiggsToTauTau_GenParticleReader_h
#define tthAnalysis_HiggsToTauTau_GenParticleReader_h

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class GenParticleReader
{
 public:
  GenParticleReader(const std::string& branchName_num, const std::string& branchName_obj); 
  ~GenParticleReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenParticle branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of GenParticle objects
   * @return Collection of GenLepton objects (GenParticles with additional data-members for charge and pdgId)
   */
  std::vector<GenLepton> read() const;
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  const int max_nParticles_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_pdgId_;

  Int_t nParticles_;
  Float_t* particle_pt_;
  Float_t* particle_eta_;
  Float_t* particle_phi_;
  Float_t* particle_mass_;
  Int_t* particle_pdgId_;

  // CV: make sure that only one GenParticleReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenParticleReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenParticleReader_h

