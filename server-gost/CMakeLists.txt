cmake_minimum_required(VERSION 3.16)
project(server-gost)

set(OPENSSL_ROOT_DIR "/opt/TLSGate")
find_package(OpenSSL REQUIRED)

add_executable(server-gost
    server-gost.cpp
    servlet.cpp  ssl.cpp
    EVP_CIPHER_CTX.cpp
    EVP_PKEY.cpp
    )
target_link_libraries(server-gost OpenSSL::SSL OpenSSL::Crypto)
