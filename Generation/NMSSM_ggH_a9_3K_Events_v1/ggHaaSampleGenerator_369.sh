#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
cd /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src
eval `scramv1 runtime -sh`
cd -
source /afs/cern.ch/cms/caf/setup.sh 
mv /afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Generation/NMSSM_ggH_a9_3K_Events_v1/ggHaaSampleGenerator_369.* . 
cmsRun ggHaaSampleGenerator_369.py
cmsStage -f NMSSM_a9_ggH_369.root /store/user/ktos/NMSSM_ggH_a9_3K_Events_v1
rm ggHaaSampleGenerator_369.*  NMSSM_a9_ggH_369.root*
if [ -e RandomEngineState_369.log ]
    then
    rm RandomEngineState_369.log*
fi
if [ -e histProbFunction_369.root ]
    then
    rm histProbFunction_369.root*
fi

exit 0
