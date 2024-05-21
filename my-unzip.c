#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// Modify the parameter variables with values read from file
int readData(FILE* file, uint32_t *number, char *character) {
    // Read the integer
    if (fread(number, sizeof(uint32_t), 1, file) != 1) {
      fprintf(stderr, "my-unzip: error reading number from file\n");
      fclose(file);
      exit(1);
    }
    // End of file reached
		else if (*number == UINT32_MAX) {
			return 1;
		}

    // Read the character
    if (fread(character, sizeof(char), 1, file) != 1) {
    	fprintf(stderr, "my-unzip: error reading character from file\n");
      fclose(file);
      exit(1);
    }

    return 0;
}


int main(int argc, char* argv[]) {
	// Exit if no arguments given
	if (argc < 2) {
		printf("my-unzip: [file1 ...]\n");
		exit(1);
	}

	FILE* file = NULL;

	// Loop through each argument
	for (int i = 1; i < argc; i++) {
		// Try to open input file in binary mode
		file = fopen(argv[i], "rb");
		if (file == NULL) {
			fprintf(stderr, "my-unzip: cannot open input file\n");
			exit(1);
		}
		
		uint32_t sameInRow = 1;
		char character = ' ';
		
		// Read each file from file
		while(readData(file, &sameInRow, &character) == 0) {
			// Print character times equal to variable sameInRow
			for (int i = sameInRow; i > 0; i--) {
				printf("%c", character);
			}
		}
		fclose(file);
	}

	return 0;
}
