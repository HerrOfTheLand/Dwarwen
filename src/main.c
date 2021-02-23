#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"

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
        if ( puts( source ) == EOF )
        {
            perror( "Could not print source" );
            free ( source );
            return EXIT_FAILURE;
        }
        free( source );
    }

    return EXIT_SUCCESS;
}