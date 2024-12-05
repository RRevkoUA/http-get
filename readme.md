# HTTP Get Program

## Overview

The HTTP Get program is a command-line tool for downloading content from web URLs with flexible output options.

## Installation

### Prerequisites
- C++ compiler with C++11 support
- CMake
- libcurl (if applicable)

### Clone the Repository

```bash
git clone git@github.com:YourUsername/http-get.git
cd http-get
```

## Building the Project

1. Create a build directory:
    ```bash
    mkdir -p build
    cd build
    ```

2. Configure the project:
    ```bash
    cmake ..
    ```

3. Build the project:
    ```bash
    make -j4
    ```

## Usage

### Basic Command Structure

```bash
http-get [--help] [--version] --url VAR [--output VAR] [--type VAR]
```

### Command Options

| Option | Description | Example |
|--------|-------------|---------|
| `-h`, `--help` | Shows help message and exits | `http-get --help` |
| `-v`, `--version` | Prints version information and exits | `http-get --version` |
| `-u`, `--url` | The URL to download from | `http-get --url https://example.com/file.txt` |
| `-o`, `--output` | The output file | `http-get --url https://example.com/file.txt --output downloaded.txt` |
| `-t`, `--type` | Output type: 'write', 'append', or 'overwrite' | `http-get --url https://example.com/file.txt --type append` |

### Examples

1. Download a file to the current directory:
    ```bash
    http-get --url https://example.com/sample.txt
    ```

2. Download and save to a specific file:
    ```bash
    http-get --url https://example.com/data.json --output mydata.json
    ```

3. Append downloaded content to an existing file:
    ```bash
    http-get --url https://example.com/log.txt --output logs.txt --type append
    ```
## Running Tests

### Automatic Testing

To run tests automatically, you can use the `test.sh` script. This script will prepare the test files, build the project, and run the tests.

```bash
./test.sh
```

### Manual Testing

If you prefer to run tests manually, follow these steps:

1. Prepare the test files:
    ```bash
    cmake --build . --target PrepareTestFiles
    ```

2. Run the tests using CTest:
    ```bash
    ctest -R "^s_test_|^f_test_"
    ```

## Pros and Cons

### Using the Script

**Pros:**
- Automates the entire process, reducing the chance of human error.
- Ensures that all required steps are performed in the correct order.
- Saves time by combining multiple commands into a single script.
- Eliminates files created during testing

**Cons:**
- Less control over individual steps.
- More difficult to debug if something goes wrong in the script.

### Manual process

**Pros:**
- Full control over each step of the process.
- Easier to debug specific issues as they arise.

**Cons:**
- More time-consuming and prone to human error.
- Requires memorizing and executing multiple commands in the correct order.