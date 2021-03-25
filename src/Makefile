all:
	gcc compiler.c -o compiler.exe
	nasm bb.asm -f win32 -o bbs.o
	gcc -m32 -c bb.c -o bbc.o
	gcc -m32 -o bb.exe bbs.o bbc.o -lwinmm -nostartfiles -e ___main
	crinkler bbs.o bbc.o ..\lib\kernel32.Lib ..\lib\WinMM.lib ..\lib\User32.lib /ENTRY:__main
	
clean:
	rm *.o
	rm *.exe