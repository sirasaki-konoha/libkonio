#include "konio.h"

#ifndef _WIN32
#include <errno.h>

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

#endif /* _WIN32 */
