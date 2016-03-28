# tth-htt
code and python config files for ttH, H -> tautau analysis with matrix element techniques
### Setup

Clone this repository into `$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau`, i.e. `git clone git@github.com:HEP-KBFI/tth-htt.git $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau`.
Set up your CMSSW working environment, do `scram b -j8` in `$CMSSW_BASE/src`. Then proceed with
```bash
mkdir -p tth_cutflow && cd $_ # make a folder (of any name, e.g. "tth_cutflow") somewhere
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/RunCuts.py # create jobs and cfgs
./run_cuts.sh # run the jobs; wait
watch -n5 squeue -u `whoami` # check your SLURM queue real time
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/FormatResults.py # once ready, create the cutflow table
python2.7 $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/Diff.py # difference table
```
Now you should have two files in your `$PWD`: the cutflow table `cutflow.txt` and the difference table `diff.txt`. Above Python commands and `sbatch` jobs will overwrite the existing files, so make a copy of your `*.txt`s.

### Synchronization

If you want to produce the ntuples for the synchronization exercise, run
```bash
ntuples_ttHJetToTT $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/ttHJetToTT_M125_13TeV_ntuples_config.py
```
Check the input/output parameters in the configuration file first, though.
