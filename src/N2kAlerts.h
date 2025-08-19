/* N2kAlerts.h
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
 * \file  N2kalerts.h
 * \brief This file contains the class tN2kAlert, which consists the main
 *        functionality of the library
 * 
 * With tN2kAlert class you can easily create alert objects.
 * 
 * For detailed description see \ref N2kalerts.
 * 
 */


#ifndef _N2KALERTS_h
#define _N2KALERTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "N2kAlertMessages.h"
#include <N2kTimer.h>

#define String_Len 50

 /**
  * @class tN2kAlert
  * @brief Represents an NMEA 2000 alert object with full alert management functionality.
  *
  * The tN2kAlert class provides a comprehensive interface for creating and managing alert objects
  * according to the NMEA 2000 standard. It allows configuration of alert type, category, priority,
  * trigger conditions, and supports features such as temporary silence, acknowledgment, and escalation.
  * The class can be linked to specific sensors and data sources, and supports threshold-based alerting
  * with flexible comparison methods. It also provides methods for integrating with NMEA 2000 messages,
  * including setting alert data in outgoing messages and parsing responses from the network.
  *
  * Key features:
  * - Configure alert system, subsystem, language, description, and location
  * - Link alerts to specific sensor instances and network IDs
  * - Set and evaluate threshold conditions (greater, lower, equal, etc.)
  * - Support for temporary silence, acknowledgment, and escalation
  * - Query current alert state, threshold status, and support flags
  * - Integrate with NMEA 2000 message handling (set and parse alert messages)
  *
  * Typical usage involves creating a tN2kAlert object, configuring its parameters, and periodically
  * testing sensor values against the configured threshold. The class manages all state transitions
  * and provides status queries for higher-level application logic.
  *
  * For detailed usage and examples, see the library documentation (\ref N2kalerts).
  */
class tN2kAlert {
public:
	tN2kAlert(tN2kAlertType AlertType, tN2kAlertCategory AlertCategory, uint16_t AlertId, tN2kAlertTriggerCondition TriggerCondition = N2kts_AlertTriggerAuto, uint8_t AlertPriority = 100,
		tN2kAlertYesNo TemporarySilenceSupport = N2kts_AlertNo, tN2kAlertYesNo AcknowledgeSupport = N2kts_AlertNo, tN2kAlertYesNo EscalationSupport = N2kts_AlertNo);
	void SetAlertSystem(uint8_t Alertsystem, uint8_t AlertSubsystem, uint64_t AcknowledgeNetworkId, tN2kAlertLanguage AlertLanguage, char* AlertDescription, char* AlertLocation);
	void SetAlertDataSource(uint8_t DataSourceInstance, uint8_t DatesourceIndexSource, uint64_t DataSourceNetworkId);
	void SetAlertThreshold(t2kNAlertThresholdMethod Method, uint8_t Format, uint64_t Level);

	uint16_t GetAlertID();
	tN2kAlertType GetAlertType();
	tN2kAlertCategory GetAlertCategory();
	tN2kAlertThresholdStatus GetAlertThresholdStatus();
	tN2kAlertState GetAlertState();

	tN2kAlertYesNo GetTemporarySilenceSupport();
	tN2kAlertYesNo GetAcknowledgeSupport();
	tN2kAlertYesNo GetEscalationSupport();

	tN2kAlertYesNo GetTemporarySilenceStatus();
	tN2kAlertYesNo GetAcknowledgeStatus();
	tN2kAlertYesNo GetEscalationStatus();

	tN2kAlertThresholdStatus TestAlertThreshold(uint64_t v);

	void SetN2kAlertText(tN2kMsg &N2kMsg);
	void SetN2kAlert(tN2kMsg &N2kMsg);

	void SetTemporarySilenceTime(uint16_t seconds);

	bool ParseAlertResponse(const tN2kMsg &N2kMsg);

	bool isAlert();
	bool isAcknowledged();
	bool isSilent();

private:
	uint16_t _AlertId;
	uint8_t _AlertPriority;
	tN2kAlertType _AlertType;
	tN2kAlertCategory _AlertCategory;
	tN2kAlertState _AlertState;
	uint8_t _Occurence;

	tN2kAlertLanguage _AlertLanguage;
	char _AlertDescription[String_Len + 1];
	char _AlertLocation[String_Len + 1];

	uint8_t _AlertSystem;
	uint8_t _AlertSubSystem;
	uint64_t _AcknowledgeNetworkId;

	uint64_t _DataSourceNetworkId;
	uint8_t _DataSourceInstance;
	uint8_t _DataSourceIndexSource;

	tN2kAlertYesNo _TemporarySilenceSupport;
	tN2kAlertYesNo _AcknowledgeSupport;
	tN2kAlertYesNo _EscalationSupport;

	tN2kAlertYesNo _TemporarySilenceStatus;
	tN2kAlertYesNo _AcknowledgeStatus;
	tN2kAlertYesNo _EscalationStatus;

	tN2kAlertTriggerCondition _TriggerCondition;
	tN2kAlertThresholdStatus _ThresholdStatus;

	t2kNAlertThresholdMethod _ThresholdMethod;
	uint8_t _ThresholdFormat;
	uint64_t _ThresholdLevel;

	tN2kScheduler _TemporarySilenceTimer;
	uint32_t _TemporarySilenceDelay;

	void SetAlertExceeded();
	void ResetAlert();
};

#endif

