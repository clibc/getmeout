#ifndef FILE_HPP
#define FILE_HPP

#include <stdio.h>
#include <stdlib.h>

#define FILE_DESC file
#define FILE_NAME "output.asm"
#define fput( ... ) fprintf( FILE_DESC, __VA_ARGS__ )

static FILE* FILE_DESC;

char* read_entire_file( const char*, int* );

void init_file() {
    FILE_DESC = fopen( FILE_NAME, "w" );
}

char* load_file( char* file_name ) {
    int size;
    return read_entire_file( file_name, &size );
}

void close_file() {
    fclose( FILE_DESC );
}

void compile_file() {
    system( "nasm -felf64 output.asm" );
    system( "ld -o output.out output.o" );
}

char* read_entire_file( const char* filePath, int* size ) {
    char* Buffer;
    int Size   = 0;
    FILE* File = fopen( filePath, "r" );

    if ( File ) {
        fseek( File, 0, SEEK_END );
        Size = ftell( File );
        rewind( File );
        Buffer = (char*)malloc( ( sizeof( char ) * Size ) + 1 );
        fread( Buffer, sizeof( char ), Size, File );
        Buffer[Size] = '\0';
    } else {
        printf( "File is not found: %s", filePath );
        exit( 1 );
    }
    *size = Size;
    return Buffer;
}

#endif  // FILE_HPP
