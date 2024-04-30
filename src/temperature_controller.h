#ifndef THERMOSTAT_CONTROLLER_H
#define THERMOSTAT_CONTROLLER_H

#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>

#include "room_api.h"

//controller action state
enum temp_action {
    HEAT, COOL, NONE
};

#define DEFAULT_MIN_TEMP 288.0
#define DEFAULT_MAX_TEMP 295.0

class temperature_controller {

private:
    double min_temp_, max_temp_;
    temp_action current_state = NONE;
    room_api *room_ = nullptr;

    /**
     * @brief Method for fetching and evaluating the current room temperature
     */
    void update_action();

    /**
     * @brief Method for applying corrective action based on the latest temperature evaluation
     */
    void apply_action();

    /**
     * @brief Method for sending an alert to the user
     * @param message - message to be sent to user
     */
    void alert_user(const char *message);

public:

    /**
     * @brief Temperature controller class
     * @param room - pointer to the room_api class
     * @param min_temp - lower range boundary (in degrees Kelvin)
     * @param max_temp - upper range boundary (in degrees Kelvin)
     */
    temperature_controller(room_api *room, double min_temp = DEFAULT_MIN_TEMP, double max_temp = DEFAULT_MAX_TEMP);

    ~temperature_controller() = default;

    /**
     * @brief Method for modifying the desired temperature range (in degrees Kelvin)
     * @param min_temp - lower range boundary (in degrees Kelvin)
     * @param max_temp - upper range boundary (in degrees Kelvin)
     * @return 0 -> success , 1 -> failure
     */
    int change_temperature_limits(double min_temp, double max_temp);

    /**
     * @brief Method for fetching the currently configured lower temperature boundary
     * @return Currently configured lower temperature boundary (in degrees Kelvin)
     */
    double get_min();

    /**
     * @brief Method for fetching the currently configured upper temperature boundary
     * @return Currently configured upper temperature boundary (in degrees Kelvin)
     */
    double get_max();

    /**
     * @brief Method for fetching the current room temperature using the room_api
     * @return Current room temperature (in degrees Kelvin)
     */
    double get_temp();

    /**
     * @brief Method for triggering the temperature to evaluate room temperature and act
     */
    void adjust_temperature();
};

#endif //THERMOSTAT_CONTROLLER_H
