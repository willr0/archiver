//tools.c
//willroller

#include <stdio.h>
#include <string.h>
#include "prototypesC.h"
#include "constants.h"

int list(char *argv[]){
    FILE *fi;
    int i, n, size, length, fileSize;
    char c, file[MAX], buffer;
    
    if((fi=fopen(argv[2], "rb"))==NULL){                        //error check
        printf("Error opening archive: %s", argv[2]);
        return(0);
    }
    
    size=sizeOf(fi);
    fread(&n, 4, 1, fi);                                        //first byte = number of files
    
    printf("Total size of archive: %d\nNumber of files in archive: %d\nFiles in archive:\n", size, n);
    
    for(i=0;i<n;i++){                                           //iterate through archive
        fread(&c, sizeof(char), 1, fi);
        length=c;
        fread(&file[0], sizeof(char), length+1, fi);
        file[length+1]='\0';
        fread(&fileSize, 4, 1, fi);
        printf("%s %d\n", file, fileSize);                      //print results
        fread(&buffer, sizeof(char), fileSize, fi);             //skip fileSize bytes
    }
    fclose(fi);
    return 0;
}

int verify(char *argv[], int argc){
    FILE *fi, *arc;
    char file[MAX], Afile[MAX], Acontent, content;
    unsigned int a;
    int n=argc-3, x=0, i, s, length=0, size=0, An, Alength, Asize=0, Ab, y=0, j;
    
    if((arc=fopen(argv[2], "rb"))==NULL){
        printf("Error opening archive: %s", argv[2]);           //error check
        return(0);
    }
    Ab=sizeOf(arc);
    
    fread(&a, 4, 1, arc);                                       //number of files in archive
    An=a;
    
    for(i=3;i<argc;i++){
        char c;
        strcpy(file, argv[i]);
        if((fi=fopen(file, "r"))==NULL){                        //error check
            printf("Error opening input file: %s", file);
            return 0;
        }
        
        length=strlen(file);                                    //gather info from input
        fseek(fi, 0, SEEK_END);
        s=ftell(fi);
        rewind(fi);
        size+=s;
        
        fclose(fi);
        
        fread(&c, sizeof(char), 1, arc);
        Alength=c;
        fread(&Afile[0], sizeof(char), Alength+1, arc);
        Afile[Alength+1]='\0';
        if(strcmp(file, Afile)!=0){                             //archive names = file names
            y++;
        }
        fread(&Asize, 4, 1, arc);
        while((content=fgetc(fi))!=EOF){
            for(j=0;j<size;j++){
                fread(&Acontent, 1, 1, arc);
                if(Acontent!=content){                       //archive = files
                    y++;
                }
            }
        }
        fseek(arc, Asize, SEEK_CUR);
        

        x+=length+1;                                              //increment length
    }
    
    x= x+4+n+(4*n)+size;                                        //total file size
    if(Ab<x){                                                  //archive has less bytes than files
        printf("%s is missing %i bytes.\n", argv[2], x-Ab);
    }
    else if(x<=Ab){                                         //archive has right number of bytes and files
        if(y==0){                                               //archive matches
            printf("%s verified.\n", argv[2]);
        }
        else{                                                   //archive data is not 100%
            printf("%s is corrupted.\n", argv[2]);
        }
    }
    fclose(arc);
    return 0;
}
