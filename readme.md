# NMEA 2000 Alertmessages

## Description  
This library provides a set of functions for handling NMEA 2000 alert messages.
It allows you to parse and generate NMEA 2000 alert messages, as well as handle various alert conditions and notifications.

## Functions
```c++
// Constructor for the NMEA 2000 alert(tN2kAlert) class.
//_AlertType            The type of alert(e.g., warning, alarm, etc.).
//_AlertCategory        The category of the alert(e.g., engine, navigation, etc.).
//_AlertId              The unique identifier for the alert.
//_TriggerCondition     The condition that triggers the alert.
//_AlertPriority        The priority level of the alert.
//_TemporarySilenceSupport Whether temporary silence is supported for this alert.
//_AcknowledgeSupport   Whether acknowledgment is supported for this alert.
//_EscalationSupport    Whether escalation is supported for this alert.

tN2kAlert::tN2kAlert(tN2kAlertType _AlertType, tN2kAlertCategory _AlertCategory, uint16_t _AlertId, tN2kAlertTriggerCondition _TriggerCondition, uint8_t _AlertPriority,
	tN2kAlertYesNo _TemporarySilenceSupport, tN2kAlertYesNo _AcknowledgeSupport, tN2kAlertYesNo _EscalationSupport) 
```

```c++
//Sets parameters for an NMEA 2000 alert system.
//_Alertsystem          The alert system identifier.
//_AlertSubsystem       The alert subsystem identifier.
//_AcknowledgeNetworkId The network ID for acknowledgment.
//_AlertLanguage        The language for the alert description.
//_AlertDescription     the alert description.
//_AlertLocation        the alert location.
void tN2kAlert::SetAlertSystem(uint8_t _Alertsystem, uint8_t _AlertSubsystem,
                               uint64_t _AcknowledgeNetworkId, tN2kAlertLanguage _AlertLanguage,
                               char* _AlertDescription, char* _AlertLocation)
```

```c++
//Configures parameters for linking an NMEA 2000 alert with a specific sensor.
//_DataSourceInstance   The unique identifier (UID) of the device (e.g., temperature sensor).
//_DatesourceIndexSource The ID of the sensor on the device (sensor index).
//_DataSourceNetworkId  The network ID associated with the sensor device.
void tN2kAlert::SetAlertDataSource(uint8_t _DataSourceInstance, uint8_t _DatesourceIndexSource,
                                   uint64_t _DataSourceNetworkId)
```

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