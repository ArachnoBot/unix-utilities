#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// Write the parameter values to the file using fwrite
void writeData(uint32_t count, char character) {
    // Write the integer
    if (fwrite(&count, sizeof(uint32_t), 1, stdout) != 1) {
      fprintf(stderr, "my-zip: error writing number to file\n");
      exit(1);
    }

    // Write the character
    if (fwrite(&character, sizeof(char), 1, stdout) != 1) {
      fprintf(stderr, "my-zip: error writing character to file\n");
      exit(1);
    }
    
	return;
}


int main(int argc, char* argv[]) {
	// Return 0 if no arguments given
	if (argc < 2) {
		printf("my-zip: file1 [file2 ...]\n");
		exit(1);
	}

	// Initialize variables
	FILE* file = NULL;
	char* line = NULL;
	size_t lineSize = 0;

	// Loop through each argument
	for (int i = 1; i < argc; i++) {
		// Try to open input file
		file = fopen(argv[i], "r");
		if (file == NULL) {
			fprintf(stderr, "my-zip: cannot open input file\n");
			free(line);
			exit(1);
		}
		
		// Initialize sameInRow to one as each letter appears at least once
		uint32_t sameInRow = 1;
		
		// Read each line from file
		while (getline(&line, &lineSize, file) > 0) {
			// Read each letter from file
			for (int i = 0; i < strlen(line); i++) {
				// If next letter is the same, increment counter and go to next letter
				if (line[i] == line[i + 1]) {
					sameInRow++;
					continue;
				}
				// If next letter is different and letters were in row, write data
				else if (sameInRow > 1) {
					writeData(sameInRow, line[i]);
					sameInRow = 1;
				}
				// Otherwise just write the single letter
				else {
					writeData(sameInRow, line[i]);
				}
			}
		}
		fclose(file);
	}

	// Write max value to signal end of file
	writeData(UINT32_MAX, line[0]);

	// Free the line memory allocated by getline
	free(line);
	
	return 0;
}
