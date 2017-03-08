//main.c
//willroller

#include <stdio.h>
#include <string.h>
#include "prototypesA.h"
#include "prototypesB.h"


int main(int argc, char * argv[]) {
    if(strcmp(argv[1],"-a")==0){                    //archiver -a flag
        if(!(argc>=4)){
            printf("Too few arguments (-a requires at least 4)");
            return 0;
        }
        archiver(argv, argc);
    }
    else if(strcmp(argv[1],"-u")==0){               //unpacker -u flag
        if(argc!=3){
            printf("Too few arguments (-u requires exactly 3)");
            return 0;
        }
        unpacker(argv);
    }
    else if(strcmp(argv[1],"-l")==0){               //list -l flag
        if(argc!=3){
            printf("Too few arguments (-l requires exactly 3)");
            return 0;
        }

        list(argv);
    }
    else if(strcmp(argv[1],"-v")==0){               //verify -v flag
        if(!(argc>=4)){
            printf("Too few arguments (-v requires at least 4)");
            return 0;
        }
        verify(argv, argc);
    }
    else{
        printf("Flag not specified (-a -u -l -v)");
    }
    return 0;
}
