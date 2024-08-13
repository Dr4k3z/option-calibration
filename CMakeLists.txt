cmake_minimum_required(VERSION 3.12)
project(option-calibration)

find_package(SQLite3 REQUIRED)

# Add your source files here
set(SOURCES
    #src/portfolio-backtester.cpp
    #src/ETL.cpp
    #src/ETL.cpp
    #src/option_mc.cpp
    #src/black_scholes.hpp
    main.cpp
    headers/options.h
    headers/rapidcsv.h
    headers/pricing_models.h
    headers/date.h
    #src/rapidcsv.hpp
    src/date.cpp
)

# Add any additional include directories here
#include_directories(include)

# Add any additional library directories here
#link_directories(lib)

# Add any additional libraries here
#set(LIBRARIES
#    mylib
#)

# Set the output directory for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)
