#include <math.h>

float randomFloat() {
  return random(10000) / 10000.0;
}

float randomGaussian() {
  float u1 = randomFloat();
  float u2 = randomFloat();

//  Calculate two independent Gaussian random variables z1 and z2 using Box - Muller transform
  float z1 = sqrt(-2 * log(u1)) * cos(2 * PI * u2);

  return z1;
}

float lognormalShadowing(float shadowingStdDev, float Mean) {
  float mean = Mean; // Mean of the log-normal distribution (usually 0)
  float shadowing = 0.0;
  float sigma = shadowingStdDev;
  float z1 = randomGaussian();

  shadowing = exp(mean + sigma * z1);

  return shadowing;
}

float* lognormdistrib(float dev[]) {
  //collect all value RSSSi in array
  //calculate maean RSSI
  static float lgnorm[2];
  float temp[stuct];
  float sum1 = 0, sum2 = 0;
  // how to get mean
  for (int a = 0; a < stuct; a++) {
    sum1 += dev[a];
  }
  lgnorm[0] = sum1 / stuct;
  // ----------------------------------
  // range to get mean in zero log-normal distribution
  lgnorm[0] = ((lgnorm[0] < 2) && (lgnorm[0] > (-20))) ? lgnorm[0] : 0;
  // how to get standard deviasi
  for (int b = 0; b < stuct; b++) {
    temp[b] = pow((dev[b] - lgnorm[0]), 2);
  }
  for (int c = 0; c < stuct; c++) {
    sum2 += temp[c];
  }
  lgnorm[1] = sqrt((sum2 / stuct));
  // -----------------------------------
  // range for standard deviation in Environments (indoor, outdoor, specific)
  lgnorm[1] = ((lgnorm[1] > 0) && (lgnorm[1] < 15)) ? lgnorm[1] : random(1,6);
  
  return lgnorm;
}
