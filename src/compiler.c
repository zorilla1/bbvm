#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE* f_in = fopen(argv[1], "r");
	if (!f_in)
	{
		printf("Unable to open %s. Exiting.\n", argv[1]);
		exit(1);
	}
	
	fseek(f_in, 0L, SEEK_END);
	long size = ftell(f_in);
	fseek(f_in, 0L, SEEK_SET);
	char* buffer = malloc(size);
	
	if (!buffer)
	{
		printf("Unable to allocate memory. Exiting.\n");
		exit(1);
	}
	
	if (fread(buffer, size, 1, f_in) != 1)
	{
		printf("Unable to read %s. Exiting.\n", argv[1]);
		free(buffer);
		exit(1);
	}
	buffer[size] = 0;
	
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
		else if (strcmp(token, "<<") == 0)
		{
			printf("%c", (29 << 1) | 1);
		}
		else if (strcmp(token, ">>") == 0)
		{
			printf("%c", (32 << 1) | 1);
		}
		else if (strcmp(token, "==") == 0)
		{
			printf("%c", (35 << 1) | 1);
		}
		else if (strcmp(token, "<=") == 0)
		{
			printf("%c", (36 << 1) | 1);
		}
		else if (strcmp(token, ">=") == 0)
		{
			printf("%c", (37 << 1) | 1);
		}
		else
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
}