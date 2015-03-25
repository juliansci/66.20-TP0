#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEndOfLine(char c) {
    if (c == '\n') {
        return 1;
    }
    return 0;
}

void concatBuffer(char** line, const char* buffer) {
    size_t len1 = *line ? strlen(*line) : 0;
    size_t len2 = buffer ? strlen(buffer) : 0;
    char *res = realloc(*line, len1 + len2 + 1);
    if (res) {
        memcpy(res + len1, buffer, len2 + 1);
        *line = res;
    }
}

int tacFile(char* fileName, char* outputFileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        return (EXIT_FAILURE);
    }

    FILE *resultFile;
    resultFile = fopen(outputFileName, "w");

    if (resultFile == NULL) {
        printf("Error opening file: %s!\n", outputFileName);
        exit(1);
    }

    char ** info = NULL;
    int lineLenght;
    int lineCounter = 0;
    const int bufIncrSize = 11;
    char buffer[bufIncrSize];
    char* line = (char *) calloc(bufIncrSize, sizeof (char));
    while (fgets(buffer, bufIncrSize, fp)) {
        concatBuffer(&line, buffer);
        char lastCharacterBuffer = buffer[strlen(buffer) - 1];
        if (isEndOfLine(lastCharacterBuffer)) {
            info = realloc(info, (lineCounter + 1) * sizeof (char *));
            lineLenght = strlen(line);
            info[lineCounter] = calloc(sizeof (char), lineLenght + 1);
            strcpy(info[lineCounter], line);
            lineCounter++;
            line = (char *) calloc(bufIncrSize, sizeof (char));
        }
    }

    int i;
    for (i = lineCounter - 1; i >= 0; i--) {
        fprintf(resultFile, "%s", info[i]);
    }

    fclose(fp);
    fclose(resultFile);

    return (EXIT_SUCCESS);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("%s", "Faltan parametros\n");
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

    char* outputFileName;

    if (argc >= 3) {
        outputFileName = argv[2];
    } else {
        outputFileName = "output/resultFile.txt";
    }

    int result = tacFile(argv[1], outputFileName);
    return (result);
}

//prueba commit

