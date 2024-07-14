/* 
    Group 13 Alice Park & Sayeh Hesamzadeh 
*/ 

void configureAllSensors(); //configures all sensors to standard configuration 
void goMotor(int motPower); // sets motorA and motorD to the given power 
void rotateAngle(int angle, int motPower); // rotate the robot for the specified angle 
void driveDistance(int dist_cm, int motPower, int & prevDeg, bool & button_press); // drives the robot the specified distance 
void waitButton(TEV3Buttons button_name); // wait for push and release of specified button 

// Drives the robot in a square and then back 
task main() 
{ 
    const int ANGLE_CORNER = 90; 
    const int SIDE_LENGTH = 50; 
    bool button_press = false; 

    configureAllSensors(); 
    waitButton(buttonEnter); 

    int prevDeg = ANGLE_CORNER; 
    while(!button_press) 
    { 
        driveDistance(SIDE_LENGTH, 50, prevDeg, button_press); 
        if (!button_press) 
            rotateAngle(prevDeg, 25); 
    } 
} 

void configureAllSensors() 
{ 
    SensorType[S1] = sensorEV3_Touch; 
    SensorType[S2] = sensorEV3_Ultrasonic; 
    SensorType[S3] = sensorEV3_Color; 
    wait1Msec(50); 
    SensorMode[S3] = modeEV3Color_Color; 
    wait1Msec(50); 
    SensorType[S4] = sensorEV3_Gyro; 
    wait1Msec(50); 
    SensorMode[S4] = modeEV3Gyro_Calibration; 
    wait1Msec(100); 
    SensorMode[S4] = modeEV3Gyro_RateAndAngle; 
    wait1Msec(50); 
} 

void goMotor(int motPower) 
{ 
    motor[motorA] = motor[motorD] = motPower; 
} 

void rotateAngle(int angle, int motPower) 
{ 
    resetGyro(S4); 
    if (angle < 0) 
    { 
        motor[motorA] = motPower; 
        motor[motorD] = -motPower; 
    } 
    else 
    { 
        motor[motorA] = -motPower; 
        motor[motorD] = motPower; 
    } 
    angle = abs(angle); 
    while(abs(getGyroDegrees(S4)) < angle) 
    {} 
    motor[motorA] = motor[motorD] = 0; 
} 

void driveDistance(int dist_cm, int motPower, int & prevDeg, bool & button_press) 
{ 
    motPower = abs(motPower); 

    nMotorEncoder[motorA] = 0; 
    if (dist_cm < 0) 
        motor[motorA] = motor[motorD] = -motPower; 
    else 
        motor[motorA] = motor[motorD] = motPower; 

    int enc_limit = abs(dist_cm) * 180 / (PI * 2.75) + 0.5; 
    while (abs(nMotorEncoder[motorA]) < enc_limit && S1 == 0 && !button_press) 
    { 
        if (getButtonPress(buttonEnter)) 
            button_press = true; 
    } 

    if (abs(nMotorEncoder[motorA]) < enc_limit && !button_press) 
    { 
        float dist = nMotorEncoder[motorA]; 
        rotateAngle(180, 25); 
        nMotorEncoder[motorA] = 0; 
        motor[motorA] = motor[motorD] = motPower; 
        while (abs(nMotorEncoder[motorA]) < dist) 
        {} 
        prevDeg = -prevDeg; 
    } 
    motor[motorA] = motor[motorD] = 0; 
} 

void waitButton(TEV3Buttons button_name) 
{ 
    while(!getButtonPress(button_name)) 
    {} 
} 