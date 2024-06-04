#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	// Return 0 if no arguments given
	if (argc < 2) {
		return 0;
	}

	// Initialize variables
	FILE* file = NULL;
	char* line = NULL;
	size_t lineSize = 0;

	// Loop through each argument
	for (int i = 1; i < argc; i++) {
		// Try to open file
		file = fopen(argv[i], "r");
		if (file == NULL) {
			// Test did not pass with stderr
			fprintf(stdout, "wcat: cannot open file\n");
			free(line);
			exit(1);
		}
		
		// Loop through each line and print them to the shell
		while (getline(&line, &lineSize, file) > 0) {
			printf("%s", line);
		}
		
		fclose(file);
	}

	// Free the line memory allocated by getline and close file
	free(line);
	
	return 0;
}
