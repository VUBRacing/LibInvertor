#include "DTI.h"
#include "DTI_IDs.h"

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
    uint8_t Reg_ID = REG_Current;
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
    uint8_t Reg_ID = REG_BrakeCurrent;
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
    uint8_t Reg_ID = REG_ERPM;
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
    uint8_t Reg_ID = REG_Position;
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
    uint8_t Reg_ID = REG_Relative_Current;
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
    uint8_t Reg_ID = REG_Relative_Brake_Current;
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
    uint8_t Reg_ID = REG_Set_Max_AC;
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
    uint8_t Reg_ID = REG_Set_Max_brake_AC;
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
    uint8_t Reg_ID = REG_Set_Max_DC;
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
    uint8_t Reg_ID = REG_Set_Max_brake_DC;
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
    uint8_t Reg_ID = REG_Enable;
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

/**
 *Read incomming message and add data for logging
 *Informative use for Python Interface
 * Use for 

 */
void DTI:: Logging(Message reading){
    MessageID = reading.id
    switch (MessageID)
    {
    case TRANSMIT_Control_ID:
        PrintIDlogging("TRANSMIT_Control_ID", reading);

        // update DTI logging variables 
        control_Mode = reading.datafield[0];
        Target_Iq = (reading.datafield[1] << 8) | reading.datafield[2];
        m_pos = (reading.datafield[3] << 8) | reading.datafield[4];
        M_still = reading.datafield[7];
        break;

    case TRANSMIT_ERPM_ID:
        PrintIDlogging("TRANSMIT_ERPM_ID", reading);

        // update DTI logging variables 
        ERPM = (reading.datafield[0] << 16) | (reading.datafield[1] << 8) | reading.datafield[2]; 
        Duty_Cycle = (reading.datafield[4] << 8) | reading.datafield[5];
        V_input = (reading.datafield[6] << 8) | reading.datafield[7];
        break;

    case TRANSMIT_ACDC_Current_ID:
        PrintIDlogging("TRANSMIT_ACDC_Current_ID", reading);

        // update DTI logging variables 
        AC_current = (reading.datafield[0] << 8) | reading.datafield[1];
        DC_current = (reading.datafield[2] << 8) | reading.datafield[3];
        break;

    case TRANSMIT_Temp_ID:
        PrintIDlogging("TRANSMIT_Temp_ID", reading);

        // update DTI logging variables 
        T_controller = (reading.datafield[0] << 8) | reading.datafield[1];
        T_motor = (reading.datafield[2] << 8) | reading.datafield[3];
        Fault_code = reading.datafield[4];

        // process information
        if (Fault_code != 0x00){
            Print_FaultCode();
        }
        break;

    case TRANSMIT_Id_Iq_ID:
        PrintIDlogging("TRANSMIT_Id_Iq_ID", reading);

        // update DTI logging variables 
        Id = (reading.datafield[0] << 22) | (reading.datafield[1] << 16) | (reading.datafield[2] << 8) | reading.datafield[3];
        Iq = (reading.datafield[0] << 22) | (reading.datafield[1] << 16) | (reading.datafield[2] << 8) | reading.datafield[3];
        break;

    case TRANSMIT_Throttle_ID:
        PrintIDlogging("TRANSMIT_Throttle_ID", reading);

        // update DTI logging variables 
        throttle = reading.datafield[0];
        brake = reading.datafield[1];
        digital_IN =reading.datafield[2];
        drive_EN =reading.datafield[3];
        limit_config = reading.datafield[4];
        RPM_limit = reading.datafield[5]; 
        break;

    case TRANSMIT_Max_ACcurrent_ID:
        PrintIDlogging("TRANSMIT_Max_ACcurrent_ID", reading);

        // update DTI logging variables 
        Max_AC_current = (reading.datafield[0] << 8) | reading.datafield[1];
        Avail_max_AC_current = (reading.datafield[2] << 8) | reading.datafield[3];
        Min_AC_current = (reading.datafield[4] << 8) | reading.datafield[5];
        Avail_min_AC_current = (reading.datafield[6] << 8) | reading.datafield[7];
        break;

    case TRANSMIT_Max_DCcurrent_ID:
        PrintIDlogging("TRANSMIT_Max_DCcurrent_ID", reading);

        // update DTI logging variables 
        Max_DC_current = (reading.datafield[0] << 8) | reading.datafield[1];
        Avail_max_DC_current = (reading.datafield[2] << 8) | reading.datafield[3];
        Min_DC_current =(reading.datafield[4] << 8) | reading.datafield[5];
        Avail_min_DC_current =(reading.datafield[6] << 8) | reading.datafield[7];
        break;
    
    default:
        break;
    }

}

void DTI::PrintIDlogging(String ID,Message Reading){
        Serial.print(ID);
        Serial.print(" :")
        for(int i = 0; i > reading.packet_size; i++){
            Serial.print(reading.datafield[i]);
            Serial.print(", ")
        }
        Serial.println(" :END")
        break;
}

void DTI::PrintFaultCode(){
    switch (FaultCode)
    {
    case 0x01:
        Serial.println("FAULT CODE! : Overvoltage");
        break;
    case 0x02:
        Serial.println("FAULT CODE! : Undervoltage");
        break;
    case 0x03:
        Serial.println("FAULT CODE! : DRV transistor drive error");
        break;
    case 0x04:
        Serial.println("FAULT CODE! : ABS OverCurrent (AC)");
        break;
    case 0x05:
        Serial.println("FAULT CODE! : CONTROLER Overtemp");
        break;
    case 0x06:
        Serial.println("FAULT CODE! : MOTOR Overtemp");
        break;
    case 0x07:
        Serial.println("FAULT CODE! : Sensor wire fault");
        break;
    case 0x08:
        Serial.println("FAULT CODE! : Sensor general fault");
        break;
    case 0x09: 
        Serial.println("FAULT CODE! : CAN Command Error");
        break;
    case 0x0A:
        Serial.println("FAULT CODE! : Analog Input Error");
        break;
    default:
        Serial.println("FAULT CODE! : Unknow Error Code");
        break;
    }
}



