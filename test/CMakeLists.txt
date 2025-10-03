find_package(Catch2 REQUIRED)

# Create test executable
add_executable(test_db test_db.cpp)

# Link Catch2
target_link_libraries(test_db Catch2::Catch2WithMain)
#include(CTest)
#include(Catch)
#catch_add_tests(test_db)