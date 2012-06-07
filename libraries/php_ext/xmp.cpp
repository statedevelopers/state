#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



#define VERSION "0.0.2"



#include <stdlib.h>

#include "php.h"
#include "php_ini.h"
#include "php_globals.h"
#include "ext/standard/info.h"

#include <string>
#include <stdio.h>

#if WIN_ENV
    #pragma warning ( disable : 4127 )    // conditional expression is constant
    #pragma warning ( disable : 4996 )    // '...' was declared deprecated
#endif

#define TXMP_STRING_TYPE    std::string

#include "php_xmp.h"
#include "xmp.h"

/*

    1:  XMP_SERIAL_OMITPACKETWRAPPER   = 0x0010UL
    2:  XMP_SERIAL_READONLYPACKET      = 0x0020UL
    4:  XMP_SERIAL_USECOMPACTFORMAT    = 0x0040UL
    8:  XMP_SERIAL_INCLUDETHUMBNAILPAD = 0x0100UL
    16: XMP_SERIAL_EXACTPACKETLENGTH   = 0x0200UL
    32: XMP_SERIAL_WRITEALIASCOMMENTS  = 0x0400UL
    64: XMP_SERIAL_OMITALLFORMATTING   = 0x0800UL

    0:  XMP_SERIAL_ENCODEUTF8          = 0UL,
    1:  XMP_SERIAL_ENCODEUTF16BIG      = _XMP_UTF16_BIT,
    2:  XMP_SERIAL_ENCODEUTF16LITTLE   = _XMP_UTF16_BIT | _XMP_LITTLEENDIAN_BIT,
    4:  XMP_SERIAL_ENCODEUTF32BIG      = _XMP_UTF32_BIT,
    8:  XMP_SERIAL_ENCODEUTF32LITTLE   = _XMP_UTF32_BIT | _XMP_LITTLEENDIAN_BIT

 */
static void
createSerializeMask( uint32_t &mask, long &misc, long &encoding )
{
    // Encoding
    if ( ( encoding & 1 ) != 0 )
    {
        mask += XMP_SERIAL_ENCODEUTF16BIG;
    }

    if ( ( encoding & 2 ) != 0 )
    {
        mask += XMP_SERIAL_ENCODEUTF16LITTLE;
    }

    if ( ( encoding & 4 ) != 0 )
    {
        mask += XMP_SERIAL_ENCODEUTF32BIG;
    }

    if ( ( encoding & 8 ) != 0 )
    {
        mask += XMP_SERIAL_ENCODEUTF32LITTLE;
    }

    // Misc options
    if ( ( misc & 1 ) != 0 )
    {
        mask += XMP_SERIAL_OMITPACKETWRAPPER;
    }

    if ( ( misc & 2 ) != 0 )
    {
        mask += XMP_SERIAL_READONLYPACKET;
    }

    if ( ( misc & 4 ) != 0 )
    {
        mask += XMP_SERIAL_USECOMPACTFORMAT;
    }

    if ( ( misc & 8 ) != 0 )
    {
        mask += XMP_SERIAL_INCLUDETHUMBNAILPAD;
    }

    if ( ( misc & 16 ) != 0 )
    {
        mask += XMP_SERIAL_EXACTPACKETLENGTH;
    }

    if ( ( misc & 32 ) != 0 )
    {
        mask += XMP_SERIAL_WRITEALIASCOMMENTS;
    }

    if ( ( misc & 64 ) != 0 )
    {
        mask += XMP_SERIAL_OMITALLFORMATTING;
    }

}

/*
    0:   XMP_OPEN_NOOPTION          = 0x00000000
    1:   XMP_OPEN_READ              = 0x00000001
    2:   XMP_OPEN_FORUPDATE         = 0x00000002
    4:   XMP_OPEN_OPNLYXMP          = 0x00000004
    8:   XMP_OPEN_CACHETNAIL        = 0x00000008
    16:  XMP_OPEN_STRICTLY          = 0x00000010
    32:  XMP_OPEN_USESMARTHANDLER   = 0x00000020
    64:  XMP_OPEN_USEPACKETSCANNING = 0x00000040
    128: XMP_OPEN_LIMITSCANNING     = 0x00000080
    256: XMP_OPEN_INBACKGROUND      = 0x10000000
 */
static void
createOpenMask( XmpOpenFileOptions &mask, long &openMask )
{
    mask = XMP_OPEN_NOOPTION;
    if ( ( openMask & 1 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_READ );
    }
    if ( ( openMask & 2 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_FORUPDATE );
    }
    if ( ( openMask & 4 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_OPNLYXMP );
    }
    if ( ( openMask & 8 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_CACHETNAIL );
    }
    if ( ( openMask & 16 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_STRICTLY );
    }
    if ( ( openMask & 32 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_USESMARTHANDLER );
    }
    if ( ( openMask & 64 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_USEPACKETSCANNING );
    }
    if ( ( openMask & 128 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_LIMITSCANNING );
    }
    if ( ( openMask & 256 ) != 0 )
    {
        mask = (XmpOpenFileOptions)( mask | XMP_OPEN_INBACKGROUND );
    }
}

PHP_FUNCTION( xmp_read )
{

    char    *fileName            = 0;
    int      fileNameLength      = 0,
             fileLength          = 0,
             argCount            = ZEND_NUM_ARGS();
    long     serializeMask       = 1, // XMP_SERIAL_OMITPACKETWRAPPER
             encodingMask        = 0, // XMP_SERIAL_ENCODEUTF8
             openMask            = 5; // XMP_OPEN_READ & XMP_OPEN_OPNLYXMP

    uint32_t xmpSerializeMask    = 0;
    XmpOpenFileOptions xmpOpenMask;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|lll", &fileName, &fileNameLength,
                                                                    &openMask, &serializeMask,  &encodingMask
                              ) == FAILURE
       )
    {
        php_error_docref( NULL TSRMLS_CC, E_WARNING, "Wrong parameters. Expected at least a string for the filename.\n" );
        RETVAL_FALSE;
        return;
    }

    createOpenMask( xmpOpenMask, openMask );
    createSerializeMask( xmpSerializeMask, serializeMask, encodingMask );

    //php_printf( "Open mask (read) %ld -> %ld.\n", openMask, xmpOpenMask );
    //php_printf( "Serialize mask (read) %ld, %ld -> %ld.\n", serializeMask, encodingMask, xmpSerializeMask );

    if ( !xmp_init() )
    {
        php_error( E_CORE_ERROR, "Failed to initialize XMP.\n" );
        RETVAL_LONG( -1 );
        return;
    }

    XmpFilePtr inFile = xmp_files_open_new( fileName, xmpOpenMask );

    if ( inFile == 0 )
    {
        php_error( E_WARNING, "Failed to open file %s for reading.\n", fileName );
        RETVAL_LONG( -2 );
        return;
    }

    XmpPtr xmp = xmp_files_get_new_xmp( inFile );

    if ( xmp == 0 )
    {
        xmp_files_close( inFile, XMP_CLOSE_NOOPTION );
        xmp_files_free( inFile );
        xmp_terminate();
        // php_error( E_WARNING, "File %s does not contain any XMP meta data.\n", fileName );
        RETVAL_LONG( -3 );
        return;
    }

    xmp_files_close( inFile, XMP_CLOSE_NOOPTION );
    xmp_files_free( inFile );

    XmpStringPtr output = xmp_string_new();

    if ( output == 0 )
    {
        xmp_free( xmp );
        xmp_terminate();
        php_error( E_CORE_ERROR, "Failed to allocate memory to store the extracted XMP data.\n" );
        RETVAL_LONG( -4 );
        return;
    }

    if ( !xmp_serialize_and_format( xmp, output,
                                    xmpSerializeMask,
                                    0, "\n", " ", 0
                                  )
       )
    {
        xmp_string_free( output );
        xmp_free( xmp );
        xmp_terminate();
        //php_error( E_CORE_ERROR, "Failed to serialize XMP packet into a string.\n" );
        RETVAL_LONG( -5 );
        return;
    }

    const char *resultString = xmp_string_cstr( output );

    if ( resultString == 0 )
    {
        xmp_string_free( output );
        xmp_free( xmp );
        xmp_terminate();
        //php_error( E_CORE_ERROR, "Failed to output result.\n" );
        RETVAL_LONG( -6 );
        return;
    }

    RETVAL_STRING( (char *)resultString, 1 );

    xmp_string_free( output );
    xmp_free( xmp );
    xmp_terminate();

    return;
}

PHP_FUNCTION( xmp_write )
{
    bool               hasXMP           = true;
    const char         *fileName        = 0,
                       *xmlData         = 0;
    int                fileNameLength   = 0,
                       xmlDataLength    = 0;
    long               serializeMask    = 1, // XMP_SERIAL_OMITPACKETWRAPPER
                       encodingMask     = 0, // XMP_SERIAL_ENCODEUTF8
                       openMask         = 2; // XMP_OPEN_FORUPDATE & XMP_OPEN_OPNLYXMP

    XmpOpenFileOptions xmpOpenMask;

    uint32_t           xmpSerializeMask = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "ss|lll",
                                &fileName, &fileNameLength,
                                &xmlData,  &xmlDataLength,
                                &openMask, &serializeMask,  &encodingMask
                              ) == FAILURE )
    {
        php_error_docref( NULL TSRMLS_CC, E_WARNING, "Wrong parameters. Expected at least a string for the filename and a string containing XMP data.\n" );
        RETVAL_FALSE;
        return;
    }

    createOpenMask( xmpOpenMask, openMask );
    createSerializeMask( xmpSerializeMask, serializeMask, encodingMask );

    if ( !xmp_init() )
    {
        php_error( E_CORE_ERROR, "Failed to initialize the XMP library.\n" );
        RETVAL_LONG( -1 );
        return;
    }

    XmpPtr xmp = xmp_new_empty();

    if ( !xmp_parse( xmp, (char *)xmlData, xmlDataLength ) )
    {
        //php_error( E_CORE_ERROR, "Failed to parse XML data.\n" );
        RETVAL_LONG( -2 );
        return;
    }

    //php_printf( "Open mask (write) %ld -> %ld.\n", openMask, xmpOpenMask );
    //php_printf( "Serialize mask (write) %ld,%ld -> %ld.\n", serializeMask, encodingMask, xmpSerializeMask );

    XmpFilePtr outFile = xmp_files_open_new( fileName, xmpOpenMask );

    if ( outFile == 0 )
    {
        xmp_free( xmp );
        xmp_terminate();
        //php_error( E_CORE_ERROR, "Failed to open file %s for writing.\n", fileName );
        RETVAL_LONG( -3 );
        return;
    }

    if ( !xmp_files_can_put_xmp( outFile, xmp ) )
    {
        xmp_files_close( outFile, XMP_CLOSE_NOOPTION );
        xmp_files_free( outFile );
        xmp_free( xmp );
        xmp_terminate();
        php_error( E_WARNING, "The used library does not support to write the submited XMP data to file %s.\n", fileName );
        RETVAL_LONG( -4 );
        return;
    }

    xmp_files_put_xmp( outFile, xmp );
    xmp_files_close( outFile, XMP_CLOSE_SAFEUPDATE );
    xmp_files_free( outFile );
    xmp_free( xmp );
    xmp_terminate();
    RETVAL_TRUE;

    return;
}

PHP_FUNCTION( xmp_can_write )
{
    bool               hasXMP           = true;
    const char         *fileName        = 0,
                       *xmlData         = 0;
    int                fileNameLength   = 0,
                       xmlDataLength    = 0;
    long               serializeMask    = 1, // XMP_SERIAL_OMITPACKETWRAPPER
                       encodingMask     = 0, // XMP_SERIAL_ENCODEUTF8
                       openMask         = 2; // XMP_OPEN_FORUPDATE & XMP_OPEN_OPNLYXMP

    XmpOpenFileOptions xmpOpenMask;

    uint32_t           xmpSerializeMask = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "ss|lll",
                                &fileName, &fileNameLength,
                                &xmlData,  &xmlDataLength,
                                &openMask, &serializeMask,  &encodingMask
                              ) == FAILURE )
    {
        php_error_docref( NULL TSRMLS_CC, E_WARNING, "Wrong parameters. Expected at least a string for the filename and a string containing XMP data.\n" );
        RETVAL_FALSE;
        return;
    }

    createOpenMask( xmpOpenMask, openMask );
    createSerializeMask( xmpSerializeMask, serializeMask, encodingMask );

    if ( !xmp_init() )
    {
        php_error( E_CORE_ERROR, "Failed to initialize XMP.\n" );
        RETVAL_LONG( -1 );
        return;
    }

    XmpPtr xmp = xmp_new_empty();

    if ( !xmp_parse( xmp, (char *)xmlData, xmlDataLength ) )
    {
        RETVAL_LONG( -2 );
        return;
    }

    XmpFilePtr outFile = xmp_files_open_new( fileName, xmpOpenMask );

    if ( outFile == 0 )
    {
        xmp_free( xmp );
        xmp_terminate();
        RETVAL_LONG( -3 );
        return;
    }

    bool canWrite = xmp_files_can_put_xmp( outFile, xmp );

    xmp_files_close( outFile, XMP_CLOSE_NOOPTION );
    xmp_files_free( outFile );
    xmp_free( xmp );
    xmp_terminate();

    if ( !canWrite )
    {
        RETVAL_FALSE;
        return;
    }
    RETVAL_TRUE;
    return;
}

static int le_xmp;

zend_function_entry xmp_functions[] =
{
    PHP_FE( xmp_read, NULL )
    PHP_FE( xmp_write, NULL )
    PHP_FE( xmp_can_write, NULL )
    {NULL, NULL, NULL}
};

zend_module_entry xmp_module_entry =
{
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "xmp",
    xmp_functions,
    PHP_MINIT(xmp),
    PHP_MSHUTDOWN(xmp),
    PHP_RINIT(xmp),
    PHP_RSHUTDOWN(xmp),
    PHP_MINFO(xmp),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1",
#endif
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_XMP
ZEND_GET_MODULE(xmp)
#endif

PHP_MINIT_FUNCTION(xmp)
{
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(xmp)
{
    return SUCCESS;
}

PHP_RINIT_FUNCTION(xmp)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(xmp)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(xmp)
{
    php_info_print_table_start();
    php_info_print_table_header( 1, "XMP support" );
    php_info_print_table_row( 2, "Status",  "enabled" );
    php_info_print_table_row( 2, "Version", VERSION );
    php_info_print_table_end();

}
