1) Log in to your CERN accout: ssh USERNAME@lxplus.cern.ch

2) cd into your desired directory where you want to work

3) Execute: 
	cmsrel CMSSW_7_1_11_patch2
	cd CMSSW_7_1_11_patch2/src/
	cmsenv
        mkdir BBA
	cd BBA
 	git clone https://github.com/kmtos/BBA . #Make sure you have the period, or the paths will be incorrect
	scram b -j 12

The code should be ready to go.

GENERATING
1) cd into the CMSSW_7_1_11_patch2/src/BBA/Generation/
2) Change paths on line 4, 8, 10 of SignalSampleGenerator.sh to the correct paths of your directories
3) Execute:
	scram b -j 12
	./generate.sh BBASampleGenerator SignalSampleGenerator TEST "" 1 1000 1nd 
		NOTES:  BBASampleGenerator -> cfg file
			SignalSampleGenerator -> script 
			TEST -> Name of Dir. Call it whatever you want
			1 -> start job num
			1000 -> end job num
			1nd -> bsub queue 
  
PRODUCERS
1) Change the paths of the input files in  CMSSW_7_1_11_patch2/src/BBA/Producers/bRatioProducer_cfg.py to the location of the Generated files.

VariousFunctions
1) These are some random functions I made instead of writing it a lot. They only work for GEN-SIM level generations, except for the Histogram Formating functions. They will save you some coding time.

RUNNING THE ANALYZER
1) cd into  BBA/Analyzer/
2) Execute: mkdir BSUB
3) Change the paths on line 4 and 8 of SUBMIT.sh to the path of your current directory.
4) Execute: ./analyze.sh bbanalyzer_cfg SUBMIT TEST 8nh  #TEST is just the name of whatever directory you want to use.
   	Notes:  bbanalyzer_cfg ->cfg file
		SUBMIT -> script
		TEST -> Name of Dir. Call it whatever you want
		8nh -> bsub queue

 
