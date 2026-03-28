#include "konio.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Writer wt;
  KResult result;

	// Initialize
	K_CATCH(result, 
			k_writer_new(&wt, "MyNewFile", NEW),
			exit(result.sys_errno);
	);

	// Create new file and write to file
	printf("Writing file (Create new file: MyNewFile)\n");
	K_WRAP(k_writer_append(&wt, "Hello, World!\n"), cleanup);
	K_WRAP_OR_GOTO(
			k_writer_flush(&wt), 
			fprintf(stderr, "Failed to flush file\n"), 
			cleanup);
	printf("Write and Flush done\n");


	// Check write result
	char* content;
	K_WRAP(k_read_to_string("MyNewFile", &content), 
			cleanup);

	printf("MyNewFile content: %s\n", content);
	free(content);

	// Append test
	k_writer_free(&wt);
	// Initialize in append mode
	K_CATCH(result, 
			k_writer_new(&wt, "MyNewFile", APPEND),
			exit(result.sys_errno)
	);

	printf("Writing file in append mode\n");
	K_WRAP(
			k_writer_append(&wt, "This is appended text\n"), 
			cleanup
	);
	printf("Flush done\n");
	K_WRAP(
			k_writer_flush(&wt), 
			cleanup
	);

	K_WRAP(k_read_to_string("MyNewFile", &content), 
			cleanup);

	// Check content
	printf("MyNewFile content: %s\n", content);

	goto cleanup;

cleanup:
	free(content);
	k_writer_free(&wt);
}

