
add_library(temperature_controller temperature_controller.cpp temperature_controller.h)
add_library(room_api room_api.cpp room_api.h)

find_package (Threads REQUIRED)

add_executable(demo_winter demo.cpp)
target_link_libraries(demo_winter temperature_controller room_api Threads::Threads)
target_compile_definitions(demo_winter PUBLIC SEASON_MODIFIER=-1.0)

add_executable(demo_summer demo.cpp)
target_link_libraries(demo_summer temperature_controller room_api Threads::Threads)
target_compile_definitions(demo_summer PUBLIC SEASON_MODIFIER=1.0)