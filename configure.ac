AC_INIT([konio], [0.1])
AM_INIT_AUTOMAKE([-Wall foreign])

AC_PROG_CC
AC_PROG_CC_C99
AM_PROG_AR
LT_INIT

# --- kcore ---
AC_ARG_WITH([kcore],
  [AS_HELP_STRING([--with-kcore=PATH], [path to libkcore])],
  [KCORE_DIR=$withval],
  [KCORE_DIR="../libkcore"]
)

CPPFLAGS="$CPPFLAGS -I$KCORE_DIR/src"

AC_CHECK_HEADERS([kcore.h], [], [
  AC_MSG_ERROR([kcore.h not found in $KCORE_DIR])
])

AC_COMPILE_IFELSE([
  AC_LANG_PROGRAM([[#include <kcore.h>]], [[
    KResult r = k_result_from_errno(0);
  ]])
], [], [
  AC_MSG_ERROR([kcore API incompatible])
])

AC_SUBST([KCORE_DIR])
AC_SUBST([CPPFLAGS])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_OUTPUT
