#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	char* buffer = malloc(65536);
	int i = 0;
	while (!feof(stdin))
	{
		if (fread(buffer + i, 1, 1, stdin) == 1)
			i++;
	}
	buffer[i] = 0;
	char* token = strtok(buffer, "\r\n\t\v ");
	while (token != NULL)
	{
		if (strcmp(token, "t") == 0)
		{
			printf("%c", (0 << 1) | 1);
		}
		else if (strcmp(token, "&") == 0)
		{
			printf("%c", (6 << 1) | 1);
		}
		else if (strcmp(token, "^") == 0)
		{
			printf("%c", (9 << 1) | 1);
		}
		else if (strcmp(token, "|") == 0)
		{
			printf("%c", (12 << 1) | 1);
		}
		else if (strcmp(token, "+") == 0)
		{
			printf("%c", (14 << 1) | 1);
		}
		else if (strcmp(token, "-") == 0)
		{
			printf("%c", (16 << 1) | 1);
		}
		else if (strcmp(token, "*") == 0)
		{
			printf("%c", (19 << 1) | 1);
		}
		else if (strcmp(token, "/") == 0)
		{
			printf("%c", (22 << 1) | 1);
		}
		else if (strcmp(token, "%") == 0)
		{
			printf("%c", (25 << 1) | 1);
		}
		else if (strcmp(token, "<") == 0)
		{
			printf("%c", (29 << 1) | 1);
		}
		else if (strcmp(token, ">") == 0)
		{
			printf("%c", (32 << 1) | 1);
		}
		else if (strcmp(token, "E") == 0)
		{
			printf("%c", (35 << 1) | 1);
		}
		else if (strcmp(token, "L") == 0)
		{
			printf("%c", (36 << 1) | 1);
		}
		else if (strcmp(token, "G") == 0)
		{
			printf("%c", (37 << 1) | 1);
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
				printf("%c", (42 << 1) | 1);
				fwrite(&n, 4, 1, stdout);
			}
		}
		token = strtok(NULL, "\r\n\t\v ");
	}
	printf("%c", (48 << 1) | 1);
	free(buffer);
}