#include <iostream>
#include <string>
#include "main.hpp"
#include "arguments.hpp"
#include "argparse/argparse.hpp"
#include "http_get.hpp"

static output_enum_t parse_type(const std::string type)
{
    if (type == "write") {
        return WRITE;
    } else if (type == "append") {
        return APPEND;
    } else if (type == "overwrite") {
        return OVERWRITE;
    } else {
        return INVALID;
    }
}

static argparse::ArgumentParser program(PROJECT_NAME, PROJECT_VERSION);


void arg_configure()
{
    program.add_argument("--url", "-u")
        .required()
        .help("The URL to get.");
    
    program.add_argument("--output", "-o")
        .help("The output file.");
    
    program.add_argument("--type", "-t")
        .help("The type of output to use. Use 'write', 'append', or 'overwrite'.");
}

void arg_parse(int argc, const char *const argv[])
{
    program.parse_args(argc, argv);

    std::string url = program.get<std::string>("--url");
    const char *output = program.present("--output") ? program.get<std::string>("--output").c_str() : nullptr;
    output_enum_t output_type = WRITE;
    
    if (program.is_used("--type")) {
        output_type = parse_type(program.get<std::string>("--type"));
        if (output_type == INVALID) {
            throw std::runtime_error("Invalid output type.");
        }
    } 

    if (http_download(url, output, output_type) != 0) {
        throw std::runtime_error("Could not download file.");
    }
}