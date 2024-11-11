#ifndef TLE_H_
#define TLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct tle_elements
{
    double mean_anomaly;
    double eccentricity;
    double raan_degree;
    double orb_inclination;
    double bstar;
    double mean_motion_ddot;
    double mean_motion_dot;
    double mean_motion;
    int32_t rev_number;
    int32_t elem_num;
    int32_t obj_number;
    int64_t epoch;
    char sat_designator[ 12 ];
    char * line1;
    char * line2;
};

void parse_lines( struct tle_elements * tle, char * line1, char * line2 );

#ifdef __cplusplus
}
#endif

#endif // !TLE_H_
