#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../kutil.h"
#include "konio.h"

KResult k_writer_new(Writer *wt, const char *path, WriteType type) {
  if (!wt || !path) return (KResult){K_ERR_INVALID_ARG, 0};

  const char *mode;

  switch (type) {
    case NEW:
      mode = "w";
      break;
    case APPEND:
      mode = "a";
      break;
    default:
      return (KResult){K_ERR_INVALID_ARG, 0};
  }

  FILE *fp = fopen(path, mode);
  if (!fp) return k_result_from_errno(errno);

  wt->path = safe_strdup(path);
  if (!wt->path) {
    fclose(fp);
    return (KResult){K_ERR_NO_MEMORY, errno ? errno : ENOMEM};
  }

  wt->file = fp;
  wt->type = type;

  return (KResult){K_OK, 0};
}

KResult k_writer_flush(Writer *wt) {
  if (!wt) return (KResult){K_ERR_INVALID_ARG, 0};

  if (fflush(wt->file) != 0) {
    return k_result_from_errno(errno);
  }

  return (KResult){K_OK, 0};
}

KResult k_writer_append(Writer *wt, char *content) {
  if (!wt || !wt->file || !content) return (KResult){K_ERR_INVALID_ARG, 0};

  if (fputs(content, wt->file) == EOF) return k_result_from_errno(errno);

  return (KResult){K_OK, 0};
}

KResult k_writer_clear(Writer *wt) {
  fclose(wt->file);
  FILE *fp = fopen(wt->path, "w");
  if (!fp) return k_result_from_errno(errno);

  wt->file = fp;

  return (KResult){K_OK, 0};
}

void k_writer_free(Writer *wt) {
  fclose(wt->file);
  free(wt->path);
}
