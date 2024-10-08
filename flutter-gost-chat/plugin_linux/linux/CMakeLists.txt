cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "plugin_linux")
project(${PROJECT_NAME} LANGUAGES CXX)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "plugin_linux_plugin")

find_package(OpenSSL REQUIRED)

add_library(${PLUGIN_NAME} SHARED
  "plugin_linux_plugin.cc"

  "src/logger.cpp"
  "src/sign_in.cpp"
  "src/message.cpp"
  "src/user.cpp"
  "src/check_password.cpp"
  
  #src/send_server
  "src/send_server/send.cpp"
  
  #src/send_server/EVP
  "src/send_server/EVP/client_EVP_CIPHER_CTX.cpp"
  "src/send_server/EVP/client_EVP_PKEY.cpp"
)

set_property(TARGET ${PLUGIN_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PLUGIN_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::GTK)

# List of absolute paths to libraries that should be bundled with the plugin
set(plugin_linux_bundled_libraries
  ""
  PARENT_SCOPE
)
