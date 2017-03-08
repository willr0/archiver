archiver:  main.o archive.o tools.o
    gcc main.o archive.o tools.o -o archiver
main.o: main.c
    gcc -c main.c
archive.o: archive.c
    gcc -c archive.c
tools.o: yools.c
    gcc -c tools.c

clean:
    rm *.o
