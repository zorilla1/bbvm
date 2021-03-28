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

        ; | (opcode 12)
        or eax, ecx
		ret

        ; + (neg, -) (opcode 15)
        neg ecx

        ; - (opcode 17)
        sub eax, ecx
        ret

        ; * (opcode 20)
        mul ecx
        ret

        ; / (opcode 23)
        div ecx
        ret

        ; % (opcode 26)
        div ecx
        xchg eax, edx
        ret

        ; << (opcode 30)
        shl eax, cl
        ret
        
        ; >> (opcode 33)
        shr eax, cl
        ret

        ; == (opcode 36)
        stc

        ; <= (opcode 37)
        cmc
        
        ; >= (opcode 38)
        setbe dl
        xchg eax, edx
        ret
        
        ; push imm32 (opcode 43)
        pop edx
        push eax
        push ecx
        push edx
        lodsd
        ret
        
        ; return (opcode 49)
        pop edx
        xchg eax, ebx
		xchg eax, ecx
		pop edi
		pop esi
        ret
