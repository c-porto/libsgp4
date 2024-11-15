#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

#include "../include/utils.h"

int8_t str2int32( const char * str, int32_t * value )
{
    int8_t err = 0;
    char * end_ptr = NULL;

    errno = 0;
    int64_t tmp = ( int64_t ) strtoll( str, &end_ptr, 10 );

    if( errno != 0 )
    {
        err = -1;
    }

    if( end_ptr == str )
    {
        err = -1;
    }

    if( ( tmp > INT32_MAX ) || ( tmp < INT32_MIN ) )
    {
        err = -1;
    }

    if( err == 0 )
    {
        *value = ( int32_t ) tmp;
    }

    return err;
}

int8_t str2int64( const char * str, int64_t * value )
{
    int8_t err = 0;
    char * end_ptr = NULL;

    errno = 0;
    int64_t tmp = ( int64_t ) strtoll( str, &end_ptr, 10 );

    if( errno != 0 )
    {
        err = -1;
    }

    if( end_ptr == str )
    {
        err = -1;
    }

    if( err == 0 )
    {
        *value = tmp;
    }

    return err;
}

int8_t str2f64( const char * str, double * value )
{
    int8_t err = 0;
    char * end_ptr = NULL;

    errno = 0;
    double tmp = strtod( str, &end_ptr );

    if( errno != 0 )
    {
        err = -1;
    }

    if( end_ptr == str )
    {
        err = -1;
    }

    if( err == 0 )
    {
        *value = tmp;
    }

    return err;
}

int8_t str2f32( const char * str, float * value )
{
    int8_t err = 0;
    char * end_ptr = NULL;

    errno = 0;
    float tmp = strtof( str, &end_ptr );

    if( errno != 0 )
    {
        err = -1;
    }

    if( end_ptr == str )
    {
        err = -1;
    }

    if( err == 0 )
    {
        *value = tmp;
    }

    return err;
}
