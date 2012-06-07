dnl $Id$
dnl config.m4 for extension xmp

PHP_ARG_WITH(expat,
[Location of the expat library source files],
[  --with-expat[=DIR]      Location of the expat library (required)])

PHP_ARG_WITH(exempi,
[Location of the exempi library source files],
[  --with-exempi[=DIR]     Location of the exempi library (required)])

PHP_ARG_ENABLE(xmp,
[Whether to enable XMP support in PHP],
[  --enable-xmp            Enable XMP support in PHP (default enabled)])

dnl if test "$PHP_EXEMPI" != "no"; then

  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/exempi-2.0/exempi/xmp.h"
  if test -r $PHP_EXEMPI/; then
     EXEMPI_DIR=$PHP_EXEMPI
  else
     AC_MSG_CHECKING([for exempi files in default paths])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         EXEMPI_DIR=$i
         AC_MSG_RESULT(found in $i)
         break
       fi
     done
   fi

   if test -z "$EXEMPI_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please verfiy the path to the exempi sources])
   else
     PHP_ADD_INCLUDE($EXEMPI_DIR/include/exempi-2.0/exempi)
   fi

  LIBNAME=exempi
  LIBSYMBOL=xmp_init

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EXEMPI_DIR/lib, XMP_SHARED_LIBADD)
     AC_DEFINE(HAVE_EXEMPILIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong exempi library version or library not found])
   ],[
     -L$EXEMPI_DIR/lib -lm -ldl -Wl,-rpath=$EXEMPI_DIR/lib
   ])

dnl fi

dnl if test "$PHP_EXPAT" != "no"; then

  if test -r $PHP_EXPAT/; then
     EXPAT_DIR=$PHP_EXEMPI
  else
    AC_MSG_CHECKING([for expat files in default paths])
    for i in /usr /usr/local; do
      if test -f "$i/lib/libexpat.a" || test -f "$i/lib/libexpat.so"; then
        EXPAT_DIR=$i
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
  fi

  if test -z "$EXPAT_DIR"; then
    AC_MSG_ERROR([not found. Please reinstall the expat distribution.])
  fi

  PHP_ADD_INCLUDE($EXPAT_DIR/include)
  PHP_ADD_LIBRARY_WITH_PATH(expat, $EXPAT_DIR/lib, XML_SHARED_LIBADD)
  AC_DEFINE(HAVE_EXPAT, 1, [Wether to user expat or not])

dnl fi

PHP_SUBST(XMP_SHARED_LIBADD)

AC_DEFINE(UNIX_ENV, 1, [Whether you are in a unix environment])

PHP_REQUIRE_CXX

PHP_NEW_EXTENSION(xmp, xmp.cpp, $ext_shared)
