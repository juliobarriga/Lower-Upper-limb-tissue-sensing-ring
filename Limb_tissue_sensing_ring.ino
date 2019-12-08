/*
Proyecto:     "Lower/Upper limb tissue sensing ring"
Materia:      Laboratorio de Mecatronica
Instructor:   Hiram
Diseñadores:  Julio David Barriga Tehandón
              Joel
              Ricardo
              Tony
              
 */
#define X_STEP_PIN         54   //  X Sensor
#define X_DIR_PIN          55   //  -------
#define X_ENABLE_PIN       38   //  -------
#define X_MIN_PIN           3   //  limitX
#define X_MAX_PIN           2   //  rutineButton

#define Y_STEP_PIN         60   //  Y Sensor
#define Y_DIR_PIN          61   //  -------
#define Y_ENABLE_PIN       56   //  -------
#define Y_MIN_PIN          14   //  limitY
#define Y_MAX_PIN          15   //  NOT USED

#define Z_STEP_PIN         46   //  Z Sensor
#define Z_DIR_PIN          48   //  -------
#define Z_ENABLE_PIN       62   //  -------
#define Z_MIN_PIN          18   //  limitZ
#define Z_MAX_PIN          19   //  E_MIN_PIN

#define E_STEP_PIN         26   //  Ring
#define E_DIR_PIN          28   //  -------
#define E_ENABLE_PIN       24   //  -------

#define TEMP_0_PIN         13   //  sensorX
#define TEMP_1_PIN         14   //  sensorY
#define TEMP_2_PIN         15   //  sensorZ

int limitE;                     // 0 = Home position
int limitX;                     // 0 = Home position
int limitY;                     // 0 = Home position
int limitZ;                     // 0 = Home position

int sensorX;                    // Stores the value of the X Sensor
int sensorY;                    // Stores the value of the Y Sensor
int sensorZ;                    // Stores the value of the Z Sensor

int statusX = 0;                // Sensing status of the X sensor: 0 = Not sensing; 1 = Sensing; 2 = Max sensing
int statusY = 0;                // Sensing status of the Y sensor: 0 = Not sensing; 1 = Sensing; 2 = Max sensing
int statusZ = 0;                // Sensing status of the Z sensor: 0 = Not sensing; 1 = Sensing; 2 = Max sensing

int counterX = 0;               // Counts the stepper steps of the X sensor
int counterY = 0;               // Counts the stepper steps of the Y sensor
int counterZ = 0;               // Counts the stepper steps of the Z sensor

int zone = 0;                   // Zone of sensing, max number of zones recomended is 3, it depends of the volume wanted to analyse
int study = 0;                  // 2 studies per zone, the ring rotates 50 degrees      

int const wait_home = 100;      // Delay per step, it determine the velocity of the steppers in the Home Rutine
int const wait_test = 100;      // Delay per step, it determine the velocity of the steppers in the Test Rutine
int const wait_rutine = 500;    // Delay per step, it determine the velocity of the steppers in the Rutine Rutine
int const wait_read = 1000;     // Delay per step, it determine the velocity of the steppers in the Read Rutine

int const steps = 3600;         // Number of steps for the Test and 2nd study rutine
int x;                          // Variable to count general steps

char Rutine;

void setup() {
  pinMode(X_STEP_PIN,OUTPUT); 
  pinMode(X_DIR_PIN,OUTPUT);
  pinMode(X_ENABLE_PIN,OUTPUT);
  pinMode(Y_STEP_PIN,OUTPUT); 
  pinMode(Y_DIR_PIN,OUTPUT);
  pinMode(Y_ENABLE_PIN,OUTPUT);
  pinMode(Z_STEP_PIN,OUTPUT); 
  pinMode(Z_DIR_PIN,OUTPUT);
  pinMode(Z_ENABLE_PIN,OUTPUT);
  pinMode(E_STEP_PIN,OUTPUT); 
  pinMode(E_DIR_PIN,OUTPUT);
  pinMode(E_ENABLE_PIN,OUTPUT);
  
  pinMode(X_MIN_PIN,INPUT);
  pinMode(Y_MIN_PIN,INPUT);
  pinMode(Z_MIN_PIN,INPUT);
  pinMode(Z_MAX_PIN,INPUT);
  
  Serial.begin(2000000);         // opens serial port, sets data rate to 128000 bps
  Serial.println("Estudio,Sub-estudio,Pasos X, Pasos Y, Pasos Z");
}

void loop() {
  while(Serial.available()==0){}              //  waits if there is not data
  Rutine = Serial.read();
  if(Rutine == '\n'){}
  else if (Rutine == 'H'){                    // Home Rutine
    /*
    Serial.print("Rutine = ");
    Serial.println(Rutine);
    */
    limitE = digitalRead(Z_MAX_PIN);
    limitX = digitalRead(X_MIN_PIN);
    limitY = digitalRead(Y_MIN_PIN);
    limitZ = digitalRead(Z_MIN_PIN);
    while(limitE == 1) {
      digitalWrite(E_DIR_PIN,HIGH);
      digitalWrite(E_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(E_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitE = digitalRead(Z_MAX_PIN);
    }
    while(limitX == 1) {
      digitalWrite(X_DIR_PIN,LOW);
      digitalWrite(X_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(X_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitX = digitalRead(X_MIN_PIN);
    }
    while(limitY == 1) {
      digitalWrite(Y_DIR_PIN,LOW);
      digitalWrite(Y_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(Y_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitY = digitalRead(Y_MIN_PIN);
    }
    while(limitZ == 1) {
      digitalWrite(Z_DIR_PIN,LOW);
      digitalWrite(Z_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(Z_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitZ = digitalRead(Z_MIN_PIN);
    }
    /*
    Serial.println("Ring in HOME Position");
    */
  }
  else if (Rutine == 'T'){                    // Test Rutine
    /*
    Serial.print("Rutine = ");
    Serial.println(Rutine);
    */
    for(x = 0; x < steps; x++) {
      digitalWrite(E_DIR_PIN,LOW);
      digitalWrite(E_STEP_PIN,HIGH);
      digitalWrite(X_DIR_PIN,HIGH);
      digitalWrite(X_STEP_PIN,HIGH);
      digitalWrite(Y_DIR_PIN,HIGH);
      digitalWrite(Y_STEP_PIN,HIGH);
      digitalWrite(Z_DIR_PIN,HIGH);
      digitalWrite(Z_STEP_PIN,HIGH);  
      delayMicroseconds(wait_test);
      digitalWrite(E_STEP_PIN,LOW);
      digitalWrite(X_STEP_PIN,LOW);
      digitalWrite(Y_STEP_PIN,LOW);
      digitalWrite(Z_STEP_PIN,LOW);
      delayMicroseconds(wait_test);
    }
    delay(500);
    for(x = 0; x < steps; x++) {
      digitalWrite(E_DIR_PIN,HIGH);
      digitalWrite(E_STEP_PIN,HIGH);
      digitalWrite(X_DIR_PIN,LOW);
      digitalWrite(X_STEP_PIN,HIGH);
      digitalWrite(Y_DIR_PIN,LOW);
      digitalWrite(Y_STEP_PIN,HIGH);
      digitalWrite(Z_DIR_PIN,LOW);
      digitalWrite(Z_STEP_PIN,HIGH);  
      delayMicroseconds(wait_test);
      digitalWrite(E_STEP_PIN,LOW);
      digitalWrite(X_STEP_PIN,LOW);
      digitalWrite(Y_STEP_PIN,LOW);
      digitalWrite(Z_STEP_PIN,LOW);
      delayMicroseconds(wait_test);
    }
    /*
    Serial.println("Test Finished");
    */
  }
  else if (Rutine == 'R'){                    // Read Rutine
    // Second analysis
    /*
    Serial.print("Rutine = ");
    Serial.println(Rutine);
    */
    sensorX = analogRead(TEMP_0_PIN);
    sensorY = analogRead(TEMP_1_PIN);
    sensorZ = analogRead(TEMP_2_PIN);
    counterX = 0;
    counterY = 0;
    counterZ = 0;
    if (study == 0){
      while(limitE == 1) {
      digitalWrite(E_DIR_PIN,HIGH);
      digitalWrite(E_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(E_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitE = digitalRead(Z_MAX_PIN);
      }
    }
    if (study == 1){
        for(x = 0; x < steps; x++) {
        digitalWrite(E_DIR_PIN,LOW);
        digitalWrite(E_STEP_PIN,HIGH);  
        delayMicroseconds(wait_home);
        digitalWrite(E_STEP_PIN,LOW);
        delayMicroseconds(wait_home);
      }
    }
    while (statusX == 0 || statusY == 0 || statusZ == 0 || statusX == 1 || statusY == 1 || statusZ == 1) {
      if (sensorX > 1020 && statusX == 0) {
        digitalWrite(X_DIR_PIN,HIGH);
        digitalWrite(X_STEP_PIN,HIGH); 
        delayMicroseconds(wait_rutine);
        digitalWrite(X_STEP_PIN,LOW);
        delayMicroseconds(wait_rutine);
        /*
        Serial.print("Status X = ");
        Serial.println(statusX);
        */
      }
      if (sensorY > 1020 && statusY == 0) {
        digitalWrite(Y_DIR_PIN,HIGH);
        digitalWrite(Y_STEP_PIN,HIGH); 
        delayMicroseconds(wait_rutine);
        digitalWrite(Y_STEP_PIN,LOW);
        delayMicroseconds(wait_rutine);
        /*
        Serial.print("Status Y = ");
        Serial.println(statusY);
        */
      }
      if (sensorZ > 1020 && statusZ == 0) {
        digitalWrite(Z_DIR_PIN,HIGH);
        digitalWrite(Z_STEP_PIN,HIGH); 
        delayMicroseconds(wait_rutine);
        digitalWrite(Z_STEP_PIN,LOW);
        delayMicroseconds(wait_rutine);
        /*
        Serial.print("Status Z = ");
        Serial.println(statusZ);
        */
      }
      if (sensorX <1020 && statusX == 0){
        statusX = 1;
        /*
        Serial.print("Status X = ");
        Serial.println(statusX);
        */
      }
      if (sensorY <1020 && statusY == 0){
        statusY = 1;
        /*
        Serial.print("Status Y = ");
        Serial.println(statusY);
        */
      }
      if (sensorZ <1020 && statusZ == 0){
        statusZ = 1;
        /*
        Serial.print("Status Z = ");
        Serial.println(statusZ);
        */
      }
      if (sensorX < 1020 && statusX == 1) {
        digitalWrite(X_DIR_PIN,HIGH);
        digitalWrite(X_STEP_PIN,HIGH); 
        delayMicroseconds(wait_read);
        digitalWrite(X_STEP_PIN,LOW);
        delayMicroseconds(wait_read);
        counterX = counterX + 1;
        /*
        Serial.print("Status X = ");
        Serial.println(statusX);
        */
      }
      if (sensorY < 1020 && statusY == 1) {
        digitalWrite(Y_DIR_PIN,HIGH);
        digitalWrite(Y_STEP_PIN,HIGH); 
        delayMicroseconds(wait_read);
        digitalWrite(Y_STEP_PIN,LOW);
        delayMicroseconds(wait_read);
        counterY = counterY + 1;
        /*
        Serial.print("Status Y = ");
        Serial.println(statusY);
        */
      }
      if (sensorZ < 1020 && statusZ == 1) {
        digitalWrite(Z_DIR_PIN,HIGH);
        digitalWrite(Z_STEP_PIN,HIGH); 
        delayMicroseconds(wait_read);
        digitalWrite(Z_STEP_PIN,LOW);
        delayMicroseconds(wait_read);
        counterZ = counterZ + 1;
        /*
        Serial.print("Status Z = ");
        Serial.println(statusZ);
        */
      }
      if (sensorX < 600) {
        statusX = 2;
        /*
        Serial.print("Status X = ");
        Serial.println(statusX);
        */
      }
      if (sensorY < 600) {
        statusY = 2;
        /*
        Serial.print("Status Y = ");
        Serial.println(statusY);
        */
      }
      if (sensorZ < 600) {
        statusZ = 2;
        /*
        Serial.print("Status Z = ");
        Serial.println(statusZ);
        */
      }
      /*
      Serial.print("Sensor X = ");
      Serial.println(sensorX);
      Serial.print("Sensor Y = ");
      Serial.println(sensorY);
      Serial.print("Sensor Z = ");
      Serial.println(sensorZ);
      */
      sensorX = analogRead(TEMP_0_PIN);
      sensorY = analogRead(TEMP_1_PIN);
      sensorZ = analogRead(TEMP_2_PIN);
    }
    if (statusX == 2 && statusY == 2 && statusZ == 2) {
      /*
      Serial.println("Read Finished");
      */
      delay(1500);
      limitX = digitalRead(X_MIN_PIN);
      limitY = digitalRead(Y_MIN_PIN);
      limitZ = digitalRead(Z_MIN_PIN);
      while(limitX == 1) {
        digitalWrite(X_DIR_PIN,LOW);
        digitalWrite(X_STEP_PIN,HIGH);  
        delayMicroseconds(wait_home);
        digitalWrite(X_STEP_PIN,LOW);
        delayMicroseconds(wait_home);
        limitX = digitalRead(X_MIN_PIN);
      }
      while(limitY == 1) {
        digitalWrite(Y_DIR_PIN,LOW);
        digitalWrite(Y_STEP_PIN,HIGH);  
        delayMicroseconds(wait_home);
        digitalWrite(Y_STEP_PIN,LOW);
        delayMicroseconds(wait_home);
        limitY = digitalRead(Y_MIN_PIN);
      }
      while(limitZ == 1) {
        digitalWrite(Z_DIR_PIN,LOW);
        digitalWrite(Z_STEP_PIN,HIGH);  
        delayMicroseconds(wait_home);
        digitalWrite(Z_STEP_PIN,LOW);
        delayMicroseconds(wait_home);
        limitZ = digitalRead(Z_MIN_PIN);
      }
      statusX = 0;
      statusY = 0;
      statusZ = 0;
      /*
      Serial.print("Status X = ");
      Serial.println(statusX);
      Serial.print("Status Y = ");
      Serial.println(statusY);
      Serial.print("Status Z = ");
      Serial.println(statusZ);
      Serial.print("Counter X = ");
      Serial.println(counterX);
      Serial.print("Counter Y = ");
      Serial.println(counterY);
      Serial.print("Counter Z = ");
      Serial.println(counterZ);
      Serial.print("Study = ");
      Serial.println(study);
      */
    }
    Serial.print(zone);
    Serial.print(",");
    Serial.print(study);
    Serial.print(",");
    Serial.print(counterX);
    Serial.print(",");
    Serial.print(counterY);
    Serial.print(",");
    Serial.println(counterZ);
    study = study + 1;
    if (study == 2) {
      study = 0;
      zone = zone + 1;
      limitE = digitalRead(Z_MAX_PIN);
    }
    counterX = 0;
    counterY = 0;
    counterZ = 0;
  }
  else if (Rutine == 'E'){                    // End Rutine
    zone = 0;
    study = 0;
    counterX = 0;
    counterY = 0;
    counterZ = 0;
    statusX = 0;
    statusY = 0;
    statusZ = 0;
    /*
    Serial.print("Rutine = ");
    Serial.println(Rutine);
    */
    limitE = digitalRead(Z_MAX_PIN);
    limitX = digitalRead(X_MIN_PIN);
    limitY = digitalRead(Y_MIN_PIN);
    limitZ = digitalRead(Z_MIN_PIN);
    while(limitE == 1) {
      digitalWrite(E_DIR_PIN,HIGH);
      digitalWrite(E_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(E_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitE = digitalRead(Z_MAX_PIN);
    }
    while(limitX == 1) {
      digitalWrite(X_DIR_PIN,LOW);
      digitalWrite(X_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(X_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitX = digitalRead(X_MIN_PIN);
    }
    while(limitY == 1) {
      digitalWrite(Y_DIR_PIN,LOW);
      digitalWrite(Y_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(Y_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitY = digitalRead(Y_MIN_PIN);
    }
    while(limitZ == 1) {
      digitalWrite(Z_DIR_PIN,LOW);
      digitalWrite(Z_STEP_PIN,HIGH);  
      delayMicroseconds(wait_home);
      digitalWrite(Z_STEP_PIN,LOW);
      delayMicroseconds(wait_home);
      limitZ = digitalRead(Z_MIN_PIN);
    }
    /*
    Serial.println("Ring in HOME Position");
    */
  }
  else{
  }
}
