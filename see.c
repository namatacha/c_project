#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define max_len 4096

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <FILENAME>\n", argv[0]);
		return 1;
	}

	char output_text[max_len];
	FILE *fptr;
	struct stat path_stat;

	for (int i = 1; argv[i] != NULL; i++) {
		if (stat(argv[i], &path_stat) != 0) {
			fprintf(stderr, "'%s': No such file or directory!\n", argv[i]);
			continue;
		}

		if (S_ISDIR(path_stat.st_mode)) {
			fprintf(stderr, "'%s' is a directory\n", argv[i]);
			continue;
		}
		fptr = fopen(argv[i], "r");

		if (fptr == NULL) {
			fprintf(stderr, "File '%s' not found!\n", argv[i]);
			continue;
		}
		while (fgets(output_text, sizeof(output_text), fptr)) {
			printf("%s", output_text);
		}
		fclose(fptr);
	}
	return 0;
}
