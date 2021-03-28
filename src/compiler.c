#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <io.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	setmode(fileno(stdout), O_BINARY);
	
	char* buffer = malloc(65536);
	int i = 0;
	while (!feof(stdin))
	{
		if (fread(buffer + i, 1, 1, stdin) == 1)
			i++;
	}
	buffer[i] = 0;
	
	int depth = 0;
	char* token = strtok(buffer, "\r\n\t\v ");
	while (token != NULL)
	{
		if (strcmp(token, "t") == 0)
		{
			printf("%c", (0 << 1) | 1);
			depth++;
		}
		else if (strcmp(token, "&") == 0)
		{
			printf("%c", (6 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "^") == 0)
		{
			printf("%c", (9 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "|") == 0)
		{
			printf("%c", (12 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "+") == 0)
		{
			printf("%c", (15 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "-") == 0)
		{
			printf("%c", (17 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "*") == 0)
		{
			printf("%c", (20 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "/") == 0)
		{
			printf("%c", (23 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "%") == 0)
		{
			printf("%c", (26 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "<<") == 0)
		{
			printf("%c", (30 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, ">>") == 0)
		{
			printf("%c", (33 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "==") == 0)
		{
			printf("%c", (36 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "<=") == 0)
		{
			printf("%c", (38 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, ">=") == 0)
		{
			printf("%c", (37 << 1) | 1);
			depth -= 1;				
		}
		else if (strlen(token) > 0)
		{
			int n = atoi(token);
			if (n >= 0 && n <= 127)
			{
				printf("%c", (n << 1) | 0);
			}
			else
			{
				printf("%c", (43 << 1) | 1);
				fwrite(&n, 4, 1, stdout);
			}
			depth++;			
		}
		token = strtok(NULL, "\r\n\t\v ");
	}
	printf("%c", (49 << 1) | 1);
	if (depth != 1)
		fprintf(stderr, "WARNING: Stack depth not one.\n");
	free(buffer);
}