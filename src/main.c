#include "../include/util.h"
#include "../include/parser.h"
#include "../include/token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int
main ( int argc, char** argv );

extern int
main ( int argc, char** argv )
{
    if ( argc < 3 )
    {
        perror( "Too few arguments" );
        return EXIT_FAILURE;
    }

    if ( strcmp( argv[1], "run" ) == 0 )
    {
        char* source = Util_read_ascii_file( argv[2] );
        if ( !source )
        {
            perror( "Could not load file" );
            return EXIT_FAILURE;
        }
        puts( "==SOURCE==" );
        if ( puts( source ) == EOF )
        {
            perror( "Could not print source" );
            free ( source );
            return EXIT_FAILURE;
        }
        puts( "==SOURCE==" );
        struct Token_TokenList* list = Parser_parse( source );
        if ( !list )
        {
            perror( "Could not parse tokens" );
            free( source );
            return EXIT_FAILURE;
        }

        for ( int i = 0; i < list->len; ++i )
        {
            struct Token_Token* token = Token_TokenList_get( list, i );
            
            if ( !token )
            {
                perror( "Could not get token" );
                Token_TokenList_destroy( list );
                return EXIT_FAILURE;
            }

            Token_Token_present( token );
        }

        Token_TokenList_destroy( list );
        free( source );
    }

    return EXIT_SUCCESS;
}