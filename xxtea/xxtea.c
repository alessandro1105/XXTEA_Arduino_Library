/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:  Chancey <chanceycn@gmail.com>                               |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1.2.1 2007/01/01 19:32:09 iliaa Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xxtea.h"
#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (k[p&3^e]^z);

/* If you declare any globals in php_xxtea.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xxtea)
*/

/* True global resources - no need for thread safety here */
static int le_xxtea;

/* {{{ xxtea_functions[]
 *
 * Every user visible function must have an entry in xxtea_functions[].
 */
zend_function_entry xxtea_functions[] = {
	PHP_FE(xxtea_encrypt,	NULL)
	PHP_FE(xxtea_decrypt,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in xxtea_functions[] */
};
/* }}} */

/* {{{ xxtea_module_entry
 */
zend_module_entry xxtea_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"xxtea",
	xxtea_functions,
	PHP_MINIT(xxtea),
	PHP_MSHUTDOWN(xxtea),
	PHP_RINIT(xxtea),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xxtea),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xxtea),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XXTEA
ZEND_GET_MODULE(xxtea)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xxtea.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xxtea_globals, xxtea_globals)
    STD_PHP_INI_ENTRY("xxtea.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xxtea_globals, xxtea_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_xxtea_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xxtea_init_globals(zend_xxtea_globals *xxtea_globals)
{
	xxtea_globals->global_value = 0;
	xxtea_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xxtea)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xxtea)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(xxtea)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xxtea)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xxtea)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xxtea support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xxtea_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(xxtea_encrypt)
{
	char *v, *k;
	long v_len;
    int k_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &v, &v_len, &k, &k_len) == FAILURE) {
		return;
	}
	php_xxtea_encrypt(v, v_len, k);

	RETURN_TRUE;
}

PHP_FUNCTION(xxtea_decrypt)
{
	char *v, *k;
	long v_len;
    int k_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &v, &v_len, &k, &k_len) == FAILURE) {
		return;
	}
	php_xxtea_decrypt(v, v_len, k);

	RETURN_TRUE;
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

void php_xxtea_encrypt(char* v, long n, char* k) {
    unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
    long p, q ; 
    if(n > 1) {
        q = 6 + 52/n;
        while (q-- > 0) {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX; 
            y = v[0];
            z = v[n-1] += MX; 
        }   
    }   
}

void php_xxtea_decrypt(char* v, long n, char* k) {
    unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
    long p, q ;
    if(n > 1) {
        q = 6 + 52/n;
        sum = q*DELTA ;
        while (sum != 0) {
            e = (sum >> 2) & 3;
            for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
            z = v[n-1];
            y = v[0] -= MX;
            sum -= DELTA;
        }
    }
}
