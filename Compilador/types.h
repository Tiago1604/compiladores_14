#ifndef TYPES_H
#define TYPES_H

typedef enum {
    TYPE_INT,
    TYPE_STRING,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    char* name;
    DataType type;
} Variable;

DataType check_type(char* value);
const char* type_to_string(DataType type);

#endif