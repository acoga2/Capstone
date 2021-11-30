// This sketch isolates the audio processing elements of the AM/FM radio for testing

 // Define pins
 #define pwr         D2  // Power switch (likely unneeded)
 #define mode        D4  // AM/FM mode selection switch

 #define audOutput   D3  // PWM audio output to speaker
 
 #define AMrec       A0  // AM receiver 
 #define FMrec       A1  // FM receiver 
 #define volIn       A2  // Volume control
 #define freqIn      A3  // Frequency control

 // Define variables
 // float audioIN = 0;                      // Audio input
 float NRweight = 0.3;                   // Noise reduction (NR) weight factor
 float audioOLD = 0;
 float audioAVG = 0;                     // Audio variables for noise reduction
 float audioAMP = 0, ampFactor = 5;     // Amplified audio and gain amount
 float AMPSUM = 0, AMPAVG = 0;

 // Test values
 float audioIN[26] = {0.0, 0.02, 0.06, 0.12, 0.18, 0.25, 0.33, 0.46, 0.48, 0.59, 0.66, 0.64, 0.70, 0.84, 1.0, 0.95, 0.84, 0.86, 0.73, 0.59, 0.45, 0.32, 0.20, 0.25, 0.12, 0.0};

void setup() {
  Serial.begin(9600);
  Serial.print("Program started. Entered setup(). \n");

  // Noise reduction
  /*  Exponential filter recursively reduces noise.
   *  The weight factor, 0 < a < 1, determines reduction amount
   */

  for (int i = 0; i < 26; i++) {
    
    audioAVG = ((NRweight*audioIN[i])+(1-NRweight)*audioOLD);
    audioOLD = audioAVG;

    // AMPSUM += audioAVG;
    // AMPAVG = AMPSUM / i;
  // Sound equalization 
  /*  Run thru array, get abs maximum and local max (within, say, 30 samples)
   *  Volume should be within range 0 to say 10 dB, so set max vol to 10dB
   *  Run thru array, setting vol of each sample to its ratio with max * 10
   */

  // Sound amplification
  // ampFactor = 2.5/AMPAVG;
  audioAMP = audioAVG * ampFactor;
  if (audioAMP > 5) {
    audioAMP = 5; // Cap audio at 5V
  }
  else if (audioAMP < -5) {
    audioAMP = -5; // Cap audio at -5V
  }

  Serial.print(audioAMP);
  Serial.print("\n");
  }
}

void loop() {
  

}
