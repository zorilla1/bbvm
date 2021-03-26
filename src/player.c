#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define SAMPLE_COUNT SAMPLE_RATE * 30

extern int bytebeat(int t, char* code);

void main()
{
	char code[65536];
	printf("WAVE_FORMAT_PCM = %d\n", WAVE_FORMAT_PCM);
	printf("WAVE_MAPPER = %d\n", WAVE_MAPPER);
	printf("CALLBACK_NULL = %d\n", CALLBACK_NULL);
	printf("sizeof(WAVEHDR) = %d\n", sizeof(WAVEHDR));
	int i = 0;
	while (!feof(stdin))
	{
		fread(code + i, 1, 1, stdin);
		i++;
	}

	char* buffer = malloc(SAMPLE_COUNT);
	for (int i = 0; i < SAMPLE_COUNT; i++)
		buffer[i] = bytebeat(i, code);

	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };
	WAVEHDR header = { buffer, SAMPLE_COUNT, 0, 0, 0, 0, 0, 0 };	
	HWAVEOUT hWaveOut;
	
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

	Sleep(SAMPLE_COUNT * 1000 / SAMPLE_RATE);
	exit(0);
}