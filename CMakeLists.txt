cmake_minimum_required(VERSION 3.14)
project(Dining-Philosophers-Problem)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/Fork.cpp
                               src/Logger.cpp
                               src/Philosopher.cpp
                               src/PhilosophyMeeting.cpp)

if (NOT WIN32)
target_link_libraries(${PROJECT_NAME}
                      pthread
                      -fsanitize=thread)

target_compile_options(${PROJECT_NAME}
                      PRIVATE
                      -Wall
                      -Wextra
                      -Wpedantic
                      -Wconversion
                      -Werror
                      -fsanitize=thread)
else()
target_compile_options(${PROJECT_NAME}
                       PRIVATE
                       -Wall
                       -Wextra
                       -Wpedantic
                       -Wconversion
                       -Werror)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)