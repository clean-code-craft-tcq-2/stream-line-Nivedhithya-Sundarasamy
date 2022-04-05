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

void getInputValues(char inputFileName[], int *parameterSensorADCValues){
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
	cout << endl;
	input_file.close();
}

SCENARIO( "Interpret Temperature and Voltage for randomly generated integer values of 'n' bit resolution" ){
	struct parameterInfo tempInfo;
	struct parameterInfo voltInfo;
	size_t numberOfSamples = 0;
	int voltSensorADCValues[MAX_INPUT_STREAM];
	int tempSensorADCValues[MAX_INPUT_STREAM];
	int valueReadTemp, valueReadVolt, i=0, j=0;
	int maxChar=50;
	char expectedOutput[MAX_INPUT_STREAM][10];
	char outputValueRead[maxChar];

	GIVEN( "Integer values of 'n' bit resolution for given measurement range for simulation of temperature and voltage sensor output"){

		tempInfo.minValue = -45;
		tempInfo.maxValue = 85;
		tempInfo.resolution = 10;
		voltInfo.minValue = 0;
		voltInfo.maxValue = 60;
		voltInfo.resolution = 12;	
		
		getInputValues("TempSensorValues.txt", tempSensorADCValues);
		getInputValues("VoltSensorValues.txt", voltSensorADCValues);
		
		//Expected Output Values
		string expectedTempAndVolt("OutputValues.txt");
	
		ifstream output_file(expectedTempAndVolt);

		if (!output_file.is_open()) {
			cerr << "Could not open the output file" << endl;
		}
		while (output_file.getline(outputValueRead, maxChar)){
			strcpy(expectedOutput[j], outputValueRead);	
			j++;
		}
		cout << endl;
		output_file.close();
		
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
			}
		}
	}
}

