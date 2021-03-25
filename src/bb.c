#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define SAMPLE_COUNT SAMPLE_RATE * 30

extern int bytebeat(int t, char* code);

void _pei386_runtime_relocator()
{
	return;
}

void __chkstk_ms()
{
	return;
}

void __main()
{
	char code[65536];
	int i = 0;
	FILE* f = fopen("song.bb", "r");
	while (!feof(f))
	{
		fread(code + i, 1, 1, f);
		i++;
	}
	fclose(f);
	
	char* buffer = malloc(SAMPLE_COUNT);
	for (int i = 0; i < SAMPLE_COUNT; i++)
		buffer[i] = bytebeat(i, code);

	HWAVEOUT hWaveOut;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };
	WAVEHDR header = { buffer, SAMPLE_COUNT, 0, 0, 0, 0, 0, 0 };	

	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

	Sleep(SAMPLE_COUNT * 1000 / SAMPLE_RATE);
	exit(0);
}