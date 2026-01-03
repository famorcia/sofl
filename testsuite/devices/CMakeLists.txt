
set(TEST_NAME test_sofl_devices)
add_executable(${TEST_NAME} ../TestSuiteMain.cpp TestSoFlKeyboardP.cpp)
target_compile_definitions(${TEST_NAME} PRIVATE -DSOFL_INTERNAL=1)
target_link_libraries(${TEST_NAME}  SoFl )

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})