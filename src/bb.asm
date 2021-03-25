; Big thanks to Rrrola, HellMood, Dresdenboy, and baze for help with this!

bits 32

; int bytebeat(int t, char* code)
global _bytebeat

section .text

_bytebeat:
		push esi
		push edi
		push ebx
		mov ebx, [esp + 16]
		mov esi, [esp + 20]
		
L:      xor eax, eax
        lodsb
        shr eax, 1
        jnc const
        lea edi, [eax + inst]
        cdq
        pop ecx
        pop eax
        cmp eax, ecx
        call edi
const:  push eax
        db 0x3d ; cmp eax,nnnn

inst:   ; t (opcode 0)
        pop edx
        push eax
        push ecx
        push ebx
        jmp L

        ; & (opcode 6)
        and eax, ecx
        ret

        ; ^ (opcode 9)
        xor eax, ecx
        ret

        ; | (&,+) (opcode 12)
        and eax, ecx

        ; + (neg, -) (opcode 14)
        neg ecx

        ; - (opcode 16)
        sub eax, ecx
        ret

        ; * (opcode 19)
        mul ecx
        ret

        ; / (opcode 22)
        div ecx
        ret

        ; % (opcode 25)
        div ecx
        xchg eax, edx
        ret

        ; << (opcode 29)
        shl eax, cl
        ret
        
        ; >> (opcode 32)
        shr eax, cl
        ret

        ; == (opcode 35)
        stc

        ; <= (opcode 36)
        cmc
        
        ; >= (opcode 37)
        setbe dl
        xchg eax, edx
        ret
        
        ; push imm32 (opcode 42)
        pop edx
        push eax
        push ecx
        push edx
        lodsd
        ret
        
        ; return (opcode 48)
        pop edx
        xchg eax, ebx
		xchg eax, ecx
		pop edi
		pop esi
        ret
