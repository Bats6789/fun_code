/*
 * Name: CBW_FileTools.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A collection of tools for manipulating files.
 * Vers: 1.0.0 08/10/2020 CBW - Original code.
 */

#include "CBW_FileTools.h"

int CBW_FileReadLine( FILE *file, char *line ){
    int count = 0;
    char chunk = '\0';
    while( fscanf( file, "%c", &chunk ) != EOF && chunk != '\n' ){
        line[ count ] = chunk;
        ++count;
    }
    line[ count ] = '\0';

    return( count );
}
