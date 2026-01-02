cmake_minimum_required(VERSION 3.10)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 QUIET)

# If nlohmann_json is not found, use header-only version
if(NOT nlohmann_json_FOUND)
  message(STATUS "nlohmann_json not found, using header-only version")
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

# Create executable
add_executable(weather_app main.cpp)

# Link libraries
target_link_libraries(weather_app PRIVATE CURL::libcurl)

if(nlohmann_json_FOUND)
  target_link_libraries(weather_app PRIVATE nlohmann_json::nlohmann_json)
endif()
