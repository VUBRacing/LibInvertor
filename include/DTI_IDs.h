#ifndef DTI_IDs_H
#define DTI_IDs_H
/*
Holds every regId to use with a short desciption
Those regIDs are specific to the DTI inverter and are found in the CAN datasheet
Reg IDs aresend in the ID with a specific function
*/

#define TRANSMIT_Control_ID 0x1F
#define TRANSMIT_ERPM_ID 0x20
#define TRANSMIT_ACDC_Current_ID 0x21
#define TRANSMIT_Temp_ID 0x22
#define TRANSMIT_Id_Iq_ID 0x23
#define TRANSMIT_Throttle_ID 0x24
#define TRANSMIT_Max_ACcurrent_ID 0x25
#define TRANSMIT_Max_DCcurrent_ID 0x26

#define REG_Current 0x01
#define REG_BrakeCurrent 0x02
#define REG_ERPM 0x03
#define REG_Position 0X04
#define REG_Relative_Current 0x05
#define REG_Relative_Brake_Current 0x06
#define REG_Digital_out 0x07
#define REG_Set_Max_AC 0x08
#define REG_Set_Max_brake_AC 0x09
#define REG_Set_Max_DC 0X0A
#define REG_Set_Max_brake_DC 0x0B
#define REG_Enable 0X0C

#endif