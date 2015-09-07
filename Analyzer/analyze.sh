#!/bin/bash

#parse arguments
if [ $# -ne 5 ]
    then
    echo "Usage: ./analyze.sh cfg_name script_name dir_name if_jet_output queue"
    exit 0
fi

cfg_name=$1
script_name=$2
dir_name=$3
if_jet=$4
queue=$5

mkdir -p BSUB/$dir_name
cd BSUB/$dir_name
path=$(pwd)
echo "path= $path"

echo "DIRNAME=${dir_name}"
echo "python file= ${cfg_name}_${dir_name}.py"
echo "ANALYZER=${cfg_name}_${dir_name}"
echo "Script name= ${script_name}_${dir_name}.sh"
if [ "$if_jet" == "yes" ]
  then
  echo "Jet Output enabled"
  sed -e "s%dirname%DIRNAME%g" ../../${cfg_name}.py > ../../${cfg_name}_${dir_name}.py
  sed -e "s%DIRNAME%${dir_name}%g" ../../${cfg_name}_${dir_name}.py > ${cfg_name}_${dir_name}.py
  rm ../../${cfg_name}_${dir_name}.py
fi
if [ "$if_jet" != "yes" ]
  then
  echo "Jet Output disabled"
  sed -e "s%DIRNAME%${dir_name}%g" ../../${cfg_name}.py > ${cfg_name}_${dir_name}.py
fi
sed -e "s%ANALYZER%${cfg_name}_${dir_name}%g" -e "s%DIRNAME%${dir_name}%g" ../../${script_name}.sh > ${script_name}_${dir_name}.sh
chmod u+x ${script_name}_${dir_name}.sh
bsub -q $queue -J ${cfg_name}_${dir_name} < ${script_name}_${dir_name}.sh

exit 0
