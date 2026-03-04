/**
 * Voorbeeld voor het gebruik van de DTI inverter via de class DTI
 */

#include <DTI.h>
#include <CAN_adafruit.h> 


DTI myInvertor;
CANRP2040 myCAN;
Message read;

void setup(){
    Serial.begin(9600);
    while (!myCAN.init()){
        Serial.println("CAN down");
    }
    myInvertor.setup(&myCAN);

}

void loop(){
    int current;
    myInverter.SetACCurrent(current);

    //logging can de DTI
    
}
