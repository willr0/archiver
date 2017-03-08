//archive.c
//willroller

#include <stdio.h>
#include <string.h>
#include "prototypesC.h"
#include "constants.h"

int archiver(char *argv[], int argc){
    FILE *fi, *fo;
    char content, l, file[MAX];
    long length;
    int n=argc-3, i, size, j=0;
    
    fo=fopen(argv[2],"wb");
    fwrite(&n, 4, 1, fo);                                       //write number of files to 4 bytes
    
    for(i=3;i<argc;i++){
        strcpy(file, argv[i]);
        if((fi=fopen(file,"r"))==NULL){                         //error check
            printf("Error opening input file: %s\n", file);
            return 0;
        }
        
        size=sizeOf(fi);
        length=strlen(file);

        l=length;
        fwrite(&l, sizeof(char), 1, fo);                        //write file name length
        fwrite(&file[0], sizeof(char), length+1, fo);             //write file name
        fwrite(&size, 4, 1, fo);                                //write size of file
        for(j=0; j<size; j++){
            content=fgetc(fi);
            fwrite(&content, sizeof(char), 1, fo);               //write content
        }
        fclose(fi);
    }
    fclose(fo);
    return 0;
}

int unpacker(char *argv[]){
    FILE *fi, *fo;
    int n, i, j, length, size;
    char file[MAX], c;
    
    if((fi=fopen(argv[2], "rb"))==NULL){                        //error check
        printf("Error opening archive: %s", argv[2]);
        return(0);
    }
    
    fread(&n, 4, 1, fi);                                        //first byte = number of files
    
    for(i=0;i<n;i++){                                           //iterate through archive
        fread(&c, sizeof(char), 1, fi);
        length=c;
        fread(&file[0], sizeof(char), length+1, fi);
        file[length+1]='\0';
        fread(&size, 4, 1, fi);
        fo=fopen(file, "w");                                    //open individual file
        for(j=0;j<size;j++){
            fread(&c, sizeof(char), 1, fi);                     //write each file
            fprintf(fo, "%c", c);
        }
        fclose(fo);
    }
    fclose(fi);
    return 0;
}
