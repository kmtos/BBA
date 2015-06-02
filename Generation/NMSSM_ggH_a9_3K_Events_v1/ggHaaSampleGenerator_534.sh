#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src
eval `scramv1 runtime -sh`
cd -
source /afs/cern.ch/cms/caf/setup.sh 
mv /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Generation/NMSSM_ggH_a9_3K_Events_v1/ggHaaSampleGenerator_534.* . 
cmsRun ggHaaSampleGenerator_534.py
cmsStage -f NMSSM_a9_ggH_534.root /store/user/ktos/NMSSM_ggH_a9_3K_Events_v1
rm ggHaaSampleGenerator_534.*  NMSSM_a9_ggH_534.root*
if [ -e RandomEngineState_534.log ]
    then
    rm RandomEngineState_534.log*
fi
if [ -e histProbFunction_534.root ]
    then
    rm histProbFunction_534.root*
fi

exit 0
