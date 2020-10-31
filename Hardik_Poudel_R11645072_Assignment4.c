#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Header files
#include "parser.h"
#include "lexical.h"

// File pointer
static FILE* file;

// Global variables.
char* nextToken;
char nextChar;
char* charClass;
int lexLen;
char lexeme[100];

//local variables
static char* prev;

// Funtion to get next character
static void getChar() {
	prev = charClass;
	if ((nextChar = getc(file)) != EOF) {
		if (isalpha(nextChar)) {
			charClass = LETTER;
		}
		else if (isdigit(nextChar)) {
			charClass = DIGIT;
		}
		else charClass = UNKNOWN;
	}
	else {
		charClass = "EOF";
	}
}

// Function to add character to lexeme.
static void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else {
		printf("Error! lexeme is too long.");
	}
}

// Function to determine the token of lexeme.
void lookup(char* ch) {
	if (strcmp(ch, ":=") == 0) {
		nextToken = ASSIGN_OP;
	}
	else if (strcmp(ch, "<") == 0) {
		nextToken = LESSER_OP;
	}
	else if (strcmp(ch, ">") == 0) {
		nextToken = GREATER_OP;
	}
	else if (strcmp(ch, "=") == 0) {
		nextToken = EQUAL_OP;
	}
	else if (strcmp(ch, "<>") == 0) {
		nextToken = NEQUAL_OP;
	}
	else if (strcmp(ch, "<=") == 0) {
		nextToken = LEQUAL_OP;
	}
	else if (strcmp(ch, ">=") == 0) {
		nextToken = GEQUAL_OP;
	}
	else if (strcmp(ch, "+") == 0) {
		nextToken = ADD_OP;
	}
	else if (strcmp(ch, "-") == 0) {
		nextToken = SUB_OP;
	}
	else if (strcmp(ch, "*") == 0) {
		nextToken = MULT_OP;
	}
	else if (strcmp(ch, "/") == 0) {
		nextToken = DIV_OP;
	}
	else if (strcmp(ch, "read") == 0) {
		nextToken = KEY_READ;
	}
	else if (strcmp(ch, "write") == 0) {
		nextToken = KEY_WRITE;
	}
	else if (strcmp(ch, "while") == 0) {
		nextToken = KEY_WHILE;
	}
	else if (strcmp(ch, "do") == 0) {
		nextToken = KEY_DO;
	}
	else if (strcmp(ch, "od") == 0) {
		nextToken = KEY_OD;
	}
	else if (strcmp(ch, ")") == 0) {
		nextToken = RIGHT_PAREN;
	}
	else if (strcmp(ch, "(") == 0) {
		nextToken = LEFT_PAREN;
	}
	else if (strcmp(ch, ";") == 0) {
		nextToken = SEMICOLON;
	}
	else if (strcmp(prev, LETTER) == 0)
		nextToken = IDENT;
	else {
		nextToken = UNKNOWN;
	}
}
//Function to get the non space character.
static void getNonBlank() {
	while (isspace(nextChar)) getChar();
}

// Lexical analyzer
 void lex() {
	
	lexLen = 0;
	getNonBlank();
	if (strcmp(charClass, LETTER) == 0) {
		addChar();
		getChar();
		while ((strcmp(charClass, LETTER) == 0)) {
			addChar();
			getChar();
		}
		lookup(lexeme);
	}
	else if (strcmp(charClass, DIGIT) == 0) {
		addChar();
		getChar();
		while (strcmp(charClass, DIGIT) == 0) {
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
	}
	else if (strcmp(charClass, "EOF") == 0) {
		nextToken = "EOF";
		addChar();
	}
	else {
		addChar();
		getChar();
		if (nextChar == '=' || nextChar == '>') {
			addChar();
			getChar();
		}
		lookup(lexeme);
	}
	
}

//Driver function.
int main(int argc, char* argv[]) {

	if (argv[1] == NULL) {
		printf("Missed a filename!\n");
		exit(2);
	}
	else if ((file = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open file %s\n", argv[1]);
		exit(3);
	}
	else {
		printf("%s\n\n", "DanC Parser :: R11645072");
		getChar();
		do {
			lex();
			P();
		} while (nextToken != "EOF");
		printf("Syntax Validated\n");
		exit(0);
	}
	return 0;
}