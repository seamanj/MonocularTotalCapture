#!/usr/bin/bash
cd POF/
if [ ! -f mtc_snapshots.zip ]; then 
	wget posefs1.perception.cs.cmu.edu/mtc/mtc_snapshots.zip
else
	echo "tj : mtc_snapshots.zip is already existed, downloading skipped!"
fi

# tj - : use -o option to force to output
unzip -o mtc_snapshots.zip
if [ ! -d snapshots ]; then
    echo "Pretrained model not extracted! Please check your setting."
else
    echo "Pretrained model successfully downloaded."
fi
cd ../FitAdam/model
if [ ! -f adam_blendshapes_348_delta_norm.json ]; then 
	wget posefs1.perception.cs.cmu.edu/mtc/adam_blendshapes_348_delta_norm.json
else
	echo "tj : adam_blendshapes_348_delta_norm.json is already existed, downloading skipped"
fi
cd ../include/
if [ ! -f InitializeAdamData.h ]; then
	wget posefs1.perception.cs.cmu.edu/mtc/InitializeAdamData.h
else
	echo "tj : InitializeAdamData.h is already existed, downloading skipped"
fi
cd ../../data/
if [ ! -f example_dance/example_dance.mp4 ]; then
	mkdir example_dance && cd example_dance
	wget posefs1.perception.cs.cmu.edu/mtc/example_dance.mp4
else
	echo "tj : example_dance.mp4 is already existed, downloading skipped"
	cd example_dance
fi

cd ../
if [ ! -f example_speech/example_speech.mp4 ]; then
	mkdir example_speech && cd example_speech
	wget posefs1.perception.cs.cmu.edu/mtc/example_speech.mp4
else
	echo "tj : example_speech.mp4 is already existed, downloading skipped"
fi
