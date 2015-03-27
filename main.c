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
	char* concat = realloc(*line, len1 + len2 + 1);
	if (concat) {
		memcpy(concat + len1, buffer, len2 + 1);
		*line = concat;
	}
}

int tacFile(FILE* fp, char* outputFileName) {

	FILE *resultFile;
	resultFile = fopen(outputFileName, "w");

	if (resultFile == NULL) {
		printf("Error opening file: %s!\n", outputFileName);
		exit(1);
	}

	char ** arrayLines = NULL;
	int lineLenght;
	int lineCounter = 0;
	const int bufIncrSize = 11;
	char buffer[bufIncrSize];
	char* line = (char *) calloc(bufIncrSize, sizeof(char));
	while (fgets(buffer, bufIncrSize, fp)) {
		concatBuffer(&line, buffer);
		char lastCharacterBuffer = buffer[strlen(buffer) - 1];
		if (isEndOfLine(lastCharacterBuffer)) {
			arrayLines = realloc(arrayLines,
					(lineCounter + 1) * sizeof(char *));
			lineLenght = strlen(line);
			arrayLines[lineCounter] = calloc(sizeof(char), lineLenght + 1);
			strcpy(arrayLines[lineCounter], line);
			lineCounter++;
			line = (char *) calloc(bufIncrSize, sizeof(char));
		}
	}

	int i;
	for (i = lineCounter - 1; i >= 0; i--) {
		fprintf(resultFile, "%s", arrayLines[i]);
	}

	fclose(resultFile);

	return (EXIT_SUCCESS);
}

int main(int argc, char** argv) {
	FILE *fp;

	char* outputFileName;
	if (argc >= 3) {
		outputFileName = argv[2];
	} else {
		outputFileName = "output/resultFile.txt";
	}

	int hasInputFile;

	if (argc > 1) {
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
		if ((strcmp(argv[1], "-V") == 0)
				|| (strcmp(argv[1], "--version") == 0)) {
			printf("%s", "Falta agregar información sobre la versión.\n");
			return (EXIT_SUCCESS);
		}

		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			return (EXIT_FAILURE);
		}
		hasInputFile = 1;

	} else {
		fp = stdin;
		hasInputFile = 0;
	}
	int result = tacFile(fp, outputFileName);
	if (hasInputFile == 1) {
		fclose(fp);
	}
	return (result);
}

//prueba commit

