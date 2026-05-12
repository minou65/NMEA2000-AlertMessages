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
 * The library contains functions to, e.g., create messages named with PGN like
 * \ref SetN2kPGN129025 and aliases that are easy for humans to read, like \ref
 * SetN2kLatLonRapid.
 *
 * Each SetN2kPGNxxx function sets the related message PGN and its default
 * priority. The default priority can be different for each PGN. If you
 * want to change the priority, you must do so after calling the SetXXX function.
 *
 * Each SetN2kPGNxxx function has a corresponding ParseN2kPGNxxx function which
 * can extract the data out of an incoming N2k message. These functions also have
 * an inline alias that is easier for humans to read, like \ref ParseN2kPositionRapid.
 *
 * The content of the PGNs is specified by the NMEA2000 Standard under:
 *
 * - https://web.archive.org/web/20220515054117/https://www.nmea.org/Assets/july%202010%20nmea2000_v1-301_app_b_pgn_field_list.pdf
 * - https://web.archive.org/web/20200918140201/https://www.nmea.org/Assets/20151026%20nmea%202000%20pgn_website_description_list.pdf
 *
 * If you do not send any Alert messages to the NMEA2000 bus, you do not need this library.
 * Functions for bus handling PGNs like 60928 "ISO Address Claim" have been
 * defined in the bus device library
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

 /**
  * @brief Creates an NMEA2000 Alert Notification message (PGN 126983).
  *
  * This function fills a tN2kMsg object with the data required to notify other devices
  * on the network of an alert condition. The fast-packet PGN is 28 bytes long and contains 21 fields.
  *
  * @param[out] N2kMsg                    N2kMsg object to be filled with the NMEA2000 message.
  * @param[in]  AlertType                 Type of alert (e.g., warning, critical, informational).
  * @param[in]  AlertCategory             Category of alert (e.g., navigational, technical).
  * @param[in]  AlertSystem               System that generated the alert.
  * @param[in]  AlertSubSystem            Subsystem that generated the alert.
  * @param[in]  AlertID                   Unique identifier for the alert.
  * @param[in]  SourceNetworkID           Network ID of the device that generated the alert.
  * @param[in]  DataSourceInstance        Instance of the data source that generated the alert.
  * @param[in]  DataSourceIndex           Index of the data source that generated the alert.
  * @param[in]  AlertOccurence            Number of times the alert has occurred.
  * @param[in]  AcknowledgeNetworkID      Network ID of the device that acknowledged the alert.
  * @param[in]  TriggerCondition          Condition that triggered the alert.
  * @param[in]  ThresholdStatus           Status of the alert threshold.
  * @param[in]  AlertPriority             Priority of the alert.
  * @param[in]  AlertState                State of the alert.
  * @param[in]  TemporarySilenceStatus    Temporary silence status of the alert (optional, default: N2kts_AlertNo).
  * @param[in]  AcknowledgeStatus         Acknowledge status of the alert (optional, default: N2kts_AlertNo).
  * @param[in]  EscalationStatus          Escalation status of the alert (optional, default: N2kts_AlertNo).
  * @param[in]  TemporarySilenceSupport   Temporary silence support of the alert (optional, default: N2kts_AlertNo).
  * @param[in]  AcknowledgeSupport        Acknowledge support of the alert (optional, default: N2kts_AlertNo).
  * @param[in]  EscalationSupport         Escalation support of the alert (optional, default: N2kts_AlertNo).
  *
  * @note The default transmission interval is not known.
  */
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

/************************************************************************//**
 * @brief Setting up Message "Alert Notification" - PGN 126983
 *
 * Alias of PGN 126983. This alias was introduced to improve the readability
 * of the source code. See parameter details on \ref SetN2kPGN126983
 *
 */
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

/************************************************************************//**
 * @brief Parsing Message "Alert Notification" - PGN 126983
 *
 * Parses an NMEA2000 Alert Notification message (PGN 126983) and extracts all alert-related fields.
 * See parameter details on \ref ParseN2kPGN126983.
 *
 * @param[in]  N2kMsg                    N2kMsg object containing the NMEA2000 message to be parsed.
 * @param[out] AlertType                 Type of alert (e.g., warning, critical, informational).
 * @param[out] AlertCategory             Category of alert (e.g., navigational, technical).
 * @param[out] AlertSystem               System that generated the alert.
 * @param[out] AlertSubSystem            Subsystem that generated the alert.
 * @param[out] AlertID                   Unique identifier for the alert.
 * @param[out] SourceNetworkID           Network ID of the device that generated the alert.
 * @param[out] DataSourceInstance        Instance of the data source that generated the alert.
 * @param[out] DataSourceIndex           Index of the data source that generated the alert.
 * @param[out] AlertOccurence            Number of times the alert has occurred.
 * @param[out] AcknowledgeNetworkID      Network ID of the device that acknowledged the alert.
 * @param[out] TriggerCondition          Condition that triggered the alert.
 * @param[out] ThresholdStatus           Status of the alert threshold.
 * @param[out] AlertPriority             Priority of the alert.
 * @param[out] AlertState                State of the alert.
 * @param[out] TemporarySilenceStatus    Temporary silence status of the alert.
 * @param[out] AcknowledgeStatus         Acknowledge status of the alert.
 * @param[out] EscalationStatus          Escalation status of the alert.
 * @param[out] TemporarySilenceSupport   Temporary silence support of the alert.
 * @param[out] AcknowledgeSupport        Acknowledge support of the alert.
 * @param[out] EscalationSupport         Escalation support of the alert.
 *
 * @retval true  The message was successfully parsed.
 * @retval false The message could not be parsed.
 */
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

/************************************************************************//**
 * @brief Setting up Message "Alert Response Notification" - PGN 126984
 *
 * Creates an NMEA2000 Alert Response Notification message (PGN 126984).
 * This function fills a tN2kMsg object with the data required to acknowledge or escalate an alert condition.
 * See parameter details on \ref SetN2kPGN126984.
 *
 * @param[out] N2kMsg                    N2kMsg object to be filled with the NMEA2000 message.
 * @param[in]  AlertType                 Type of alert (e.g., warning, critical, informational).
 * @param[in]  AlertCategory             Category of alert (e.g., navigational, technical).
 * @param[in]  AlertSystem               System that generated the alert.
 * @param[in]  AlertSubSystem            Subsystem that generated the alert.
 * @param[in]  AlertID                   Unique identifier for the alert.
 * @param[in]  SourceNetworkID           Network ID of the device that generated the alert.
 * @param[in]  DataSourceInstance        Instance of the data source that generated the alert.
 * @param[in]  DataSourceIndex           Index of the data source that generated the alert.
 * @param[in]  AlertOccurence            Number of times the alert has occurred.
 * @param[in]  AcknowledgeNetworkID      Network ID of the device that acknowledged the alert.
 * @param[in]  ResponseCommand           Command to acknowledge or escalate the alert.
 *
 * @note The default transmission interval is not known.
 */
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

/************************************************************************//**
 * @brief Setting up Message "Alert Response Notification" - PGN 126984
 *
 * Alias of PGN 126984. This alias was introduced to improve the readability
 * of the source code. See parameter details on \ref SetN2kPGN126984.
 */
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

/************************************************************************//**
 * @brief Parsing Message "Alert Response Notification" - PGN 126984
 *
 * Parses an NMEA2000 Alert Response Notification message (PGN 126984) and extracts all relevant fields.
 * See parameter details on \ref ParseN2kPGN126984.
 *
 * @param[in]  N2kMsg                    N2kMsg object containing the NMEA2000 message to be parsed.
 * @param[out] AlertType                 Type of alert (e.g., warning, critical, informational).
 * @param[out] AlertCategory             Category of alert (e.g., navigational, technical).
 * @param[out] AlertSystem               System that generated the alert.
 * @param[out] AlertSubSystem            Subsystem that generated the alert.
 * @param[out] AlertID                   Unique identifier for the alert.
 * @param[out] SourceNetworkID           Network ID of the device that generated the alert.
 * @param[out] DataSourceInstance        Instance of the data source that generated the alert.
 * @param[out] DataSourceIndex           Index of the data source that generated the alert.
 * @param[out] AlertOccurence            Number of times the alert has occurred.
 * @param[out] AcknowledgeNetworkID      Network ID of the device that acknowledged the alert.
 * @param[out] ResponseCommand           Command to acknowledge or escalate the alert.
 *
 * @retval true  The message was successfully parsed.
 * @retval false The message could not be parsed.
 */
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

/************************************************************************//**
 * @brief Parsing the content of a "Alert Response Notification" Message - PGN 126984
 *
 * Alias of PGN 126984. This alias was introduced to improve the readability
 * of the source code. See parameter details on \ref ParseN2kPGN126984.
 */
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

/************************************************************************//**
 * @brief Setting up Message "Alert Text Notification" - PGN 126985
 * @ingroup group_msgSetUp
 *
 * Creates an NMEA2000 Alert Text Notification message (PGN 126985).
 * This function fills a tN2kMsg object with the data required to provide text information about an alert condition.
 * See parameter details on \ref SetN2kPGN126985.
 *
 * @param[out] N2kMsg                        N2kMsg object to be filled with the NMEA2000 message.
 * @param[in]  AlertType                     Type of alert (e.g., warning, critical, informational).
 * @param[in]  AlertCategory                 Category of alert (e.g., navigational, technical).
 * @param[in]  AlertSystem                   System that generated the alert.
 * @param[in]  AlertSubSystem                Subsystem that generated the alert.
 * @param[in]  AlertID                       Unique identifier for the alert.
 * @param[in]  SourceNetworkID               Network ID of the device that generated the alert.
 * @param[in]  DataSourceInstance            Instance of the data source that generated the alert.
 * @param[in]  DataSourceIndex               Index of the data source that generated the alert.
 * @param[in]  AlertOccurence                Number of times the alert has occurred.
 * @param[in]  AlertLanguage                 Language of the alert text.
 * @param[in]  AlertTextDescription          Description of the alert.
 * @param[in]  AlertLocationTextDescription  Description of the alert location.
 *
 * @note The default transmission interval is not known.
 */
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

/************************************************************************//**
 * @brief Setting up Message "Alert Text Notification" - PGN 126985
 *
 * Alias of PGN 126985. This alias was introduced to improve the readability
 * of the source code. See parameter details on \ref SetN2kPGN126985.
 */
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

/************************************************************************//**
 * @brief Parsing the content of an "Alert Text Notification" Message - PGN 126985
 *
 * Parses an NMEA2000 Alert Text Notification message (PGN 126985) and extracts all relevant fields.
 * See parameter details on \ref ParseN2kPGN126985.
 *
 * @param[in]  N2kMsg                        N2kMsg object containing the NMEA2000 message to be parsed.
 * @param[out] AlertType                     Type of alert (e.g., warning, critical, informational).
 * @param[out] AlertCategory                 Category of alert (e.g., navigational, technical).
 * @param[out] AlertSystem                   System that generated the alert.
 * @param[out] AlertSubSystem                Subsystem that generated the alert.
 * @param[out] AlertID                       Unique identifier for the alert.
 * @param[out] SourceNetworkID               Network ID of the device that generated the alert.
 * @param[out] DataSourceInstance            Instance of the data source that generated the alert.
 * @param[out] DataSourceIndex               Index of the data source that generated the alert.
 * @param[out] AlertOccurence                Number of times the alert has occurred.
 * @param[out] AlertLanguage                 Language of the alert text.
 * @param[out] AlertTextDescription          Description of the alert.
 * @param[in]  AlertTextDescriptionSize      Size of the buffer for the alert text description.
 * @param[out] AlertLocationTextDescription  Description of the alert location.
 * @param[in]  AlertLocationTextDescriptionSize Size of the buffer for the alert location text description.
 *
 * @retval true  The message was successfully parsed.
 * @retval false The message could not be parsed.
 */
extern bool ParseN2kPGN126985(
    const tN2kMsg& N2kMsg,
    tN2kAlertType& AlertType,
    tN2kAlertCategory& AlertCategory,
    unsigned char& AlertSystem,
    unsigned char& AlertSubSystem,
    unsigned int& AlertID,
    uint64_t& SourceNetworkID,
    unsigned char& DataSourceInstance,
    unsigned char& DataSourceIndex,
    unsigned char& AlertOccurence,
    tN2kAlertLanguage& AlertLanguage,
    char* AlertTextDescription, size_t AlertTextDescriptionSize,
    char* AlertLocationTextDescription, size_t AlertLocationTextDescriptionSize
);

#endif

