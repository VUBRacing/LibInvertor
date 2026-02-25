/**
 * Voorbeeld voor het gebruik van de bamocar inverter via de classe inverter
 */

#include <Invertor.h>
#include <CAN_adafruit.h> 


Invertor myInvertor;
CANRP2040 myCAN;
Message read;

void setup(){
    Serial.begin(9600);
    while (!myCAN.init()){
        Serial.println("CAN down");
    }
    myInvertor.setup(&myCAN);

    while (myInvertor.Beginsequence_beforeprechargeCHECK(read, INV2_TX_ID)){
        Invertor.BeginSequence_beforeprecharge(INV2_RX_ID);
        read = myCAN.read();
    }

    while (myInvertor.Beginsequence_afterprechargeCHECK(read, INV2_TX_ID)){
        myInvertor.LockInverter(INV2_TX_ID);
        myInvertor.BeginSequence_afterprecharge(INV2_RX_ID);
        myInvertor.Stop(INV2_TX_ID);
        read = myCAN.read();
    }

    myInvertor.Stop();
}

void loop(){
    int speed = 0; 
    myInvertor.SetTorque(INV2_RX_ID, Speed);

    // fix for noisy inverter  
    int Pedal_position = speed;
    if(Pedal_position == 0){
      myInvertor.LockInverter(INV2_RX_ID);
    }else{
      myInvertor.UnlockInverter(INV2_RX_ID);
      myInvertor.SetTorque(INV2_RX_ID, Pedal_position);
    }
}