#include "Invertor.h"

void Invertor::setup(CANLibrary *mycan) {
    CAN = *mycan;
}

void Invertor::Beginrequest(int _Invertor_ID, int time_interval) {
    Cyclic_transmitting_request(_Invertor_ID, RegID_NominalMotorVoltage, time_interval);
    Cyclic_transmitting_request(_Invertor_ID, RegID_DCVoltage, time_interval);
    Cyclic_transmitting_request(_Invertor_ID, RegID_ActualCurrent, time_interval);
}

void Invertor::SimpleBeginSequence(int _Inverter_ID) {
    LockInverter(_Inverter_ID);
    delay(1);
    UnlockInverter(_Inverter_ID);
    delay(1);
}

void Invertor::BeginSequence_beforeprecharge(int _Inverter_ID) {
    LockInverter(_Inverter_ID);
    delay(1);
    CheckErrorBit(_Inverter_ID);
    delay(1);
    ReadStatusMask(_Inverter_ID);
    delay(1);
}

bool Invertor::Beginsequence_beforeprechargeCHECK(Message message, int _Invertor_RX_ID) {
    if (message.id != _Invertor_RX_ID) return false;
    if (message.data_field[0] != 1) return false;
    return true;
}

void Invertor::BeginSequence_afterprecharge(int _Inverter_ID) {
    ClearError(_Inverter_ID);
    delay(1);
    CheckError(_Inverter_ID);
    delay(1);
    UnlockInverter(_Inverter_ID);
    delay(1);
    ReadStatusMask(_Inverter_ID);
    delay(1);
}

void Invertor::Stop(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x51, 0x04, 0x00}};
    CAN.send(message);
}

void Invertor::LockInverter(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x51, 0x04, 0x00}};
    CAN.send(message);
}

void Invertor::ClearError(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x8E, 0x00, 0x00}};
    CAN.send(message);
}

void Invertor::ReadStatusMask(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x3D, 0x40, 0x00}};
    CAN.send(message);
}

void Invertor::CheckErrorBit(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x3D, 0x40, 0x00}};
    CAN.send(message);
}

void Invertor::CheckError(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x3D, 0x8F, 0x00}};
    CAN.send(message);
}

void Invertor::UnlockInverter(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x51, 0x00, 0x00}};
    CAN.send(message);
}

void Invertor::SetTorque(int _Inverter_ID, int _torque) {
    Message message = {_Inverter_ID, {0x90, _torque & 0xFF, (_torque >> 8) & 0xFF}};
    CAN.send(message);
}

void Invertor::Transmitting_request(int _Inverter_ID, int regID) {
    Message message = {_Inverter_ID, {0x3D, regID, 0x00}};
    CAN.send(message);
}

void Invertor::Cyclic_transmitting_request(int _Inverter_ID, int regID, int time_interval) {
    Message message = {_Inverter_ID, {0x3D, regID, time_interval}};
    CAN.send(message);
}

void Invertor::Stop_transmitting(int _Inverter_ID) {
    Message message = {_Inverter_ID, {0x3D, 0x00, 0xff}};
    CAN.send(message);
}

void Invertor::Auto_CANmessages(int _Inverter_ID) {
    Message message = {_Inverter_ID, 22, {0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}};
    CAN.send(message);
}

void Invertor::Change_transmitting_address(int _Inverter_ID, int adress) {
    Message message = {_Inverter_ID, {0x68, adress}};
    CAN.send(message);
}

void Invertor::SetSpeed(int _Inverter_ID, int speed) {
    Message message = {_Inverter_ID, {0x31, speed & 0xFF, (speed >> 8) & 0xFF}};
    CAN.send(message);
}
