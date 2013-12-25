dnl $Id$
dnl config.m4 for extension xxtea

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(xxtea, for xxtea support,
dnl Make sure that the comment is aligned:
dnl [  --with-xxtea             Include xxtea support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(xxtea, whether to enable xxtea support,
dnl Make sure that the comment is aligned:
[  --enable-xxtea           Enable xxtea support])

if test "$PHP_XXTEA" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-xxtea -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/xxtea.h"  # you most likely want to change this
  dnl if test -r $PHP_XXTEA/$SEARCH_FOR; then # path given as parameter
  dnl   XXTEA_DIR=$PHP_XXTEA
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for xxtea files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       XXTEA_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$XXTEA_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the xxtea distribution])
  dnl fi

  dnl # --with-xxtea -> add include path
  dnl PHP_ADD_INCLUDE($XXTEA_DIR/include)

  dnl # --with-xxtea -> check for lib and symbol presence
  dnl LIBNAME=xxtea # you may want to change this
  dnl LIBSYMBOL=xxtea # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XXTEA_DIR/lib, XXTEA_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_XXTEALIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong xxtea lib version or lib not found])
  dnl ],[
  dnl   -L$XXTEA_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(XXTEA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(xxtea, xxtea.c, $ext_shared)
fi
