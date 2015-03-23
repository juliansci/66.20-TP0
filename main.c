#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEndOfLine(char c) {
    if (c == '\n') {
        return 1;
    }
    return 0;
}

int isInResizeLine(int counterCharacterLine, int characterLineSize) {
    if (counterCharacterLine + 1 >= characterLineSize) {
        return 1;
    }
    return 0;
}

int isInResizeLines(int counterLines, int allLinesSize) {
    if (counterLines + 1 >= allLinesSize) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return (EXIT_FAILURE);
    }
    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
	printf("%s", "Usage:\n");
	printf("%s", "	tp0 -h\n");
	printf("%s", "	tp0 -V\n");
	printf("%s", "	tp0 [file...]\n");
	printf("%s", "Options:\n");
	printf("%s", "	-V, --version Print version and quit.\n");
	printf("%s", "	-h, --help Print this information and quit.\n");
	printf("%s", "Examples:\n");
	printf("%s", "	tp0 foo.txt bar.txt\n");
	printf("%s", "	tp0 gz.txt\n");
	return (EXIT_SUCCESS);
    }
    if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0)) {
	printf("%s", "Falta agregar información sobre la versión.\n");
	return (EXIT_SUCCESS);
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return (EXIT_FAILURE);
    }
    int allLinesSize = 2;
    char** arrayLines = (char**) malloc(sizeof (char*) * allLinesSize);
    int counterLines = 0;
    int initCharacterLineSize = 10;
    int characterLineSize = 10;
    char* line = malloc(initCharacterLineSize);
    char character;
    int counterCharacterLine = 0;
    while ((character = fgetc(fp)) != EOF) {
        line[counterCharacterLine] = character;
        counterCharacterLine++;
        if (isInResizeLine(counterCharacterLine, characterLineSize)) {
            characterLineSize *= 2;
            line = realloc(line, characterLineSize);
        }
        if (isEndOfLine(character)) {
            if (isInResizeLines(counterLines, allLinesSize)) {
                allLinesSize *= 2;
                arrayLines[allLinesSize];
                arrayLines = (char**) realloc(arrayLines, sizeof (char*) * allLinesSize);
            }
            arrayLines[counterLines] = line;
            characterLineSize = initCharacterLineSize;
            line = malloc(characterLineSize);
            counterLines++;
            counterCharacterLine = 0;
        }
    }
    counterLines--;
    for (counterLines; counterLines >= 0; counterLines--) {
        printf("%s", arrayLines[counterLines]);
    }

    fclose(fp);
    return (EXIT_SUCCESS);

}

