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

class tN2kAlert {
public:
	tN2kAlert(tN2kAlertType _AlertType, tN2kAlertCategory _AlertCategory, uint16_t _AlertId, tN2kAlertTriggerCondition _TriggerCondition = N2kts_AlertTriggerAuto, uint8_t _AlertPriority = 100,
		tN2kAlertYesNo _TemporarySilenceSupport = N2kts_AlertNo, tN2kAlertYesNo _AcknowledgeSupport = N2kts_AlertNo, tN2kAlertYesNo _EscalationSupport = N2kts_AlertNo);
	void SetAlertSystem(uint8_t _Alertsystem, uint8_t _AlertSubsystem, uint64_t _AcknowledgeNetworkId, tN2kAlertLanguage _AlertLanguage, char* _AlertDescription, char* _AlertLocation);
	void SetAlertDataSource(uint8_t _DataSourceInstance, uint8_t _DatesourceIndexSource, uint64_t _DataSourceNetworkId);
	void SetAlertThreshold(t2kNAlertThresholdMethod _Method, uint8_t _Format, uint64_t _Level);

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
	uint16_t AlertId;
	uint8_t AlertPriority;
	tN2kAlertType AlertType;
	tN2kAlertCategory AlertCategory;
	tN2kAlertState AlertState;
	uint8_t Occurence;

	tN2kAlertLanguage AlertLanguage;
	char AlertDescription[String_Len + 1];
	char AlertLocation[String_Len + 1];

	uint8_t AlertSystem;
	uint8_t AlertSubSystem;
	uint64_t AcknowledgeNetworkId;

	uint64_t DataSourceNetworkId;
	uint8_t DataSourceInstance;
	uint8_t DataSourceIndexSource;

	tN2kAlertYesNo TemporarySilenceSupport;
	tN2kAlertYesNo AcknowledgeSupport;
	tN2kAlertYesNo EscalationSupport;

	tN2kAlertYesNo TemporarySilenceStatus;
	tN2kAlertYesNo AcknowledgeStatus;
	tN2kAlertYesNo EscalationStatus;

	tN2kAlertTriggerCondition TriggerCondition;
	tN2kAlertThresholdStatus ThresholdStatus;

	t2kNAlertThresholdMethod ThresholdMethod;
	uint8_t ThresholdFormat;
	uint64_t ThresholdLevel;

	tN2kScheduler TemporarySilenceTimer;
	uint32_t TemporarySilenceDelay;

	void SetAlertExceeded();
	void ResetAlert();
};

#endif

