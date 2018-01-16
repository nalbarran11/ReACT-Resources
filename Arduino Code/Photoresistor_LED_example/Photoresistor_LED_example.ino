

const int photocell = A1; // Photoresistor at Arduino analog pin A1
const int LEDpin=9;       // Led pin at Arduino pin 9

//Variables
int reading;          

void setup(){
 Serial.begin(9600);
 pinMode(LEDpin, OUTPUT);  
 pinMode(photocell, INPUT);
}

void loop(){
  reading = analogRead(photocell);
  
  Serial.print("Reading = ");
  Serial.println(reading); 
  
  if (reading < 425){
    digitalWrite(LEDpin, LOW);  
  }
  else{
    digitalWrite(LEDpin, HIGH); 
  }

  delay(500);
}
