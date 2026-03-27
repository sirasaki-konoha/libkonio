#include "../konio.h"
#include "../kutil.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


KResult k_reader_new(Reader *reader, const char *path) {
	FILE* fp = fopen(path, "r");
	KResult result;

	if (fp == NULL) {
		return k_result_from_errno(errno);
	}

	reader->path = path;
	reader->file = fp;

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










