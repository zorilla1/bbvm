If your song is test.txt and infix, then run

	cat test.txt | infix | compiler | player

For RPN, simply omit infix

	cat test.txt | compiler | player
	
Note that if there are any errors in your song, the player will most likely crash.
The build scripts will produce an executable called bb.exe in the src\ directory from the
infix song in src\song.txt. The build scripts expect you to have nasm, gcc, and
crinkler in your path.