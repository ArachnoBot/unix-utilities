#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	// Check if number of arguments is invalid
	if (argc < 2) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	} 
	
	// Get search term from arguments
	char* searchTerm = argv[1];

	// Initialize variables
	FILE* file = NULL;
	char* line = NULL;
	size_t lineSize = 0;

	// Read user input if only search term given
	if (argc < 3) {
		while (getline(&line, &lineSize, stdin) > 1) {
			// Check if substring is included in line
			if (strstr(line, searchTerm) != NULL) {
                                printf("%s", line);
			}
		}
	} else {
		for (int i = 2; i < argc; i++) {
			// Try to open file
			file = fopen(argv[i], "r");	
			if (file == NULL) {
				// Test did not pass with stderr
				fprintf(stdout, "wgrep: cannot open file\n");
				free(line);
				exit(1);
			}
			// Loop through each line and print them to the shell
			while (getline(&line, &lineSize, file) > 0) {
				// Check if substring is included in line
				if (strstr(line, searchTerm) != NULL) {
					printf("%s", line);
				}
			}
		}
		fclose(file);
	}

	// Free the line memory allocated by getline
	free(line);
	
	return 0;
}
