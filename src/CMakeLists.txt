if(BUILD_TESTING)
    add_executable(ImageTest ImageTest.cpp)
    add_executable(ImageCpp Image.cpp
            ImageTest.cpp)
    target_link_libraries(ImageCpp PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(ImageTest)
endif()
