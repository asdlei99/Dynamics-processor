// testNoiseGate.cpp: 定义控制台应用程序的入口点。
// 功能: 整合basic noiseGate effect，并进行封装及测试
// 

#include "stdafx.h"
#include <iostream>
#include "NoiseGate.h"
#include "AudioFile.cpp"
#include <vector>
using namespace std;

int main()
{
	// step 1: read the audio data
	AudioFile<double> af;
	string directory = ".\\assets\\";
	string file_name = "audio_in_with_noise.wav";
	af.load(directory + file_name);
	af.printSummary();
	vector<double> output;

	// step 2: initialize the noise gate with default coefficients.
	//			you can custom the parameters int the noise_gate_buff.
	//			For more details,please find the readme file.
	noise_gate_buff NG;

	// step 3: Apply the noise gate effect to the Mono audio data.
	for (auto sample : af.samples[0]) {
		output.push_back( noiseGate(sample, NG) );
	}

	// step 4: Output the processed audio data.
	vector<vector<double>> audio_buff{output};			
	af.setAudioBuffer(audio_buff);
	af.save(directory+"after_noise_gate01.wav");
    return 0;
}

