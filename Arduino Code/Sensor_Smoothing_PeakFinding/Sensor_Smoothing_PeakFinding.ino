#include <Wire.h>
#include <SPI.h>

#define ARRAYSIZE 100                // number of accel elements to hold

int const MA = 4;                    // length of moving average (samples)
int const PEAKCOUNTING = 1;         // are we counting steps?
//int const DISPLAYING = 0;           // are we sending to display?


//int const DISPLAYING = 1;           // are we sending to display?
float const PEAKTHRESHOLD = 90;   // threshold for step (g)
int const MINIMUMPEAKTIME = 5000;    // minimum time between steps (ms)


int peakCounter = 0;                // # of steps
//int tLastUpdate = 0;                // time since last screen update

int waitTime = 0;                   // time since last step
float sensorData[ARRAYSIZE] = {0};   // initialize array holding accel data

int sensorPin = A3;
int sensorReading;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
    sensorReading = analogRead(sensorPin);
//    Serial.print("Analog reading = ");
//    Serial.println(sensorReading);    

    if (PEAKCOUNTING) {                     
      // shift new data into array
    updateArray(sensorData, sensorReading);
    
    // ***RUNNING AVERAGE SMOOTHING***
    // smooth the data with runing-average filter
    float smData[ARRAYSIZE] = {0};  
    smoothData(sensorData, smData, MA);

    
    // look for peak, if peak is above threshold AND enough time has passed 
    // since last step, then this is a new step
    float peak = findPeak(smData);    

    // *** Threshold***//
    //Students can edit this function below for their peronal agorithm
    if ((peak>PEAKTHRESHOLD) && (millis()-waitTime > MINIMUMPEAKTIME)) {
      peakCounter++;
      waitTime = millis();  
    }
  }

  printData();
}

// shift array once to left, add in new datapoint
void updateArray(float *ar, float newData)
{
  int s = ARRAYSIZE;
  for (int i=0; i<=s-2; i++) {
    ar[i] = ar[i+1];
  }
  ar[s-1] = newData;
}


// m point moving average filter of array ain
void smoothData(float *ain, float *aout, int m)
{
  int s = ARRAYSIZE;
  for (int n = 0; n < s ; n++) {
    int kmin = n>(m-1) ? n - m + 1: 0;
    aout[n] = 0;
  
    for (int k = kmin; k <= n; k++) {
      int d = m > n+1 ? n+1 : m;
      aout[n] += ain[k] / d;
    }
  }
}


// find peak in the array, not-very-good algorithm (O(n)), may consider binary search
// complexity of O(log(n)).
float findPeak(float *ar)
{
  int s = ARRAYSIZE;   // s is length of vector ar
  float p = 0;
  for (int i = 1; i<s-1; i++) {
    if ((ar[i] >= ar[i-1]) && (ar[i] >= ar[i+1])) {
      p = ar[i];
    }
  }
  return p;
}

void printData() {

  // Print the time
  Serial.print(millis());
  Serial.print(", ");

  Serial.print("Reading: ");
  Serial.print(sensorReading);
  Serial.print(", ");

  Serial.print("Peak Count: ");
  Serial.print(peakCounter);
  Serial.println(", ");

//  Serial.print("Peak: ");
//  Serial.print(peak);
//  Serial.print(", ");
   
}

