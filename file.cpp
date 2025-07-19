#include <iostream>
#include <fstream>
#include <string>


int main(void) {
    FILE * pfile;
    char* buffer;
    size_t result;
    pfile = fopen("hehe.txt", "r");

    if (pfile == NULL) {
        std::cout << "File doesn't exist" << std::endl; exit(1);
    }
    else {
        fseek(pfile, 0, SEEK_END);
        long size = ftell(pfile);
        rewind(pfile);

        buffer = (char*) malloc(sizeof(char)*size);
        if (buffer == NULL) {
            std::cout << "memory error"; exit(2);
        }

        while (fread(buffer,1,size/2,pfile) == size/2) {
            std::cout << buffer<< std::endl;
        }
  //if (result != size) {fputs ("Reading error",stderr); exit (3);}
    }


    fclose(pfile);
    free(buffer);
}