#ifndef DTI_H
#define DTI_H

#include <CAN_Library.h>
#include <CAN_Adafruit.h>
#include <CAN_RP2040.h>
#include <Invertor_IDs.h>
#include <Arduino.h>



class DTI {
public:
    #if defined(ARDUINO_FEATHER_M4_CAN)
        void setup(CANAdafruit *mycan);
    #else
        void setup(CANRP2040 *mycan);
    #endif

    int Make_Full_ID(int _Inveter_ID, int Reg_ID);
    void BigEndian(int number, uint8_t* buffer, uint8_t length);
    void SetACCurrent(int _Inverter_ID, int speed);
    void SetBrakeCurrent(int _Inverter_ID, int Brake);
    void SetERPM(int _Inverter_ID, int speed);
    void SetPosition(int _Inverter_ID, int position);
    void SetRelativeCurrent(int _Inverter_ID, int current);
    void SetRelatieveBrakeCurrent(int _Inverter_ID, int brake);
    void SetmaximumACcurrent(int _Inverter_ID, int max_AC);
    void SetMaximumACBrakeCurrent(int _Inverter_ID, int current);
    void SetMaximumDCcurrent(int _Inverter_ID,int max_DC);
    void SetmaximumDCBrakeCurrent(int _Inverter_ID, int speed);
    void DriveEnable(int _Inverter_ID);
    void Logging(Message reading);
    void :PrintIDlogging(String ID,Message Reading); 

private:
    #if defined(ARDUINO_FEATHER_M4_CAN)
        CANAdafruit CAN;
    #else
        CANRP2040 CAN;
    #endif

    // data given in Control ID
    int control_Mode;
    int Target_Iq;
    int m_pos;
    int m_still;
    //data   given in ERPM ID
    int ERPM;
    int Duty_Cycle;
    int V_input;
    // data given in ACDC current ID
    int AC_current;
    int DC_current;
    // data  given in Temp ID
    int T_controller;
    int T_motor;
    int Fault_code;
    // data given in Id Iq ID
    int Id;
    int Iq;
    // data given in throttle ID
    int throttle;
    int brake;
    int digital_IN;
    int drive_EN;
    int limit_config;
    int RPM_limit;
    // data give in MAX AC current ID
    int Max_AC_current;
    int Avail_max_AC_current;
    int Min_AC_current;
    int Avail_min_AC_current; 
    // data given in MAC DC current ID
    int Max_DC_current;
    int Avail_max_DC_current; 
    int Min_DC_current;
    int Avail_min_DC_current;
};

#endif // 
