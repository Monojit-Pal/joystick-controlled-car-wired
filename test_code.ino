// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "Joystick.h"


// Pin Definitions
#define DCMOTORDRIVERL298_1_PIN_INT1	2
#define DCMOTORDRIVERL298_1_PIN_ENB	6
#define DCMOTORDRIVERL298_1_PIN_INT2	3
#define DCMOTORDRIVERL298_1_PIN_ENA	5
#define DCMOTORDRIVERL298_1_PIN_INT3	4
#define DCMOTORDRIVERL298_1_PIN_INT4	7
#define DCMOTORDRIVERL298_2_PIN_INT1	8
#define DCMOTORDRIVERL298_2_PIN_ENB	10
#define DCMOTORDRIVERL298_2_PIN_INT2	11
#define DCMOTORDRIVERL298_2_PIN_ENA	9
#define DCMOTORDRIVERL298_2_PIN_INT3	12
#define DCMOTORDRIVERL298_2_PIN_INT4	13
#define JOYSTICK_PIN_SW	A1
#define JOYSTICK_PIN_VRX	A3
#define JOYSTICK_PIN_VRY	A4



// Global variables and defines

// object initialization
DCMDriverL298 dcMotorDriverL298_1(DCMOTORDRIVERL298_1_PIN_ENA,DCMOTORDRIVERL298_1_PIN_INT1,DCMOTORDRIVERL298_1_PIN_INT2,DCMOTORDRIVERL298_1_PIN_ENB,DCMOTORDRIVERL298_1_PIN_INT3,DCMOTORDRIVERL298_1_PIN_INT4);
DCMDriverL298 dcMotorDriverL298_2(DCMOTORDRIVERL298_2_PIN_ENA,DCMOTORDRIVERL298_2_PIN_INT1,DCMOTORDRIVERL298_2_PIN_INT2,DCMOTORDRIVERL298_2_PIN_ENB,DCMOTORDRIVERL298_2_PIN_INT3,DCMOTORDRIVERL298_2_PIN_INT4);
Joystick joystick(JOYSTICK_PIN_VRX,JOYSTICK_PIN_VRY,JOYSTICK_PIN_SW);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors #1 - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298_1.setMotorA(200,1);
    dcMotorDriverL298_1.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298_1.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // L298N Motor Driver with Dual Hobby DC motors #2 - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298_2.setMotorA(200,1);
    dcMotorDriverL298_2.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298_2.stopMotors();
    delay(2000);

    }
    else if(menuOption == '3') {
    // PS2 Joystick two axis module - Test Code
    // Read Joystick X,Y axis and press
    int joystickX =  joystick.getX();
    int joystickY =  joystick.getY();
    int joystickSW =  joystick.getSW();
    Serial.print(F("X: ")); Serial.print(joystickX);
    Serial.print(F("\tY: ")); Serial.print(joystickY);
    Serial.print(F("\tSW: ")); Serial.println(joystickSW);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors #1"));
    Serial.println(F("(2) L298N Motor Driver with Dual Hobby DC motors #2"));
    Serial.println(F("(3) PS2 Joystick two axis module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing PS2 Joystick two axis module"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
} 
