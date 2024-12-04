#ifndef OUTPUT_ENUMS_HPP
#define OUTPUT_ENUMS_HPP
#include <map>
#include <string>

typedef enum {
    WRITE = 0,  // Write to a new file.
    APPEND,     // Append to an existing file.    
    OVERWRITE,  // Overwrite an existing file.
} output_enum_t;

std::map <output_enum_t, std::string> output_enum_map = {
    {WRITE, "wb"},
    {APPEND, "ab"},
    {OVERWRITE, "wb"},
};

#endif // OUTPUT_ENUMS_HPP