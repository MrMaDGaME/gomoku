# Now simply link against gtest or gtest_main as needed. Eg
add_executable(check_5 check_5/test_check_5.cc)
target_link_libraries(check_5 gtest_main core)
