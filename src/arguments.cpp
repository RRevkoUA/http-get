#include <iostream>
#include <string>
#include "main.hpp"
#include "arguments.hpp"
#include "argparse/argparse.hpp"


static argparse::ArgumentParser program(PROJECT_NAME, PROJECT_VERSION);


void arg_configure()
{
    /* 
        --url -u: The URL to get.
        --output -o: The output file. 
    */
}

void arg_parse(int argc, const char *const argv[])
{
    program.parse_args(argc, argv);

    std::cout << program;
}