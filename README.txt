If your song is test.txt and infix, then run

	cat test.txt | infix | compiler | player

Note that if there are any errors in your RPN, player.exe will most likely crash.
The build scripts will produce an executable called bb.exe in the src\ directory from the
infix song in src\song.txt.