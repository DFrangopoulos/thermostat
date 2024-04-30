#ifndef THERMOSTAT_TEMPERATURE_CONTROLLER_TEST_H
#define THERMOSTAT_TEMPERATURE_CONTROLLER_TEST_H

#include "../src/room_api.h"
#include "../src/temperature_controller.h"
#include <gmock/gmock.h>

class mock_room_api: public room_api{
public:
    mock_room_api() : room_api() {}
    MOCK_METHOD(double,get_room_temp,(),(override));
    MOCK_METHOD(void,heater_off,(),(override));
    MOCK_METHOD(void,heater_on,(),(override));
    MOCK_METHOD(void,cooler_off,(),(override));
    MOCK_METHOD(void,cooler_on,(),(override));
};


#endif //THERMOSTAT_TEMPERATURE_CONTROLLER_TEST_H
