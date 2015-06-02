#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src
eval `scramv1 runtime -sh`
cd -
source /afs/cern.ch/cms/caf/setup.sh
cp /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/ggH_a9_10K_Events_v1_ReqTauPlots_MAY_25_v1/ggHanalyzer_cfg_ggH_a9_10K_Events_v1_ReqTauPlots_MAY_25_v1.py .
cmsRun ggHanalyzer_cfg_ggH_a9_10K_Events_v1_ReqTauPlots_MAY_25_v1.py
rm ggHanalyzer_cfg_ggH_a9_10K_Events_v1_ReqTauPlots_MAY_25_v1.py 
exit 0
