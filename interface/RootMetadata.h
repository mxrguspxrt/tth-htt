#ifndef tthAnalysis_HiggsToTauTau_RootMetadata_h
#define tthAnalysis_HiggsToTauTau_RootMetadata_h

#include <string>
using namespace std;

class RootMetadata
{
  public:
    RootMetadata() = default;
    std::string toString();

    int numEntries;
    int selectedEntries;
    double selectedEntriesWeighted;

    bool save(std::string fileName);
};

#endif // tthAnalysis_HiggsToTauTau_RootMetadata_h
