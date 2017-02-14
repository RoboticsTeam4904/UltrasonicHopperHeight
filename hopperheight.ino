    /*
    * Ultrasonic Sensor HC-SR04 and Arduino Tutorial
    *
    * Crated by Dejan Nedelkovski,
    * www.HowToMechatronics.com
    *
    */
    // original from http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
    // defines pins numbers
    const int trigPinLeft = 4;
    const int echoPinLeft = 3;
    const int trigPinRight = 2;
    const int echoPinRight = 1;
    // defines variables
    long durationLeft;
    int distanceLeft; //cm
    long durationRight; 
    int distanceRight; //cm
    float ballHeightLeft; //cm
    float ballHeightRight; //cm
    float ballHeightAvg; //cm
    float ballHopperVolume; //cm^3
    float SIN_OF_MOUNTANGLE = 0.7071; //45°, can arduino do sin without libraries?
    float HOPPERHEIGHT = 100; //cm
    float HOPPERBASE = 5000; //cm^2
    float SENSORWIDTH = 1.375; //cm, actual length
    float BALLSTACKEFFICIENCY = 0.5; 
    float BALLVOLUME = 1072.5; //cm^3, actual volume
    float totalBalls;
    void setup() {
    pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
    pinMode(trigPinRight, OUTPUT);
    pinMode(echoPinRight, INPUT);
    Serial.begin(9600); // Starts the serial communication
    }
    void loop() {
    // Clears the trigPin
    digitalWrite(trigPinLeft, LOW);
    digitalWrite(trigPinRight, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPinLeft, HIGH);
    digitalWrite(trigPinRight, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinLeft, LOW);
    digitalWrite(trigPinRight, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    durationLeft = pulseIn(echoPinLeft, HIGH);
    durationRight = pulseIn(echoPinRight, HIGH);
    // Calculating the distance
    distanceLeft= durationLeft*0.034/2;
    distanceRight= durationRight*0.034/2;
    ballHeightLeft = HOPPERHEIGHT-SIN_OF_MOUNTANGLE*(distanceLeft+SENSORWIDTH);
    ballHeightRight = HOPPERHEIGHT-SIN_OF_MOUNTANGLE*(distanceRight+SENSORWIDTH);
    ballHeightAvg = (ballHeightLeft+ballHeightRight)/2;
    totalBalls = (HOPPERBASE*ballHeightAvg)/(BALLSTACKEFFICIENCY*BALLVOLUME);
    // Prints the distance on the Serial Monitor
    Serial.print("Total balls: ");
    Serial.println(totalBalls);
    
    }
