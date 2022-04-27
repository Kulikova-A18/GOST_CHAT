cmake_minimum_required(VERSION 3.16)
project(server-client-ssl-tcp)

set(OPENSSL_ROOT_DIR "/opt/TLSGate")
find_package(OpenSSL REQUIRED)

add_executable(server-gost
    server-gost.cpp
    servlet.cpp
    ssl.cpp
    server_send.cpp
    )
target_link_libraries(server-gost OpenSSL::SSL OpenSSL::Crypto)

add_executable(client-gost
    client-gost.cpp
    send.cpp
    client_ssl.cpp
    )
target_link_libraries(client-gost OpenSSL::SSL OpenSSL::Crypto)
