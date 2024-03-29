#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* symbol(char c)
{
	switch (c)
	{
		case '&':
			return "&";
		case '^':
			return "^";
		case '|':
			return "|";
		case 'E':
			return "==";
		case 'G':
			return ">=";
		case 'L':
			return "<=";
		case '<':
			return "<<";
		case '>':
			return ">>";
		case '+':
			return "+";
		case '-':
			return "-";
		case '*':
			return "*";
		case '/':
			return "/";
		case '%':
			return "%";
	}
}

int p(char c)
{
	switch (c)
	{
		case '&':
			return 10;
		case '^':
			return 10;
		case '|':
			return 10;
		case 'E':
			return 11;
		case 'G':
			return 12;
		case 'L':
			return 12;
		case '<':
			return 13;
		case '>':
			return 13;
		case '+':
			return 14;
		case '-':
			return 14;
		case '*':
			return 15;
		case '/':
			return 15;
		case '%':
			return 15;
			
		case '(':
			return 99;
	}
}

int main(int argc, char** argv)
{
	char os[65536];
	char token[256];
	char c = 0;
	int sp = -1;
	
	while (!feof(stdin))
	{
		if (fread(&c, 1, 1, stdin) != 1)
			break;
		if (c >= '0' && c <= '9')
		{
			int i = 0;
			while (c >= '0' && c <= '9' && !feof(stdin))
			{
				token[i] = c;
				i++;
				fread(&c, 1, 1, stdin);
			}
			token[i] = 0;
			printf("%s ", token);
		}

		if (c == 't')
		{
			printf("t ");
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '&' || c == '^' || c == '|')
		{
			while (sp >= 0 && p(os[sp]) >= p(c) && os[sp] != '(')
				printf("%s ", symbol(os[sp--]));
			os[++sp] = c;
		}
        else if (c == '<')
		{
			fread(&c, 1, 1, stdin);
			if (c == '<')
			{
				while (sp >= 0 && p(os[sp]) >= p('<') && os[sp] != '(')
					printf("%s ", symbol(os[sp--]));
				os[++sp] = '<';
			}
			else if (c == '=')
			{
				while (sp >= 0 && p(os[sp]) >= p('L') && os[sp] != '(')
					printf("%s ", symbol(os[sp--]));
				os[++sp] = 'L';
			}
			else
			{
				fprintf(stderr, "Malformed expression (< followed by invalid char)\n");
			}

		}
        else if (c == '>')
		{
			fread(&c, 1, 1, stdin);
			if (c == '>')
			{
				while (sp >= 0 && p(os[sp]) >= p('>') && os[sp] != '(')
					printf("%s ", symbol(os[sp--]));
				os[++sp] = '>';
			}
			else if (c == '=')
			{
				while (sp >= 0 && p(os[sp]) >= p('G') && os[sp] != '(')
					printf("%s ", symbol(os[sp--]));
				os[++sp] = 'G';
			}
			else
			{
				fprintf(stderr, "Malformed expression (> followed by invalid char)\n");
			}
			
		}
        else if (c == '=')
		{
			fread(&c, 1, 1, stdin);
			if (c == '=')
			{
				while (sp >= 0 && p(os[sp]) >= p('E') && os[sp] != '(')
					printf("%s ", symbol(os[sp--]));
				os[++sp] = 'E';
			}
			else
			{
				fprintf(stderr, "Malformed expression (= not followed by =)\n");
			}
		}
		else if (c == '(')
		{
			os[++sp] = c;
		}
		else if (c == ')')
		{
			while (sp >= 0 && os[sp] != '(')
				printf("%s ", symbol(os[sp--]));
			if (os[sp] == '(') sp--;
		}
		else if (!isspace(c))
		{
			fprintf(stderr, "WARNING: Unrecognized character \"%c\"\n", c);
		}
	}
	
	while (sp >= 0)
		printf("%s ", symbol(os[sp--]));
	
	return 0;
}