#include <stdio.h>
#include <konio.h>
#include <stdlib.h>


int main() {
	Reader reader;
	KResult result;
	char* content;

	result = k_reader_new(&reader, "test.sh");
	if (K_FAILED(result)) {
		k_result_print(result);
		return -1;
	}

	result = k_reader_read_all(&reader, &content);
	if (K_FAILED(result)) {
		k_reader_free(&reader);
		k_result_print(result);
		return -1;
	}

	printf("test.sh content: \n%s\n", content);

	unsigned long total_len = k_reader_get_total_line(reader);
	char* line_13 = malloc(255);

	result = k_reader_getline(&reader, total_len - 1, line_13, sizeof(char) * 255);
	if (K_FAILED(result)) {
		k_reader_free(&reader);
		k_result_print(result);
		return -1;
	}
	
	printf("test.sh:13: %s\n", line_13);

	free(line_13);
	k_reader_free(&reader);
	free(content);
}

