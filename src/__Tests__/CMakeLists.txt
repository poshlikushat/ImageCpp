if(BUILD_TESTING)
    add_executable(ImageTest test.cpp)
    target_link_libraries(ImageTest PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(ImageTest)
endif()