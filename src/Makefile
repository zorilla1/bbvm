all:
	gcc compiler.c -o compiler.exe
	gcc infix.c -o infix.exe	
	nasm bb.asm -f win32 -o bb.o
	gcc player.c bb.o -lwinmm -o player.exe
	cat song.txt | infix | compiler > song.bb
	nasm start.asm -f win32 -o start.o	
	crinkler bb.o start.o ..\lib\kernel32.Lib ..\lib\WinMM.lib /ENTRY:start /OUT:bb.exe /UNSAFEIMPORT /NODEFAULTLIB /TINYHEADER
	
clean:
	rm *.o
	rm *.exe
	rm *.bb