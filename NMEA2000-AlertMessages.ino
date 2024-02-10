// Demo: NMEA2000 library. Send main cabin temperature to the bus.

#include <Arduino.h>
//#define N2k_SPI_CS_PIN 53    // If you use mcp_can and CS pin is not 53, uncomment this and modify definition to match your CS pin.
//#define N2k_CAN_INT_PIN 21   // If you use mcp_can and interrupt pin is not 21, uncomment this and modify definition to match your interrupt pin.
//#define USE_MCP_CAN_CLOCK_SET 8  // If you use mcp_can and your mcp_can shield has 8MHz chrystal, uncomment this.
#define ESP32_CAN_TX_PIN GPIO_NUM_5 // If you use ESP32 and do not have TX on default IO 16, uncomment this and and modify definition to match your CAN TX pin.
#define ESP32_CAN_RX_PIN GPIO_NUM_4 // If you use ESP32 and do not have RX on default IO 4, uncomment this and and modify definition to match your CAN TX pin.
//#define NMEA2000_ARDUINO_DUE_CAN_BUS tNMEA2000_due::CANDevice1  // If you use Arduino DUE and want to use CAN bus 1 instead of 0, uncomment this.
//#define NMEA2000_TEENSY_CAN_BUS 1 // If you use Teensy 3.5 or 3.6 and want to use second CAN bus, uncomment this.
#include <NMEA2000_CAN.h>  // This will automatically choose right CAN library and create suitable NMEA2000 object
#include <N2kMessages.h>

#include "src/N2kAlerts.h"

#define TemperaturDevice 0
#define AlarmDevice 1


// List here messages your device will transmit.
const unsigned long TemperaturDeviceMessages[] PROGMEM = {
    130312L, // Temperature - DEPRECATED
    0
};
const unsigned long AlarmDeviceDeviceMessages[] PROGMEM = {
    126983L, // Alert
    126984L, // Alert response
    126985L, // Alert text
    0
};

// Define schedulers for messages. Define schedulers here disabled. Schedulers will be enabled
// on OnN2kOpen so they will be synchronized with system.
// We use own scheduler for each message so that each can have different offset and period.
// Setup periods according PGN definition (see comments on IsDefaultSingleFrameMessage and
// IsDefaultFastPacketMessage) and message first start offsets. Use a bit different offset for
// each message so they will not be sent at same time.
tN2kSyncScheduler TemperatureScheduler(false, 2000, 500);
tN2kSyncScheduler AlarmScheduler(false, 500, 100);


tN2kAlert TemperatureAlert(N2kts_AlertTypeWarning, N2kts_AlertCategoryTechnical, 10);

// *****************************************************************************
// Call back for NMEA2000 open. This will be called, when library starts bus communication.
// See NMEA2000.SetOnOpen(OnN2kOpen); on setup()
void OnN2kOpen() {
    // Start schedulers now.
    TemperatureScheduler.UpdateNextTime();
    AlarmScheduler.UpdateNextTime();
}

// *****************************************************************************
void setup() {
    // Enable multi device support for 2 devices
    NMEA2000.SetDeviceCount(2);

    // Reserve enough buffer for sending all messages. This does not work on small memory devices like Uno or Mega
    NMEA2000.SetN2kCANMsgBufSize(8);
    NMEA2000.SetN2kCANReceiveFrameBufSize(150);
    NMEA2000.SetN2kCANSendFrameBufSize(150);

    // Set Product information for temperatur device
    NMEA2000.SetProductInformation(
        "00000001", // Manufacturer's Model serial code
        100, // Manufacturer's product code
        "Simple temp monitor",  // Manufacturer's Model ID
        "1.0.0.0 (2024-02-10)",  // Manufacturer's Software version code
        "1.0.0.0 (2024-02-10)", // Manufacturer's Model version
        1,
        0xffff,
        0xff,
        TemperaturDevice
    );

    // Set Product information for Alarm Device
    NMEA2000.SetProductInformation(
        "00000002", // Manufacturer's Model serial code
        200, // Manufacturer's product code
        "Simple alert monitor",  // Manufacturer's Model ID
        "1.0.0.0 (2024-02-10)",  // Manufacturer's Software version code
        "1.0.0.0 (2024-02-10)", // Manufacturer's Model version
        1,
        0xffff,
        0xff,
        AlarmDevice
    );

    // Set temperature device information
    NMEA2000.SetDeviceInformation(
        112233, // Unique number. Use e.g. Serial number.
        130, // Device function=Temperature. See DEVICE_FUNCTION (0 - 255) https://canboat.github.io/canboat/canboat.html#main
        75, // Device class=Sensor Communication Interface. DEVICE_CLASS (0 - 127) https://canboat.github.io/canboat/canboat.html#main
        2040, // Just choosen free from code list on MANUFACTURER_CODE (0 - 2047) https://canboat.github.io/canboat/canboat.html#main
        4, // Marine. INDUSTRY_CODE (0 - 7)
        TemperaturDevice
    );

    // Set temperature device information
    NMEA2000.SetDeviceInformation(
        112234, // Unique number. Use e.g. Serial number.
        120, // Device function=Alarm Enunciator. See DEVICE_FUNCTION (0 - 255) https://canboat.github.io/canboat/canboat.html#main
        75, // Device class=Sensor Communication Interface. DEVICE_CLASS (0 - 127) https://canboat.github.io/canboat/canboat.html#main
        2040, // Just choosen free from code list on MANUFACTURER_CODE (0 - 2047) https://canboat.github.io/canboat/canboat.html#main
        4, // Marine. INDUSTRY_CODE (0 - 7)
        AlarmDevice
    );

    // Uncomment 2 rows below to see, what device will send to bus. Use e.g. OpenSkipper or Actisense NMEA Reader                           
    Serial.begin(115200);
    NMEA2000.SetForwardStream(&Serial);
    // If you want to use simple ascii monitor like Arduino Serial Monitor, uncomment next line
    NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text. Leave uncommented for default Actisense format.

    TemperatureAlert.SetAlertSystem(1, 1, 1, N2kts_AlertLanguageEnglishUS, "Temperatur", "Temperatur engine rooom exceeded the threshold");
    TemperatureAlert.SetAlertDataSource(112233, 1, 1);
    TemperatureAlert.SetAlertThreshold(N2kts_AlertThresholddMethodGreater, 0, 60);

    // If you also want to see all traffic on the bus use N2km_ListenAndNode instead of N2km_NodeOnly below
    NMEA2000.SetMode(tNMEA2000::N2km_NodeOnly);

    NMEA2000.SetN2kSource(22, TemperaturDevice);
    NMEA2000.SetN2kSource(23, AlarmDevice);

    //NMEA2000.SetDebugMode(tNMEA2000::dm_Actisense); // Uncomment this, so you can test code without CAN bus chips on Arduino Mega
    NMEA2000.EnableForward(false); // Disable all msg forwarding to USB (=Serial)

    // Here we tell library, which PGNs we transmit
    NMEA2000.ExtendTransmitMessages(TemperaturDeviceMessages);
    NMEA2000.ExtendTransmitMessages(AlarmDeviceDeviceMessages);

    // Define OnOpen call back. This will be called, when CAN is open and system starts address claiming.
    NMEA2000.SetOnOpen(OnN2kOpen);
    NMEA2000.Open();
}


// *****************************************************************************
void loop() {

    SendN2kTemperature();
    SendN2kAlarm();
    NMEA2000.ParseMessages();
}

// *****************************************************************************
double EngineRoomTemp() {

    double Temperatur = 22.5; // Read here the true temperature e.g. from analog input
    tN2kAlertThresholdStatus Status = TemperatureAlert.TestAlertThreshold(Temperatur);
    return CToKelvin(Temperatur); 
}

// *****************************************************************************
void SendN2kTemperature() {
    tN2kMsg N2kMsg;

    if (TemperatureScheduler.IsTime()) {
        TemperatureScheduler.UpdateNextTime();
        SetN2kTemperature(N2kMsg, 1, 1, N2kts_EngineRoomTemperature, EngineRoomTemp());
        NMEA2000.SendMsg(N2kMsg, TemperaturDevice);
    }
}

// *****************************************************************************
void SendN2kAlarm() {
    tN2kMsg N2kMsg;

    if (AlarmScheduler.IsTime()) {
        AlarmScheduler.UpdateNextTime();
        TemperatureAlert.SetN2kAlertText(N2kMsg);
        NMEA2000.SendMsg(N2kMsg, AlarmDevice);

        TemperatureAlert.SetN2kAlert(N2kMsg);
        NMEA2000.SendMsg(N2kMsg, AlarmDevice);
    }
}
