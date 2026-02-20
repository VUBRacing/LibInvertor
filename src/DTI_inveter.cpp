#include "DTI.h"

/* The DTI hope after the UK race.
Goal: more power, faster car

CAN DTI: ID
    - REG, Inverter ID 

ex. - ID inverter: 67 HEX?
    - REG  0X01
    ID  full : 0X 00 00 01 22 
    Weird can CAN have this big of ID???
    
    
Datafield: Data can be send undermany types in byte
    - DTI system uses Big_Edian
    */

#if defined(ARDUINO_FEATHER_M4_CAN)
    void DTI::setup(CANAdafruit *mycan) {
        CAN = *mycan;
    }
#else
    void DTI::setup(CANRP2040 *mycan) {
        CAN = *mycan;
    }
#endif

/**
 * ID is here shifted with the inveter ID first add the reg, masked to ensure proper format
 * Then add inverter ID also masked to ensure proper format
 */
uint16_t DTI::Make_Full_ID(uint8_t inverterID, uint8_t regID)
{
    return ((regID & 0x3F) << 5) | (inverterID & 0x1F);
}

/**
 * Big Edian notation is notation uses by the DTI buffer is private
 * For proper format you have to add 0xFF after the datalength
 */
void DTI::BigEndian(int number, uint8_t* buffer, uint8_t length) {
    // Fill 8 bytes with 0xFF
    for (uint8_t i = 0; i < 8; i++)
        buffer[i] = 0xFF;

    // Write big endian value
    for (uint8_t i = 0; i < length; i++)
    {
        buffer[i] = (number >> (8 * (length - 1 - i))) & 0xFF;
    }
}


/**
 * Torque setting: set torque (AC current to motor)
 * Range: 
 * length:
 */
void DTI::SetACCurrent(int _Inverter_ID, int speed) {
    Message message;
    // create ID
    uint8_t Reg_ID = 0x000001;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    //create datafield
    int candata[8];
    BigEndian(speed, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //Send message
    CAN.send(message);
}

/**
 * BrakeCurrent setting: set inverse torque (negatieve AC current)
 * Range:
 * Lenght:
 */
void DTI::SetBrakeCurrent(int _Inverter_ID, int brake) {
    Message message;
    // create ID
    uint8_t Reg_ID = 0x000002;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(brake, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * ERPM setting: set a RPM for motor !nor the same as RPM
 * Range:
 * Length:
 */
void DTI::SetERPM(int _Inverter_ID, int speed) {
    Message message;
    // create ID
    uint8_t Reg_ID = 0x000003;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(Speed, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Position setting: set the motor in a exact position
 * Range:
 * Length:
 */
void DTI::SetPosition(int _Inverter_ID, int position) {
    Message message;
    uint8_t Reg_ID = 0x000004;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(position, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Relatieve Current setting: set the current in relation to current setting
 * Not exact understand: add current like  a boost???
 * Range:
 * Length:
 */
void DTI::SetRelativeCurrent(int _Inverter_ID, int current) {
    Message message;
    uint8_t Reg_ID = 0x000005;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(current, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Relatieve braking current: set the inverse current in relation to current setting
 * Not exact understand: add current like  a boost???
 * Range:
 * Lenght:
 */
void DTI::SetRelatieveBrakeCurrent(int _Inverter_ID, int brake) {
    Message message;
    uint8_t Reg_ID = 0x000006;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(brake, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Maximimum Ac current setting: Set maximum AC current
 * Range:
 * Lenght:
 */
void DTI::SetmaximumACcurrent(int _Inverter_ID, int max_AC) {
    Message message;
    // create ID
    uint8_t Reg_ID = 0x000008;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
     // create datafield
    int candata[8];
    BigEndian(max_AC, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Maximum AC braking current: set maximum AC braking current
 * Range:
 * Lenght:
 */ 
void DTI::SetMaximumACBrakeCurrent(int _Inverter_ID, int current) {
    Message message;
    // createID
    uint8_t Reg_ID = 0x000001;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(current, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);;
}

/**
 * Maximum DC  current: set maximum DC current
 * Range:
 * Lenght:
 */ 
void DTI::SetMaximumDCcurrent(int _Inverter_ID,int max_DC){
    Message message;
    // create ID
    uint8_t Reg_ID = 0x00000A;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(brake, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);  
}

/**
 * Maximum DC braking current: set maximum DC braking current
 * Range:
 * Lenght:
 */ 
void DTI::SetmaximumDCBrakeCurrent(int _Inverter_ID, int speed) {
    Message message;
    // createID
    uint8_t Reg_ID = 0x000001;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(brake, candata,2)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    //send message
    CAN.send(message);
}

/**
 * Drive enable: need to be send periodicaly to hold the inverter in enable position
 * Send 1 byte 0x01
 */
void DTI::DriveEnable(int _Inverter_ID){
    Message message;
    // createID
    uint8_t Reg_ID = 0x00000C;
    message.id = Make_Full_ID(_Inverter_ID, Reg_ID);
    // create datafield
    int candata[8];
    BigEndian(0x01, candata,1)
    for (int i = 0; i < 8; i++) {
        Message.datafield.pushback(candata[i]);
    }
    // send message
    CAN.send(message);
}

void



