#include "konio.h"
#include <stdio.h>

#ifndef _WIN32
#include <errno.h>
#include <string.h>

KResult k_result_from_errno(int err)
{
    KResult res;
    res.sys_errno = err;

    switch (err) {
        case 0:
            res.code = K_OK;
            break;

        case ENOENT:
            res.code = K_ERR_FILE_NOT_FOUND;
            break;

        case EACCES:
        case EPERM:
            res.code = K_ERR_PERMISSION;
            break;

        case EISDIR:
            res.code = K_ERR_IS_DIRECTORY;
            break;

        case ENOSPC:
            res.code = K_ERR_NO_SPACE;
            break;

		case ENOMEM:
			res.code = K_ERR_NO_MEMORY;
			break;

        case EINVAL:
            res.code = K_ERR_INVALID_ARG;
            break;

        case EIO:
            res.code = K_ERR_IO;
            break;

        default:
            res.code = K_ERR_UNKNOWN;
            break;
    }

    return res;
}

const char* k_result_str(KResult result)
{
    switch (result.code) {
        case K_OK:
            return "OK";

        case K_ERR_IO:
            return "I/O error";

        case K_ERR_FILE_NOT_FOUND:
            return "No such file or directory";

        case K_ERR_IS_DIRECTORY:
            return "Is a directory";

        case K_ERR_INVALID_ARG:
            return "Invalid argument";

        case K_ERR_NO_MEMORY:
            return "Out of memory";

        case K_ERR_NO_SPACE:
            return "No space left on device";

        case K_ERR_PERMISSION:
            return "Permission denied";

        case K_ERR_ALREADY_OPEN:
            return "Already open";

        case K_ERR_NOT_OPEN:
            return "Not open";

        default:
            return "Unknown error";
    }
}

void k_result_print(KResult r)
{
    if (r.sys_errno)
        printf("%s (errno=%d: %s)\n",
            k_result_str(r),
            r.sys_errno,
            strerror(r.sys_errno));
    else
        printf("%s\n", k_result_str(r));
}

#endif /* _WIN32 */

