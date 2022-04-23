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
    int maxTemp = *(std::max_element(temperatureInput.begin(), temperatureInput.end()));
    std::cout << "Maximum temperature = " << maxTemp << "\n" ;
    return maxTemp;
}

int getTemperatureMin(){
    int minTemp =  *(std::min_element(temperatureInput.begin(), temperatureInput.end()));
    std::cout << "Minimum temperature = " << minTemp << "\n" ;
    return minTemp;
}

int getVoltageMax(){
    int maxVoltage = *(std::max_element(voltageInput.begin(), voltageInput.end()));
    std::cout << "Maximum temperature = " << maxVoltage << "\n" ;
    return maxVoltage;
}

int getVoltageMin(){
    int minVoltage = *(std::min_element(voltageInput.begin(), voltageInput.end()));
    std::cout << "Maximum temperature = " << minVoltage << "\n" ;
    return minVoltage;
}

int getSimpleMovingAverageTemperature(){
    int sum = 0;
    for(auto iter = temperatureInput.end()-5; iter < temperatureInput.end(); iter++){
        sum += *iter;
    }
    std::cout << "Simple moving average of temperature reading = " << sum / 5 << "\n" ;
    return sum / 5;
}

int getSimpleMovingAverageVoltage(){
    int sum = 0;
    for(auto iter = voltageInput.end()-5; iter < voltageInput.end(); iter++){
        sum += *iter;
    }
    std::cout << "Simple moving average of voltage reading = " << sum / 5 << "\n" ;
    return sum / 5;
}