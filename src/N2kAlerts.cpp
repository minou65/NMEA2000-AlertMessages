/* N2kAlerts.cpp
 *
 * Copyright (c) 2024 Andreas Zogg
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

/*************************************************************************//**
 * \file  N2kalerts.cpp
 * \brief This file contains the class tN2kAlert, which consists the main
 *        functionality of the library
 *
 * With tN2kAlert class you can easily create alert objects.
 *
 * For detailed description see \ref N2kalerts.
 *
 */

#include "N2kAlerts.h"
#include "N2kAlertMessagesEnumToStr.h"


// Constructor for the NMEA 2000 alert(tN2kAlert) class.
// \param _AlertType            The type of alert(e.g., warning, alarm, etc.).
// \param _AlertCategory        The category of the alert(e.g., engine, navigation, etc.).
// \param _AlertId              The unique identifier for the alert.
// \param _TriggerCondition     The condition that triggers the alert.
// \param _AlertPriority        The priority level of the alert.
// \param _TemporarySilenceSupport Whether temporary silence is supported for this alert.
// \param _AcknowledgeSupport   Whether acknowledgment is supported for this alert.
// \param _EscalationSupport    Whether escalation is supported for this alert.
tN2kAlert::tN2kAlert(tN2kAlertType _AlertType, tN2kAlertCategory _AlertCategory, uint16_t _AlertId, tN2kAlertTriggerCondition _TriggerCondition, uint8_t _AlertPriority,
	tN2kAlertYesNo _TemporarySilenceSupport, tN2kAlertYesNo _AcknowledgeSupport, tN2kAlertYesNo _EscalationSupport) :
	AlertType(_AlertType),
	AlertCategory(_AlertCategory),
	AlertId(_AlertId),
	AlertPriority(_AlertPriority),
	TemporarySilenceSupport(_TemporarySilenceSupport),
	AcknowledgeSupport(_AcknowledgeSupport),
	EscalationSupport(_EscalationSupport),
	TemporarySilenceStatus(N2kts_AlertNo),
	AcknowledgeStatus(N2kts_AlertNo),
	EscalationStatus(N2kts_AlertNo),
	Occurence(0),
	TriggerCondition(_TriggerCondition) {

	ThresholdStatus = N2kts_AlertThresholdStatusNormal;
	SetTemporarySilenceTime(3600);
	TemporarySilenceTimer = tN2kScheduler(TemporarySilenceDelay);

};

// Sets parameters for an NMEA 2000 alert system.
// \param _Alertsystem          The alert system identifier.
// \param _AlertSubsystem       The alert subsystem identifier.
// \param _AcknowledgeNetworkId The network ID for acknowledgment.
// \param _AlertLanguage        The language for the alert description.
// \param _AlertDescription     the alert description.
// \param _AlertLocation        the alert location.
void tN2kAlert::SetAlertSystem(uint8_t _Alertsystem, uint8_t _AlertSubsystem, uint64_t _AcknowledgeNetworkId, tN2kAlertLanguage _AlertLanguage, char* _AlertDescription, char* _AlertLocation) {
	AlertSystem = _Alertsystem;
	AlertSubSystem = _AlertSubsystem;
	AcknowledgeNetworkId = _AcknowledgeNetworkId;
	AlertLanguage = _AlertLanguage;
	strlcpy(AlertDescription, _AlertDescription, String_Len);
	strlcpy(AlertLocation, _AlertLocation, String_Len);
}

// Set parameters for linking an NMEA 2000 alert with a specific sensor.
// \param _DataSourceInstance   The unique identifier (UID) of the device (e.g., temperature sensor).
// \param _DatesourceIndexSource The ID of the sensor on the device (sensor index).
// \param _DataSourceNetworkId  The network ID associated with the sensor device.
void tN2kAlert::SetAlertDataSource(uint8_t _DataSourceInstance, uint8_t _DatesourceIndexSource, uint64_t _DataSourceNetworkId) {
	DataSourceNetworkId = _DataSourceNetworkId;
	DataSourceInstance = _DataSourceInstance;
	DataSourceIndexSource = _DatesourceIndexSource;
}

// Set the alert threshold.
// \param _Method  The method for the threshold (e.g., greater, lower, equal).
// \param _Format  The format for the threshold (e.g., temperature, pressure, etc.).
// \param _Level   The threshold level.
void tN2kAlert::SetAlertThreshold(t2kNAlertThresholdMethod _Method, uint8_t _Format, uint64_t _Level){
	ThresholdMethod = _Method;
	ThresholdFormat = _Format;
	ThresholdLevel = _Level;
}

// Returns the alert ID.
uint16_t tN2kAlert::GetAlertID(){
	return AlertId;
}

// Returns the alert type.
tN2kAlertType tN2kAlert::GetAlertType(){
	return tN2kAlertType(AlertType);
}

// Returns the alert category.
tN2kAlertCategory tN2kAlert::GetAlertCategory(){
	return tN2kAlertCategory(AlertCategory);
}

// Returns the alert system.
tN2kAlertThresholdStatus tN2kAlert::GetAlertThresholdStatus(){
	return tN2kAlertThresholdStatus(ThresholdStatus);
}

// Returns the alert state.
tN2kAlertState tN2kAlert::GetAlertState(){
	return tN2kAlertState(AlertState);
}

// Returns if temporary silence is supported or not.
tN2kAlertYesNo tN2kAlert::GetTemporarySilenceSupport(){
	return tN2kAlertYesNo(TemporarySilenceSupport);
}

// Returns if acknowledgment is supported or not.
tN2kAlertYesNo tN2kAlert::GetAcknowledgeSupport(){
	return tN2kAlertYesNo(AcknowledgeSupport);
}

// Returns if escalation is supported or not.
tN2kAlertYesNo tN2kAlert::GetEscalationSupport(){
	return tN2kAlertYesNo(EscalationSupport);
}

// Returns if temorary silence is active or not.
tN2kAlertYesNo tN2kAlert::GetTemporarySilenceStatus(){
	return tN2kAlertYesNo(TemporarySilenceStatus);
}

// Returns if acknowledgment is active or not.
tN2kAlertYesNo tN2kAlert::GetAcknowledgeStatus(){
	return tN2kAlertYesNo(AcknowledgeStatus);
}

// Returns if escalation is active or not.
tN2kAlertYesNo tN2kAlert::GetEscalationStatus(){
	return tN2kAlertYesNo(EscalationStatus);
}

// Set it the alert is exceeded.
void tN2kAlert::SetAlertExceeded() {

	if (Occurence > 250) Occurence = 0;

	if (ThresholdStatus == N2kts_AlertThresholdStatusNormal) {
		ThresholdStatus = N2kts_AlertThresholdStatusExceeded;
		Occurence++;
	}

	if (ThresholdStatus == N2kts_AlertThresholdStatusExceeded) {
		AlertState = N2kts_AlertStateActive;
		if (TemporarySilenceStatus == N2kts_AlertYes) {
			AlertState == N2kts_AlertStateSilenced;
		}

		if (AcknowledgeStatus == N2kts_AlertYes) {
			AlertState == N2kts_AlertStateAcknowledged;
			ThresholdStatus = N2kts_AlertThresholdStatusAcknowledged;
		}
	}
}

// Reset the alert.
void tN2kAlert::ResetAlert() {

	ThresholdStatus = N2kts_AlertThresholdStatusNormal;
	AlertState = N2kts_AlertStateNormal;

	AcknowledgeStatus = N2kts_AlertNo;
}

// Test the alert threshold.
// \param v The value to test against the threshold.
// \return The status of the alert threshold.
tN2kAlertThresholdStatus tN2kAlert::TestAlertThreshold(uint64_t v){
	if (ThresholdMethod == N2kts_AlertThresholddMethodGreater) {
		if (v > ThresholdLevel) {
			SetAlertExceeded();
		}
		else {
			ResetAlert();
		}
	}

	if (ThresholdMethod == N2kts_AlertThresholdMethodLower) {
		if (v < ThresholdLevel) {
			SetAlertExceeded();
		}
		else {
			ResetAlert();
		}
	}

	if (ThresholdMethod == N2kts_AlertThresholdMethodEqual) {
		if (v == ThresholdLevel) {
			SetAlertExceeded();
		}
		else {
			ResetAlert();
		}
	}

	if (TemporarySilenceTimer.IsTime()) {
		TemporarySilenceStatus = N2kts_AlertNo;
	}

	return tN2kAlertThresholdStatus(ThresholdStatus);
}

// set the alert text.
// \param N2kMsg The NMEA 2000 message to set the alert text.
void tN2kAlert::SetN2kAlertText(tN2kMsg &N2kMsg){
	SetN2kPGN126985(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertId, 
		DataSourceNetworkId, DataSourceInstance, DataSourceIndexSource, 
		Occurence, AlertLanguage, AlertDescription, AlertLocation);
}

// set the alert.
// \param N2kMsg The NMEA 2000 message to set the alert.
void tN2kAlert::SetN2kAlert(tN2kMsg &N2kMsg){
	SetN2kPGN126983(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertId, 
		DataSourceNetworkId, DataSourceInstance, DataSourceIndexSource, 
		Occurence, AcknowledgeNetworkId, TriggerCondition, ThresholdStatus, AlertPriority, AlertState,
		TemporarySilenceStatus, AcknowledgeStatus, EscalationStatus, 
		TemporarySilenceSupport, AcknowledgeSupport, EscalationSupport);
}

// set the temporary silence time.
// \param seconds The time in seconds to set the temporary silence time.
void tN2kAlert::SetTemporarySilenceTime(uint16_t seconds){
	TemporarySilenceDelay = seconds * 1000;
}

// parse the alert response.
// \param N2kMsg The NMEA 2000 message to parse the alert response.
// \return True if the alert response was parsed successfully.
bool tN2kAlert::ParseAlertResponse(const tN2kMsg &N2kMsg){
	tN2kAlertType _AlertType;
	tN2kAlertCategory _AlertCategory;
	unsigned char _AlertSystem;
	unsigned char _AlertSubSystem;
	unsigned int _AlertID;
	uint64_t _SourceNetworkID;
	unsigned char _DataSourceInstance;
	unsigned char _DataSourceIndex;
	unsigned char _AlertOccurence;
	uint64_t _AcknowledgeNetworkID;
	tN2kAlertResponseCommand _ResponseCommand;

	if (ParseN2kAlertResponse(N2kMsg, _AlertType, _AlertCategory, _AlertSystem, _AlertSubSystem, _AlertID, 
		_SourceNetworkID, _DataSourceInstance, _DataSourceIndex, _AlertOccurence, _AcknowledgeNetworkID, 
		_ResponseCommand)) {
		if ((AlertSystem == _AlertSystem) && (AlertSubSystem == _AlertSubSystem)) {
			switch (_ResponseCommand) {
				case N2kts_AlertResponseAcknowledge:
					AcknowledgeStatus = N2kts_AlertYes;
					break;

				case N2kts_AlertResponseTemporarySilence:
					TemporarySilenceStatus = N2kts_AlertYes;
					TemporarySilenceTimer.FromNow(TemporarySilenceDelay);
					break;

				case N2kts_AlertResponseTestCommandOff:
					break;

				case N2kts_AlertResponseTestCommandOn:
					break;
					
			}
		}
		return true;

	}

	return false;
}

// return true if the alert is active.
bool tN2kAlert::isAlert(){
	return ThresholdStatus != N2kts_AlertThresholdStatusNormal;
}

// return true if the alert is acknowledged.
bool tN2kAlert::isAcknowledged(){
	return AcknowledgeStatus = N2kts_AlertYes;
}

// return true if the alert is silenced.
bool tN2kAlert::isSilent(){
	return TemporarySilenceStatus = N2kts_AlertYes;
}
;


