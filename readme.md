# NMEA2000 Alertmessages library for C++

## Description  
This library provides a set of functions for handling NMEA 2000 alert messages.
It allows you to parse and generate NMEA 2000 alert messages, as well as handle various alert conditions and notifications.
It is a extension of the [NMEA2000](https://github.com/ttlappalainen/NMEA2000) library from Timo Lappalainen.

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

## Functions
### tN2kAlert
```c++
// Constructor for the NMEA 2000 alert(tN2kAlert) class.
// \param _AlertType            The type of alert(e.g., warning, alarm, etc.).
// \param _AlertCategory        The category of the alert(e.g., engine, navigation, etc.).
// \param _AlertId              The unique identifier for the alert.
// \param _TriggerCondition     The condition that triggers the alert.
// \param _AlertPriority        The priority level of the alert.
// \param _TemporarySilenceSupport Whether temporary silence is supported for this alert.
// \param _AcknowledgeSupport   Whether acknowledgment is supported for this alert.
// \param _EscalationSupport    Whether escalation is supported for this alert.
tN2kAlert::tN2kAlert(tN2kAlertType _AlertType, tN2kAlertCategory _AlertCategory, uint16_t _AlertId, tN2kAlertTriggerCondition _TriggerCondition, uint8_t _AlertPriority, tN2kAlertYesNo _TemporarySilenceSupport, tN2kAlertYesNo _AcknowledgeSupport, tN2kAlertYesNo _EscalationSupport) 
```

### SetAlertSystem
```c++
// Sets parameters for an NMEA 2000 alert system.
// \param _Alertsystem          The alert system identifier.
// \param _AlertSubsystem       The alert subsystem identifier.
// \param _AcknowledgeNetworkId The network ID for acknowledgment.
// \param _AlertLanguage        The language for the alert description.
// \param _AlertDescription     the alert description.
// \param _AlertLocation        the alert location.
void tN2kAlert::SetAlertSystem(uint8_t _Alertsystem, uint8_t _AlertSubsystem, uint64_t _AcknowledgeNetworkId, tN2kAlertLanguage _AlertLanguage, char* _AlertDescription, char* _AlertLocation)
```

### SetAlertDataSource
```c++
// Set parameters for linking an NMEA 2000 alert with a specific sensor.
// \param _DataSourceInstance   The unique identifier (UID) of the device (e.g., temperature sensor).
// \param _DatesourceIndexSource The ID of the sensor on the device (sensor index).
// \param _DataSourceNetworkId  The network ID associated with the sensor device.
void tN2kAlert::SetAlertDataSource(uint8_t _DataSourceInstance, uint8_t _DatesourceIndexSource, uint64_t _DataSourceNetworkId)
```

### SetAlertThreshold
```c++
// Set the alert threshold.
// \param _Method  The method for the threshold (e.g., greater, lower, equal).
// \param _Format  The format for the threshold (e.g., temperature, pressure, etc.).
// \param _Level   The threshold level.
void tN2kAlert::SetAlertThreshold(tN2kAlertThresholdMethod _Method, tN2kAlertThresholdFormat _Format, double _Level)
```

At the moment, format is not used, but it is planned to use it in the future.

## Usage
For each alert that you need, you create an alertobject
```c++
tN2kAlert TemperatureAlert(N2kts_AlertTypeWarning, N2kts_AlertCategoryTechnical, 10);
```

then you setup the alert
```c++
TemperatureAlert.SetAlertSystem(1, 1, NMEA2000.GetN2kSource(AlarmDevice), N2kts_AlertLanguageEnglishUS, "Temperatur", "Temperatur engine rooom exceeded the threshold");
TemperatureAlert.SetAlertDataSource(1, 1, NMEA2000.GetN2kSource(TemperaturDevice));
TemperatureAlert.SetAlertThreshold(N2kts_AlertThresholddMethodGreater, 0, 60);
```

each time you read a value from the sensor you can check if the value triggers the alert
```c++
    double Temperatur = 22.5; // Read here the true temperature e.g. from analog input
    tN2kAlertThresholdStatus Status = TemperatureAlert.TestAlertThreshold(Temperatur);
```

in hte main loop, when the time is right, you send the messages for the alert and the alert text
```c++
    tN2kMsg N2kMsg;

    if (AlarmScheduler.IsTime()) {
        AlarmScheduler.UpdateNextTime();
        TemperatureAlert.SetN2kAlert(N2kMsg);
        NMEA2000.SendMsg(N2kMsg, AlarmDevice);
    }

    if (AlarmTextScheduler.IsTime()) {
        AlarmTextScheduler.UpdateNextTime();
        TemperatureAlert.SetN2kAlertText(N2kMsg);
        NMEA2000.SendMsg(N2kMsg, AlarmDevice);
    }
```

for more infos, see the example in the examples folder