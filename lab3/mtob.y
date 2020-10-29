%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

// id table
int len = 0;
char namelist[MAXN][50];
double vallist[MAXN];

// single id
int p;
char* lval;
char namein[50];

extern int yyparse();
FILE* yyin;

int yylex();
void yyerror(const char* s);
%}

%union{
	float fval;
	struct {
		char* name;
		double value;
	}idt;
}

%token<fval> T_NUMBER	
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT
%token T_QUIT T_TEST
%token T_EQUAL
%token<idt> T_ID

%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%left T_EQUAL

%start lines

%%

lines: lines T_TEST {
		printf("idt length: %d\n", len);
		for (int i = 0; i < len; i++)
			printf("%d: %s %f\n", i, namelist[i], vallist[i]);
	  }
	  | lines { printf("\t"); } expression ';' { printf("\n"); }
	  | lines ';'
	  | lines T_QUIT	{ printf("\tThanks for using!\n"); exit(0); }
	  |
;

expression: T_NUMBER				        { printf("%.0lf ", $1); }
	  | T_ID	{ printf("%s ", $1.name); }
	  | T_MINUS { printf("0 "); } expression	{ printf("- "); }
	  | T_PLUS expression
	  | expression T_PLUS expression	{ printf("+ "); }
	  | expression T_MINUS expression	{ printf("- "); }
	  | expression T_MULTIPLY expression{ printf("* "); }
      | expression T_DIVIDE expression	{ printf("/ "); }
	  | T_LEFT expression T_RIGHT		
;

%%

int isAlpha(int t)
{
	if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z')
		return 1;
	return 0;
}

int isdigit(int t)
{
	if (t >= '0' && t <= '9')
		return 1;
	return 0;
}

int ishex(int t)
{
	if (t >= '0' && t <= '9' || t >= 'a' && t <= 'f' || t >= 'A' && t <= 'F')
		return 1;
	return 0;
}

int isoct(int t)
{
	if (t >= '0' && t <= '7')
		return 1;
	return 0;
}

char itoc(int t)
{
	char ch = t;
	return ch;
}

int htod(int t)
{
	if (t >= '0' && t <= '9')
		return t - '0';
	if (t >= 'a' && t <= 'f')
		return t - 'a' + 10;
	if (t >= 'A' && t <= 'F')
		return t - 'A' + 10;
}

int yylex()
{
	int t;
	while (1)
	{
		t = getchar();
		if (t == ' ' || t == '\t' || t == '\n')
			continue;
		if (t == '+')
			return T_PLUS;
		if (t == '-')
			return T_MINUS;
		if (t == '*')
			return T_MULTIPLY;
		if (t == '/')
			return T_DIVIDE;
		if (t == '=')
			return T_EQUAL;
		if (t == '(')
			return T_LEFT;
		if (t == ')')
			return T_RIGHT;
		if (isdigit(t))
		{
			yylval.fval = t - '0';
			if (t == '0')
			{
				t = getchar();
				if (t == 'X' || t == 'x')
				{
					// hex number
					t = getchar();
					while (ishex(t))
					{
						yylval.fval = yylval.fval * 16 + htod(t);
						t = getchar();
					}
					ungetc(t, stdin);
					return T_NUMBER;
				}
				else if (isoct(t))
				{
					// oct number
					while(isoct(t))
					{
						yylval.fval = yylval.fval * 8 + t - '0';
						t = getchar();
					}
					ungetc(t, stdin);
					return T_NUMBER;
				}
				ungetc(t, stdin);
			}
			while (1)
			{
				t = getchar();
				if (!isdigit(t)) break;
				yylval.fval = yylval.fval * 10 + t - '0';
			}
			ungetc(t, stdin);
			return T_NUMBER;
		}
		if (isAlpha(t) || t == '_')
		{
			// id
			// init
			p = 0;
			memset(namein, 0, sizeof(namein));
			namein[p] = itoc(t);
			p = p + 1;
			if (t == 'q' || t == 'Q')
			{
				t = getchar();
				if (t == '\n')
					return T_QUIT;
				ungetc(t, stdin);
			}
			else if (t == 'i' || t == 'I')
			{
				t = getchar();
				if (t == '\n')
					return T_TEST;
				ungetc(t, stdin);
			}
			while (1)
			{
				t = getchar();
				if (!isAlpha(t) && !isdigit(t) && t != '_')
					break;
				namein[p] = itoc(t);
				p = p + 1;
			}
			namein[p] = '\0';
			if (t == '=')
				lval = namein;
			ungetc(t, stdin);
			// save into idt
			for (int i = 0; i < len; i++)
				if (strcmp(namelist[i], namein) == 0)
				{
					// if in idt
					yylval.idt.name = namein;
					yylval.idt.value = vallist[i];
					return T_ID;
				}
			for (int i = 0; i < strlen(namein); i++)
				namelist[len][i] = namein[i];
			namelist[len][strlen(namein)] = '\0';
			vallist[len] = 0;
			len = len + 1;
			// back value
			yylval.idt.name = namein;
			yylval.idt.value = 0;
			return T_ID;
		}
		return t;
	}
}

int main() {
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
