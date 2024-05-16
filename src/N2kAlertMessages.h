/* N2kAlertMessages.h
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

/************************************************************************//**
 * \file   N2kAlertMessages.h
 *  \brief  This File contains all SetXXX functions which will be needed to
 *          transfer data with a specific PGN.
 *
 * This is a collection of functions for handling NMEA2000 bus messages.
 * Library contains functions to e.g. create message named with PGN like
 * \ref SetN2kPGN129025 and alias easy for humans to read like \ref
 * SetN2kLatLonRapid.
 *
 * Each SetN2kPNGxxx function sets related message PGN and its default
 * priority. The default priority can be different for each PGN. So if you
 * want to change priority on function, you have to do it after Setxxx call.
 *
 * Each SetN2kPNGxxx function has a corresponding ParsN2kPGNxxx function which
 * can extract the data out of an incoming N2k Message. These functions have as
 * well an inline alias easy for humans to read like \ref ParseN2kPositionRapid.
 *
 * The content of the PGNs is specified by the NMEA2000 Standard under
 *
 * - https://web.archive.org/web/20220515054117/https://www.nmea.org/Assets/july%202010%20nmea2000_v1-301_app_b_pgn_field_list.pdf
 * - https://web.archive.org/web/20200918140201/https://www.nmea.org/Assets/20151026%20nmea%202000%20pgn_website_description_list.pdf
 *
 * If you do not send anything to NMEA2000 bus, you do not need this library.
 * Funtions for BUS handling PGN:s like 60928 "ISO Address Claim" has been
 * defined in bus device library
 *
 *  NMEA2000.h
 *
 * ********************************************************************/

#ifndef _N2KALERTMESSAGES_h
#define _N2KALERTMESSAGES_h

#if defined(ARDUINO)  &&ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <N2kMessages.h>
#include "N2kAlertTypes.h"

// Alert Notification
// The default transmission interval is not known
// This fast - packet PGN is 28 bytes long and contains 21 fields.
// The Alert Notification PGN is used to notify other devices on the network of an alert condition.
// \param N2kMsg                N2kMsg Object, Output: NMEA2000 message ready to be send.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AcknowledgeNetworkID  Network ID of the device that acknowledged the alert.
// \param TriggerCondition      Condition that triggered the alert.
// \param ThresholdStatus       Status of the alert threshold.
// \param AlertPriority         Priority of the alert.
// \param AlertState            State of the alert.
// \param TemporarySilenceStatus Temporary silence status of the alert.
// \param AcknowledgeStatus     Acknowledge status of the alert.
// \param EscalationStatus      Escalation status of the alert.
// \param TemporarySilenceSupport Temporary silence support of the alert.
// \param AcknowledgeSupport    Acknowledge support of the alert.
// \param EscalationSupport     Escalation support of the alert.
// \return                      True if the message was successfully created, false otherwise.
extern void SetN2kPGN126983(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    uint64_t AcknowledgeNetworkID,
    tN2kAlertTriggerCondition TriggerCondition,
    tN2kAlertThresholdStatus ThresholdStatus,
    unsigned char AlertPriority,
    tN2kAlertState AlertState,
    tN2kAlertYesNo TemporarySilenceStatus = N2kts_AlertNo,
    tN2kAlertYesNo AcknowledgeStatus = N2kts_AlertNo,
    tN2kAlertYesNo EscalationStatus = N2kts_AlertNo,
    tN2kAlertYesNo TemporarySilenceSupport = N2kts_AlertNo,
    tN2kAlertYesNo AcknowledgeSupport = N2kts_AlertNo,
    tN2kAlertYesNo EscalationSupport = N2kts_AlertNo
);

// Alias of PGN 126992. This alias was introduced to improve the readability
// of the source code.See parameter details on \ref SetN2kPGN126983
inline void SetN2kAlert(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    uint64_t AcknowledgeNetworkID,
    tN2kAlertTriggerCondition TriggerCondition,
    tN2kAlertThresholdStatus ThresholdStatus,
    unsigned char AlertPriority,
    tN2kAlertState AlertState,
    tN2kAlertYesNo TemporarySilenceStatus = N2kts_AlertNo,
    tN2kAlertYesNo AcknowledgeStatus = N2kts_AlertNo,
    tN2kAlertYesNo EscalationStatus = N2kts_AlertNo,
    tN2kAlertYesNo TemporarySilenceSupport = N2kts_AlertNo,
    tN2kAlertYesNo AcknowledgeSupport = N2kts_AlertNo,
    tN2kAlertYesNo EscalationSupport = N2kts_AlertNo
) {
    SetN2kPGN126983(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertID, SourceNetworkID, DataSourceInstance, DataSourceIndex, AlertOccurence,
        AcknowledgeNetworkID, TriggerCondition, ThresholdStatus, AlertPriority, AlertState, TemporarySilenceStatus, AcknowledgeStatus, EscalationStatus,
        TemporarySilenceSupport, AcknowledgeSupport, EscalationSupport);

};

// Alert Notification
// Parsing the PGN 126983.
// \param N2kMsg                N2kMsg Object, Input: NMEA2000 message to be parsed.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AcknowledgeNetworkID  Network ID of the device that acknowledged the alert.
// \param TriggerCondition      Condition that triggered the alert.
// \param ThresholdStatus       Status of the alert threshold.
// \param AlertPriority         Priority of the alert.
// \param AlertState            State of the alert.
// \param TemporarySilenceStatus Temporary silence status of the alert.
// \param AcknowledgeStatus     Acknowledge status of the alert.
// \param EscalationStatus      Escalation status of the alert.
// \param TemporarySilenceSupport Temporary silence support of the alert.
// \param AcknowledgeSupport    Acknowledge support of the alert.
// \param EscalationSupport     Escalation support of the alert.
// \return                      True if the message was successfully parsed, false otherwise.
extern bool ParseN2kPGN126983(
    const tN2kMsg &N2kMsg,
    tN2kAlertType &AlertType,
    tN2kAlertCategory &AlertCategory,
    unsigned char &AlertSystem,
    unsigned char &AlertSubSystem,
    unsigned int &AlertID,
    uint64_t &SourceNetworkID,
    unsigned char &DataSourceInstance,
    unsigned char &DataSourceIndex,
    unsigned char &AlertOccurence,
    uint64_t &AcknowledgeNetworkID,
    tN2kAlertTriggerCondition &TriggerCondition,
    tN2kAlertThresholdStatus &ThresholdStatus,
    unsigned char &AlertPriority,
    tN2kAlertState &AlertState,
    tN2kAlertYesNo &TemporarySilenceStatus,
    tN2kAlertYesNo &AcknowledgeStatus,
    tN2kAlertYesNo &EscalationStatus,
    tN2kAlertYesNo &TemporarySilenceSupport,
    tN2kAlertYesNo &AcknowledgeSupport,
    tN2kAlertYesNo &EscalationSupport
);

// Alert Response Notification
// The default transmission interval is not known
// This fast - packet PGN is 25 bytes long and contains 12 fields.
// The Alert Response Notification PGN is used to acknowledge or escalate an alert condition.
// \param N2kMsg                N2kMsg Object, Output: NMEA2000 message ready to be send.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AcknowledgeNetworkID  Network ID of the device that acknowledged the alert.
// \param ResponseCommand       Command to acknowledge or escalate the alert.
// \return                      True if the message was successfully created, false otherwise.
extern void SetN2kPGN126984(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    uint64_t AcknowledgeNetworkID,
    tN2kAlertResponseCommand ResponseCommand
);

// Alias of PGN 126984. This alias was introduced to improve the readability
// of the source code.See parameter details on \ref SetN2kPGN126984
inline void SetN2kAlertReponse(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    uint64_t AcknowledgeNetworkID,
    tN2kAlertResponseCommand ResponseCommand
) {
    SetN2kPGN126984(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertID,
        SourceNetworkID, DataSourceInstance, DataSourceIndex, AlertOccurence, AcknowledgeNetworkID,
        ResponseCommand);
};

// Alert Response Notification
// Parsing the PGN 126984.
// \param N2kMsg                N2kMsg Object, Input: NMEA2000 message to be parsed.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AcknowledgeNetworkID  Network ID of the device that acknowledged the alert.
// \param ResponseCommand       Command to acknowledge or escalate the alert.
// \return                      True if the message was successfully parsed, false otherwise.
extern bool ParseN2kPGN126984(
    const tN2kMsg &N2kMsg,
    tN2kAlertType &AlertType,
    tN2kAlertCategory &AlertCategory,
    unsigned char &AlertSystem,
    unsigned char &AlertSubSystem,
    unsigned int &AlertID,
    uint64_t &SourceNetworkID,
    unsigned char &DataSourceInstance,
    unsigned char &DataSourceIndex,
    unsigned char &AlertOccurence,
    uint64_t &AcknowledgeNetworkID,
    tN2kAlertResponseCommand &ResponseCommand
);

// Alias of PGN 126984. This alias was introduced to improve the readability
// of the source code.See parameter details on \ref ParseN2kPGN126984
inline bool ParseN2kAlertResponse(
    const tN2kMsg &N2kMsg,
    tN2kAlertType &AlertType,
    tN2kAlertCategory &AlertCategory,
    unsigned char &AlertSystem,
    unsigned char &AlertSubSystem,
    unsigned int &AlertID,
    uint64_t &SourceNetworkID,
    unsigned char &DataSourceInstance,
    unsigned char &DataSourceIndex,
    unsigned char &AlertOccurence,
    uint64_t &AcknowledgeNetworkID,
    tN2kAlertResponseCommand &ResponseCommand
) {
    ParseN2kPGN126984(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertID, 
        SourceNetworkID, DataSourceInstance, DataSourceIndex, AlertOccurence, AcknowledgeNetworkID, 
        ResponseCommand);
};

// Alert Text Notification
// The default transmission interval is not known
// This fast - packet PGN is 17 bytes long and contains 12 fields.
// The Alert Text Notification PGN is used to provide text information about an alert condition.
// \param N2kMsg                N2kMsg Object, Output: NMEA2000 message ready to be send.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AlertLanguage         Language of the alert text.
// \param AlertTextDescription  Description of the alert.
// \param AlertLocationTextDescription Description of the alert location.
// \return                      True if the message was successfully created, false otherwise.
extern void SetN2kPGN126985(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    tN2kAlertLanguage AlertLanguage,
    char* AlertTextDescription,
    char* AlertLocationTextDescription
);

// Alias of PGN 126985. This alias was introduced to improve the readability
// of the source code.See parameter details on \ref SetN2kPGN126985
inline void SetN2kAlertText(
    tN2kMsg &N2kMsg,
    tN2kAlertType AlertType,
    tN2kAlertCategory AlertCategory,
    unsigned char AlertSystem,
    unsigned char AlertSubSystem,
    unsigned int AlertID,
    uint64_t SourceNetworkID,
    unsigned char DataSourceInstance,
    unsigned char DataSourceIndex,
    unsigned char AlertOccurence,
    tN2kAlertLanguage AlertLanguage,
    char* AlertTextDescription,
    char* AlertLocationTextDescription
) {
    SetN2kPGN126985(N2kMsg, AlertType, AlertCategory, AlertSystem, AlertSubSystem, AlertID,
        SourceNetworkID, DataSourceInstance, DataSourceIndex, AlertOccurence, AlertLanguage,
        AlertTextDescription, AlertLocationTextDescription);

};

// Alert Text Notification
// Parsing the PGN 126985.
// \param N2kMsg                N2kMsg Object, Input: NMEA2000 message to be parsed.
// \param AlertType             Type of alert (e.g., warning, critical, informational).
// \param AlertCategory         Category of alert (e.g., navigational, technical).
// \param AlertSystem           System that generated the alert.
// \param AlertSubSystem        Subsystem that generated the alert.
// \param AlertID               Unique identifier for the alert.
// \param SourceNetworkID       Network ID of the device that generated the alert.
// \param DataSourceInstance    Instance of the data source that generated the alert.
// \param DataSourceIndex       Index of the data source that generated the alert.
// \param AlertOccurence        Number of times the alert has occurred.
// \param AlertLanguage         Language of the alert text.
// \param AlertTextDescription  Description of the alert.
// \param AlertLocationTextDescription Description of the alert location.
// \return                      True if the message was successfully parsed, false otherwise.
extern bool ParseN2kPGN126985(
    const tN2kMsg &N2kMsg,
    tN2kAlertType &AlertType,
    tN2kAlertCategory &AlertCategory,
    unsigned char &AlertSystem,
    unsigned char &AlertSubSystem,
    unsigned int &AlertID,
    uint64_t &SourceNetworkID,
    unsigned char &DataSourceInstance,
    unsigned char &DataSourceIndex,
    unsigned char &AlertOccurence,
    tN2kAlertLanguage &AlertLanguage,
    char* &AlertTextDescription,
    char* &AlertLocationTextDescription
);

#endif

