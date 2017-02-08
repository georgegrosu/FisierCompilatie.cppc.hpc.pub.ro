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

#define INTS 8

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
        
        while ( endOfFile - ftell( listFile) > INTS) {

            fscanf( listFile, "%s %d %d", lineRead, &startLine, &linesNumber);
            
            currentFile = filesNumber;
            
			compilationFileName[ filesNumber ] = malloc( strlen( lineRead + 1 ));

			strcpy( compilationFileName[ filesNumber ], lineRead);
            
            //printf("%s\n", compilationFileName[filesNumber]);

            for ( i=0; i < filesNumber; i++) {
                if ( ! strcmp( compilationFileName[i], compilationFileName[ currentFile ]) ) {
					free( compilationFileName[ filesNumber ]);
                    //compilationFileName[ filesNumber ] = NULL;
                    filesNumber--;
                    currentFile = i;
                    break;
                }
            }
            
           filesNumber++;

           if ( i == filesNumber ) {
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
                if ( currentLine >= startLine && currentLine < startLine + linesNumber) {
                    fprintf( compilationFile, "%s", lineRead);
                }
                currentLine ++;
            }
            
            fclose( sourceFile);
        }

		for( i=0; i < filesNumber; i++ ) {
            //compilationFileName[i] = malloc(1);
            if ( compilationFileName[i] != NULL) {
                free( compilationFileName[i]);
            }
        }

		free( compilationFileName);
        
        printf( "Fisiere folosite: %d\n", filesNumber);
        
        fclose( listFile);
        fclose( compilationFile);
    }
    else {
        printf( "Introduceti numele catalogului!\n");
    }
    return 0;
}
