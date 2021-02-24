#ifndef DWARVEN_PARSER_H
#define DWARVEN_PARSER_H

#include "token.h"


extern struct Token_TokenList*
Parser_parse ( char* source );

extern int
Parser_number_get ( char* str );

extern enum Token_TokenInstruction
Parser_instruction_get ( char* str );

#endif