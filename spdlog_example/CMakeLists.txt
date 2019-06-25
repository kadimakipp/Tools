project(example)

add_executable(spdlog_example spdlog_example.cpp)
target_link_libraries(spdlog_example -lpthread)
