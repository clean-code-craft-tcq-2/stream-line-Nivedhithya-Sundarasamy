#include <stdio.h>
#include <math.h>
#include <string.h>
#include "InterpretTemperatureAndVoltageValues.h"


	
int calculateMaxIntegerValue(int ADC_Resolution) {
	int maxIntegerValue;
	// Integer Value starts with zero
	maxIntegerValue = (1 << ADC_Resolution) - 1;
	return maxIntegerValue;
}

int calculateTotalMeasurementRange(int minValue, int maxValue) {
	int totalMeasurementRange;
	totalMeasurementRange = maxValue - minValue;
	return totalMeasurementRange;
}

float calculateMultiplyingFactor(int param_1, int param_2) {
	float multiplyingFactor;
	multiplyingFactor = float(param_1) / float(param_2);
	return multiplyingFactor;
}

float convertInputIntegerToParameterValue(float conversionFactor, float scalingFactor, parameterInfo ParameterInfo){
	float parameterValue;	
	parameterValue = ParameterInfo.minValue + (ParameterInfo.maxValue * conversionFactor * scalingFactor);
	return parameterValue;
}

int roundOffParameterValue(float interpretedValue){
	int roundedOffValue;
	roundedOffValue = round(interpretedValue);
	return roundedOffValue;
}

void allocateCharJaggedArray(char* p[], int arraySize){
	for (int i=0; i < arraySize; i++) {
		p[i] = (char*)malloc(10);
	}
}

void printOnConsole(char* tempAndVoltValuesInCSV[], size_t numberOfSamples) {
	printf("Temperature, Voltage \n");
	for (size_t i=0; i<numberOfSamples; i++) {
		printf("%s\n", tempAndVoltValuesInCSV[i]);
	}
}

void freeMemoryForCharJaggedArray(char* pChar[], int arraySize) {
	for (int i=0; i < arraySize; i++) {
		free(pChar[i]);
	}
}

void formatOutputInCSV(int *interpretedTempValues, int *interpretedVoltValues, char* tempAndVoltValuesInCSV[], size_t numberOfSamples){

	allocateCharJaggedArray(tempAndVoltValuesInCSV, numberOfSamples);
	for (size_t i=0; i < numberOfSamples; i++) {	
		sprintf(tempAndVoltValuesInCSV[i], "%d, %d", interpretedTempValues[i], interpretedVoltValues[i]);
	}
	printOnConsole(tempAndVoltValuesInCSV, numberOfSamples);
}

void interpretParameterValues(parameterInfo ParameterInfo, int sensorValues[], int* interpretedParameterValues, size_t numberOfSamples){
	
	int maxIntValue, totalMeasurementRange, roundedOffValue;
	float conversionFactor, scalingFactor, interpretedValue;

	maxIntValue = calculateMaxIntegerValue(ParameterInfo.resolution);
	totalMeasurementRange = calculateTotalMeasurementRange(ParameterInfo.minValue, ParameterInfo.maxValue);
	scalingFactor = calculateMultiplyingFactor(totalMeasurementRange, ParameterInfo.maxValue);
	for (size_t i=0; i<numberOfSamples; i++){
		conversionFactor = calculateMultiplyingFactor(sensorValues[i], maxIntValue);
		interpretedValue = convertInputIntegerToParameterValue(conversionFactor, scalingFactor, ParameterInfo);
		roundedOffValue = roundOffParameterValue(interpretedValue);
		interpretedParameterValues[i] = roundedOffValue;
	}
}

void interpretTemperatureAndVoltageValuesFromSensors(parameterInfo tempInfo, parameterInfo voltInfo, int tempSensorValues[],
	int voltageSensorValues[], char* tempAndVoltValuesInCSV[], size_t numberOfSamples){

	int interpretedTempValues[numberOfSamples];
	int interpretedVoltValues[numberOfSamples];

	interpretParameterValues(tempInfo, tempSensorValues, interpretedTempValues, numberOfSamples);
	interpretParameterValues(voltInfo, voltageSensorValues, interpretedVoltValues, numberOfSamples);
	formatOutputInCSV(interpretedTempValues, interpretedVoltValues, tempAndVoltValuesInCSV, numberOfSamples);
}
