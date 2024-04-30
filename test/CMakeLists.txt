include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)

add_executable(thermostat_test
        ../src/temperature_controller.h ../src/temperature_controller.cpp
        ../src/room_api.cpp ../src/room_api.h mock_room_api.h
        temperature_controller_test.cpp
        )
target_link_libraries(thermostat_test GTest::gmock GTest::gmock_main)

add_test(AllTestsInthermostat thermostat_test)