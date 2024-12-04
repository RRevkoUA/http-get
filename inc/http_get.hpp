#ifndef HTTP_GET_HPP
#define HTTP_GET_HPP

#include <string>
#include "output_enums.hpp"

// Function to download a file from a URL.
// url - The URL to download from.
// output - The output file name. If nullptr, the file will be saved in the current directory with the same name as the URL.
// output_type - The type of output to use. See output_enums.hpp for more information.
// Returns 0 on success, -1 on failure.
int8_t http_download(const std::string url, const char *const output, const output_enum_t output_type);

#endif