#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>
#include <stdint.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define utilDEG2RAD( x )         ( ( x ) * M_PI / 180.0 )

#define utilRAD2DEG( x )         ( ( x ) * 180.0 / M_PI )

#define utilPRIME_ANGLE( angle ) ( angle ) - 360.0 * floor( ( angle ) / 360.0 )

#define utilFIX_ANGLE( angle, limit )         \
    do                                        \
    {                                         \
        if( ( angle ) > ( limit ) )           \
        {                                     \
            ( angle ) -= ( double ) 2 * M_PI; \
        }                                     \
    } while( 0 )

int8_t str2int32( const char * str, int32_t * value );

int8_t str2int64( const char * str, int64_t * value );

int8_t str2f64( const char * str, double * value );

int8_t str2f32( const char * str, float * value );

#endif
