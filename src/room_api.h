#ifndef THERMOSTAT_ROOM_API_H
#define THERMOSTAT_ROOM_API_H

#include <cstdlib>
#include <iostream>

class room_api {
private:
    double room_temp_;
    bool heater_assembly_on_ = false;
    bool cooler_assembly_on_ = false;

    void add_heat();

    void remove_heat();

public:
    room_api();

    virtual ~room_api() = default;

    virtual double get_room_temp();

    virtual void heater_on();

    virtual void heater_off();

    virtual void cooler_on();

    virtual void cooler_off();

    void weather_influence(double input);
};


#endif //THERMOSTAT_ROOM_API_H
