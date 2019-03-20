#include <stdint.h>
#include <stdlib.h>
#include "NoiseGate.h"
#include "wavfile.h"
#include "dr_wav.h"
#define DR_WAV_IMPLEMENTATION
//using namespace std;
void noiseGateUintTest() {
	// step 1: read the audio data
	WAV* wavfile = wavfile_read("audio_in_with_noise.wav");
	size_t samplerate = wavfile->sampleRate;
	size_t len = wavfile->totalPCMFrameCount;
	float* out = (float*)malloc(sizeof(float)*len);

	// step 2: initialize the noise gate with default coefficients.
	//			you can custom the parameters int the noise_gate_buff.
	//			For more details,please find the readme file.
	NoiseGate_t* NG = createNoiseGate(0.01, 0.2, -24, samplerate);

	// step 3: Apply the noise gate effect to the Mono audio data.
	for (size_t n = 0; n < len; n++)
	{
		runNoiseGate(NG, wavfile->pDataFloat[0][n], out[n]);
	}

	// step 4: Output the processed audio data.
	wavfile_write_f32("noise gate output.wav", &out, len, 1, samplerate);

	wavfile_destory(wavfile);
	freeNoiseGate(NG);
	free(out);
}
int main()
{
	noiseGateUintTest();
    return 0;
}

