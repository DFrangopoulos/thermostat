#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "room_api.h"
#include "temperature_controller.h"

#define MAX_ITERATIONS 1000
#define TEMPERATURE_DELAY 10


void weather_influence(bool *shutdown, room_api *room) {
    while (true) {
        if (*shutdown)
            return;
        room->weather_influence((rand() % 10) * 0.1 * SEASON_MODIFIER);
        std::this_thread::sleep_for(std::chrono::milliseconds(TEMPERATURE_DELAY * 2));
    }
}

int main() {
    srand(time(NULL));

    room_api room;
    bool stop_weather = false;

    //Setup temperature controller
    double demo_min_temp = rand() % 300 + 1;
    double demo_max_temp = demo_min_temp + (rand() % 10) + 1;
    temperature_controller controller(&room, demo_min_temp, demo_max_temp);

    //Enable weather influence
    std::thread weather(weather_influence, &stop_weather, &room);
    weather.detach();

    int iterations;
    for (iterations = 0; iterations < MAX_ITERATIONS; iterations++) {
        controller.adjust_temperature();
        std::cout << " --> target: " << controller.get_min() << " - " << controller.get_max() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(TEMPERATURE_DELAY));
    }
    stop_weather = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(TEMPERATURE_DELAY * 5));

    return 0;
}