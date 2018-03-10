#include "IS2020.h"
#include <Arduino.h>
//#include <SoftwareSerial1.h>
//#include "MMI.h"
#include "Music.h"
#include "commands.h"
#include "events.h"

//uint8_t BTstate[2][32] ; //array of state of devices ....


IS2020::IS2020(uint32_t baudrate)
{
  Serial2.begin(baudrate);
  //IS2020::IS2020_init(baudrate);
}
/**
   Destructor
*/
IS2020::~IS2020()
{
}

//void IS2020::IS2020_init(uint32_t baudrate) {
//
// 
//  //delay(500);
//  //IS2020::Read_Link_Status();
//}


/*
   debug output
*/
void IS2020::DBG(String text) {
  if (DEBUG) Serial1.print("DBG: ");Serial1.println(text);;
}
/*

  Command Format:  Command Command ID  Command Parameters  Return Event
  Make_Call 0x00  data_base_index, phone_number call status

  Description:  This command is used to trigger HF action for making an outgoing call.

  Command Parameters: data_base_index SIZE: 1 BYTE
  Value Parameter Description
  0x00  database 0 for a dedicate link
  0x01  database 1 for a dedicate link

  phone_number  SIZE: 19 BYTES
  Value Parameter Description
  0xXXXX  Phone number of ASCII code. The max length of phone number is 19 byte.

*/
uint8_t IS2020::MakeCall(uint8_t deviceId, char phoneNumber[19]) //return event from BT will be handled elseware??? event call status
{
  IS2020::DBG("MC");

  IS2020::SendPacketArrayChar(21, CMD_Make_Call, deviceId, phoneNumber);
}

/*

  Command Format:  Command Command ID  Command Parameters  Return Event
  Make_Extension_Call 0x01  data_base_index, extension_number

  Description:  This command is used to trigger HF action for making an extension call number.

  Command Parameters: data_base_index SIZE: 1 BYTE
  Value Parameter Description
  0x00  database 0 for a dedicate link
  0x01  database 1 for a dedicate link

  extention_number  SIZE: 10 BYTES
  Value Parameter Description
  0xXXXX  Extension phone number of ASCII code. The max length of phone number is 10 byte


*/
uint8_t IS2020::Make_Extension_Call(uint8_t deviceId, char phoneNumber[10])
{
  IS2020::DBG("MEC");
  IS2020::SendPacketArrayChar(12, CMD_Make_Extension_Call, deviceId, phoneNumber);
  //    }
}
/*

  Command Format:  Command Command ID  Command Parameters  Return Event
  MMI_Action  0x02  data_base_index, action

  Description:  MMI action

  Command Parameters: data_base_index SIZE: 1 BYTE
  Value Parameter Description
  0x00  database 0 that related to a dedicate HF device
  0x01  database 1 that related to a dedicate HF device

  action  SIZE: 1 BYTE
  Value Parameter Description
  0x01  add/remove SCO link
  0x02  force end active call
  0x04  Accept an incoming call
  0x05  Reject an incoming call
  0x06  1. End call if SCO exist. 2. Voice transfer to headset if SCO not exist.
  0x07  1. Mute microphone if microphone is not mute 2. Active microphone if microphone is mute
  0x08  Mute microphone
  0x09  Active microphone
  0x0A  voice dial
  0x0B  cancel voice dial
  0x0C  last number redial
  0x0D  Set the active call on hold and active the hold call
  0x0E  voice transfer
  0x0F  Query call list information(CLCC)
  0x10  three way call
  0x11  release the waiting call or on hold call
  0x12  accept the waiting call or active the on hold call and release the active call
  0x16  initiate HF connection
  0x17  disconnect HF link
  0x24  increase microphone gain
  0x25  decrease microphone gain
  0x26  switch primary HF device and secondary HF device role
  0x30  increase speaker gain
  0x31  decrease speaker gain
  0x34  Next song
  0x35  previous song
  0x3B  Disconnect A2DP link
  0x3C  next audio effect
  0x3D  previous audio effect
  0x50  enter pairing mode (from power off state)
  0x51  power on button press
  0x52  power on button release
  0x56  Reset some eeprom setting to default setting
  0x5D  fast enter pairing mode (from non-off mode)
  0x5E  switch power off:  to execute the power_off process directly, actually, the combine command set, power off button press and release, could be replace by this command.
  0x60  Enable buzzer if buzzer is OFF Disable buzzer if buzzer is ON
  0x61  Disable buzzer
  0x62  Enable buzzer Disable buzzer if buzzer is ON
  0x63  Change tone set (SPK module support two sets of tone)
  0x6A  Indicate battery status
  0x6B  Exit pairing mode
  0x6C  link last device
  0x6D  disconnect all link


  Note1:Query call list information(CLCC)
  action  SIZE: 1 BYTE
  Value Parameter Description
  0x0f  trigger SPK Module to query call list information


*/
void  IS2020::MMI_Action  (uint8_t deviceId, uint8_t action) {
  String debug="text" + action;
  DBG(debug);
  uint8_t data[1] = {action};
  IS2020::SendPacketArrayInt(0x03, CMD_MMI_Action, deviceId, data);
}
void  IS2020::Event_Mask_Setting  () {}

/*

  Command Format:  Command Command ID  Command Parameters  Return Event
  Music_Control 0x04  data_base_index, action

  Description:  This command is used to trigger AVRCP command for music control.

  Command Parameters:
  data_base_index SIZE: 1 BYTE
  Value Parameter Description
  0x00  reserved

  action  SIZE: 1 BYTE
  Value Parameter Description
  0x00  Stop fast forward or rewind
  0x01  fast forward
  0x02  fast forward with repeat send fast forward command every 800ms
  0x03  rewind
  0x04  rewind with repeat send rewind command every 800ms
  0x05  PLAY command
  0x06  PAUSE command
  0x07  PLAY PAUSE toggle
  0x08  STOP command


*/

void  IS2020::Music_Control(uint8_t deviceId, uint8_t action) {
  //  uint8_t data[3];
  //  uint16_t packetSize=0x03;//Payload length low byte(including command id and data)
  //  data[0]=CMD_Music_Control; //Command Id
  //  data[1]=0x00; //data_base_index = 0x00
  //  data[2]=action;//play/stop/etc... sear IS2020.h file
  uint8_t data[1] = {action};
  IS2020::SendPacketArrayInt(0x03, CMD_Music_Control, deviceId, data);
};
void  IS2020::Change_Device_Name  () {}
void  IS2020::Change_PIN_Code () {}
void  IS2020::BTM_Parameter_Setting () {}
void  IS2020::Read_BTM_Version  () {}
void  IS2020::Get_PB_By_AT_Cmd  () {}
void  IS2020::Vendor_AT_Command () {}
void  IS2020::AVC_Specific_Cmd  () {}
void  IS2020::AVC_Group_Navigation  () {}
/*
  Command Format: Command Command ID  Command Parameters  Return Event
  Read_Link_Status  0x0D  dummy_byte  Read_Link_Status_Reply

  Description:  It is used to query device and profile link status

  Command Parameters: dummy_byte  SIZE: 1 BYTE
  Value Parameter Description
  0x00  reserved

*/
void  IS2020::Read_Link_Status()
{
  IS2020::SendPacketInt(CMD_Read_Link_Status, DUMMYBYTE);
}

/*

  Command Format:  Command Command ID  Command Parameters  Return Event
  Read_Paired_Device_Record 0x0E  dummy_byte  Read_Paired_Device_Record_Reply

  Description:  This command is used to read the paired device information of BTM recorded.

  Command Parameters: dummy_byte  SIZE: 1 BYTE
    Parameter Description
  dummy_byte  RFD


  Event Format:  Event Event Code  Event Parameters
  Read_Paired_Device_Record_Reply 0x1F  paired_device_number, paired_record
uint8_t RX, uint8_t TX
  Description:  This event is used to reply the  Read_Paired_Device_Information command.


  -----------------Read_Paired_Device_Record_Reply--------------------------------------------------
  Event Parameters: paired_device_number  SIZE: 1 BYTE
    Parameter Description
  byte0 the paired device number.

  paired_record : 7bytes per record SIZE: (7*total_record) BYTE
    Parameter Description
  byte0 link priority : 1 is the highest(newest device) and 4 is the lowest(oldest device)
  byte1~byte6 linked device BD address (6 bytes with low byte first)
  …
  --------------------------------------------------------------------------------------------

*/
void  IS2020::Read_Paired_Device_Record () {
  IS2020::SendPacketInt(CMD_Read_Paired_Device_Record, DUMMYBYTE);
}
void  IS2020::Read_Local_BD_Address () {}
void  IS2020::Read_Local_Device_Name  () {}
void  IS2020::Set_Access_PB_Method  () {}
void  IS2020::Send_SPP_iAP_Data () {}
void  IS2020::BTM_Utility_Function  () {}
/*
  Command Format:  Command Command ID  Command Parameters  Return Event
  Event_ACK 0x14  event_id

  Description:  This command is used for MCU to ack the received BTM's EVENT.


  Command Parameters: event_id  SIZE: 1 BYTE
    Parameter Description
  0xXX  the acked event_id.

*/
void IS2020::Event_ACK (uint8_t eventID) {
  DBG("Event ACK:"+(char)eventID);
  IS2020::SendPacketInt(CMD_Event_ACK, eventID);
}
void  IS2020::Additional_Profiles_Link_Setup  () {}
/*
  Command Format:  Command Command ID  Command Parameters  Return Event
  Read_Linked_Device_Information  0x16  database_index, type  Read_Linked_Device_Information_Reply

  Description:  MCU can use this to retrieve linked device bluetooth info, such as device name and in-band ringtone status.

  Command Parameters: database_index  SIZE: 1 BYTE
  Value Parameter Description
  0x00  database 0 for a dedicate link
  0x01  database 1 for a dedicate link

  type  SIZE: 1 BYTE
  Value Parameter Description
  0x00  query device name
  0x01  query in-band ringtone status
  0x02  query if remote device is iAP device
  0x03  query if remote device support AVRCP v1.3
  0x04  query HF&A2DP gain
  0x05  query Line_In gain
  others  reserved

*/
void  IS2020::Read_Linked_Device_Information(uint8_t deviceId, uint8_t query)
{
  uint8_t data[1] = {query};
  IS2020::SendPacketArrayInt(0x03, CMD_Read_Linked_Device_Information, deviceId, data);
}
void  IS2020::Profiles_Link_Back  () {}
void  IS2020::Disconnect  () {}
void  IS2020::MCU_Status_Indication () {}
void  IS2020::User_Confirm_SPP_Req_Reply  () {}
void  IS2020::Set_HF_Gain_Level () {}
void  IS2020::EQ_Mode_Setting () {}
void  IS2020::DSP_NR_CTRL () {}
void  IS2020::GPIO_Control  () {}
void  IS2020::MCU_UART_Rx_Buffer_Size () {}
void  IS2020::Voice_Prompt_Cmd  () {}
void  IS2020::MAP_REQUEST () {}
void  IS2020::Security_Bonding_Req  () {}
void  IS2020::Set_Overall_Gain  () {}

void  IS2020::SendPacketInt (uint8_t cmd, uint8_t data) {
  Serial2.write(STARTBYTE);
  //  Serial1.println(STARTBYTE,HEX);
  Serial2.write((byte)0x00);
  //  Serial1.println((0x00),HEX);
  //uint8_t checkSum = 0x00;
  Serial2.write(0x02);
  //  Serial1.println((0x02),HEX);
  uint8_t checkSum = 0x02;
  Serial2.write(cmd);
  //  Serial1.println(cmd,HEX);
  checkSum += (cmd);
  Serial2.write(data);
  //  Serial1.println(data,HEX);
  checkSum += data;
  // Serial1.println(0x100-checkSum,HEX);
  Serial2.write(0x100 - checkSum);
}

void  IS2020::SendPacketArrayInt (uint16_t packetSize, uint8_t cmd, uint8_t deviceId, uint8_t data[]) {
  Serial2.write(STARTBYTE);
  //  Serial1.println(STARTBYTE,HEX);
  Serial2.write(packetSize >> 8);
  //  Serial1.println((packetSize>>8),HEX);
  uint8_t checkSum = packetSize >> 8;
  Serial2.write(packetSize & 0xFF);
  //  Serial1.println((packetSize & 0xFF),HEX);
  checkSum += (packetSize & 0xFF);
  Serial2.write(cmd);
  //  Serial1.println(cmd,HEX);
  checkSum += (cmd);
  Serial2.write(deviceId);
  // Serial1.println(deviceId,HEX);
  checkSum += (deviceId);
  for (uint16_t dataPos = 0; dataPos < packetSize - 2; dataPos++) {
    Serial2.write(data[dataPos]);
    //  Serial1.println(data[dataPos],HEX);
    checkSum += data[dataPos];
  }
  // Serial1.println(0x100-checkSum,HEX);
  Serial2.write(0x100 - checkSum);
}

void  IS2020::SendPacketArrayChar (uint16_t packetSize, uint8_t cmd, uint8_t deviceId, char data[]) {
  Serial2.write(STARTBYTE);
  Serial2.write(packetSize >> 8);
  uint8_t checkSum = packetSize >> 8;
  Serial2.write(packetSize & 0xFF);
  checkSum += (packetSize & 0xFF);
  Serial2.write(cmd);
  checkSum += (cmd);
  Serial2.write(deviceId);
  checkSum += (deviceId);
  for (uint16_t dataPos = 0; dataPos < packetSize - 2; dataPos++) {
    Serial2.write(data[dataPos]);
    checkSum += data[dataPos];
  }
  Serial2.write(0x100 - checkSum);
}

int IS2020::SerialAvailable () {
  return Serial2.available();
}

int IS2020::SerialRead() {
  return Serial2.read();
  //  if (Serial2.available()) {
  //    Serial1.write(Serial2.read());
  //  }
}
uint8_t IS2020::checkCkeckSum(int size, uint8_t data[]) {
  if (DEBUG)
  {
    Serial1.println("dumping event data:");
    Serial1.print("packet size: "); Serial1.print(size, DEC); Serial1.print(" ("); Serial1.print(size, HEX); Serial1.println(")");
    Serial1.print("Event:   "); Serial1.println(data[0],HEX);
    Serial1.print("data: ");
  }
  uint8_t csum = (size >> 8);
  csum += (size & 0xFF);
  csum += data[0];
  for (uint8_t i = 1; i < size; i++) { //
    csum += data[i];
    if (DEBUG) {
      Serial1.print(data[i], HEX); Serial1.print(" ");
    }
  }
  if (DEBUG)Serial1.println();

  if (data[size] == (0x100 - csum) ) {
    if (DEBUG) Serial1.println("Checksum OK");
    return true;
  } else {
    if (DEBUG)Serial1.println("Bad checksum");
    return false;
  }
}


int IS2020::getNextEventFromBT() {
  while (Serial2.available()) {

    if (Serial2.read() == 0xAA) { //start of event

      uint16_t packetSize = (Serial2.read() << 8) | (Serial2.read() & 0xff);

      uint8_t event[packetSize + 1];

      for (uint8_t i = 0; i < packetSize + 1; i++) {
        event[i] = Serial2.read();
      }

      if (checkCkeckSum(packetSize, event)) {


        switch (event[0]) {
          /*
             Event Format: Event       Event Code  Event Parameters
                           Command ACK 0x00        cmd_id, status

             Description:

             Event Parameters:
                cmd_id       SIZE: 1 BYTE

                Value Parameter Description
                0xXX  the command id to ack

            status  SIZE: 1 BYTE
            Value Parameter Description
            0x00  command complete : BTM can handle this command.
            0x01  command disallow : BTM can not handle this command.
            0x02  unknow command
            0x03  parameters error
            0x04  "BTM is busy:
            This status is used for SPP data cannot be sent out in this moment because of ACL Tx buffer or RFCOMM credit issue. BTM will reply the ""Complete"" status once the SPP data can be processed.
            "
            0x05  "BTM memory is full:
            This status is used for SPP data cannot be sent out in this moment because of os heap memory is full. BTM will reply the ""Complete"" status once the SPP data can be processed. "
            others  RFD

          */
          case EVT_Command_ACK:
            {
              Event_ACK(EVT_Command_ACK);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            BTM_Status  0x01  state, link_info

            Description:  This event is used to indicate about the BTM status. BTM will send it event while the status was changed.

            Event Parameters: state SIZE: 1 BYTE
            Value Parameter Description
            0x00  Power OFF state
            0x01  pairing state (discoverable mode)
            0x02  Power ON state
            0x03  pairing successful
            0x04  pairing fail
            0x05  HF link established
            0x06  A2DP link established
            0x07  HF link disconnected
            0x08  A2DP link disconnected
            0x09  SCO link connected
            0x0A  SCO link disconnected
            0x0B  AVRCP link established
            0x0C  AVRCP link disconnected
            0x0D  Standard SPP connected
            0x0E  Standard_SPP / iAP disconnected
            0x0F  Standby state
            0x10  iAP connected
            0x11  ACL disconnected

            link_info SIZE: 1 BYTE
            state:0x04
            Value Parameter Description
            0xXX  "For pairing not complete(0x04) case, this parameter indicate not completed reason
            0: time out
            1: fail

            "
            state:0x05,0x06,0x0B,0x0D
            Value Parameter Description
            0xXX  "this parameter indicate both link device and data base information.
            The format is shown as below:
            Bit7~4 : linked device id(0~7)
            Bit3~0 : linked data base(0 or 1)

            "
            state:0x07~0x08,0x0C,0x0E
            Value Parameter Description
            0xXX  "his parameter show the linked_data_base (0 or 1)


            "
            state:0x11
            Value Parameter Description
            0xXX  "0:disconnection
            1:link loss


            "

          */
          case EVT_BTM_Status:
            BTMStatus[0] = event[1];
            BTMStatus[1] = event[2];
            BTMstatusChanged = 1; //there is more to do with data but not here, we do not have time ...
            Event_ACK(EVT_BTM_Status);
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Call_Status 0x02  data_base_index, call_status

            Description:  This event is used to indicate about the HF call status of BTM.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            call_status SIZE: 1 BYTE
            Value Parameter Description
            0x00  Idle
            0x01  voice dial
            0x02  incoming call
            0x03  outgoing call
            0x04  call active
            0x05  a call active with a call waiting
            0x06  a call active with a call hold

          */
          case EVT_Call_Status:
            callStatus[event[1]] = event[2];
            Event_ACK(EVT_Call_Status);
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Caller_ID 0x03  data_base_index, num

            Description:  This event is used to indicate about the caller ID of the incoming call.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            num SIZE: N OCTETS
            Value Parameter Description
            0xXX..  caller Id or phone number

          */
          case EVT_Caller_ID:
            {
              for (uint8_t i = 0; i < packetSize; i++) {
                callerId[event[1]][packetSize] = event[i + 2]; //no need to any sort of flag bit, cose we have callstatus change flag and in case of incoming call we just read this array
              }
              Event_ACK(EVT_Caller_ID);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            SMS_Received_Indication 0x04  data_base_index, indication

            Description:  This event is used to indicate about the sms status that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            indication  SIZE: 1 BYTE
            Value Parameter Description
            0x00  no new sms received
            0x01  new sms received

          */
          case EVT_SMS_Received_Indication:
            {
              SMSstatus[event[1]] = event[2];
              Event_ACK(EVT_SMS_Received_Indication);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Missed_Call_Indication  0x05  data_base_index, information

            Description:  This event is used to indicate about the missed call indication that BTM received from mobile phone

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            information SIZE: 1 BYTE
            Value Parameter Description
            0xXX  reserved

          */
          case EVT_Missed_Call_Indication:
            {
              missedCallStatus[event[1]] = event[2];
              Event_ACK(EVT_Missed_Call_Indication);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Phone_Max_Battery_Level 0x06  data_base_index, battery_level

            Description:  This event is used to indicate about the mobile phone max battery level that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            battery_level SIZE: 1 BYTE
            Value Parameter Description
            0xXX  max battery level

          */
          case EVT_Phone_Max_Battery_Level:
            {
              maxBatteryLevel[event[1]] = event[2];
              Event_ACK(EVT_Phone_Max_Battery_Level);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Phone_Current_Battery_Level 0x07  data_base_index, battery_level

            Description:  This event is used to indicate about the mobile phone current battery level that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            battery_level SIZE: 1 BYTE
            Value Parameter Description
            0xXX  current battery level

          */
          case EVT_Phone_Current_Battery_Level:
            {
              currentBatteryLevel[event[1]] = event[2];
              Event_ACK(EVT_Phone_Current_Battery_Level);
            }
            break;
          /*
            Event Format:  Event Event Code  Event Parameters
            Roaming_Status  0x08  data_base_index, status

            Description:  This event is used to indicate about the roaming status that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            status  SIZE: 1 BYTE
            Value Parameter Description
            0x00  non-roaming
            0x01  roaming

          */
          case EVT_Roaming_Status: {
              roamingStatus[event[1]] = event[2];
              Event_ACK(EVT_Roaming_Status);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Phone_Max_Signal_Strength_Level 0x09  data_base_index, signal_level

            Description:  This event is used to indicate about the max signal strength level that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            signal_level  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  phone's max signal strength level

          */
          case EVT_Phone_Max_Signal_Strength_Level:
            {
              maxSignalLevel[event[1]] = event[2];
              Event_ACK(EVT_Phone_Max_Signal_Strength_Level);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Phone_Current_Signal_Strength_Level 0x0A  data_base_index, signal_strength

            Description:  This event is used to indicate about the signal strength level that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            This event is used to indicate the MCU about the current signal strength level that BTM received from mobile phone. SIZE: 1 BYTE
            Value Parameter Description
            0xXX  phone's current signal strength level

          */
          case EVT_Phone_Current_Signal_Strength_Level:
            {
              currentSignalLevel[event[1]] = event[2];
              Event_ACK(EVT_Phone_Current_Signal_Strength_Level);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Phone_Service_Status  0x0B  data_base_index, service

            Description:  This event is used to indicate about the service status that BTM received from mobile phone.

            Event Parameters: data_base_index SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            service SIZE: 1 BYTE
            Value Parameter Description
            0x00  No service available
            0x01  service available

          */
          case EVT_Phone_Service_Status :
            {
              serviceStatus[event[1]] = event[2];
              Event_ACK(EVT_Phone_Service_Status);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            BTM_Battery_Status  0x0C  battery_status, voltage_level

            Description:  This event is used to indicate about the BTM's battery status.

            Event Parameters: battery_status  SIZE: 1 BYTE
            Value Parameter Description
            0x00  dangerous level, and will auto shutdown
            0x01  low level
            0x02  normal level
            0x03  high level
            0x04  full level
            0x05  in charging
            0x06  charging complete

            voltage_level SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "0x00: 3.0V
            0x01: 3.1V
            0x02: 3.2V
            0x03: 3.3V
            0x04: 3.4V
            0x05: 3.5V
            0x06: 3.6V
            0x07: 3.7V
            0x08: 3.8V
            0x09: 3.9V
            0x0A: 4.0V
            0x0B: 4.1V
            0x0C: 4.2V"

          */
          case EVT_BTM_Battery_Status :
            {
              BTMBatteryStatus[0] = event[1];
              BTMBatteryStatus[1] = event[2];
              Event_ACK(EVT_BTM_Battery_Status);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            BTM_Charging_Status 0x0D  charger_status, dummy

            Description:

            Event Parameters: charger_status  SIZE: 1 BYTE
            Value Parameter Description
            0x00  No charger plug in
            0x01  in charging
            0x02  charging complete
            0x03  charging fail

            dummy SIZE: 1 BYTE
            Value Parameter Description
            0xXX  reserved

          */
          case EVT_BTM_Charging_Status: {
              BTMChargingStatus = event[1];
              Event_ACK(EVT_BTM_Charging_Status);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Reset_To_Default  0x0E  dummy1,dummy2

            Description:  This event is used to indicate the BTM finish the Master Reset command for the MMI command (0x56) trigger.

            Event Parameters: dummy1  SIZE: 1 BYTE
            Value Parameter Description
            0x00

            dummy2  SIZE: 1 BYTE
            Value Parameter Description
            0x00

          */
          case EVT_Reset_To_Default:
            {
              Event_ACK(EVT_Reset_To_Default);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Report_HF_Gain_Level  0x0F  database_index, level

            Description:  This is used to report the HF gain level set by remote Audio Gateway (Phone)

            Event Parameters:
            database_index  SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate HF/HS device
            0x01  database 1 for a dedicate HF/HS device

            level     SIZE: 1 BYTE
            Value Parameter Description
            0x00-0x0F gain level that sync. with HF device

          */
          case EVT_Report_HF_Gain_Level:
            {
              HFGainLevel[event[1]] = event[2];
              Event_ACK(EVT_Report_HF_Gain_Level);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            EQ_Mode_Indication  0x10  mode, dummy

            Description:  This event is used to notice the EQ_mode setting by MMI or EQ_Mode_Setting command

            Event Parameters: mode  SIZE: 1 BYTE
            Value Parameter Description
            0x00  Off Mode
            0x01  Soft Mode
            0x02  Bass Mode
            0x03  Treble Mode
            0x04  Classical Mode
            0x05  Rock Mode
            0x06  Jazz Mode
            0x07  Pop Mode
            0x08  Dance Mode
            0x09  R&B Mode
            0x0A  User Mode 1

            dummy SIZE: 1 BYTE
            Value Parameter Description
            0xXX  reserved

          */
          case EVT_EQ_Mode_Indication:
            {
              EQMode = event[1];
              Event_ACK(EVT_EQ_Mode_Indication);
            }
            break;
          case EVT_PBAP_Missed_Call_History:
            {
              Event_ACK(EVT_PBAP_Missed_Call_History);
            }
            break;
          case EVT_PBAP_Received_Call_History:
            {
              Event_ACK(EVT_PBAP_Received_Call_History);
            }
            break;
          case EVT_PBAP_Dialed_Call_History:
            {
              Event_ACK(EVT_PBAP_Received_Call_History);
            }
            break;
          case EVT_PBAP_Combine_Call_History:
            {
              Event_ACK(EVT_PBAP_Combine_Call_History);
            }
            break;
          case EVT_Phonebook_Contacts:
            {
              Event_ACK(EVT_Phonebook_Contacts);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            PBAP_Access_Finish  0x16  type, reserved

            Description:

            Event Parameters: type  SIZE: 1 BYTE
            Value Parameter Description
            0x0B  Retrieve miss call history records finish
            0x0C  Retrieve answered call history records finish
            0x0D  Retrieve dialed call history records finish
            0x0E  Retrieve combined call(missed, dialed,answered) history records finish
            0x0F  Retrieve phone book contacts finish


            reserved  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  reserved

          */
          case EVT_PBAP_Access_Finish:
            {
              PBAPAccessFinish = event[1];
              Event_ACK(EVT_PBAP_Access_Finish);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Read_Linked_Device_Information_Reply  0x17  database_index, type, info

            Description:  This event is used to reply Read_Linked_Device_Information command.

            Event Parameters: database_index  SIZE: 1 BYTE
            Value Parameter Description
            0x00  database 0 for a dedicate link
            0x01  database 1 for a dedicate link

            type  SIZE: 1 BYTE
            Value Parameter Description
            0x00  reply device name
            0x01  reply in-band ringtone status
            0x02  reply if remote device is a iAP device
            0x03  reply if remote device support AVRCP v1.3
            0x04  reply HF&A2DP gain
            0x05  reply Line_In gain
            others  reserved

            info (for device name)  SIZE: N OCTETS
            Value Parameter Description
            0xXX… "N bytes bluetooth name with NULL terminated. (N <= 249 with NULL terminated)

            Note:If remote device response empty name string, then BTM will report name with data NULL terminate(0x00) only."

            info (for in-band ringtone status)  SIZE: 1 BYTE
            Value Parameter Description
            0x00  disable
            0x01  enable

            info (for spp type : iAP device or not) SIZE: 1 BYTE
            Value Parameter Description
            0x00  Standard SPP device
            0x01  iAP device

            info (for AVRCP type : AVRCP v1.3 device or not)  SIZE: 1 BYTE
            Value Parameter Description
            0x00  not support AVRCP v1.3
            0x01  support AVRCP v1.3

            info (for type 0x04)  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "bit[3:0]: A2DP gain
            bit[7:4]: HF gain"

            info (for type 0x05)  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  Line_In gain

          */
          case EVT_Read_Linked_Device_Information_Reply:
            {
              if (DEBUG) {
                Serial1.println();
                Serial1.println("EVT_Read_Linked_Device_Information_Reply");
              }
              switch (event[2]) { //event[1] is device id
                case 0x00://reply device name
                  //N bytes bluetooth name with NULL terminated. (N <= 249 with NULL terminated)
                  for (uint8_t i = 3; i < DEVICENAME_LENGHT_SUPPORT + 2/*packetSize-1*/; i++) { //event[2] is information type definition, last is checksum
                    //check if data are not NULL
                    if (event[i] == 0x00) break;
                    deviceName[event[1]][i - 3] = event[i];
                  }
                  break;
                case 0x01://reply in-band ringtone status
                  /*
                    info (for in-band ringtone status) SIZE: 1 BYTE
                    Value Parameter Description
                    0x00  disable
                    0x01  enable
                  */
                  deviceInBandRingtone[event[1]] = event[3];
                  break;
                case 0x02://reply if remote device is a iAP device
                  /*
                    info (for spp type : iAP device or not) SIZE: 1 BYTE
                    Value Parameter Description
                    0x00  Standard SPP device
                    0x01  iAP device
                  */
                  deviceIsiAP[event[1]] = event[3];
                  break;
                case 0x03://reply if remote device support AVRCP v1.3
                  deviceSupportAVRCPA13[event[1]] = event[3];
                  break;
                case 0x04://reply HF&A2DP gain
                  /*
                    info (for type 0x04) SIZE: 1 BYTE
                    Value Parameter Description
                    0xXX  "bit[3:0]: A2DP gain
                    bit[7:4]: HF gain"
                  */
                  deviceHfAndA2dpGain[event[1]] = event[3];
                  break;
                case 0x05: //reply Line_In gain
                  /*
                    info (for type 0x05)  SIZE: 1 BYTE
                    Value Parameter Description
                    0xXX  Line_In gain
                  */
                  deviceLineInGain[event[1]] = event[3];
                  break;
                default:
                  if (DEBUG) {
                    Serial1.print("Reserved response: ");
                    Serial1.println(event[1], HEX);
                  }
              }
              Event_ACK(EVT_Read_Linked_Device_Information_Reply);
            }
            break;
          /*
            Event Format: Event Event Code  Event Parameters
            Read_BTM_Version_Reply  0x18  type, version

            Description:

            Event Parameters: type  SIZE: 1 BYTE
            Value Parameter Description
            0x00  uart version
            0x01  BTM FW version

            version SIZE: 2 Octets
            Value Parameter Description
            0xXXYY
            1st byte bit[7:5]: flash version
            1st byte bit[4:0]: rom version
            2nd byte bit[7:4] : flash sub version
            2nd byte bit[3:0] : flash control version
            for example 00 07 means version 0.07

          */
          case EVT_Read_BTM_Version_Reply:
            {
              if (DEBUG) {
                Serial1.println();
                Serial1.println("EVT_Read_BTM_Version_Reply");
              }
              if (event[1] == 0x00) BTMUartVersion = (event[2] << 8) | (event[3] & 0xff);
              if (event[1] == 0x01) BTMFWVersion = (event[2] << 8) | (event[3] & 0xff);

              Event_ACK(EVT_Read_BTM_Version_Reply);
            }
            break;
          case EVT_Call_List_Report:
            {
              Event_ACK(EVT_Call_List_Report);
            }
            break;
          case EVT_AVC_Specific_Rsp:
            {
              Event_ACK(EVT_AVC_Specific_Rsp);
            }
            break;
          case EVT_BTM_Utility_Req:
            {
              Event_ACK(EVT_BTM_Utility_Req);
            }
            break;
          case EVT_Vendor_AT_Cmd_Reply:
            {
              Event_ACK(EVT_Vendor_AT_Cmd_Reply);
            }
            break;
          case EVT_Report_Vendor_AT_Event:
            {
              Event_ACK(EVT_Report_Vendor_AT_Event);
            }
            break;
          /*
            Event Format:  Event    Event Code     Event Parameters
            Read_Link_Status_Reply  0x1E           device_state,
                                                   database0_connect_status,
                                                   database1_connect_status,
                                                   database0_play_status,
                                                   database1_play_status,
                                                   database0_stream_status,
                                                   database1_stream_status,

            Description:  This event is used to reply the Read_Link_Status command.

            Event Parameters: device_state  SIZE: 1 BYTE
            Value Parameter Description
            0x00  Power OFF state
            0x01  pairing state (discoverable mode)
            0x02  standby state
            0x03  Connected state with only HF profile connected
            0x04  Connected state with only A2DP profile connected
            0x05  Connected state with only SPP profile connected
            0x06  Connected state with multi-profile connected

            database0_connect_status  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "1 indicate connected
            Bit0 : A2DP profile signaling channel connected
            Bit1 : A2DP profile stream channel connected
            Bit2 : AVRCP profile connected
            Bit3 : HF profile connected
            Bit4 : SPP connected"

            database1_connect_status  SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "1 indicate connected
            Bit0 : A2DP profile signaling channel connected
            Bit1 : A2DP profile stream channel connected
            Bit2 : AVRCP profile connected
            Bit3 : HF profile connected
            Bit4 : SPP connected"

            "database0_play_status,
            database1_play_status," SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "0x00:STOP
            0x01:PLAYING
            0x02:PAUSED
            0x03:FWD_SEEK
            0x04:REV_SEEK
            0x05:FAST_FWD
            0x06:REWIND
            0x07:WAIT_TO_PLAY
            0x08:WAIT_TO_PAUSE"

            "database0_stream_status,
            database1_stream_status," SIZE: 1 BYTE
            Value Parameter Description
            0xXX  "1 indicate connected
            0x00: no stream
            0x01: stream on-going"

          */
          case EVT_Read_Link_Status_Reply:
            {
              if (DEBUG) Serial1.println("ReadLinkStatusReply");
              for (uint8_t i = 0; i < 8; i++) {
                LinkStatus[i] = event[i + 1]; //link status is array of 7 bytes, like response is 7bytes.
              }
              Event_ACK(EVT_Read_Link_Status_Reply);
            }
            break;
          case EVT_Read_Paired_Device_Record_Reply:
            {
              /*
                Event Format: Event Event Code  Event Parameters
                Read_Paired_Device_Record_Reply 0x1F  paired_device_number, paired_record

                Description:  This event is used to reply the  Read_Paired_Device_Information command.

                Event Parameters: paired_device_number  SIZE: 1 BYTE
                Parameter Description
                byte0 the paired device number.

                paired_record : 7bytes per record SIZE: (7*total_record) BYTE
                Parameter Description
                byte0 link priority : 1 is the highest(newest device) and 4 is the lowest(oldest device)
                byte1~byte6 linked device BD address (6 bytes with low byte first)
                …

              */
              uint8_t deviceId = event[1];
              if (DEBUG) {
                Serial1.print("Read paired device record reply: ");
                Serial1.print("[");
                Serial1.print(deviceId, HEX);
                Serial1.print("] [");
              }


              for (uint8_t i = 6; i > 0; i--) { // -- cose : byte1~byte6 linked device BD address (6 bytes with low byte first)
                btAddress[deviceId][i] = event[i + 2]; // low byte first so 6,5,4,3,2,1 ? check in reality!
                if (DEBUG) {
                  Serial1.print(event[i + 2], HEX); Serial1.print(":");
                }
              }
              if (DEBUG) Serial1.println();

              //all fine, set flag that we are calling? ore something .... have to create something for it ... function to return pointer tu array of status ...

              // }
              Event_ACK(EVT_Read_Paired_Device_Record_Reply);
            }
            break;
          case EVT_Read_Local_BD_Address_Reply:
            {
              Event_ACK(EVT_Read_Local_BD_Address_Reply);
            }
            break;
          case EVT_Read_Local_Device_Name_Reply:
            {
              Event_ACK(EVT_Read_Local_Device_Name_Reply);
            }
            break;
          case EVT_Report_SPP_iAP_Data:
            {
              Event_ACK(EVT_Report_SPP_iAP_Data);
            }
            break;
          case EVT_Report_Link_Back_Status:
            {
              Event_ACK(EVT_Report_Link_Back_Status);
            }
            break;
          case EVT_Ringtone_Finish_Indicate:
            {
              Event_ACK(EVT_Ringtone_Finish_Indicate);
            }
            break;
          case EVT_User_Confrim_SSP_Req:
            {
              Event_ACK(EVT_User_Confrim_SSP_Req);
            }
            break;
          case EVT_Report_AVRCP_Vol_Ctrl:
            {
              Event_ACK(EVT_Report_AVRCP_Vol_Ctrl);
            }
            break;
          case EVT_Report_Input_Signal_Level:
            {
              Event_ACK(EVT_Report_Input_Signal_Level);
            }
            break;
          case EVT_Report_iAP_Info:
            {
              Event_ACK(EVT_Report_iAP_Info);
            }
            break;
          case EVT_REPORT_AVRCP_ABS_VOL_CTRL:
            {
              Event_ACK(EVT_REPORT_AVRCP_ABS_VOL_CTRL);
            }
            break;
          case EVT_Report_Voice_Prompt_Status:
            {
              Event_ACK(EVT_Report_Voice_Prompt_Status);
            }
            break;
          case EVT_Report_MAP_Data:
            {
              Event_ACK(EVT_Report_MAP_Data);
            }
            break;
          case EVT_Security_Bonding_Res:
            {
              Event_ACK(EVT_Security_Bonding_Res);
            }
            break;
          case EVT_Report_Type_Codec:
            {
              Event_ACK(EVT_Report_Type_Codec);
            }
            break;
          default:
            {
              Serial1.println();
              Serial1.print("Unknown  BYTE: ");
              for (uint8_t i = 0; i < packetSize; i++) {


                Serial1.print(event[i], HEX);
              }
              Serial1.println();
            }
        }
      }
    }
  }
}

