#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* inString;
char* subString;
int printLevel;

void getArgs(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: ./program <input_string> <sub_string> <printLevel>\n");
        exit(EXIT_FAILURE);
    }

    inString = argv[1];
    subString = argv[2];
    printLevel = atoi(argv[3]);
}

void init() {
    int inLen = strlen(inString);
    int subLen = strlen(subString);

    if (inLen == 0 || subLen == 0) {
        printf("Stringul de cautat sau substringul nu poate fi gol\n");
        exit(EXIT_FAILURE);
    }
}

void printFound(int found) {
    if (printLevel == 0) return;       
    else if (printLevel == 1) {
        if (found) printf("Substringul a fost gasit.\n");
        else printf("Substringul NU a fost gasit.\n");
    } else {                            
        printf("Input string: %s\n", inString);
        printf("Substring cautat: %s\n", subString);
        if (found) printf("Rezultat: substringul a fost gasit.\n");
        else printf("Rezultat: substringul NU a fost gasit.\n");
    }
}

int main(int argc, char** argv) {
    getArgs(argc, argv);
    init();

    int inLen = strlen(inString);
    int subLen = strlen(subString);
    int counter = 0;
    int found = 0;

    for (int i = 0; i < inLen; i++) {
        if (inString[i] == subString[counter]) {
            counter++;
            if (counter == subLen) {
                found = 1;
                break;
            }
        } else {
            counter = 0;
        }
    }

    printFound(found);

    return 0;
}
