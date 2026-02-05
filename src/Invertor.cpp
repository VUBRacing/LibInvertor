#include "Invertor.h"

void Invertor::setup(CANLibrary *mycan) {
    CAN = *mycan;
}

void Invertor::Beginrequest(int _Invertor_ID, int time_interval) {
    Cyclic_transmitting_request(_Invertor_ID, RegID_NominalMotorVoltage, time_interval);
    Cyclic_transmitting_request(_Invertor_ID, RegID_DCVoltage, time_interval);
    Cyclic_transmitting_request(_Invertor_ID, RegID_ActualCurrent, time_interval);
}

/**
 * simple beginsequence for the inverter
 * @param _Inverter_ID ID from inverter in CAN_ID
 * geeft geen respons van de invertor
 * Source: mail Unitek
 */
void Invertor::SimpleBeginSequence(int _Inverter_ID) {
    LockInverter(_Inverter_ID);
    delay(1);
    UnlockInverter(_Inverter_ID);
    delay(1);
}

/**
 * beginsequence of the inverter before the precharge is done
 * @param _Inverter_ID ID from inverter in CAN_ID
 *
 * Invertor antwoord op statusmask met
 * 
 * Source: mail Unitek
 */
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
    if (message.data_field[0] != 0x30) return false;
    if (message.data_field[3] != 2) return false;
    return true;
}

/**
 * beginsequence of the invertor after the precharge is done
 * @param _Inverter_ID ID from inverter in CAN_ID
 *
 * source: mail Unitek
 */
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

bool Invertor::Beginsequence_afterprechargeCHECK(Message message, int _Invertor_RX_ID){
    if(message.id != _Invertor_RX_ID) return false;
    if (message.data_field[0] != 0x32 ) return false;
    if (message.data_field[3] != 1) return false;
    return true; 
  }

/**
 * Stop the inverter
 * @param _Inverter_ID ID from inverter in CAN_ID
 */
void Invertor::Stop(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x51);
    message.data_field.push_back(0x04);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * lock the inverter
 * @param _Inverter_ID ID from inverter in CAN_ID
 * No CAN respons from the invertor
 */
void Invertor::LockInverter(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x51);
    message.data_field.push_back(0x04);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * clears the invertor
 * @param _Inverter_ID ID from inverter in CAN_ID
 * No CAN respons from the invertor
 */
void Invertor::ClearError(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x8E);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Read Status
 * Geeft een waarde terug waarschijnelijk over de status in de invertor
 * @param _Inverter_ID ID from inverter in CAN_ID
 */
void Invertor::ReadStatusMask(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x40);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Check for errors bit
 * Invertor antwoord met de bit error
 *    error :
 *    No error :
 * 
 * @param _Inverter_ID ID from inverter in CAN_ID
 */
void Invertor::CheckErrorBit(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x40);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Checks for errors
 * Answer of the invertor
 *  Error :
 *  No error : 
 * @param _Inverter_ID ID from inverter in CAN_ID
 */
void Invertor::CheckError(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x8F);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Unlock the inverter
 * @param _Inverter_ID ID from inverter in CAN_ID
 * No CAN respons of the invertor
 */
void Invertor::UnlockInverter(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x51);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Set the torque of the motor
 * @param _Inverter_ID ID from inverter in CAN_ID
 * @param torque the torque of the motor
 * No answer of the invertor
 */
void Invertor::SetTorque(int _Inverter_ID, int _torque) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x90);
    message.data_field.push_back(_torque & 0xFF);
    message.data_field.push_back((_torque >>= 8) & 0xFF);

    CAN.send(message);
}

/**
 * Transmitting request Sending once
 *@param _Inverter_ID ID from inverter in CAN_ID
 *@param regID regbit to send, see CAN manual
 * CAN respons of the needed regValue
 */
void Invertor::Transmitting_request(int _Inverter_ID, int regID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(regID);
    message.data_field.push_back(0x00);

    CAN.send(message);
}

/**
 * Cycic Transmitting request
 *@param _Inverter_ID ID from inverter in CAN_ID
 *@param regID regbit to send, see CAN manual
 *@param time_interval 0-254ms time interval for transmittion
 *cyclic CAN respons of needed regValue
 */
void Invertor::Cyclic_transmitting_request(int _Inverter_ID, int regID, int time_interval) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(regID);
    message.data_field.push_back(time_interval);

    CAN.send(message);
}

/**
 * Stop Cycic Transmitting request
 *@param _Inverter_ID ID from inverter in CAN_ID
 *No CAN respons from the inverter
 */
void Invertor::Stop_transmitting(int _Inverter_ID) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0xff);

    CAN.send(message);
}



/**
 * Changes the transmitting adress
 * @param _Inverter_ID previous adress
 * @param adress New adress
 * No CAN respons from the inverter
 * (pls do not use)
 */
void Invertor::Change_transmitting_address(int _Inverter_ID, int adress) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x68);
    message.data_field.push_back(adress);

    CAN.send(message);
}

void Invertor::SetSpeed(int _Inverter_ID, int speed) {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x31);
    message.data_field.push_back(speed & 0xFF);
    message.data_field.push_back((speed >>= 8) & 0xFF);

    CAN.send(message);
}
