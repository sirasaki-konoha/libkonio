#ifndef _LIB_KONIO_H
#define _LIB_KONIO_H

#include <dirent.h>
#include <stdio.h>
#include <kcore.h>


typedef enum {
  APPEND,
  NEW,
} WriteType;

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
