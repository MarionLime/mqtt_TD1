
cmake_minimum_required(VERSION 3.5)

project(mqtt_project_TD_1)

find_package(PahoMqttCpp REQUIRED)

add_executable(connexion broker_connexion.cpp)

target_link_libraries(connexion PahoMqttCpp::paho-mqttpp3)

target_include_directories(connexion PRIVATE ${PAHO_MQTT_INCLUDE_DIRS})