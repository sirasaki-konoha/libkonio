#include <stdio.h>
#include <konio.h>
#include <stdlib.h>


int main() {
	Reader reader;
	KResult result;
	char* content;

	result = k_reader_new(&reader, "Makefile.am");
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

	printf("Makefile.am content: \n%s\n", content);

	unsigned long total_len = k_reader_get_total_line(reader);
	printf("total lines = %lu\n", total_len);

	char* line_1 = malloc(255);

	result = k_reader_getline(&reader, total_len - 1, line_1, sizeof(char) * 255);
	if (K_FAILED(result)) {
		k_reader_free(&reader);
		k_result_print(result);
		return -1;
	}
	
	printf("Makefile.am:1: %s\n", line_1);

	free(line_1);
	k_reader_free(&reader);
	free(content);
}

