//size.c
//willroller

#include <stdio.h>
#include <string.h>

int sizeOf(FILE *fi){
    
    fseek(fi, 0, SEEK_END);                                     //archive file size
    long b=ftell(fi);
    rewind(fi);
    
    return b;
}
