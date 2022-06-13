cmake_minimum_required(VERSION 3.16)
project(server-client-gost)

set(OPENSSL_ROOT_DIR "/opt/TLSGate")
find_package(OpenSSL REQUIRED)

add_executable(server-gost
    server-gost.cpp
    server_send.cpp

    #data
    data/check-json-data.cpp
    data/create-json-data.cpp

    #EVP
    EVP/EVP_CIPHER_CTX.cpp
    EVP/EVP_PKEY.cpp
    EVP/EVP_MD_CTX.cpp
    )
target_link_libraries(server-gost OpenSSL::SSL OpenSSL::Crypto)

add_executable(client-gost
    client-gost.cpp
    send.cpp

    #EVP
    EVP/client_EVP_CIPHER_CTX.cpp
    EVP/client_EVP_PKEY.cpp
    EVP/client_EVP_MD_CTX.cpp
    )
target_link_libraries(client-gost OpenSSL::SSL OpenSSL::Crypto)
