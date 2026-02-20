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

private:
    #if defined(ARDUINO_FEATHER_M4_CAN)
        CANAdafruit CAN;
    #else
        CANRP2040 CAN;
    #endif
    int m_speed;
    int m_torque;
    int m_status;
    int m_airTemperature;
    int m_inverterTemperature;
    int m_motorTemperature;
    int m_Vdc;
    int m_current;
};

#endif // INVERTOR_H
