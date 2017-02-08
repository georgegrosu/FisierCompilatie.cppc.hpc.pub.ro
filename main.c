//
//  main.c
//  Fisier Compilatie
//
//  Created by George Mircea on 2/7/17.
//  Copyright © 2017 Grosu George-Mircea. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char **compilationFileName;
    char lineRead[512];
    long endOfFile;
    int filesNumber=0, currentLine=0, currentFile;
    int startLine, linesNumber, i;
    
    if ( argc > 1) {
        
        FILE *listFile = fopen( argv[1], "rt");
        if ( listFile == NULL) {
            exit( -1);
        }

        compilationFileName = malloc( sizeof(char *) );
        compilationFileName[0] = malloc( strlen( argv[1]) + 4 * sizeof(char) + 1);
        if ( compilationFileName == NULL && compilationFileName[0] == NULL) {
            exit( -1);
        }
        
        strcpy( compilationFileName[0], argv[1]);
        strcat( compilationFileName[0], ".cpl");
        
        printf( "%s\n", compilationFileName[0]);
        
        FILE *compilationFile = fopen( compilationFileName[0], "wt");
        if ( compilationFile == NULL) {
            exit( -1);
        }
        
        free( compilationFileName[0]);
        free( compilationFileName);
        
        compilationFileName = malloc( sizeof(char *));
        
        if ( compilationFileName == NULL) {
            exit( -1);
        }
        
        fseek( listFile, 0, SEEK_END);
        endOfFile = ftell( listFile);
        fseek( listFile, 0, SEEK_SET);
        
        while ( ftell( listFile) != endOfFile) {
            
            fscanf( listFile, "%s %d %d", compilationFileName[ filesNumber ], &startLine,
                   &linesNumber);
            
            currentFile = filesNumber;
            
            for ( i=0; i < filesNumber; i++) {
<<<<<<< HEAD
                if ( ! strcmp( compilationFileName[i], compilationFileName[filesNumber]) ) {
                    strcpy( compilationFileName[filesNumber], " ");
                    filesNumber--;
                    currentFile = i;
				printf( "da\n");
=======
                if ( compilationFileName[i] == compilationFileName[filesNumber]) {
                    strcpy( compilationFileName[filesNumber], "");
                    filesNumber--;
                    currentFile = i;
>>>>>>> 8accaead283a420308ce8bb0a4eb1a3462651331
                    break;
                }
            }
            
<<<<<<< HEAD
           if ( i == filesNumber ) {
				printf( "da\n");
=======
            if ( i == filesNumber ) {
>>>>>>> 8accaead283a420308ce8bb0a4eb1a3462651331
                filesNumber++;
                compilationFileName = realloc( compilationFileName, (filesNumber + 1) * sizeof(char *));
                if ( compilationFileName == NULL) {
                    exit( -1);
                }
            }
            
            FILE *sourceFile = fopen( compilationFileName[ currentFile ], "rt");
            if ( sourceFile == NULL) {
                exit( -1);
            }
            
            currentLine = 1;
            
            while ( fgets( lineRead, 512, sourceFile)) {
<<<<<<< HEAD
                if ( currentLine >= startLine && currentLine < startLine + linesNumber) {
=======
                if ( currentLine >= startLine && currentLine <= startLine + linesNumber) {
>>>>>>> 8accaead283a420308ce8bb0a4eb1a3462651331
                    fprintf( compilationFile, "%s", lineRead);
                }
                currentLine ++;
            }
            
            fclose( sourceFile);
<<<<<<< HEAD
            //filesNumber++;
        }
        
        printf( "Fisiere folosite: %d\n", filesNumber);
        
=======
        }
        
>>>>>>> 8accaead283a420308ce8bb0a4eb1a3462651331
        fclose( listFile);
        fclose( compilationFile);
    }
    else {
        printf( "Introduceti numele catalogului!\n");
    }
    return 0;
}
