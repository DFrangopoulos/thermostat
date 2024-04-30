#include "room_api.h"

room_api::room_api() {
    room_temp_ = 200 + (rand() % 20) * 0.1;
}

void room_api::add_heat() {
    room_temp_ = room_temp_ + (rand() % 10) * 0.1;
}

void room_api::remove_heat() {
    room_temp_ = std::max((room_temp_ - (rand() % 10) * 0.1), 1.0);
}

void room_api::heater_on() {
    if (!heater_assembly_on_) {
        std::cout << "Heater ON!" << std::endl;
        heater_assembly_on_ = true;
    }
}

void room_api::heater_off() {
    if (heater_assembly_on_) {
        std::cout << "Heater OFF!" << std::endl;
        heater_assembly_on_ = false;
    }
}

void room_api::cooler_on() {
    if (!cooler_assembly_on_) {
        std::cout << "Cooler ON!" << std::endl;
        cooler_assembly_on_ = true;
    }
}

void room_api::cooler_off() {
    if (cooler_assembly_on_) {
        std::cout << "Cooler OFF!" << std::endl;
        cooler_assembly_on_ = false;
    }
}

double room_api::get_room_temp() {
    if (cooler_assembly_on_)
        remove_heat();
    if (heater_assembly_on_)
        add_heat();
    std::cout << room_temp_ << std::endl;
    return room_temp_;
}

void room_api::weather_influence(double input) {
    double new_temp = room_temp_ + input;
    if (new_temp > 0)
        room_temp_ = new_temp;
}