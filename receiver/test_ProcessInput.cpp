#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test-framework/catch.hpp"
#include "processInput.h"

TEST_CASE("check max in temperature input"){
    readParamFromConsole();
    REQUIRE(85 == getTemperatureMax());
}

TEST_CASE("check min in temperature input"){
    REQUIRE(-44 == getTemperatureMin());
}

TEST_CASE("check min in Voltage input"){
    REQUIRE(60 == getVoltageMax());
}

TEST_CASE("check min in voltage input"){
    REQUIRE(0 == getVoltageMin());
}

TEST_CASE("check simple moving average of last 5 voltage values"){
    REQUIRE(44 == getSimpleMovingAverageVoltage());
}

TEST_CASE("check simple moving average of last 5 temperature values"){
    REQUIRE(-7 == getSimpleMovingAverageTemperature());
}

