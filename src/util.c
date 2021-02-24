#include "../include/util.h"

#include <stdio.h>
#include <stdlib.h>


extern char*
Util_read_ascii_file ( const char* path )
{
    FILE* file = fopen( path, "r" );

    if ( !file )
    {
        perror( "Could not open file");
        return NULL;
    }

    if ( fseek( file, 0, SEEK_END ) )
    {
        perror( "Fseek error" );
        fclose( file );
        return NULL;
    }

    long file_size = ftell( file );

    if ( fseek( file, 0, SEEK_SET ) )
    {
        perror( "Fseek error" );
        fclose( file );
        return NULL;
    }

    char* buf = (char*)calloc( file_size, sizeof( char ) );

    if ( !buf )
    {
        perror( "Cound not allocate memory for file" );
        fclose( file );
        return NULL;
    }

    if ( fread( buf, 1, file_size, file ) != (size_t)file_size )
    {
        perror( "Could not read file" );
        fclose( file );
        return NULL;
    }

    fclose( file );
    return buf;
}