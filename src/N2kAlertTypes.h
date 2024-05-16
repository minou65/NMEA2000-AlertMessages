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

#ifndef _N2KALERTTYPES_h
#define _N2KALERTTYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


 // Enumerations for alert types
enum tN2kAlertType {
    N2kts_AlertTypeEmergencyAlarm = 1,
    N2kts_AlertTypeAlarm = 2,
    N2kts_AlertTypeWarning = 5,
    N2kts_AlertTypeCaution = 8
};

// Enumerations for alert categories
enum tN2kAlertCategory {
    N2kts_AlertCategoryNavigational = 0,
    N2kts_AlertCategoryTechnical = 1
};

// Enumerations for alert conditions
enum tN2kAlertTriggerCondition {
    N2kts_AlertTriggerManual = 0,
    N2kts_AlertTriggerAuto = 1,
    N2kts_AlertTriggerTest = 2,
    N2kts_AlertTriggerDisabled = 3
};

// Enumerations for alert thresholds
enum tN2kAlertThresholdStatus {
    N2kts_AlertThresholdStatusNormal = 0,
    N2kts_AlertThresholdStatusExceeded = 1,
    N2kts_AlertThresholdStatusExtremeExceeded = 2,
    N2kts_AlertThresholdStatusLowExceeded = 3,
    N2kts_AlertThresholdStatusAcknowledged = 4,
    N2kts_AlertThresholdStatusAwaitingAcknowledge = 5
};

// Enumerations for alert states
enum tN2kAlertState {
    N2kts_AlertStateDisabled = 0,
    N2kts_AlertStateNormal = 1,
    N2kts_AlertStateActive = 2,
    N2kts_AlertStateSilenced = 3,
    N2kts_AlertStateAcknowledged = 4,
    N2kts_AlertStateAwaitingAcknowledge = 5
};

// Enumerations for alert languages
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

// Enumerations for alert response commands
enum tN2kAlertResponseCommand {
    N2kts_AlertResponseAcknowledge = 0,
    N2kts_AlertResponseTemporarySilence = 1,
    N2kts_AlertResponseTestCommandOff = 2,
    N2kts_AlertResponseTestCommandOn = 3
};

// Enumerations for alert yes/no
enum tN2kAlertYesNo {
    N2kts_AlertNo = 0,
    N2kts_AlertYes = 1
};

// Enumerations for alert threshold methods
// this values are not defined in the standard
enum t2kNAlertThresholdMethod {
    N2kts_AlertThresholdMethodEqual = 0,
    N2kts_AlertThresholdMethodLower = 1,
    N2kts_AlertThresholddMethodGreater = 2
};

#endif

