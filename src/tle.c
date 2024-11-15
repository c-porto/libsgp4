#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/tle.h"
#include "../include/utils.h"

static bool validate_tle_checksum( const char * tle_line, uint8_t line_number );

bool check_tle_checksum( const char * line1, const char * line2 )
{
    return validate_tle_checksum( line1, 1U ) &&
           validate_tle_checksum( line2, 2U );
}

int8_t parse_lines( tle_elements_t * tle,
                    const char * line1,
                    const char * line2 )
{
    int8_t err = -1;

    if( check_tle_checksum( line1, line2 ) )
    {
        /* Satellite Number in string format */
        ( void ) memcpy( tle->satnum, &line1[ 2 ], 5U );

        /* Satellite Classification */
        tle->classification = line1[ 7 ];

        /* Internation Designator */
        ( void ) memcpy( tle->sat_designator, &line1[ 9 ], 6U );

        /* Ephemeris Type */
        tle->eph_type = line1[ 62 ];

        /* Start of orbital elements parsing (With error handling for conversion
         * errors) */

        /* Temporary buffer for indirect conversions */
        char buf[ 15 ] = { 0 };
        /* Temporary exponent value */
        int32_t e = 0;

        ( void ) memcpy( buf, &line1[ 18 ], 2U );
        err = str2int32( buf, &tle->epochyr );

        if( err == 0 )
        {
            err = str2f64( &line1[ 20 ], &tle->epochdays );
        }

        if( err == 0 )
        {
            err = str2f64( &line1[ 33 ], &tle->derivative_mean_motion );
        }

        if( err == 0 )
        {
            buf[ 0 ] = line1[ 44 ];
            buf[ 1 ] = '.';
            ( void ) memcpy( &buf[ 2 ], &line1[ 45 ], 5U );
            buf[ 2U + 5U ] = '\0';
            err = str2f64( buf, &tle->second_derivative_mean_motion );
        }

        if( err == 0 )
        {
            err = str2int32( &line1[ 50 ], &e );
        }

        if( err == 0 )
        {
            tle->second_derivative_mean_motion *= pow( 10.0, ( double ) e );
        }

        if( err == 0 )
        {
            buf[ 0 ] = line1[ 53 ];
            buf[ 1 ] = '.';
            ( void ) memcpy( &buf[ 2 ], &line1[ 54 ], 5U );
            buf[ 2U + 5U ] = '\0';
            err = str2f64( buf, &tle->bstar );
        }

        if( err == 0 )
        {
            err = str2int32( &line1[ 59 ], &e );
        }

        if( err == 0 )
        {
            tle->bstar *= pow( 10.0, ( double ) e );
        }

        if( err == 0 )
        {
            ( void ) memcpy( buf, &line1[ 64 ], 4 );
            buf[ 5 ] = '\0';
            err = str2int32( buf, &tle->elemnum );
        }

        if( err == 0 )
        {
            err = str2f64( &line2[ 8 ], &tle->inclination );
        }

        if( err == 0 )
        {
            err = str2f64( &line2[ 17 ], &tle->raan_degree );
        }

        if( err == 0 )
        {
            buf[ 0 ] = '.';
            ( void ) memcpy( &buf[ 1 ], &line2[ 26 ], 7U );
            buf[ 7 ] = '\0';
            err = str2f64( buf, &tle->eccentricity );
        }

        if( err == 0 )
        {
            err = str2f64( &line2[ 34 ], &tle->arg_perigee );
        }

        if( err == 0 )
        {
            err = str2f64( &line2[ 43 ], &tle->mean_anomaly );
        }

        if( err == 0 )
        {
            ( void ) memcpy( buf, &line2[ 52 ], 11U );
            buf[ 11 ] = '\0';
            err = str2f64( buf, &tle->mean_motion );
        }

        if( err == 0 )
        {
            ( void ) memcpy( buf, &line2[ 63 ], 5 );
            buf[ 5 ] = '\0';
            err = str2int32( buf, &tle->revnum );
        }
    }

    return err;
}

static bool validate_tle_checksum( const char * tle_line, uint8_t line_number )
{
    int32_t checksum = 0;

    uint8_t n = ( uint8_t ) tle_line[ 0 ] - ( uint8_t ) '0';

    for( uint8_t i = 0U; i < 68U; ++i )
    {
        char c = tle_line[ i ];
        if( ( c >= '0' ) && ( c <= '9' ) )
        {
            char c_as_int = c - '0';
            checksum += ( int8_t ) c_as_int;
        }
        else if( c == '-' )
        {
            checksum += 1; // Minus sign counts as 1
        }
        else
        {
            continue;
        }
    }

    int8_t chksum_mod = ( int8_t ) ( checksum % 10 );
    char tle_chksum = ( tle_line[ 68 ] - '0' );

    return ( chksum_mod == ( int8_t ) tle_chksum ) && ( line_number == n );
}
