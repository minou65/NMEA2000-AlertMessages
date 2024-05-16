/* N2kAlertMessages.cpp
*
* Copyright(c) 2024 Andreas Zogg
*
*Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files(the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and /or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions :
*The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* /

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

#include "N2kAlertMessages.h"

//*****************************************************************************
// This PGN is used to report the status of an aler
void SetN2kPGN126983(
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
	tN2kAlertYesNo TemporarySilenceStatus,
	tN2kAlertYesNo AcknowledgeStatus,
	tN2kAlertYesNo EscalationStatus,
	tN2kAlertYesNo TemporarySilenceSupport,
	tN2kAlertYesNo AcknowledgeSupport,
	tN2kAlertYesNo EscalationSupport
) {
	unsigned char v;

	N2kMsg.SetPGN(126983L);
	N2kMsg.Priority = 2;
	v = (AlertCategory << 4) | (AlertType);
	N2kMsg.AddByte(v);
	N2kMsg.AddByte(AlertSystem);
	N2kMsg.AddByte(AlertSubSystem);
	N2kMsg.Add2ByteUInt(AlertID);
	N2kMsg.AddUInt64(SourceNetworkID);
	N2kMsg.AddByte(DataSourceInstance);
	N2kMsg.AddByte(DataSourceIndex);
	N2kMsg.AddByte(AlertOccurence);

	v = (0x03 << 6) | (EscalationSupport << 5) | (AcknowledgeSupport << 4) | (TemporarySilenceSupport << 3) | (EscalationStatus << 2) | (AcknowledgeStatus << 1) | TemporarySilenceStatus;
	N2kMsg.AddByte(v);
	N2kMsg.AddUInt64(AcknowledgeNetworkID);

	v = (ThresholdStatus << 4) | (TriggerCondition);
	N2kMsg.AddByte(v);
	N2kMsg.AddByte(AlertPriority);
	N2kMsg.AddByte(AlertState);
};

bool ParseN2kPGN126983(
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
) {
	if (N2kMsg.PGN != 126983L) return false;
	int Index = 0;
	unsigned char v;
	v = N2kMsg.GetByte(Index);
	AlertType = tN2kAlertType(v & 0xf);
	AlertCategory = tN2kAlertCategory((v >> 4) & 0xf);
	AlertSystem = N2kMsg.GetByte(Index);
	AlertSubSystem = N2kMsg.GetByte(Index);
	AlertID = N2kMsg.Get2ByteInt(Index);
	SourceNetworkID = N2kMsg.GetUInt64(Index);
	DataSourceInstance = N2kMsg.GetByte(Index);
	DataSourceIndex = N2kMsg.GetByte(Index);
	AlertOccurence = N2kMsg.GetByte(Index);
	v = N2kMsg.GetByte(Index);
	TemporarySilenceStatus = tN2kAlertYesNo(v & 0x01);
	AcknowledgeStatus = tN2kAlertYesNo((v >> 1) & 0x01);
	EscalationStatus = tN2kAlertYesNo((v >> 2) & 0x01);
	TemporarySilenceSupport = tN2kAlertYesNo((v >> 3) & 0x01);
	AcknowledgeSupport = tN2kAlertYesNo((v >> 4) & 0x01);
	EscalationSupport = tN2kAlertYesNo((v >> 5) & 0x01);
	AcknowledgeNetworkID = N2kMsg.GetUInt64(Index);
	v = N2kMsg.GetByte(Index);
	TriggerCondition = tN2kAlertTriggerCondition(v & 0xf);
	ThresholdStatus = tN2kAlertThresholdStatus((v >> 4) & 0xf);
	AlertPriority = N2kMsg.GetByte(Index);
	AlertState = tN2kAlertState(N2kMsg.GetByte(Index));
	return true;
}

//*****************************************************************************
// Alert Response Notification
void SetN2kPGN126984(
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
	unsigned char v;
	N2kMsg.SetPGN(126984L);
	N2kMsg.Priority = 2;

	v = (AlertCategory << 4) | (AlertType);
	N2kMsg.AddByte(v);
	N2kMsg.AddByte(AlertSystem);
	N2kMsg.AddByte(AlertSubSystem);
	N2kMsg.Add2ByteUInt(AlertID);
	N2kMsg.AddUInt64(SourceNetworkID);
	N2kMsg.AddByte(DataSourceInstance);
	N2kMsg.AddByte(DataSourceIndex);
	N2kMsg.AddByte(AlertOccurence);
	N2kMsg.AddUInt64(AcknowledgeNetworkID);

	v = 0xFC | ResponseCommand;
	N2kMsg.AddByte(v);
}

bool ParseN2kPGN126984(
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
	if (N2kMsg.PGN != 126984L) return false;
	int Index = 0;
	unsigned char v;
	v = N2kMsg.GetByte(Index);
	AlertType = tN2kAlertType(v & 0xf);
	AlertCategory = tN2kAlertCategory((v >> 4) & 0xf);
	AlertSystem = N2kMsg.GetByte(Index);
	AlertSubSystem = N2kMsg.GetByte(Index);
	AlertID = N2kMsg.Get2ByteInt(Index);
	SourceNetworkID = N2kMsg.GetUInt64(Index);
	DataSourceInstance = N2kMsg.GetByte(Index);
	DataSourceIndex = N2kMsg.GetByte(Index);
	AlertOccurence = N2kMsg.GetByte(Index);
	AcknowledgeNetworkID = N2kMsg.GetUInt64(Index);
	v = N2kMsg.GetByte(Index);
	ResponseCommand = tN2kAlertResponseCommand(v & 0x03);
	return true;
}

//*****************************************************************************
// Alert Text Notification
void SetN2kPGN126985(
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
	unsigned char v;

	N2kMsg.SetPGN(126985L);
	N2kMsg.Priority = 2;

	v = (AlertCategory << 4) | (AlertType);
	N2kMsg.AddByte(v);
	N2kMsg.AddByte(AlertSystem);
	N2kMsg.AddByte(AlertSubSystem);
	N2kMsg.Add2ByteUInt(AlertID);
	N2kMsg.AddUInt64(SourceNetworkID);
	N2kMsg.AddByte(DataSourceInstance);
	N2kMsg.AddByte(DataSourceIndex);
	N2kMsg.AddByte(AlertOccurence);
	N2kMsg.AddByte(AlertLanguage);
	N2kMsg.AddVarStr(AlertTextDescription);
	N2kMsg.AddVarStr(AlertLocationTextDescription);
};

bool ParseN2kPGN126985(
	const tN2kMsg  &N2kMsg,
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
) {
	if (N2kMsg.PGN != 126985L) return false;
	int Index = 0;
	unsigned char v;
	v = N2kMsg.GetByte(Index);
	AlertType = tN2kAlertType(v & 0xf);
	AlertCategory = tN2kAlertCategory((v >> 4) & 0xf);
	AlertSystem = N2kMsg.GetByte(Index);
	AlertSubSystem = N2kMsg.GetByte(Index);
	AlertID = N2kMsg.Get2ByteInt(Index);
	SourceNetworkID = N2kMsg.GetUInt64(Index);
	DataSourceInstance = N2kMsg.GetByte(Index);
	DataSourceIndex = N2kMsg.GetByte(Index);
	AlertOccurence = N2kMsg.GetByte(Index);
	AlertLanguage = tN2kAlertLanguage(N2kMsg.GetByte(Index));
	size_t AlertTextDescriptionSize = sizeof(AlertTextDescription);
	N2kMsg.GetVarStr(AlertTextDescriptionSize, (char*)AlertTextDescription, Index);
	size_t AlertLocationTextDescriptionSize = sizeof(AlertLocationTextDescription);
	N2kMsg.GetVarStr(AlertLocationTextDescriptionSize, (char*)AlertLocationTextDescription, Index);
	return true;
};


