include(AddCatch2)

add_executable(test_vector3 test_vector3.cpp)
target_link_libraries(test_vector3 PRIVATE application Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test_vector3)

add_test(NAME Vector3 COMMAND test_vector3)