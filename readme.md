# NMEA2000 Alert Messages Library for C++

## Description  
This library provides a comprehensive set of functions for handling NMEA 2000 alert messages according to the NMEA 2000 standard. It enables you to:

- Parse and generate NMEA 2000 alert messages (PGN 126983, 126984, 126985)
- Handle various alert conditions and notifications with customizable thresholds
- Manage alert states, acknowledgments, and temporary silence
- Link alerts to specific sensors and data sources
- Support multiple alert types, categories, and priority levels

This library is an extension of the excellent [NMEA2000](https://github.com/ttlappalainen/NMEA2000) library by Timo Lappalainen and is designed to seamlessly integrate with existing NMEA2000 applications.

## Features
- **Alert Management**: Create and manage complex alert objects with configurable parameters
- **Threshold Monitoring**: Monitor sensor values against configurable thresholds with multiple comparison methods
- **State Management**: Track alert states (Normal, Active, Silenced, Acknowledged, etc.)
- **Multi-device Support**: Support for multiple devices and alert systems on the same NMEA2000 network
- **Flexible Configuration**: Customizable alert descriptions, locations, languages, and priorities
- **Arduino Compatible**: Designed for Arduino and compatible microcontrollers

## Installation
1. Download or clone this repository
2. Place the library folder in your Arduino libraries directory (usually `Documents/Arduino/libraries/`)
3. Install the required [NMEA2000](https://github.com/ttlappalainen/NMEA2000) library
4. Restart the Arduino IDE

## License
This library is licensed under the MIT License.

Copyright (c) 2024 Andreas Zogg

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


## API Reference

### tN2kAlert Constructor

```c++
// Constructor for the NMEA 2000 alert (tN2kAlert) class.
// \param AlertType              The type of alert (e.g., warning, alarm, etc.).
// \param AlertCategory          The category of the alert (e.g., engine, navigation, etc.).
// \param AlertId                The unique identifier for the alert.
// \param TriggerCondition       The condition that triggers the alert (default: Auto).
// \param AlertPriority          The priority level of the alert (default: 100).
// \param TemporarySilenceSupport Whether temporary silence is supported for this alert.
// \param AcknowledgeSupport     Whether acknowledgment is supported for this alert.
// \param EscalationSupport      Whether escalation is supported for this alert.
tN2kAlert(tN2kAlertType AlertType, tN2kAlertCategory AlertCategory, uint16_t AlertId, 
          tN2kAlertTriggerCondition TriggerCondition = N2kts_AlertTriggerAuto, 
          uint8_t AlertPriority = 100,
          tN2kAlertYesNo TemporarySilenceSupport = N2kts_AlertNo, 
          tN2kAlertYesNo AcknowledgeSupport = N2kts_AlertNo, 
          tN2kAlertYesNo EscalationSupport = N2kts_AlertNo)
```

### SetAlertSystem

```c++
// Sets parameters for an NMEA 2000 alert system.
// \param AlertSystem            The alert system identifier.
// \param AlertSubsystem         The alert subsystem identifier.
// \param AcknowledgeNetworkId   The network ID for acknowledgment.
// \param AlertLanguage          The language for the alert description.
// \param AlertDescription       The alert description text.
// \param AlertLocation          The alert location description.
void SetAlertSystem(uint8_t AlertSystem, uint8_t AlertSubsystem, 
                   uint64_t AcknowledgeNetworkId, tN2kAlertLanguage AlertLanguage, 
                   char* AlertDescription, char* AlertLocation)
```

### SetAlertDataSource

```c++
// Set parameters for linking an NMEA 2000 alert with a specific sensor.
// \param DataSourceInstance     The unique identifier (UID) of the device (e.g., temperature sensor).
// \param DataSourceIndexSource  The ID of the sensor on the device (sensor index).
// \param DataSourceNetworkId    The network ID associated with the sensor device.
void SetAlertDataSource(uint8_t DataSourceInstance, uint8_t DataSourceIndexSource, 
                       uint64_t DataSourceNetworkId)
```

### SetAlertThreshold

```c++
// Set the alert threshold parameters.
// \param Method    The method for the threshold comparison (e.g., greater, lower, equal).
// \param Format    The format for the threshold (reserved for future use).
// \param Level     The threshold level value.
void SetAlertThreshold(tN2kAlertThresholdMethod Method, uint8_t Format, uint64_t Level)
```

**Note**: The `Format` parameter is currently not used but is planned for future implementation to specify data types (e.g., temperature, pressure, etc.).

### Additional Methods

```c++
// Test if a value exceeds the configured threshold
tN2kAlertThresholdStatus TestAlertThreshold(uint64_t value);

// Set alert message in NMEA2000 message
void SetN2kAlert(tN2kMsg &N2kMsg);

// Set alert text message in NMEA2000 message  
void SetN2kAlertText(tN2kMsg &N2kMsg);

// Parse alert response from network
bool ParseAlertResponse(const tN2kMsg &N2kMsg);

// Query alert status
bool isAlert();           // Returns true if alert is active
bool isAcknowledged();    // Returns true if alert is acknowledged
bool isSilent();          // Returns true if alert is temporarily silenced
```

## Basic Usage

### 1. Create Alert Object

For each alert that you need, create an alert object with the appropriate type, category, and unique ID:

```c++
tN2kAlert TemperatureAlert(N2kts_AlertTypeWarning, N2kts_AlertCategoryTechnical, 10);
```

### 2. Configure Alert System

Set up the alert with system information, description, and location:

```c++
TemperatureAlert.SetAlertSystem(1, 1, NMEA2000.GetN2kSource(AlarmDevice), 
                               N2kts_AlertLanguageEnglishUS, 
                               "Temperature", 
                               "Temperature in engine room exceeded threshold");
```

### 3. Configure Data Source

Link the alert to a specific sensor or data source:

```c++
TemperatureAlert.SetAlertDataSource(1, 1, NMEA2000.GetN2kSource(TemperatureDevice));
```

### 4. Set Threshold

Configure the threshold that will trigger the alert:

```c++
TemperatureAlert.SetAlertThreshold(N2kts_AlertThresholdMethodGreater, 0, 60);
```

### 5. Monitor Values

Each time you read a value from the sensor, test if it triggers the alert:

```c++
double temperature = 22.5; // Read actual temperature from sensor
tN2kAlertThresholdStatus status = TemperatureAlert.TestAlertThreshold(temperature);
```

### 6. Send Alert Messages

In your main loop, periodically send alert and alert text messages:

```c++
tN2kMsg N2kMsg;

// Send alert status (every 500ms)
if (AlarmScheduler.IsTime()) {
    AlarmScheduler.UpdateNextTime();
    TemperatureAlert.SetN2kAlert(N2kMsg);
    NMEA2000.SendMsg(N2kMsg, AlarmDevice);
}

// Send alert text (every 5 seconds)
if (AlarmTextScheduler.IsTime()) {
    AlarmTextScheduler.UpdateNextTime();
    TemperatureAlert.SetN2kAlertText(N2kMsg);
    NMEA2000.SendMsg(N2kMsg, AlarmDevice);
}
```

## Complete Example

For a complete working example, see the [TemperatureMonitor example](examples/TemperatureMonitor/TemperatureMonitor.ino) in the examples folder. This example demonstrates:

- Setting up multiple NMEA2000 devices (temperature sensor and alarm device)
- Configuring alert objects with proper parameters
- Reading sensor data and testing thresholds
- Sending alert messages to the NMEA2000 network
- Handling alert responses and acknowledgments

## Alert Types and Categories

The library supports various predefined alert types and categories according to the NMEA 2000 standard:

### Alert Types
- `N2kts_AlertTypeWarning` - Warning level alerts
- `N2kts_AlertTypeAlarm` - Alarm level alerts  
- `N2kts_AlertTypeCaution` - Caution level alerts

### Alert Categories
- `N2kts_AlertCategoryTechnical` - Technical system alerts
- `N2kts_AlertCategoryNavigation` - Navigation related alerts
- `N2kts_AlertCategorySafety` - Safety system alerts

### Threshold Methods
- `N2kts_AlertThresholdMethodGreater` - Trigger when value is greater than threshold
- `N2kts_AlertThresholdMethodLower` - Trigger when value is lower than threshold
- `N2kts_AlertThresholdMethodEqual` - Trigger when value equals threshold

## Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

## Dependencies

- [NMEA2000 Library](https://github.com/ttlappalainen/NMEA2000) by Timo Lappalainen

## Compatibility

This library is compatible with:
- Arduino IDE
- ESP32, ESP8266
- Arduino Mega, Due
- Teensy 3.x, 4.x
- Any microcontroller supported by the NMEA2000 library