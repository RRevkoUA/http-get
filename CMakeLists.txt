cmake_minimum_required(VERSION 3.14)
project(http-get)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(MIDDLEWARE_DIR ${CMAKE_SOURCE_DIR}/middlewares)
set(TEST_CWD ${CMAKE_BINARY_DIR}/test)

set(LIBCURL_DIR ${MIDDLEWARE_DIR}/curl)
set(ARGPARSE_DIR ${MIDDLEWARE_DIR}/argparse)
set(MIMETYPES_DIR ${MIDDLEWARE_DIR}/MimeTypes)

add_subdirectory(${LIBCURL_DIR})
add_subdirectory(${ARGPARSE_DIR})

find_package(CURL REQUIRED)
add_executable(http-get 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/arguments.cpp
    ${SRC_DIR}/http_get.cpp
    ${MIMETYPES_DIR}/MimeTypes.cpp
    )

target_include_directories(http-get PRIVATE 
    ${INC_DIR}
    ${MIMETYPES_DIR}
    ${LIBCURL_DIR}
    ${ARGPARSE_DIR}
)

target_link_libraries(http-get PRIVATE 
    CURL::libcurl
    argparse
)

enable_testing()

add_custom_target(PrepareTestFiles
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_CWD}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_CWD}
)

add_dependencies(http-get PrepareTestFiles)


add_test(NAME s_test_help COMMAND http-get -h)
add_test(NAME s_test_version COMMAND http-get -v)

# Successful test
# download html file, without setting dir
add_test(NAME s_test_download_html COMMAND http-get -u https://www.google.com/) 
#download html, without protocol
add_test(NAME s_test_url_without_protocol COMMAND http-get -u www.google.com -o ./test/missing_protocol.html)
# download html file, setting dir
add_test(NAME s_test_download_html_dir COMMAND http-get -u https://www.google.com/ -o ./test/)
# download image file, without setting dir
add_test(NAME s_test_download_image COMMAND http-get -u https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png)
# download image file, setting dir
add_test(NAME s_test_download_image_dir COMMAND http-get -u https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png -o ./test/)
# download image, overwrite file
add_test(NAME s_test_download_image_overwrite COMMAND http-get -u https://png.pngtree.com/png-vector/20231019/ourmid/pngtree-happy-smile-cat-images-png-image_10276665.png -o ./test/googlelogo_color_272x92dp.png -t overwrite)
# download html with custom name 
add_test(NAME s_test_download_html_custom_name COMMAND http-get -u https://www.google.com/ -o ./test/google.html)
# download new html and append it to existing file
add_test(NAME s_test_download_html_append COMMAND http-get -u https://github.com/RRevkoUA -o ./test/google.html -t append)
set_tests_properties(s_test_download_html_append PROPERTIES DEPENDS s_test_download_html_custom_name)

# Failed tests
# download non-existing file
add_test(NAME f_test_download_non_existing COMMAND http-get -u https://www.somestrangeurl.url.ua)
set_tests_properties(f_test_download_non_existing PROPERTIES WILL_FAIL TRUE)

# download file to non-existing dir
add_test(NAME f_test_download_to_non_existing_dir COMMAND http-get -u https://www.google.com/ -o ./non_existing_dir/)
set_tests_properties(f_test_download_to_non_existing_dir PROPERTIES WILL_FAIL TRUE)

# download file to dir with no write permissions
add_test(NAME f_test_download_to_dir_no_write_permissions COMMAND http-get -u https://www.google.com/ -o /root/)
set_tests_properties(f_test_download_to_dir_no_write_permissions PROPERTIES WILL_FAIL TRUE)

# download file with invalid type
add_test(NAME f_test_download_invalid_type COMMAND http-get -u https://www.google.com/ -t invalid_type)
set_tests_properties(f_test_download_invalid_type PROPERTIES WILL_FAIL TRUE)