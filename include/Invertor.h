#ifndef INVERTOR_H
#define INVERTOR_H

#include <CAN_Library.h>
#include <Invertor_IDs.h>
#include <Arduino.h>

class Invertor {
public:
    void setup(CANAdafruit *mycan);
    void Beginrequest(int _Invertor_ID, int time_interval);
    void SimpleBeginSequence(int _Inverter_ID);
    void BeginSequence_beforeprecharge(int _Inverter_ID);
    bool Beginsequence_beforeprechargeCHECK(Message message, int _Invertor_RX_ID);
    void BeginSequence_afterprecharge(int _Inverter_ID);
    bool Beginsequence_afterprechargeCHECK(Message message, int _Invertor_RX_ID);
    void Stop(int _Inverter_ID);
    void LockInverter(int _Inverter_ID);
    void ClearError(int _Inverter_ID);
    void ReadStatusMask(int _Inverter_ID);
    void CheckErrorBit(int _Inverter_ID);
    void CheckError(int _Inverter_ID);
    void UnlockInverter(int _Inverter_ID);
    void SetTorque(int _Inverter_ID, int _torque = 0);
    void Transmitting_request(int _Inverter_ID, int regID);
    void Cyclic_transmitting_request(int _Inverter_ID, int regID, int time_interval);
    void Stop_transmitting(int _Inverter_ID);
    void Auto_CANmessages(int _Inverter_ID);
    void Change_transmitting_address(int _Inverter_ID, int adress);
    void SetSpeed(int _Inverter_ID, int speed);

private:
    CANAdafruit CAN;
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
