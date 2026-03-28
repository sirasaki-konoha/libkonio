#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../konio.h"
#include "../kutil.h"

KResult k_reader_new(Reader *reader, const char *path) {
  KResult result;
  FILE *fp = fopen(path, "r");
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
      reader->positions = realloc(reader->positions, sizeof(fpos_t) * capacity);
    }

    if (fgetpos(fp, &reader->positions[line]) != 0) break;

    if (!fgets(buf, sizeof(buf), fp)) break;

    line++;
  }

  reader->path = safe_strdup(path);
  reader->file = fp;
  reader->line_count = line;

  result.code = K_OK;
  result.sys_errno = errno;
  return result;
}

KResult k_reader_read_all(Reader *r, char **out) {
  if (!r || !r->file || !out) return (KResult){K_ERR_INVALID_ARG, 0};

  if (fseek(r->file, 0, SEEK_END) != 0) return k_result_from_errno(errno);

  long size = ftell(r->file);
  if (size < 0) return k_result_from_errno(errno);

  rewind(r->file);

  *out = malloc((size_t)size + 1);
  if (!*out) return (KResult){K_ERR_NO_MEMORY, errno ? errno : ENOMEM};

  size_t read_size = fread(*out, 1, (size_t)size, r->file);
  if (read_size != (size_t)size) {
    free(*out);
    return k_result_from_errno(errno);
  }

  (*out)[size] = '\0';

  return (KResult){K_OK, 0};
}

KResult k_reader_getline(Reader *r, size_t index, char **out) {
    if (!r || !r->file || !out)
        return (KResult){K_ERR_INVALID_ARG, 0};

    if (index >= r->line_count)
        return (KResult){K_ERR_INVALID_ARG, 0};

    if (!r->positions)
        return (KResult){K_ERR_INVALID_ARG, 0};

    if (fsetpos(r->file, &r->positions[index]) != 0)
        return k_result_from_errno(errno);

    size_t cap = 128;
    size_t len = 0;
    char* buf = malloc(cap);
    if (!buf)
        return (KResult){K_ERR_NO_MEMORY, errno};

    int c;
    while ((c = fgetc(r->file)) != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char* tmp = realloc(buf, cap);
            if (!tmp) {
                free(buf);
                return (KResult){K_ERR_NO_MEMORY, errno};
            }
            buf = tmp;
        }

        buf[len++] = (char)c;

        if (c == '\n')
            break;
    }

    if (len == 0 && c == EOF) {
        free(buf);
        return (KResult){K_ERR_IO, 0};
    }

    buf[len] = '\0';
    *out = buf;

    return (KResult){K_OK, 0};
}

void k_reader_get_total_line(Reader r, unsigned long* len) { *len = r.line_count; }

void k_reader_free(Reader *r) {
  fclose(r->file);
  free(r->positions);
  free(r->path);
}


KResult k_read_to_string(const char *path, char **out) {
	Reader reader;
	KResult res = (KResult) {K_OK, 0};
	
	K_CATCH(res, 
			k_reader_new(&reader, path), 
			return res
	);

	K_CATCH(res,
			k_reader_read_all(&reader, out), 
			goto cleanup
	);

	goto cleanup;

cleanup:
	k_reader_free(&reader);
	return res;
}
