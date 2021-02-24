#include "../include/parser.h"
#include "../include/token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern struct Token_TokenList*
Parser_parse ( char* source )
{
    struct Token_TokenList* list = Token_TokenList_create( 8 );
    if ( !list )
    {
        perror( "Could not create token list" );
        return NULL;
    }

    char lex_buf[256];
    int lex_index = 0;
    int src_index = 0;
    int line = 0;
    
    while ( 1 )
    {
        if ( !memset( lex_buf, 0, 256 ) )
        {
            perror( "Could not set memory" );
            Token_TokenList_destroy( list );
            return NULL;
        }

        lex_index = 0;

        while ( source[src_index] != ' ' && source[src_index] != '\n' && source[src_index] != '\0' )
        {
            lex_buf[lex_index++] = source[src_index++];
        }

        if ( lex_index == 0 )
        {
            if ( source[src_index] == '\n' )
            {
                ++line;
            }

            if ( source[src_index] == '\0' )
            {
                break;
            }
            
            ++src_index;

            continue;
        }

        if ( lex_buf[0] == '#' )
        {
            int num = Parser_number_get( lex_buf );
            struct Token_Token* token = Token_Token_create( Token_TokenType_NUMBER, num, line );

            if ( !token )
            {
                perror( "Could not allocate memory" );
                Token_TokenList_destroy( list );
                return NULL;
            }

            if ( !Token_TokenList_push_back( list, token ) )
            {
                perror( "Could not push back" );
                Token_Token_destroy( token );
                Token_TokenList_destroy( list );
                return NULL;
            }
        }
        else // Must be instruction
        {
            enum Token_TokenInstruction instruction = Parser_instruction_get( lex_buf );
            if ( instruction == Token_TokenInstruction_ERR )
            {
                printf( "%s at line %d:\n", lex_buf, line );
                perror( "Unknown instruction" );
                Token_TokenList_destroy( list );
                return NULL;
            }

            struct Token_Token* token = Token_Token_create( Token_TokenType_INSTRUCTION, instruction, line );
            
            if ( !token )
            {
                perror( "Could not allocate memory" );
                Token_TokenList_destroy( list );
                return NULL;
            }

            if ( !Token_TokenList_push_back( list, token ) )
            {
                perror( "Could not push back" );
                Token_Token_destroy( token );
                Token_TokenList_destroy( list );
                return NULL;
            }
        }

        if ( source[src_index] == '\n' )
        {
            ++line;
        }

        if ( source[src_index] == '\0' )
        {
            break;
        }

        ++src_index;
    }

    return list;
}

extern int
Parser_number_get ( char* str )
{
    ++str; // TODO: Add any number parse, not 10th only
    return atoi( str );
}

extern enum Token_TokenInstruction
Parser_instruction_get ( char* str )
{
    if ( strcmp( str, "NOP" ) == 0 )
    {
        return Token_TokenInstruction_NOP;
    }
    if ( strcmp( str, "PUSH" ) == 0 )
    {
        return Token_TokenInstruction_PUSH;
    }
    if ( strcmp( str, "ADD" ) == 0 )
    {
        return Token_TokenInstruction_ADD;
    }
    if ( strcmp( str, "HLT" ) == 0 )
    {
        return Token_TokenInstruction_HLT;
    }
    return Token_TokenInstruction_ERR;
}