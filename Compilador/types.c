#include "types.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

DataType check_type(char* value) {
    if (value[0] == '"') return TYPE_STRING;
    
    // Verifica se é número
    for (int i = 0; value[i]; i++) {
        if (!isdigit(value[i])) return TYPE_UNKNOWN;
    }
    return TYPE_INT;
}

const char* type_to_string(DataType type) {
    switch(type) {
        case TYPE_INT: return "int";
        case TYPE_STRING: return "string";
        default: return "unknown";
    }
}