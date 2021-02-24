#include "../include/token.h"

#include <stdio.h>
#include <stdlib.h>

extern struct Token_Token*
Token_Token_create ( enum Token_TokenType type, int data, int line )
{
    struct Token_Token* token = malloc( sizeof( struct Token_Token ) );

    if ( !token )
    {
        perror( "Could not allocate memory" );
        return NULL;
    }

    token->type = type;
    token->data = data;
    token->line = line;

    return token;
}

extern void
Token_Token_present( struct Token_Token* token )
{
    switch ( token->type )
    {
        case Token_TokenType_INSTRUCTION:
            switch ( token->data )
            {
                case Token_TokenInstruction_ERR:
                    printf( "Type: Instruction, Data: ERR, Line: %d\n" , token->line );
                    break;

                case Token_TokenInstruction_NOP:
                    printf( "Type: Instruction, Data: NOP, Line: %d\n" , token->line );
                    break;
                
                case Token_TokenInstruction_PUSH:
                    printf( "Type: Instruction, Data: PUSH, Line: %d\n" , token->line );
                    break;
                
                case Token_TokenInstruction_ADD:
                    printf( "Type: Instruction, Data: ADD, Line: %d\n" , token->line );
                    break;
                
                case Token_TokenInstruction_HLT:
                    printf( "Type: Instruction, Data: HLT, Line: %d\n" , token->line );
                    break;

                default:
                    printf( "Type: Instruction, Data: %d, Line: %d\n" , token->data, token->line );
                    break;
            }
            break;

        case Token_TokenType_NUMBER:
            printf( "Type: Number, Data: %d, Line: %d\n" , token->data, token->line );
            break;

        default:
            printf( "Type: %d, Data: %d, Line: %d\n" , token->type, token->data, token->line );
            break;
    }
}

extern void
Token_Token_destroy ( struct Token_Token* token )
{
    if ( !token )
    {
        free( token );
    }
}

extern struct Token_TokenList*
Token_TokenList_create( int size )
{
    struct Token_TokenList* list = malloc( sizeof( struct Token_TokenList ) );

    if ( !list )
    {
        perror( "Could not allocate memory" );
        return NULL;
    }

    list->data = calloc( size, sizeof( struct Token_Token* ) );

    if ( !list->data )
    {
        perror( "Could not allocate memory" );
        free( list );
        return NULL;
    }

    list->len = 0;
    list->size = size;

    return list;
}

extern struct Token_Token*
Token_TokenList_push_back ( struct Token_TokenList* list, struct Token_Token* token )
{
    if ( list->len >= list->size )
    {
        struct Token_Token** tokens = (struct Token_Token**)realloc( list->data, list->size * sizeof( struct Token_Token* ) * 2 );

        if ( !tokens )
        {
            perror( "Could not realloc memory" );
            Token_TokenList_destroy( list );
            return NULL;
        }
        list->data = tokens;
    }
    list->data[list->len++] = token;
    
    return token;
}

extern struct Token_Token*
Token_TokenList_get ( struct Token_TokenList* list, int index )
{
    if ( index >= list->len )
    {
        return NULL;
    }

    return list->data[index];
}

extern void
Token_TokenList_destroy( struct Token_TokenList* list )
{
    for ( int i = 0; i < list->len; ++i )
    {
        if ( !list->data[i] )
        {
            Token_Token_destroy( list->data[i] );
        }
    }
    free( list );
}
