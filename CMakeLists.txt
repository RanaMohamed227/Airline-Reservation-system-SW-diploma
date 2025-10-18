cmake_minimum_required(VERSION 3.10)
project(AirlineReservationSystem VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/user.cpp
    src/admin.cpp
    src/bookingagent.cpp
    src/passenger.cpp
    src/aircraft.cpp
    src/flight.cpp
    src/reservation.cpp
    src/payment.cpp
    src/maintenance.cpp
    src/systemmanager.cpp
    src/menu.cpp
)

# Header files
set(HEADERS
    inc/user.hpp
    inc/admin.hpp
    inc/bookingagent.hpp
    inc/passenger.hpp
    inc/aircraft.hpp
    inc/flight.hpp
    inc/reservation.hpp
    inc/payment.hpp
    inc/maintenance.hpp
    inc/systemmanager.hpp
    inc/menu.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/inc
)

# Find and link nlohmann_json (assuming it's installed)
# If not installed, you can include it as a submodule or download the single header
find_package(nlohmann_json 3.2.0 QUIET)

if(nlohmann_json_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
else()
    # If nlohmann_json is not found, try to use it as header-only
    message(STATUS "nlohmann_json not found, assuming header-only in external/")
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external)
endif()

# Create data directory at build time
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/reports)

# Copy data files if they exist
if(EXISTS ${CMAKE_SOURCE_DIR}/data)
    file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX _CRT_SECURE_NO_WARNINGS)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
endif()

# Custom targets
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Airline Reservation System..."
)

add_custom_target(clean-data
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/data
    COMMENT "Cleaning data directory..."
)

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION bin/data
    OPTIONAL
)

# Print configuration
message(STATUS "")
message(STATUS "========== Build Configuration ==========")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary directory: ${CMAKE_BINARY_DIR}")
message(STATUS "=========================================")
message(STATUS "")