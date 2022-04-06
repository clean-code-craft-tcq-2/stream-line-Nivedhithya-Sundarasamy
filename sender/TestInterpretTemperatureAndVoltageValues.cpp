#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "../test-framework/catch.hpp"
#include "InterpretTemperatureAndVoltageValues.h"

#include <iostream>
#include <fstream>

using std::cout; 
using std::cerr;
using std::endl; 
using std::string;
using std::ifstream;

void readInputValuesFromFile(string inputFileName, int *parameterSensorADCValues){
	int  valueRead, i=0;
	string InputValues(inputFileName);
	ifstream input_file(InputValues);

	if(!input_file.is_open()) {
		cerr << "Could not open the input file" << endl;
	}
	while (input_file >> valueRead) {
		parameterSensorADCValues[i] = valueRead;
		i++;
	}
	input_file.close();
}

void readExpectedOutputValuesFromFile(string outputFileName, char expectedOutput[][10]){
	int maxChar=50, i=0;
	char outputValueRead[maxChar];
	string expectedTempAndVolt(outputFileName);
	ifstream output_file(expectedTempAndVolt);
	
	if (!output_file.is_open()) {
		cerr << "Could not open the output file" << endl;
	}
	while (output_file.getline(outputValueRead, maxChar)){
		strcpy(expectedOutput[i], outputValueRead);	
		i++;
	}
	output_file.close();
}

SCENARIO( "Interpret Temperature and Voltage for randomly generated integer values of 'n' bit resolution" ){
	struct parameterInfo tempInfo;
	struct parameterInfo voltInfo;
	size_t numberOfSamples = 0;
	int voltSensorADCValues[MAX_INPUT_STREAM];
	int tempSensorADCValues[MAX_INPUT_STREAM];
	char expectedOutput[MAX_INPUT_STREAM][10];

	GIVEN( "Integer values of 'n' bit resolution for given measurement range for simulation of temperature and voltage sensor output"){

		tempInfo.minValue = -45;
		tempInfo.maxValue = 85;
		tempInfo.resolution = 10;
		voltInfo.minValue = 0;
		voltInfo.maxValue = 60;
		voltInfo.resolution = 12;	
		
		readInputValuesFromFile("TempSensorValues.txt", tempSensorADCValues);
		readInputValuesFromFile("VoltSensorValues.txt", voltSensorADCValues);
		
		readExpectedOutputValuesFromFile("OutputValues.txt", expectedOutput);
		
		// Size of Input Samples
		numberOfSamples = sizeof(tempSensorADCValues) / sizeof(tempSensorADCValues[0]);
		
		char* tempAndVoltValuesInCSV[numberOfSamples];

		WHEN ( "interpretChargingCurrentRangeAndOccurences method is called" ) {
			interpretTemperatureAndVoltageValuesFromSensors(tempInfo, voltInfo, tempSensorADCValues,
					voltSensorADCValues, tempAndVoltValuesInCSV, numberOfSamples);

			THEN ( "Interpreted parameter values in CSV format should be" ) {
				for(size_t k=0; k < numberOfSamples; k++) {
					REQUIRE(strcmp(tempAndVoltValuesInCSV[k], expectedOutput[k]) == 0);
				}
			freeMemoryForCharJaggedArray(tempAndVoltValuesInCSV, numberOfSamples);
			}
		}
	}
}

