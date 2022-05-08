cmake_minimum_required(VERSION 3.16)
project(service-flutter-gost-gost)

set(OPENSSL_ROOT_DIR "/opt/TLSGate")
find_package(OpenSSL REQUIRED)

add_executable(service-flutter-gost-gost
    server-gost.cpp
    #EVP
    EVP/EVP_CIPHER_CTX.cpp
    )
target_link_libraries(service-flutter-gost-gost OpenSSL::SSL OpenSSL::Crypto)
