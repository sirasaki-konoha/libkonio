#include "../konio.h"
#include "../kutil.h"
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


KResult k_reader_new(Reader *reader, const char *path) {
	KResult result;
	FILE* fp = fopen(path, "r");
	char buf[256];
	unsigned long line = 0;


	if (fp == NULL) {
		return k_result_from_errno(errno);
	}

	size_t capacity = 1024;
	reader->positions = malloc(sizeof(fpos_t) * capacity);

	while (1) {
		if (line >= capacity) {
			capacity *= 2;
			reader->positions = realloc(
					reader->positions, 
					sizeof(fpos_t) * capacity
			);
		}

		if (fgetpos(fp, &reader->positions[line]) != 0)
			break;

		if (!fgets(buf, sizeof(buf), fp))
			break;

		line++;
	}

	reader->path = safe_strdup(path);
	reader->file = fp;
	reader->line_count = line;

	result.code = K_OK;
	result.sys_errno = errno;
	return result;
}



KResult k_reader_read_all(Reader *r, char** out) {
    if (!r || !r->file || !out)
        return (KResult){K_ERR_INVALID_ARG, 0};

    if (fseek(r->file, 0, SEEK_END) != 0)
        return k_result_from_errno(errno);

    long size = ftell(r->file);
    if (size < 0)
        return k_result_from_errno(errno);

    rewind(r->file);

    *out = malloc((size_t)size + 1);
    if (!*out)
        return (KResult){K_ERR_NO_MEMORY, errno ? errno : ENOMEM};

    size_t read_size = fread(*out, 1, (size_t)size, r->file);
    if (read_size != (size_t)size) {
        free(*out);
        return k_result_from_errno(errno);
    }

    (*out)[size] = '\0';

    return (KResult){K_OK, 0};
}

KResult k_reader_getline(Reader *r, unsigned long line, char *out, size_t size) {
	if (!r || !r->file || !out) {
		return (KResult) {K_ERR_INVALID_ARG, 0};
	}

	if (line >= r->line_count) 
		return (KResult) {K_ERR_INVALID_ARG, 0};

	if (fsetpos(r->file, &r->positions[line]) != 0) {
		return k_result_from_errno(errno);
	}

	if (!fgets(out, size, r->file))
		return k_result_from_errno(errno);

	return (KResult) {K_OK, 0};
}


long unsigned int k_reader_get_total_line(Reader r) {
	return r.line_count;
}



void k_reader_free(Reader *r) {
	fclose(r->file);
	free(r->positions);
	free(r->path);
}






