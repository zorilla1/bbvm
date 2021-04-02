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
			printf("0x%x,", (0 << 1) | 1);
			depth++;
		}
		else if (strcmp(token, "&") == 0)
		{
			printf("0x%x,", (6 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "^") == 0)
		{
			printf("0x%x,", (9 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "|") == 0)
		{
			printf("0x%x,", (12 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "+") == 0)
		{
			printf("0x%x,", (15 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "-") == 0)
		{
			printf("0x%x,", (17 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "*") == 0)
		{
			printf("0x%x,", (20 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "/") == 0)
		{
			printf("0x%x,", (23 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "%") == 0)
		{
			printf("0x%x,", (26 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "<<") == 0)
		{
			printf("0x%x,", (30 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, ">>") == 0)
		{
			printf("0x%x,", (33 << 1) | 1);
			depth -= 1;
		}
		else if (strcmp(token, "==") == 0)
		{
			printf("0x%x,", (36 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, "<=") == 0)
		{
			printf("0x%x,", (38 << 1) | 1);
			depth -= 1;			
		}
		else if (strcmp(token, ">=") == 0)
		{
			printf("0x%x,", (37 << 1) | 1);
			depth -= 1;				
		}
		else if (strlen(token) > 0)
		{
			int n = atoi(token);
			if (n >= 0 && n <= 127)
			{
				printf("0x%x,", (n << 1) | 0);
			}
			else
			{
				printf("0x%x,", (43 << 1) | 1);
				printf("0x%x,", n & 0xFF);
				printf("0x%x,", (n >> 8) & 0xFF);
				printf("0x%x,", (n >> 16) & 0xFF);
				printf("0x%x,", (n >> 24) & 0xFF);
			}
			depth++;			
		}
		token = strtok(NULL, "\r\n\t\v ");
	}
	printf("0x%x,", (49 << 1) | 1);
	if (depth != 1)
		fprintf(stderr, "WARNING: Stack depth not one.\n");
	free(buffer);
}