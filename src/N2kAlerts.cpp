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


 // Constructor for the NMEA 2000 alert (tN2kAlert) class.
 /**
  * \brief Creates a new alert object with all relevant parameters.
  *
  * Initializes all status and control variables to their default values.
  * The alert state is set to "Normal", and the threshold status is set to "Normal".
  * Temporary silence is initially disabled and set to 3600 seconds (1 hour).
  * The associated timer is initialized accordingly.
  *
  * \param AlertType                The type of alert (e.g., warning, alarm).
  * \param AlertCategory            The category of the alert (e.g., engine, navigation).
  * \param AlertId                  The unique identifier for the alert.
  * \param TriggerCondition         The condition that triggers the alert.
  * \param AlertPriority            The priority level of the alert.
  * \param TemporarySilenceSupport  Whether temporary silence is supported for this alert.
  * \param AcknowledgeSupport       Whether acknowledgment is supported for this alert.
  * \param EscalationSupport        Whether escalation is supported for this alert.
  */
tN2kAlert::tN2kAlert(tN2kAlertType AlertType, tN2kAlertCategory AlertCategory, uint16_t AlertId, tN2kAlertTriggerCondition TriggerCondition, uint8_t AlertPriority,
	tN2kAlertYesNo TemporarySilenceSupport, tN2kAlertYesNo AcknowledgeSupport, tN2kAlertYesNo EscalationSupport) :
	_AlertType(AlertType),
	_AlertCategory(AlertCategory),
	_AlertId(AlertId),
	_AlertPriority(AlertPriority),
	_AlertState(N2kts_AlertStateNormal),
	_TemporarySilenceSupport(TemporarySilenceSupport),
	_AcknowledgeSupport(AcknowledgeSupport),
	_EscalationSupport(EscalationSupport),
	_TemporarySilenceStatus(N2kts_AlertNo),
	_AcknowledgeStatus(N2kts_AlertNo),
	_EscalationStatus(N2kts_AlertNo),
	_Occurence(0),
	_TriggerCondition(TriggerCondition) {

	_ThresholdStatus = N2kts_AlertThresholdStatusNormal;
	SetTemporarySilenceTime(3600);
	_TemporarySilenceTimer = tN2kScheduler(_TemporarySilenceDelay);

}

tN2kAlert::tN2kAlert(
	tN2kAlertType AlertType,
	tN2kAlertCategory AlertCategory,
	uint16_t AlertId,
	tN2kAlertTriggerCondition TriggerCondition,
	uint8_t AlertPriority,
	tN2kAlertYesNo TemporarySilenceSupport,
	tN2kAlertYesNo AcknowledgeSupport,
	tN2kAlertYesNo EscalationSupport,
	uint8_t OccurenceThreshold
) :
	_AlertType(AlertType),
	_AlertCategory(AlertCategory),
	_AlertId(AlertId),
	_AlertPriority(AlertPriority),
	_AlertState(N2kts_AlertStateNormal),
	_TemporarySilenceSupport(TemporarySilenceSupport),
	_AcknowledgeSupport(AcknowledgeSupport),
	_EscalationSupport(EscalationSupport),
	_TemporarySilenceStatus(N2kts_AlertNo),
	_AcknowledgeStatus(N2kts_AlertNo),
	_EscalationStatus(N2kts_AlertNo),
	_Occurence(0),
	_OccurenceThreshold(OccurenceThreshold),
	_TriggerCondition(TriggerCondition)
{
	_ThresholdStatus = N2kts_AlertThresholdStatusNormal;
	SetTemporarySilenceTime(3600);
	_TemporarySilenceTimer = tN2kScheduler(_TemporarySilenceDelay);

	if (OccurenceThreshold == 0) {
		_OccurenceThreshold = 1; // Ensure that the threshold is at least 1
	}
	
	if (OccurenceThreshold > 250) {
		_OccurenceThreshold = 1; // Cap the threshold to a maximum of 250
	}
}

/**
 * @brief Sets parameters for an NMEA 2000 alert system.
 *
 * This method configures the alert system and subsystem, the network ID for acknowledgment,
 * the language for the alert description, as well as the alert description and location text.
 * All values are copied or assigned to the corresponding member variables of the alert object.
 *
 * @param Alertsystem           The alert system identifier.
 * @param AlertSubsystem        The alert subsystem identifier.
 * @param AcknowledgeNetworkId  The network ID used for acknowledgment messages.
 * @param AlertLanguage         The language used for the alert description.
 * @param AlertDescription      The alert description text (null-terminated C string).
 * @param AlertLocation         The alert location text (null-terminated C string).
 */
void tN2kAlert::SetAlertSystem(uint8_t Alertsystem, uint8_t AlertSubsystem, uint64_t AcknowledgeNetworkId, tN2kAlertLanguage AlertLanguage, char* AlertDescription, char* AlertLocation) {
	_AlertSystem = Alertsystem;
	_AlertSubSystem = AlertSubsystem;
	_AcknowledgeNetworkId = AcknowledgeNetworkId;
	_AlertLanguage = AlertLanguage;
	strlcpy(_AlertDescription, AlertDescription, String_Len);
	strlcpy(_AlertLocation, AlertLocation, String_Len);
}

/**
 * @brief Sets parameters for linking an NMEA 2000 alert with a specific sensor.
 *
 * This method assigns the data source information to the alert object.
 * It links the alert to a specific device (e.g., a temperature sensor) by setting the device instance,
 * the sensor index on that device, and the network ID associated with the sensor device.
 *
 * @param DataSourceInstance      The unique identifier (instance) of the device (e.g., temperature sensor).
 * @param DatesourceIndexSource   The index of the sensor on the device (sensor index).
 * @param DataSourceNetworkId     The network ID associated with the sensor device.
 */
void tN2kAlert::SetAlertDataSource(uint8_t DataSourceInstance, uint8_t DatesourceIndexSource, uint64_t DataSourceNetworkId) {
	_DataSourceNetworkId = DataSourceNetworkId;
	_DataSourceInstance = DataSourceInstance;
	_DataSourceIndexSource = DatesourceIndexSource;
}

/**
 * @brief Sets the alert threshold parameters.
 *
 * This method configures the threshold detection for the alert. It sets the method
 * used to compare values (e.g., greater than, less than, equal), the format of the
 * threshold (such as temperature, pressure, etc.), and the threshold level itself.
 * These parameters determine when the alert will be triggered based on incoming sensor data.
 *
 * @param Method   The method for threshold comparison (e.g., greater, lower, equal).
 * @param Format   The format for the threshold (e.g., temperature, pressure, etc.).
 * @param Level    The threshold level value.
 */
void tN2kAlert::SetAlertThreshold(t2kNAlertThresholdMethod Method, uint8_t Format, uint64_t Level){
	_ThresholdMethod = Method;
	_ThresholdFormat = Format;
	_ThresholdLevel = Level;
}

/**
 * @brief Returns the alert ID.
 *
 * This method returns the unique identifier assigned to the alert object.
 *
 * @return The alert ID as a 16-bit unsigned integer.
 */
uint16_t tN2kAlert::GetAlertID(){
	return _AlertId;
}

/**
 * @brief Returns the alert type.
 *
 * This method returns the type of the alert (e.g., warning, alarm).
 *
 * @return The alert type as a tN2kAlertType value.
 */
tN2kAlertType tN2kAlert::GetAlertType(){
	return tN2kAlertType(_AlertType);
}

/**
 * @brief Returns the alert category.
 *
 * This method returns the category of the alert (e.g., engine, navigation).
 *
 * @return The alert category as a tN2kAlertCategory value.
 */
tN2kAlertCategory tN2kAlert::GetAlertCategory(){
	return tN2kAlertCategory(_AlertCategory);
}

/**
 * @brief Returns the alert threshold status.
 *
 * This method returns the current threshold status of the alert (e.g., normal, exceeded, acknowledged).
 *
 * @return The alert threshold status as a tN2kAlertThresholdStatus value.
 */
tN2kAlertThresholdStatus tN2kAlert::GetAlertThresholdStatus(){
	return tN2kAlertThresholdStatus(_ThresholdStatus);
}

/**
 * @brief Returns the alert state.
 *
 * This method returns the current state of the alert (e.g., normal, active, silenced, acknowledged).
 *
 * @return The alert state as a tN2kAlertState value.
 */
tN2kAlertState tN2kAlert::GetAlertState(){
	return tN2kAlertState(_AlertState);
}

/**
 * @brief Returns whether temporary silence is supported.
 *
 * This method returns whether the alert supports temporary silence functionality.
 *
 * @return N2kts_AlertYes if supported, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetTemporarySilenceSupport(){
	return tN2kAlertYesNo(_TemporarySilenceSupport);
}

/**
 * @brief Returns whether acknowledgment is supported.
 *
 * This method returns whether the alert supports acknowledgment functionality.
 *
 * @return N2kts_AlertYes if supported, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetAcknowledgeSupport(){
	return tN2kAlertYesNo(_AcknowledgeSupport);
}

/**
 * @brief Returns whether escalation is supported.
 *
 * This method returns whether the alert supports escalation functionality.
 *
 * @return N2kts_AlertYes if supported, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetEscalationSupport(){
	return tN2kAlertYesNo(_EscalationSupport);
}

/**
 * @brief Returns whether temporary silence is currently active.
 *
 * This method returns the current status of temporary silence for the alert.
 *
 * @return N2kts_AlertYes if temporary silence is active, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetTemporarySilenceStatus(){
	return tN2kAlertYesNo(_TemporarySilenceStatus);
}

/**
 * @brief Returns whether acknowledgment is currently active.
 *
 * This method returns the current acknowledgment status for the alert.
 *
 * @return N2kts_AlertYes if acknowledged, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetAcknowledgeStatus(){
	return tN2kAlertYesNo(_AcknowledgeStatus);
}

/**
 * @brief Returns whether escalation is currently active.
 *
 * This method returns the current escalation status for the alert.
 *
 * @return N2kts_AlertYes if escalation is active, otherwise N2kts_AlertNo.
 */
tN2kAlertYesNo tN2kAlert::GetEscalationStatus(){
	return tN2kAlertYesNo(_EscalationStatus);
}

/**
 * @brief Sets the alert as exceeded if the threshold condition is met.
 *
 * This method updates the alert's internal state when the threshold condition is exceeded.
 * If the threshold status was previously normal, it is set to exceeded and the occurrence counter is incremented.
 * If the alert is in the exceeded state, the alert state is set to active, silenced, or acknowledged
 * depending on the current silence and acknowledgment status. If the occurrence counter exceeds 250,
 * it is reset to 0 to prevent overflow.
 */
void tN2kAlert::SetAlertExceeded() {
	if (_Occurence > 250) _Occurence = 0; // reset occurence if it is too high

	if (_ThresholdStatus == N2kts_AlertThresholdStatusNormal) {
		_Occurence++;
		if (_Occurence >= _OccurenceThreshold) {
			_ThresholdStatus = N2kts_AlertThresholdStatusExceeded;
		}
	}

	if (_ThresholdStatus == N2kts_AlertThresholdStatusExceeded) {
		_AlertState = N2kts_AlertStateActive;
		if (_TemporarySilenceStatus == N2kts_AlertYes) {
			_AlertState = N2kts_AlertStateSilenced;
		}
		if (_AcknowledgeStatus == N2kts_AlertYes) {
			_AlertState = N2kts_AlertStateAcknowledged;
			_ThresholdStatus = N2kts_AlertThresholdStatusAcknowledged;
		}
	}
}

/**
 * @brief Resets the alert to its normal state.
 *
 * This method resets the alert's threshold status and state to normal.
 * The acknowledgment status is also cleared. Other statuses, such as temporary silence,
 * are not affected by this method.
 */
void tN2kAlert::ResetAlert() {
	_ThresholdStatus = N2kts_AlertThresholdStatusNormal;
	_AlertState = N2kts_AlertStateNormal;
	_AcknowledgeStatus = N2kts_AlertNo;
	_Occurence = 0;
}

/**
 * @brief Tests a value against the alert threshold and updates the alert state.
 *
 * This method compares the given value to the configured threshold using the selected method
 * (greater, lower, or equal). If the threshold is exceeded, the alert is set as exceeded;
 * otherwise, it is reset. If the temporary silence timer has expired, the silence status is cleared.
 *
 * @param v The value to test against the threshold.
 * @return The current threshold status after evaluation.
 */
tN2kAlertThresholdStatus tN2kAlert::TestAlertThreshold(uint64_t v){
	switch (_ThresholdMethod) {
	case N2kts_AlertThresholdMethodGreater:
		(v > _ThresholdLevel) ? SetAlertExceeded() : ResetAlert();
		break;
	case N2kts_AlertThresholdMethodLower:
		(v < _ThresholdLevel) ? SetAlertExceeded() : ResetAlert();
		break;
	case N2kts_AlertThresholdMethodEqual:
		(v == _ThresholdLevel) ? SetAlertExceeded() : ResetAlert();
		break;
}

	if (_TemporarySilenceTimer.IsTime()) {
		_TemporarySilenceStatus = N2kts_AlertNo;
	}

	return tN2kAlertThresholdStatus(_ThresholdStatus);
}

// set the alert text.
// \param N2kMsg The NMEA 2000 message to set the alert text.
void tN2kAlert::SetN2kAlertText(tN2kMsg &N2kMsg){
	SetN2kPGN126985(N2kMsg, _AlertType, _AlertCategory, _AlertSystem, _AlertSubSystem, _AlertId, 
		_DataSourceNetworkId, _DataSourceInstance, _DataSourceIndexSource, 
		_Occurence, _AlertLanguage, _AlertDescription, _AlertLocation);
}

// set the alert.
// \param N2kMsg The NMEA 2000 message to set the alert.
void tN2kAlert::SetN2kAlert(tN2kMsg &N2kMsg){
	SetN2kPGN126983(N2kMsg, _AlertType, _AlertCategory, _AlertSystem, _AlertSubSystem, _AlertId, 
		_DataSourceNetworkId, _DataSourceInstance, _DataSourceIndexSource, 
		_Occurence, _AcknowledgeNetworkId, _TriggerCondition, _ThresholdStatus, _AlertPriority, _AlertState,
		_TemporarySilenceStatus, _AcknowledgeStatus, _EscalationStatus, 
		_TemporarySilenceSupport, _AcknowledgeSupport, _EscalationSupport);
}

// set the temporary silence time.
// \param seconds The time in seconds to set the temporary silence time.
void tN2kAlert::SetTemporarySilenceTime(uint16_t seconds){
	_TemporarySilenceDelay = seconds * 1000;
}

void tN2kAlert::SetOccurenceThreshold(uint8_t threshold) {
	_OccurenceThreshold = threshold;
	if (_OccurenceThreshold == 0) {
		_OccurenceThreshold = 1; // prevent division by zero
	}
}

uint8_t tN2kAlert::GetOccurenceThreshold() const {
	return _OccurenceThreshold;
}

/**
 * @brief Parses an incoming NMEA 2000 alert response message.
 *
 * This method processes a received NMEA 2000 message and updates the alert object's status
 * based on the response command contained in the message. It checks if the alert system and
 * subsystem match the current alert, and then handles acknowledgment, temporary silence, or
 * test commands accordingly. The method returns true if the message was successfully parsed
 * and processed for this alert.
 *
 * @param N2kMsg The NMEA 2000 message to parse for an alert response.
 * @return True if the alert response was parsed and processed successfully, otherwise false.
 */
bool tN2kAlert::ParseAlertResponse(const tN2kMsg &N2kMsg){
	tN2kAlertType AlertType;
	tN2kAlertCategory AlertCategory;
	unsigned char AlertSystem;
	unsigned char AlertSubSystem;
	unsigned int AlertID;
	uint64_t SourceNetworkID;
	unsigned char DataSourceInstance;
	unsigned char DataSourceIndex;
	unsigned char AlertOccurence;
	uint64_t AcknowledgeNetworkID;
	tN2kAlertResponseCommand ResponseCommand;

	if (ParseN2kAlertResponse(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertID, 
		SourceNetworkID, DataSourceInstance, DataSourceIndex, AlertOccurence, AcknowledgeNetworkID, 
		ResponseCommand)) {
		if ((AlertSystem == _AlertSystem) && (AlertSubSystem == _AlertSubSystem)) {
			switch (ResponseCommand) {
				case N2kts_AlertResponseAcknowledge:
					_AcknowledgeStatus = N2kts_AlertYes;
					break;

				case N2kts_AlertResponseTemporarySilence:
					_TemporarySilenceStatus = N2kts_AlertYes;
					_TemporarySilenceTimer.FromNow(_TemporarySilenceDelay);
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

/**
 * @brief Returns whether the alert is currently active.
 *
 * This method checks if the alert threshold status is not normal, indicating that
 * the alert condition has been triggered.
 *
 * @return true if the alert is active, otherwise false.
 */
bool tN2kAlert::isAlert(){
	return _ThresholdStatus != N2kts_AlertThresholdStatusNormal;
}

/**
 * @brief Returns whether the alert has been acknowledged.
 *
 * This method checks if the acknowledgment status is set, indicating that
 * the alert has been acknowledged by the user or system.
 *
 * @return true if the alert is acknowledged, otherwise false.
 */
bool tN2kAlert::isAcknowledged(){
	return _AcknowledgeStatus == N2kts_AlertYes;
}

/**
 * @brief Returns whether the alert is currently silenced.
 *
 * This method checks if the temporary silence status is set, indicating that
 * the alert is currently in a silenced state.
 *
 * @return true if the alert is silenced, otherwise false.
 */
bool tN2kAlert::isSilent(){
	return _TemporarySilenceStatus == N2kts_AlertYes;
}





