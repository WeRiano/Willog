add_executable(Test Test.cpp)

target_include_directories(Test PRIVATE ../src/Willog)
target_link_directories(Test PRIVATE Willog)