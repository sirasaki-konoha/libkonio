#include <stdio.h>
#include <konio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	Reader reader;
	KResult result;
	char* content;

	result = k_reader_new(&reader, "test.sh");

	k_reader_read_all(&reader, &content);
	k_reader_free(&reader);

	printf("Makefile content: \n%s\n", content);

	free(content);
}

