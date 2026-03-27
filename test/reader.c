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


	k_reader_free(&reader);

	printf("Makefile content: \n%s\n", content);

	free(content);
}

