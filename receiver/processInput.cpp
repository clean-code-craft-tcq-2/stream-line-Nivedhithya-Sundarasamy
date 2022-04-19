#include "processInput.h"

std::vector<int> temperatureInput;
std::vector<int> voltageInput;

void readParamFromConsole(){
    char temp;
    int tempInput, voltage;
    std::string headerInput;
    getline(std::cin, headerInput);
    for(int i = 0; i < 50; i++) {
        std::cin >> tempInput >> temp >> voltage;
        temperatureInput.push_back(tempInput);
        voltageInput.push_back(voltage);
    }
}

int getTemperatureMax(){
    return *(std::max_element(temperatureInput.begin(), temperatureInput.end()));
}

int getTemperatureMin(){
    return *(std::min_element(temperatureInput.begin(), temperatureInput.end()));
}

int getVoltageMax(){
    return *(std::max_element(voltageInput.begin(), voltageInput.end()));
}

int getVoltageMin(){
    return *(std::min_element(voltageInput.begin(), voltageInput.end()));
}

int getSimpleMovingAverageTemperature(){
    int sum = 0;
    for(auto iter = temperatureInput.end()-5; iter < temperatureInput.end(); iter++){
        sum += *iter;
    }
    return sum / 5;
}

int getSimpleMovingAverageVoltage(){
    int sum = 0;
    for(auto iter = voltageInput.end()-5; iter < voltageInput.end(); iter++){
        sum += *iter;
    }
    return sum / 5;
}