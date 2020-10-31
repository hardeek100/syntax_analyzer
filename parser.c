#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header files
#include "parser.h"
#include "lexical.h"

static void error_() {
	printf("Error encounter: The next lexeme was %s and the next token was %s\n", lexeme, nextToken);
	exit(1);
}

// P ::= S
void P() {
	S();
}

// S ::= V:=E | read(V) | write(V) | while C do S od | SS'
void S() {
	if (strcmp(nextToken, IDENT) == 0) {
		V();
	}
	else if (strcmp(nextToken, KEY_READ) == 0) {
		read_();
	}
	else if (strcmp(nextToken, KEY_WRITE) == 0) {
		write_();
	}
	else if (strcmp(nextToken, KEY_WHILE) == 0) {
		while_();
	}

	if (strcmp(nextToken, ASSIGN_OP) == 0) {
		lex();
		E();
	}

	S_();
}

// S' ::= ;SS' | e
void S_() {
	if (strcmp(nextToken, SEMICOLON) == 0) {
		lex();
		if ((strcmp(nextToken, "EOF") == 0) || (strcmp(nextToken, KEY_OD) == 0)) {
			error_();
		}
		S();
	}
}

// E::= TE' 
void E() {
	if ((strcmp(nextToken, IDENT) == 0) || (strcmp(nextToken, INT_LIT) == 0)) {
		T();
	}
	E_();
}

// E' ::= +TE' | -TE'
void E_() {
	while ((strcmp(nextToken, ADD_OP) == 0) || (strcmp(nextToken, SUB_OP) == 0)) {
		lex();
		T();
	}
}

// T ::= FT'
void T() {
	F();
	T_();
}

// T' ::= *FT' | /FT' | e
void T_() {
	while ((strcmp(nextToken, MULT_OP) == 0) || (strcmp(nextToken, DIV_OP) == 0)) {
		lex();
		F();
	}
}


// F := (E) | N | V
void F() {
	if (strcmp(nextToken, INT_LIT) == 0) {
		N();
	}
	else if (strcmp(nextToken, IDENT) == 0) {
		V();
	}
	else if (strcmp(nextToken, LEFT_PAREN) == 0) {
		lex();
		E();
		if (strcmp(nextToken, RIGHT_PAREN) == 0) {
			lex();
			S_();
		}
		else {
			error_();
		}
	}
}

// N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N 
void N() {
	while (strcmp(nextToken, INT_LIT) == 0) {
		lex();
	}
}

// V ::= a | b | … | y | z | aV | bV | … | yV | zV 
void V() {
	while (strcmp(nextToken, IDENT) == 0) {
		lex();
	}
}

// read(V) S'
void read_() {
	lex();
	if (strcmp(nextToken, LEFT_PAREN) == 0) {
		lex();
		if (strcmp(nextToken, IDENT) == 0) {
			V();
		}
		else {
			error_();
		}
		if (strcmp(nextToken, RIGHT_PAREN) == 0) {
			lex();
			S_();
		}
		else {
			error_();
		}
	}
	else {
		error_();
	}
}

// write(V) S'
void write_() {
	lex();
	if (strcmp(nextToken, LEFT_PAREN) == 0) {
		lex();
		if (strcmp(nextToken, IDENT) == 0) {
			V();
		}
		else {
			error_();
		}
		if (strcmp(nextToken, RIGHT_PAREN) == 0) {
			lex();
			S_();
		}
		else {
			error_();
		}
	}
	else {
		error_();
	}
}

// C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E
void C() {
	if (strcmp(nextToken, IDENT) == 0) {
		E();
		if ((strcmp(nextToken, LESSER_OP) == 0) || (strcmp(nextToken, GREATER_OP) == 0) || (strcmp(nextToken, EQUAL_OP) == 0) || (strcmp(nextToken, NEQUAL_OP) == 0) || (strcmp(nextToken, LEQUAL_OP) == 0) || (strcmp(nextToken, GEQUAL_OP) == 0)) {
			lex();
			E();
		}
		else {
			error_();
		}
	}
	else {
		error_();
	}
}

// while C do S od S'
void while_() {
	lex();
	if (strcmp(nextToken, IDENT) == 0) {
		C();
	}
	if (strcmp(nextToken, KEY_DO) == 0) {
		lex();
		S();
		if (strcmp(nextToken, KEY_OD) == 0) {
			lex();
			S_();
		}
		else {
			error_();
		}
	}
	else {
		error_();
	}
}
