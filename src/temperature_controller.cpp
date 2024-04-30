#include "temperature_controller.h"

temperature_controller::temperature_controller(room_api *room, double min_temp, double max_temp) {

    assert(min_temp > 0);
    assert(max_temp > min_temp);
    assert(room != nullptr);
    room_ = room;
    max_temp_ = max_temp;
    min_temp_ = min_temp;
}

int temperature_controller::change_temperature_limits(double min_temp, double max_temp) {

    if ((min_temp < 0) || (max_temp < min_temp))
        return 1;

    max_temp_ = max_temp;
    min_temp_ = min_temp;
    return 0;
}

double temperature_controller::get_min() {
    return min_temp_;
}

double temperature_controller::get_max() {
    return max_temp_;
}

double temperature_controller::get_temp() {
    return room_->get_room_temp();
}

void temperature_controller::alert_user(const char *message) {
    std::cout << message << std::endl;
}

void temperature_controller::update_action() {
    /* did not implement any temperature buffer zones
    (for avoiding continuous toggling of the heater/cooler)
    as the size of these zones would depend on the
    heating/cooling capacity of the device, which is not known.
    */

    double new_temp = get_temp();
    if (new_temp < min_temp_) {
        current_state = HEAT;
    } else if (new_temp > max_temp_) {
        current_state = COOL;
    } else {
        current_state = NONE;
    }
}

void temperature_controller::apply_action() {
    switch (current_state) {
        case HEAT:
            room_->cooler_off();
            room_->heater_on();
            break;
        case COOL:
            room_->heater_off();
            room_->cooler_on();
            break;
        case NONE:
            room_->cooler_off();
            room_->heater_off();
            break;
        default:
            alert_user("Unknown action, controller malfunction!");
            break;
    }
}

void temperature_controller::adjust_temperature() {
    update_action();
    apply_action();
}
