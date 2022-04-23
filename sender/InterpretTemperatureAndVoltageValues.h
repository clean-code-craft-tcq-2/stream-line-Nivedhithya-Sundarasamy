#define MAX_INPUT_STREAM 50

struct parameterInfo{
	int minValue;
	int maxValue;
	int resolution;
};

void interpretTemperatureAndVoltageValuesFromSensors(parameterInfo tempInfo, parameterInfo voltInfo, int tempSensorValues[],
	int VoltageSensorValues[], char* tempAndVoltValuesInCSV[], size_t numberOfSamples);
int calculateMaxIntegerValue(int ADC_Resolution);
int calculateTotalMeasurementRange(int minValue, int maxValue);
float calculateMultiplyingFactor(int param_1, int param_2);
float convertInputIntegerToParameterValue(float conversionFactor, float scalingFactor, parameterInfo ParameterInfo);
int roundOffParameterValue(float interpretedValue);
void allocateCharJaggedArray(char* p[], int arraySize);
void printOnConsole(char* tempAndVoltValuesInCSV[], size_t numberOfSamples);
void freeMemoryForCharJaggedArray(char* pChar[], int arraySize);
void interpretParameterValues(parameterInfo ParameterInfo, int sensorValues[], int* interpretedParameterValues, size_t numberOfSamples);
