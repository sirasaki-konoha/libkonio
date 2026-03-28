#include <konio.h>
#include <stdio.h>
#include <stdlib.h>


void on_err(KResult r) {
	k_result_print(r);
	exit(EXIT_FAILURE);
}

void read_file(const char* path) {
	Reader reader;
	KResult res;

	K_CATCH(res,
			k_reader_new(&reader, path), 
			on_err(res));

	unsigned long total_len;
	k_reader_get_total_line(reader, &total_len);


	char* line = malloc(1);
	for (unsigned long index; index != total_len; index++) {
		free(line);
		K_CATCH(res,
				k_reader_getline(&reader, index - 1, &line),
				goto errclean);

		printf("%s", line);
	}

	free(line);

errclean:
	k_reader_free(&reader);
	on_err(res);
}


int main(int argc, const char** argv) {
	if (argc != 2) {
		printf("Usage: reader_cat <file>\n");
		return EXIT_FAILURE;
	}

	read_file(argv[1]);
}




