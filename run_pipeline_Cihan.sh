#!/usr/bin/bash

set -e
# input param 
# $1: sequence name
# $2: whether the video is upper body only (false by default, enable by -f)

#dataDir=/vol/research/extol/personal/cihan/data/MonocularTotalCapture/
dataDir=/home/seamanj/Workspace/MonocularTotalCapture/data
seqName=example_speech
upperBody=-f

#mkdir $dataDir"/"$seqName
#mv $dataDir"/"$seqName".mp4" $dataDir"/"$seqName"/"$seqName".mp4"

# Assume that you already have a video in $dataDir/(seqName)/(seqName).mp4 
#dataDir=/vol/research/extol/personal/cihan/data/MonocularTotalCapture/
# Git clone openpose to ../openpose and compile with cmake
openposeDir=/home/seamanj/Software/openpose
# Where the monocular total capture is installed
MTCDir=/home/seamanj/Workspace/MonocularTotalCapture

# convert to absolute path
MTCDir=$(readlink -f $MTCDir)
dataDir=$(readlink -f $dataDir)
openposeDir=$(readlink -f $openposeDir)

if [ ! -f $dataDir/$seqName/calib.json ]; then
	echo "Camera intrinsics not specified, use default."
	cp -v $MTCDir/POF/calib.json $dataDir/$seqName
fi

# use ffmpeg to extract image frames
cd $dataDir/$seqName
if [ ! -d raw_image ]; then
	mkdir raw_image
	ffmpeg -i $seqName.mp4 raw_image/${seqName}_%08d.png
fi

num_raw_image=$(ls $dataDir/$seqName/raw_image/$seqName_* | wc -l)
echo "num_raw_image: $num_raw_image"


# Check if Openpose has already been extracted and compressed
cd $dataDir/$seqName
if [ -f openpose_result.tar.gz ]; then
	tar -xzvf openpose_result.tar.gz
fi

# run OpenPose on image frames
if [ ! -d openpose_result ]; then
	mkdir openpose_result
	cd $openposeDir
	./build/examples/openpose/openpose.bin \
	--face \
	--hand_scale_number 8 --hand_scale_range 0.4 --hand \
	--image_dir $dataDir/$seqName/raw_image \
	--write_json $dataDir/$seqName/openpose_result \
	--render_pose 1 \
	--display 0 \
	--model_pose BODY_25 \
	--number_people_max 1 \
	--write_video $dataDir/$seqName/$seqName"_openpose.mp4" \
	--write_video_fps 25
else  # openpose didn't run on all raw images
	num_openpose_result=$(ls $dataDir/$seqName/openpose_result/$seqName_* | wc -l)
	echo "num_openpose_result: $num_openpose_result"
	if [ $num_openpose_result -lt $num_raw_image ]; then
		cd $openposeDir
		./build/examples/openpose/openpose.bin \
		--face \
		--hand_scale_number 8 --hand_scale_range 0.4 --hand \
		--image_dir $dataDir/$seqName/raw_image \
		--write_json $dataDir/$seqName/openpose_result \
		--render_pose 1 \
		--display 0 \
		--model_pose BODY_25 \
		--number_people_max 1 \
		--write_video $dataDir/$seqName/$seqName"_openpose.mp4" \
		--write_video_fps 25
	fi
fi

# merge openpose results into a single file
# tj : wc -l  - word counting the number of lines
# https://en.wikipedia.org/wiki/Wc_(Unix)
cd $MTCDir
#numFrame=$(ls $dataDir/$seqName/openpose_result/$seqName_* | wc -l)
python3 POF/collect_openpose.py -n $seqName -r $dataDir/$seqName -c $num_raw_image

# run POF generation code
cd $dataDir/$seqName
if [ -f net_output.tar.gz ]; then
	tar -xzvf net_output.tar.gz
fi
cd $MTCDir/POF
if [ ! -d $dataDir/$seqName/net_output/ ]; then
	python3 save_total_sequence.py -s $seqName -p $dataDir/$seqName $upperBody
else
	num_POF=$(ls $dataDir/$seqName/net_output/*.txt | wc -l)
	echo "num_POF: $num_POF"
	if [ $num_POF -lt $num_raw_image ]; then
		python3 save_total_sequence.py -s $seqName -p $dataDir/$seqName $upperBody
	else
		echo "POF results exist. Skip POF generation."
	fi
fi

#tj : count the number of frame

if [ -d $dataDir/$seqName/body_3d_frontal/ ]; then
	stage1_numPng=$(ls $dataDir/$seqName/body_3d_frontal/*.png | wc -l) 
	stage1_numTxt=$(ls $dataDir/$seqName/body_3d_frontal/*.txt | wc -l)
	stage1_numFrame=$((stage1_numPng<stage1_numTxt?stage1_numPng:stage1_numTxt))
	if [ $stage1_numFrame -eq 0 ]; then 
		stage1_numFrame=1
	fi
else
	stage1_numFrame=1
fi 

if [ -d $dataDir/$seqName/body_3d_frontal_tracking/ ]; then
	stage2_numPng=$(ls $dataDir/$seqName/body_3d_frontal_tracking/*.png | wc -l) 
	stage2_numTxt=$(ls $dataDir/$seqName/body_3d_frontal_tracking/*.txt | wc -l)
	stage2_numFrame=$((stage2_numPng<stage2_numTxt?stage2_numPng:stage2_numTxt))
	if [ $stage2_numFrame -eq 0 ]; then 
		stage2_numFrame=1
	fi
else
	stage2_numFrame=1
fi


echo "stage1_numFrame: $stage1_numFrame"
echo "stage2_numFrame: $stage2_numFrame"


# run Adam Fitting
# tj : run from the last results
cd $MTCDir/FitAdam/
if [ ! -f ./build/run_fitting ]; then
	echo "C++ project not correctly compiled. Please check your setting."
else
	if [ $stage1_numFrame -lt $num_raw_image ]; then
		./build/run_fitting --root_dirs $dataDir --seqName $seqName --start $stage1_numFrame --end $((num_raw_image + 1)) --stage 1 --imageOF
	fi
	if [ $stage2_numFrame -lt $num_raw_image ]; then
		./build/run_fitting --root_dirs $dataDir --seqName $seqName --start $stage2_numFrame --end $((num_raw_image + 1)) --stage 2 --imageOF
	fi
fi
#./build/run_fitting --root_dirs $dataDir --seqName $seqName --start 1 --end $((numFrame + 1)) --stage 1 --imageOF

cd $dataDir/$seqName
# tj : generate videos
# -i url(input) 
# -c[:stream_specifier] codec (input/output,per-stream)
# -codec[:stream_specifier] codec (input/output,per-stream)
#  Select an encoder (when used before an output file) or a decoder (when used before an input file) for one or
#  more streams. codec is the name of a decoder/encoder or a special value copy (output only) to indicate that 
#  the stream is not to be re-encoded.
# https://ffmpeg.org/ffmpeg.html#Options
ffmpeg -i body_3d_frontal/%04d.png -c:v libx264 $seqName"_body_3d_frontal.mp4"
#rm body_3d_frontal/*.png
#tar -czvf body_3d_frontal.tar.gz body_3d_frontal
#rm -rf body_3d_frontal
#
cd $dataDir/$seqName
ffmpeg -i body_3d_frontal_tracking/%04d.png -c:v libx264 $seqName"_body_3d_frontal_tracking.mp4"
#rm body_3d_frontal_tracking/*.png
#tar -czvf body_3d_frontal_tracking.tar.gz body_3d_frontal_tracking
#rm -rf body_3d_frontal_tracking
#

# tj : merge multiple videos into one
cd $dataDir/$seqName


# tj : -filter_complex filtergraph (global)
# Define a complex filtergraph, i.e. one with arbitrary number of inputs and/or outputs.
# https://ffmpeg.org/ffmpeg-filters.html

# tj : -crf : The range of the CRF scale is 0–51, where 0 is lossless, 23 is the default, and 51 is worst quality possible. 
# -preset : A preset is a collection of options that will provide a certain encoding speed to compression ratio
# https://trac.ffmpeg.org/wiki/Encode/H.264
ffmpeg \
  -i $seqName".mp4" \
  -i $seqName"_openpose.mp4" \
  -filter_complex "hstack,format=yuv420p" \
  -c:v libx264 \
  -crf 18 \
  -preset veryfast \
  top.mp4

ffmpeg \
  -i $seqName"_body_3d_frontal.mp4" \
  -i $seqName"_body_3d_frontal_tracking.mp4" \
  -filter_complex "hstack,format=yuv420p" \
  -c:v libx264 \
  -crf 18 \
  -preset veryfast \
  -preset veryfast \
  bottom.mp4

ffmpeg \
  -i top.mp4 \
  -i bottom.mp4 \
  -filter_complex "vstack,format=yuv420p" \
  -c:v libx264 \
  -crf 18 \
  -preset veryfast \
  -preset veryfast \
  $seqName"_monocular_total_capture.mp4"
#
#rm top.mp4
#rm bottom.mp4
#
## Clean up
## Remove image data
#cd $dataDir/$seqName
#if [ -d raw_image ]; then
#	rm -rf raw_image
#fi
#
#cd $dataDir/$seqName
#if [ ! -f openpose_result.tar.gz ]; then
#	tar -czvf openpose_result.tar.gz openpose_result
#fi
#rm -rf openpose_result
#
#cd $dataDir/$seqName
#if [ ! -f net_output.tar.gz ]; then
#	tar -czvf net_output.tar.gz net_output
#fi
#rm -rf net_output
