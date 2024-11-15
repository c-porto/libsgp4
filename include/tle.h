#ifndef TLE_H_
#define TLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
    double mean_anomaly;
    double eccentricity;
    double arg_perigee;
    double raan_degree;
    double inclination;
    double bstar;
    double second_derivative_mean_motion;
    double derivative_mean_motion;
    double mean_motion;
    double epochdays;
    int32_t epochyr;
    int32_t revnum;
    int32_t elemnum;
    int32_t objnum;
    char satnum[ 5 ];
    char classification;
    char sat_designator[ 6 ];
    uint8_t eph_type;
} tle_elements_t;

int8_t parse_lines( tle_elements_t * tle,
                    const char * line1,
                    const char * line2 );

bool check_tle_checksum( const char * line1, const char * line2 );

#ifdef __cplusplus
}
#endif

#endif // !TLE_H_
