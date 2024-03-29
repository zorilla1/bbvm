bits 32

%define WAVE_MAPPER -1
%define WAVE_FORMAT_PCM 1
%define CALLBACK_NULL 0

%define SAMPLE_RATE 44100
%define SAMPLE_COUNT 3940352

extern _bytebeat
extern _waveOutOpen@24
extern _waveOutPrepareHeader@12
extern _waveOutWrite@12
extern _Sleep@4
global _start

section .text

_start:

	push CALLBACK_NULL
	push byte 0
	push byte 0
	push wavFormatEx
	push WAVE_MAPPER
	push hWaveOut
	call _waveOutOpen@24
	add esp, 24
	
	mov ecx, SAMPLE_COUNT
L:	push bytecode
	push ecx
	call _bytebeat
	add esp, 8
	mov byte [buffer + ecx], al
	loop L

	push 32
	push wavHdr
	push dword [hWaveOut]
	call _waveOutPrepareHeader@12
	add esp, 12

	push 32
	push wavHdr
	push dword [hWaveOut]
	call _waveOutWrite@12
	add esp, 12

	push SAMPLE_COUNT * 1000 / 44100
	call _Sleep@4
	add esp, 4
	ret
	
section .data

wavHdr:			dd buffer, SAMPLE_COUNT, 0, 0, 0, 0, 0, 0
wavFormatEx: 	dw WAVE_FORMAT_PCM, 1
                dd SAMPLE_RATE, SAMPLE_RATE
				dw 1, 8, 0
bytecode:		incbin 'song.bb'
section .bss

hWaveOut:	resd 1
buffer:		resb SAMPLE_COUNT