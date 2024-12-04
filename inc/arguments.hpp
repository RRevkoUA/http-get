#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

// Configure the arguments for the program.
void arg_configure();

// Parse the arguments for the program.
// argc: The number of arguments.
// argv: The arguments.
void arg_parse(int argc, const char *const argv[]);

#endif // ARGUMENTS_HPP