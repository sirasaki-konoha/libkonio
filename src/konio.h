#ifndef _LIB_KONIO_H
#define _LIB_KONIO_H

#include <dirent.h>
#include <stdio.h>

#define K_FAILED(r) ((r).code != K_OK)
#define K_SUCCEEDED(r) ((r).code == K_OK)

#define K_WRAP(expr, label) \
  do {                      \
    KResult _r = (expr);    \
    if (_r.code != K_OK) {  \
      k_result_print(_r);   \
      goto label;           \
    }                       \
  } while (0)

#define K_WRAP_OR_GOTO(expr_call, on_error, label) \
  do {                                             \
    KResult _r = (expr_call);                      \
    if (_r.code != K_OK) {                         \
      on_error;                                    \
      goto label;                                  \
    }                                              \
  } while (0)

#define K_CATCH(res, expr_call, on_error) \
  do {                                    \
    (res) = (expr_call);                  \
    if ((res).code != K_OK) {             \
      on_error;                           \
    }                                     \
  } while (0)


typedef enum {
  APPEND,
  NEW,
} WriteType;

typedef enum {
  K_OK = 0,
  K_ERR_FILE_NOT_FOUND = 1,
  K_ERR_PERMISSION,
  K_ERR_IS_DIRECTORY,
  K_ERR_NO_SPACE,
  K_ERR_NO_MEMORY,
  K_ERR_INVALID_ARG,
  K_ERR_IO,
  K_ERR_ALREADY_OPEN,
  K_ERR_NOT_OPEN,
  K_ERR_UNKNOWN,
} K_RESULT;

typedef struct {
  K_RESULT code;
  int sys_errno;
} KResult;

typedef struct {
  FILE* file;
  char* path;
  WriteType type;
} Writer;

typedef struct {
  FILE* file;
  char* path;
  fpos_t* positions;
  unsigned long line_count;
} Reader;

typedef struct {
  const char* path;
  DIR* dir;
} Directory;

/* Utility */
KResult k_result_from_errno(int err);
const char* k_result_str(KResult result);
void k_result_print(KResult r);

/* Writer */
KResult k_writer_new(Writer* wt, const char* path, WriteType type);
KResult k_writer_append(Writer* wt, char* content);
KResult k_writer_clear(Writer* wt);
KResult k_writer_flush(Writer* wt);
void k_writer_free(Writer* wt);

/* Reader */
KResult k_reader_new(Reader* reader, const char* path);
KResult k_reader_read_all(Reader* r, char** out);
KResult k_reader_getline(Reader* r, unsigned long index, char** out);
KResult k_read_to_string(const char* path, char** out);
void k_reader_get_total_line(Reader r, unsigned long* len);
void k_reader_free(Reader* r);

/* Directory */
KResult k_dir_open(Directory* dir, const char* path);
KResult k_dir_next(Directory dir);
KResult k_dir_prev(Directory* dir);
KResult k_dir_free(Directory* dir);

/* delete/move */
KResult k_delete_file(const char* path);
KResult k_delete_directory(const char* path, int recursive);
KResult k_move(const char* src, const char* dist);

#endif /* _LIB_KONIO_H */
