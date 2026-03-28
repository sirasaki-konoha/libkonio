#include <konio.h>
#include <stdio.h>
#include <stdlib.h>

void on_error(KResult res) {
	exit(res.sys_errno);
}

void write_to_file(const char* path, const char* content) {
	Writer wt;
	KResult res;

	// On error, execute on_error function
	K_CATCH(res, 
			k_writer_new(&wt, path, NEW),
			on_error(res));

	// On error, outputs error message and execute `goto cleanup`
	K_WRAP(k_writer_append(&wt, (char*)content),
			cleanup);

cleanup:
	k_writer_free(&wt);
}

int main(int argc, const char** argv) {
	printf("Argc: %d\n", argc);
	if (argc != 3) {
		printf("Usage: write_file <file> <content>\n");
		return 1;
	}

	const char* path = argv[1];
	const char* content = argv[2];

	write_to_file(path, content);
}





