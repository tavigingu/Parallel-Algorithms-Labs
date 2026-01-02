#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000
#define MAX_LINES 1000000

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage: %s file1 file2\n", argv[0]);
		printf("Checks if all lines in file1 are present in file2\n");
		exit(1);
	}

	char *file1_name = argv[1];
	char *file2_name = argv[2];
	
	FILE *file1 = fopen(file1_name, "r");
	if (file1 == NULL) {
		printf("Error opening file: %s\n", file1_name);
		exit(1);
	}

	FILE *file2 = fopen(file2_name, "r");
	if (file2 == NULL) {
		printf("Error opening file: %s\n", file2_name);
		fclose(file1);
		exit(1);
	}

	// Read all lines from file2 into memory
	char **file2_lines = malloc(sizeof(char*) * MAX_LINES);
	int file2_count = 0;
	char line[MAX_LINE_LENGTH];
	
	while (fgets(line, MAX_LINE_LENGTH, file2) != NULL && file2_count < MAX_LINES) {
		// Remove trailing newline if present
		size_t len = strlen(line);
		if (len > 0 && line[len-1] == '\n') {
			line[len-1] = '\0';
		}
		file2_lines[file2_count] = malloc(strlen(line) + 1);
		strcpy(file2_lines[file2_count], line);
		file2_count++;
	}
	fclose(file2);

	// Check each line from file1
	int all_found = 1;
	int file1_line_num = 0;
	
	while (fgets(line, MAX_LINE_LENGTH, file1) != NULL) {
		file1_line_num++;
		// Remove trailing newline if present
		size_t len = strlen(line);
		if (len > 0 && line[len-1] == '\n') {
			line[len-1] = '\0';
		}
		
		// Search for this line in file2
		int found = 0;
		for (int i = 0; i < file2_count; i++) {
			if (strcmp(line, file2_lines[i]) == 0) {
				found = 1;
				break;
			}
		}
		
		if (!found) {
			all_found = 0;
			printf("Line %d from %s not found in %s: %s\n", 
			       file1_line_num, file1_name, file2_name, line);
		}
	}
	fclose(file1);

	// Free memory
	for (int i = 0; i < file2_count; i++) {
		free(file2_lines[i]);
	}
	free(file2_lines);

	if (all_found) {
		printf("All lines from %s are present in %s\n", file1_name, file2_name);
		return 0;
	} else {
		printf("Some lines from %s are NOT present in %s\n", file1_name, file2_name);
		return 1;
	}
}
