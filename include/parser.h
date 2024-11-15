#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>

typedef enum
{
    PARSER_TLE,
    PARSER_REDUCED_TLE,
    PARSER_OMM,
} elem_parser_types_t;

typedef struct elem_parser elem_parser_t;

typedef int8_t ( *parse_fn )( elem_parser_t * parser,
                              void * sat_record,
                              void * elements );

struct elem_parser
{
    elem_parser_types_t type;
    void * parser_data;
    void * parser_cfg;
    parse_fn parse_elements;
};

int8_t create_parser( elem_parser_t * parser, elem_parser_types_t type );

int8_t create_parser_static( elem_parser_t * parser,
                             elem_parser_types_t type,
                             void * parser_data,
                             void * parser_cfg );

int8_t set_parser_conf( elem_parser_t * parser, void * parser_conf );

int8_t set_parser_data( elem_parser_t * parser, void * parser_data );

#endif
