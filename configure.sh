#!/bin/bash

if [ -f configure.sh ]; then
if [ "X$BSC_MACHINE" == "X" ]; then

   export EXTRAE_HOME=/opt/bsctools/extrae/3.4.1/

else
   source .config/configure/configure_$BSC_MACHINE
fi

rm -f sched-job.sh
ln -s .config/sched-job/sched-job_$BSC_MACHINE sched-job.sh

export LD_LIBRARY_PATH=$EXTRAE_HOME/lib/:$LD_LIBRARY_PATH

else
   echo ERROR: configure.sh should be run in its own directory
fi
