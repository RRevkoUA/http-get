#include "include/curl/curl.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "main.hpp"
#include "output_enums.hpp"
#include "http_get.hpp"

static int8_t download_prepare(std::string *output_file, const std::string url, const char *const output, const output_enum_t output_type);

int8_t http_download(const std::string url, const char *const output, const output_enum_t output_type)
{
    CURL *curl;
    CURLcode res;
    FILE *file;
    std::string output_file;

    curl = curl_easy_init();
    if (curl)
    {
        if (download_prepare(&output_file, url, output, output_type) != 0)
        {
            std::cerr << "Error: File already exists." << std::endl;
            return -1;
        }
        std::cout<<"Downloading file to: "<<output_file<<std::endl;
        file = fopen(output_file.c_str(), output_enum_map[output_type].c_str());
        if (file)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
                return -1;
            }
            curl_easy_cleanup(curl);
            fclose(file);
            return 0;
        }
        else
        {
            std::cerr << "Error: Could not open file for writing." << std::endl;
            return -1;
        }
    }
    else
    {
        std::cerr << "Error: Could not initialize curl." << std::endl;
        return -1;
    }
}

static int8_t download_prepare(std::string *output_file, const std::string url, const char *const output, const output_enum_t output_type)
{
    std::cout<<"Preparing to download file from: "<<url<<std::endl;
    if (output == nullptr) {
        *output_file = "./";
        *output_file += url.substr(url.find_last_of("/") + 1);
        std::cout<<"Output file not specified. Using default: "<<*output_file<<std::endl;

    } 
    else if (std::filesystem::is_directory(output)) {
        *output_file = output;
        *output_file += "/";
        *output_file += url.substr(url.find_last_of("/") + 1);
    }
    else {
        *output_file = output;
    }
    
    if (output_type == WRITE && std::filesystem::exists(*output_file)) {
        std::cerr << "Error: File already exists." << std::endl;
        return -1;
    }

    return 0;
}