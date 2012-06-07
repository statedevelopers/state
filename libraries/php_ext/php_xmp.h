#ifndef PHP_XMP_H
#define PHP_XMP_H

extern zend_module_entry xmp_module_entry;
#define phpext_xmp_ptr &xmp_module_entry

#ifdef PHP_WIN32
#define PHP_XMP_API __declspec(dllexport)
#else
#define PHP_XMP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(xmp);
PHP_MSHUTDOWN_FUNCTION(xmp);
PHP_RINIT_FUNCTION(xmp);
PHP_RSHUTDOWN_FUNCTION(xmp);
PHP_MINFO_FUNCTION(xmp);

#ifdef ZTS
#define XMP_G(v) TSRMG(xmp_globals_id, zend_xmp_globals *, v)
#else
#define XMP_G(v) (xmp_globals.v)
#endif

#endif
