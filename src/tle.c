#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tle.h"

static double str_slice_to_double( char * str,
                                   uint8_t index1,
                                   uint8_t index2,
                                   bool implied_decimal );

static int32_t str_slice_to_int32( char * str, uint8_t index1, uint8_t index2 );

static int64_t str_slice_to_int64( char * str, uint8_t index1, uint8_t index2 );

static bool validate_tle_checksum( const char * tle_line );

bool check_tle_checksum( char * line1, char * line2 )
{
    return validate_tle_checksum( line1 ) && validate_tle_checksum( line2 );
}

int8_t parse_lines( struct tle_elements * tle, char * line1, char * line2 )
{
    int8_t err = -1;

    if( check_tle_checksum( line1, line2 ) )
    {
        tle->line1 = line1;
        tle->line2 = line2;

        tle->obj_number = str_slice_to_int32( line1, 2U, 7U );

        strncpy( tle->sat_designator, &line1[ 9 ], 8U );

        tle->mean_motion_dot = str_slice_to_double( line1, 35U, 44U, true );

        if( line1[ 33 ] == '-' )
        {
            tle->mean_motion_dot *= -1.0;
        }

        tle->mean_motion_ddot = str_slice_to_double( line1, 45U, 50U, true );

        if( line1[ 44 ] == '-' )
        {
            tle->mean_motion_ddot *= -1.0;
        }
        tle->mean_motion_ddot *= pow( 10.0,
                                      str_slice_to_double( line1,
                                                           50U,
                                                           52U,
                                                           false ) );

        tle->bstar = str_slice_to_double( line1, 54U, 59U, true );
        if( line1[ 53 ] == '-' )
        {
            tle->bstar *= -1.0;
        }
        tle->bstar *= pow( 10.0,
                           str_slice_to_double( line1, 59U, 61U, false ) );

        tle->elem_num = str_slice_to_int32( line1, 64U, 68U );

        tle->orb_inclination = str_slice_to_double( line2, 8U, 16U, false );

        tle->raan_degree = str_slice_to_double( line2, 17U, 25U, false );

        tle->eccentricity = str_slice_to_double( line2, 26U, 33U, true );

        tle->arg_perigee = str_slice_to_double( line2, 34U, 42U, false );

        tle->mean_anomaly = str_slice_to_double( line2, 43U, 51U, false );

        tle->mean_motion = str_slice_to_double( line2, 52U, 63U, false );

        tle->rev_number = str_slice_to_int64( line2, 63U, 68U );

        /* TODO EPOCH */
        // tle->epoch = ?
    }

    return err;
}

static double str_slice_to_double( char * str,
                                   uint8_t index1,
                                   uint8_t index2,
                                   bool implied_decimal )
{
    double retval;
    char tmp[ 16 ];

    int32_t slice_size = index2 - index1;

    if( implied_decimal )
    {
        tmp[ 0 ] = '0';
        tmp[ 1 ] = '.';
        strncpy( &tmp[ 2 ], &str[ index1 ], slice_size );
        tmp[ slice_size + 2U ] = '\0';
        retval = strtod( tmp, NULL );
    }
    else
    {
        strncpy( tmp, &str[ index1 ], slice_size );
        tmp[ slice_size ] = '\0';
        retval = strtod( tmp, NULL );
    }

    return retval;
}

static bool validate_tle_checksum( const char * tle_line )
{
    int32_t checksum = 0;

    for( uint8_t i = 0U; i < 68U; ++i )
    {
        char c = tle_line[ i ];
        if( c >= '0' && c <= '9' )
        {
            checksum += c - '0'; // Convert character to integer and add
        }
        else if( c == '-' )
        {
            checksum += 1; // Minus sign counts as 1
        }
    }

    return ( checksum % 10 ) == ( tle_line[ 68 ] - '0' );
}

static int32_t str_slice_to_int32( char * str, uint8_t index1, uint8_t index2 )
{
    int32_t retval;
    char tmp[ 16 ];

    int32_t slice_size = index2 - index1;

    strncpy( tmp, &str[ index1 ], slice_size );
    tmp[ slice_size ] = '\0';
    retval = strtoll( tmp, NULL, 10 );

    return retval;
}

static int64_t str_slice_to_int64( char * str, uint8_t index1, uint8_t index2 )
{
    int64_t retval;
    char tmp[ 16 ];

    int32_t slice_size = index2 - index1;

    strncpy( tmp, &str[ index1 ], slice_size );
    tmp[ slice_size ] = '\0';
    retval = strtoll( tmp, NULL, 10 );

    return retval;
}
