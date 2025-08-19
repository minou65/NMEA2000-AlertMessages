/* N2kAlertTypes.h
 *
 * Copyright (c) 2024 Andreas Zogg
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
 * \file  N2kAlertTypes.h
 * \brief This File contains all specific Enumerations to make NMEA2000
 *        Messages easier for humans to read.
 *
 * Each NMEA2000 message has a specific CanID (address) which consists a
 * PGN Number (eg. PGN127802) and carries 8byte of raw data. For every PGN
 * exists a detailed description how these 8 bytes transfer into usable values.
 * To save bandwidth not all of values have the size of 1byte. All sizes from
 * 1bit to 64bits are allowed. The Enumerations of this file make these values
 * easier for humans to read, and are used in the corresponding SetXXX and
 * ParseXXX functions of \ref N2kMessages.h .
 */

 /** @{ \ingroup  group_msgTypes */

/*************************************************************************//**
 * \file  N2kAlertTypes.h
 * \brief This file contains all specific enumerations to make NMEA2000
 *        alert messages easier for humans to read and process.
 *
 * Each NMEA2000 message has a specific CAN ID (address) which consists of a
 * PGN number (e.g., PGN127802) and carries 8 bytes of raw data. For every PGN
 * there is a detailed description of how these 8 bytes are converted into usable values.
 * To save bandwidth, not all values have the size of 1 byte. All sizes from
 * 1 bit to 64 bits are allowed. The enumerations in this file make these values
 * easier for humans to read and are used in the corresponding SetXXX and
 * ParseXXX functions of \ref N2kMessages.h.
 *
 * Enumerations defined in this file include:
 * - tN2kAlertType:        Types of alerts (e.g., emergency alarm, warning, caution)
 * - tN2kAlertCategory:    Categories of alerts (e.g., navigational, technical)
 * - tN2kAlertTriggerCondition: Conditions that trigger an alert (manual, auto, test, disabled)
 * - tN2kAlertThresholdStatus:  Status of the alert threshold (normal, exceeded, acknowledged, etc.)
 * - tN2kAlertState:       State of the alert (disabled, normal, active, silenced, acknowledged, etc.)
 * - tN2kAlertLanguage:    Supported languages for alert messages
 * - tN2kAlertResponseCommand: Response commands for alert handling (acknowledge, silence, test, etc.)
 * - tN2kAlertYesNo:       Yes/No values for alert features and states
 * - t2kNAlertThresholdMethod: Methods for threshold comparison (equal, lower, greater)
 *
 * These enumerations are essential for the configuration, evaluation, and handling
 * of NMEA2000 alert messages in the tN2kAlert class and related functions.
 *
 * For detailed usage and examples, see the library documentation (\ref N2kalerts).
 */

#ifndef _N2KALERTTYPES_h
#define _N2KALERTTYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


 /**
  * @enum tN2kAlertType
  * @brief Defines the type of NMEA 2000 alert.
  *
  * This enumeration specifies the severity or nature of an alert in the NMEA 2000 alert system.
  * Each value represents a different alert level, which can be used to distinguish between
  * critical alarms, general alarms, warnings, and cautions. The alert type determines how
  * the alert should be handled and displayed by the system.
  *
  * - N2kts_AlertTypeEmergencyAlarm (1): Indicates an emergency alarm, the highest severity level.
  * - N2kts_AlertTypeAlarm (2): Represents a general alarm condition that requires immediate attention.
  * - N2kts_AlertTypeWarning (5): Signals a warning, which is less severe than an alarm but should be noted.
  * - N2kts_AlertTypeCaution (8): Indicates a caution, the lowest severity, used for informational or minor issues.
  */
enum tN2kAlertType {
    N2kts_AlertTypeEmergencyAlarm = 1,
    N2kts_AlertTypeAlarm = 2,
    N2kts_AlertTypeWarning = 5,
    N2kts_AlertTypeCaution = 8
};

/**
 * @enum tN2kAlertCategory
 * @brief Defines the category of an NMEA 2000 alert.
 *
 * This enumeration specifies the main category to which an alert belongs.
 * It helps to distinguish between navigational and technical alerts, allowing
 * systems to handle and display them differently.
 *
 * - N2kts_AlertCategoryNavigational (0): Navigational alert (e.g., related to course, position, or navigation systems).
 * - N2kts_AlertCategoryTechnical (1): Technical alert (e.g., related to engine, electrical, or other onboard systems).
 */
enum tN2kAlertCategory {
    N2kts_AlertCategoryNavigational = 0,
    N2kts_AlertCategoryTechnical = 1
};

/**
 * @enum tN2kAlertTriggerCondition
 * @brief Defines the condition that triggers an NMEA 2000 alert.
 *
 * This enumeration specifies how an alert is triggered, such as manually by the user,
 * automatically by the system, for testing purposes, or if the alert is disabled.
 *
 * - N2kts_AlertTriggerManual (0): Alert is triggered manually.
 * - N2kts_AlertTriggerAuto (1): Alert is triggered automatically by the system.
 * - N2kts_AlertTriggerTest (2): Alert is triggered for test purposes.
 * - N2kts_AlertTriggerDisabled (3): Alert is disabled and will not be triggered.
 */
enum tN2kAlertTriggerCondition {
    N2kts_AlertTriggerManual = 0,
    N2kts_AlertTriggerAuto = 1,
    N2kts_AlertTriggerTest = 2,
    N2kts_AlertTriggerDisabled = 3
};

/**
 * @enum tN2kAlertThresholdStatus
 * @brief Defines the threshold status of an NMEA 2000 alert.
 *
 * This enumeration indicates the current status of the alert threshold, such as whether
 * the threshold is normal, exceeded, acknowledged, or awaiting acknowledgment.
 *
 * - N2kts_AlertThresholdStatusNormal (0): Threshold is within normal range.
 * - N2kts_AlertThresholdStatusExceeded (1): Threshold has been exceeded.
 * - N2kts_AlertThresholdStatusExtremeExceeded (2): Threshold has been extremely exceeded.
 * - N2kts_AlertThresholdStatusLowExceeded (3): Threshold has been exceeded on the low side.
 * - N2kts_AlertThresholdStatusAcknowledged (4): Exceeded threshold has been acknowledged.
 * - N2kts_AlertThresholdStatusAwaitingAcknowledge (5): Awaiting acknowledgment for exceeded threshold.
 */
enum tN2kAlertThresholdStatus {
    N2kts_AlertThresholdStatusNormal = 0,
    N2kts_AlertThresholdStatusExceeded = 1,
    N2kts_AlertThresholdStatusExtremeExceeded = 2,
    N2kts_AlertThresholdStatusLowExceeded = 3,
    N2kts_AlertThresholdStatusAcknowledged = 4,
    N2kts_AlertThresholdStatusAwaitingAcknowledge = 5
};

/**
 * @enum tN2kAlertState
 * @brief Defines the state of an NMEA 2000 alert.
 *
 * This enumeration represents the current state of the alert, such as whether it is
 * disabled, normal, active, silenced, acknowledged, or awaiting acknowledgment.
 *
 * - N2kts_AlertStateDisabled (0): Alert is disabled.
 * - N2kts_AlertStateNormal (1): Alert is in normal state (not active).
 * - N2kts_AlertStateActive (2): Alert is active.
 * - N2kts_AlertStateSilenced (3): Alert is active but silenced.
 * - N2kts_AlertStateAcknowledged (4): Alert has been acknowledged.
 * - N2kts_AlertStateAwaitingAcknowledge (5): Alert is awaiting acknowledgment.
 */
enum tN2kAlertState {
    N2kts_AlertStateDisabled = 0,
    N2kts_AlertStateNormal = 1,
    N2kts_AlertStateActive = 2,
    N2kts_AlertStateSilenced = 3,
    N2kts_AlertStateAcknowledged = 4,
    N2kts_AlertStateAwaitingAcknowledge = 5
};

/**
 * @enum tN2kAlertLanguage
 * @brief Defines the language for NMEA 2000 alert messages.
 *
 * This enumeration specifies the language used for alert descriptions and messages.
 * It allows alerts to be displayed in the preferred language of the user or system.
 *
 * (See enum values for supported languages.)
 */
enum tN2kAlertLanguage {
    N2kts_AlertLanguageEnglishUS = 0,
    N2kts_AlertLanguageEnglishUK = 1,
    N2kts_AlertLanguageArabic = 2,
    N2kts_AlertLanguageChineseSimplified = 3,
    N2kts_AlertLanguageCroatian = 4,
    N2kts_AlertLanguageDanish = 5,
    N2kts_AlertLanguageDutch = 6,
    N2kts_AlertLanguageFinnish = 7,
    N2kts_AlertLanguageFrench = 8,
    N2kts_AlertLanguageGerman = 9,
    N2kts_AlertLanguageGreek = 10,
    N2kts_AlertLanguageItalian = 11,
    N2kts_AlertLanguageJapanese = 12,
    N2kts_AlertLanguageKorean = 13,
    N2kts_AlertLanguageNorwegian = 14,
    N2kts_AlertLanguagePolish = 15,
    N2kts_AlertLanguagePortuguese = 16,
    N2kts_AlertLanguageRussian = 17,
    N2kts_AlertLanguageSpanish = 18,
    N2kts_AlertLanguageSwedish = 19
};

/**
 * @enum tN2kAlertResponseCommand
 * @brief Defines the response commands for NMEA 2000 alerts.
 *
 * This enumeration specifies the possible commands that can be sent in response to an alert,
 * such as acknowledgment, temporary silence, or test commands.
 *
 * - N2kts_AlertResponseAcknowledge (0): Acknowledge the alert.
 * - N2kts_AlertResponseTemporarySilence (1): Temporarily silence the alert.
 * - N2kts_AlertResponseTestCommandOff (2): Send a test command to turn off test mode.
 * - N2kts_AlertResponseTestCommandOn (3): Send a test command to turn on test mode.
 */
enum tN2kAlertResponseCommand {
    N2kts_AlertResponseAcknowledge = 0,
    N2kts_AlertResponseTemporarySilence = 1,
    N2kts_AlertResponseTestCommandOff = 2,
    N2kts_AlertResponseTestCommandOn = 3
};

/**
 * @enum tN2kAlertYesNo
 * @brief Defines a yes/no value for NMEA 2000 alert features and states.
 *
 * This enumeration is used for flags and options that require a simple yes/no (enabled/disabled) value.
 *
 * - N2kts_AlertNo (0): No / Disabled.
 * - N2kts_AlertYes (1): Yes / Enabled.
 */
enum tN2kAlertYesNo {
    N2kts_AlertNo = 0,
    N2kts_AlertYes = 1
};

/**
 * @enum t2kNAlertThresholdMethod
 * @brief Defines the method for threshold comparison in NMEA 2000 alerts.
 *
 * This enumeration specifies how a value is compared to the threshold to determine if an alert should be triggered.
 * These values are not defined in the NMEA 2000 standard but are used for internal logic.
 *
 * - N2kts_AlertThresholdMethodEqual (0): Trigger alert if value is equal to threshold.
 * - N2kts_AlertThresholdMethodLower (1): Trigger alert if value is lower than threshold.
 * - N2kts_AlertThresholdMethodGreater (2): Trigger alert if value is greater than threshold.
 */
enum t2kNAlertThresholdMethod {
    N2kts_AlertThresholdMethodEqual = 0,
    N2kts_AlertThresholdMethodLower = 1,
    N2kts_AlertThresholdMethodGreater = 2
};

#endif

