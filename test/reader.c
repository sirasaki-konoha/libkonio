#include <konio.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Reader reader;
  KResult result;
  char* content;

	K_CATCH(result, 
			k_reader_new(&reader, "Makefile.am"),
			return result.sys_errno);

	// allocate new memory buffer in k_reader_read_all
	// requires free after use
	K_WRAP(k_reader_read_all(&reader, &content), 
			cleanup);

  printf("Makefile.am content: \n%s\n", content);
	free(content);

  unsigned long total_len;
	k_reader_get_total_line(reader, &total_len);
  printf("total lines = %lu\n", total_len);

  char* line_1 = NULL;

  K_WRAP(k_reader_getline(&reader, total_len - 1, &line_1), cleanup);

  printf("Makefile.am:1: %s\n", line_1);

  free(line_1);
	goto cleanup;

cleanup:
	k_reader_free(&reader);
	return result.sys_errno;
}
