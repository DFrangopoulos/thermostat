#include "mock_room_api.h"
using ::testing::Return;

TEST(temperature_controller,verify_get_min) {
    srand(time(NULL));
    mock_room_api room;

    double expected_min = rand() % 200 + 1.0;
    temperature_controller controller(&room,expected_min,300);

    ASSERT_DOUBLE_EQ(controller.get_min(),expected_min);
}

TEST(temperature_controller,verify_get_max) {
    srand(time(NULL));
    mock_room_api room;

    double expected_max = rand() % 200 + 1.0;
    temperature_controller controller(&room,0.1,expected_max);

    ASSERT_DOUBLE_EQ(controller.get_max(),expected_max);
}

TEST(temperature_controller,verify_change_temperature_limits) {
    srand(time(NULL));
    mock_room_api room;

    temperature_controller controller(&room);

    double min_temp = rand() % 300 + 1;
    double max_temp = min_temp + (rand() % 10) + 1;

    ASSERT_EQ(controller.change_temperature_limits(min_temp,max_temp),0);

    ASSERT_DOUBLE_EQ(controller.get_min(),min_temp);
    ASSERT_DOUBLE_EQ(controller.get_max(),max_temp);
}

//ensure that invalid inputs to change_temperature_limits have no effect
//on the temperature controller's configuration
TEST(temperature_controller,verify_change_temperature_limits_invalid) {
    srand(time(NULL));
    mock_room_api room;

    temperature_controller controller(&room,200,300);

    double min_temp = 100 + rand() % 10;
    double max_temp = 50 + rand() % 10;
    ASSERT_EQ(controller.change_temperature_limits(min_temp,max_temp),1);

    ASSERT_DOUBLE_EQ(controller.get_min(),200);
    ASSERT_DOUBLE_EQ(controller.get_max(),300);
}

TEST(temperature_controller,verify_get_temp){
    srand(time(NULL));
    mock_room_api room;
    ON_CALL(room,get_room_temp()).WillByDefault(Return(100.3));
    EXPECT_CALL(room, get_room_temp()).Times(1);
    temperature_controller controller(&room);
    ASSERT_DOUBLE_EQ(controller.get_temp(),100.3);
}

//verify that the controller turns on the heater and turns off the cooler
//if the room temperature is too low
TEST(temperature_controller,verify_undertemp_behavior){
    srand(time(NULL));
    mock_room_api room;
    ON_CALL(room,get_room_temp()).WillByDefault(Return(100.3));
    EXPECT_CALL(room, get_room_temp()).Times(1);
    EXPECT_CALL(room, heater_on()).Times(1);
    EXPECT_CALL(room, cooler_off()).Times(1);
    temperature_controller controller(&room,200.0,210.0);
    controller.adjust_temperature();
}

//verify that the controller turns off the heater and turns on the cooler
//if the room temperature is too high
TEST(temperature_controller,verify_overtemp_behavior){
    srand(time(NULL));
    mock_room_api room;
    ON_CALL(room,get_room_temp()).WillByDefault(Return(100.3));
    EXPECT_CALL(room, get_room_temp()).Times(1);
    EXPECT_CALL(room, heater_off()).Times(1);
    EXPECT_CALL(room, cooler_on()).Times(1);
    temperature_controller controller(&room,10.0,20.0);
    controller.adjust_temperature();
}

//verify that the controller turns off the heater and turns off the cooler
//if the room temperature is within range
TEST(temperature_controller,verify_inrangetemp_behavior){
    srand(time(NULL));
    mock_room_api room;
    ON_CALL(room,get_room_temp()).WillByDefault(Return(100.3));
    EXPECT_CALL(room, get_room_temp()).Times(1);
    EXPECT_CALL(room, heater_off()).Times(1);
    EXPECT_CALL(room, cooler_off()).Times(1);
    temperature_controller controller(&room,100.0,120.0);
    controller.adjust_temperature();
}