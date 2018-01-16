

const int photocell = A1; // Photoresistor at Arduino analog pin A1

//Variables
int reading;          

void setup(){
 Serial.begin(9600);
 
 pinMode(photocell, INPUT);
}

void loop(){
  reading = analogRead(photocell);
  
  Serial.print("Reading = ");
  Serial.println(reading); 

  delay(500);
}
