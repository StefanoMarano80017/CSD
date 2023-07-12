#include "TruncateMean.h"
void TruncatedMean_Init(TruncatedMeanData *data) {
  for (int i = 0; i < SAMPLES; i++) {
    data->temperature[i] = 0;
    data->humidity[i] = 0;
  }
  data->index = 0;
}

void TruncatedMean_AddSample(TruncatedMeanData *data, float temperature, float humidity) {
  data->temperature[data->index] = temperature;
  data->humidity[data->index] = humidity;
  data->index = (data->index + 1) % SAMPLES;
}

float TruncatedMean_CalculateTemperature(TruncatedMeanData *data) {
  float sum = 0;

  float min = data->temperature[0];
  float max = data->temperature[0];
  for (int i = 0; i < SAMPLES; i++) {
    sum += data->temperature[i];
    if (data->temperature[i] < min) {
      min = data->temperature[i];
    }
    if (data->temperature[i] > max) {
      max = data->temperature[i];
    }
  }
  sum -= min;
  sum -= max;
  return sum / (SAMPLES - 2);
}

float TruncatedMean_CalculateHumidity(TruncatedMeanData *data) {
  float sum = 0;
  float min = data->humidity[0];
  float max = data->humidity[0];
  for (int i = 0; i < SAMPLES; i++) {
    sum += data->humidity[i];
    if (data->humidity[i] < min) {
      min = data->humidity[i];
    }
    if (data->humidity[i] > max) {
      max = data->humidity[i];
    }
  }
  sum -= min;
  sum -= max;
  return sum / (SAMPLES - 2);
}
