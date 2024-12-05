#include "include/curl/curl.h"
#include "output_enums.hpp"
#include "http_get.hpp"
#include "main.hpp"
#include "MimeTypes.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <string.h>
#include <algorithm>

// Generate name for output file.
static int8_t download_prepare(std::string *output_file, const std::string url, const char *const output, const output_enum_t output_type);
static int8_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata);

// Content type of the file, parsed from header.
static std::string content_type;

int8_t http_download(const std::string url, const char *const output, const output_enum_t output_type)
{
    CURL *curl;
    CURLcode res;
    FILE *file;
    std::string output_file;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 0L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);

        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return -1;
        }
        
        if (download_prepare(&output_file, url, output, output_type) != 0) {
            std::cerr << "Error: File already exists." << std::endl;
            return -1;
        }

        std::cout << "Downloading file to: " << output_file << std::endl;
        file = fopen(output_file.c_str(), output_enum_map[output_type].c_str());
        if (file)
        {
            curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
            curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 0L);
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
    std::string temp = "";
    std::string temp_url = url;
    std::string extention = "";

    if (temp_url.back() == '/') {
        temp_url.pop_back();
    }

    std::cout<<"URL: "<<temp_url<<std::endl;
    temp_url = temp_url.substr(temp_url.find_last_of("/") + 1);


// Compare content type with MIME type. If its true, we would use url file extension.

    if (content_type.size()) {
        if (temp_url.find_last_of(".") != std::string::npos) {
            // compare with content type.
            temp = temp_url.substr(temp_url.find_last_of(".") + 1);

            if (!temp.size() && content_type == MimeTypes::getType(temp.c_str())) {
                std::cout<<"Content type matches MIME type."<<std::endl;
            }
            else {
                temp = "";
            }
        }

        if (!temp.size()) {
            extention = ".";
            extention += MimeTypes::getExtension(content_type.c_str());
        }
    }

    
    std::cout<<"Preparing to download file from: "<<url<<std::endl;
    if (output == nullptr) {
        *output_file = "./";
        *output_file += temp_url;
        *output_file += extention;

        std::cout<<"Output file not specified. Using default: "<<*output_file<<std::endl;

    } 
    else if (std::filesystem::is_directory(output)) {
        *output_file = output;
        *output_file += "/";
        *output_file += temp_url;
        *output_file += extention;
    }
    else {
        *output_file = output;
    }
    
    if (output_type == WRITE && std::filesystem::exists(*output_file)) {
        return -1;
    }

    return 0;
}

static int8_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    if (content_type.size()) {
        return size * nitems;
    }

    std::string header = std::string(buffer);
    std::string content_type_str = "content-type:";
    
    std::transform(header.begin(), header.end(), header.begin(), ::tolower);
    
    size_t pos = header.find(content_type_str);

    if (pos != std::string::npos) {
        std::cout << "Found content type." << pos << header << content_type_str.length() << header.substr(pos + content_type_str.length()) << std::endl;

        std::string temp_type = header.substr(pos + content_type_str.length());
        temp_type = temp_type.substr(0, temp_type.find(";"));
        temp_type.erase(0, temp_type.find_first_not_of(" \t\n\r\f\v"));
        temp_type.erase(temp_type.find_last_not_of(" \t\n\r\f\v") + 1);

        content_type = temp_type;
        std::cout << "Content type: |" << content_type << '|' <<std::endl;
    }
    
    return size * nitems;
}