cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "plugin_linux")
project(${PROJECT_NAME} LANGUAGES CXX)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "plugin_linux_plugin")

add_library(${PLUGIN_NAME} SHARED
  "plugin_linux_plugin.cc"

  #src/checking_bad_words.cpp
  "include/src/checking_bad_words.cpp"
  "include/src/native_add.cpp"
)
apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::GTK)

# List of absolute paths to libraries that should be bundled with the plugin
set(plugin_linux_bundled_libraries
  ""
  PARENT_SCOPE
)
