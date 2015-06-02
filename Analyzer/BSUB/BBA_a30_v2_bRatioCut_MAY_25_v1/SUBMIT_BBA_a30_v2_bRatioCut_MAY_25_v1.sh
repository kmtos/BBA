#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src
eval `scramv1 runtime -sh`
cd -
source /afs/cern.ch/cms/caf/setup.sh
cp /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a30_v2_bRatioCut_MAY_25_v1/bbanalyzer_cfg_BBA_a30_v2_bRatioCut_MAY_25_v1.py .
cmsRun bbanalyzer_cfg_BBA_a30_v2_bRatioCut_MAY_25_v1.py
rm bbanalyzer_cfg_BBA_a30_v2_bRatioCut_MAY_25_v1.py 
exit 0
