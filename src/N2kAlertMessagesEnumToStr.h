/* N2kAlertMessagesEnumToStr.h
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
 * \file    N2kAlertMessagesEnumToStr.h
 * \brief   This File contains functions to convert enums from N2kAlertMessages.h
 *          to const char
 *
 * This is collection of functions for handling enums of NMEA2000 bus messages.
 * There are basically 2 functions in the library to convert enums
 * derived from N2kAlertMessages to const char *:
 *
 * #### const char * N2kEnumAlertTypeToStr(enumType enumVal)
 *
 *  This functions returns a const char * value thats representing the given
 *  enum Value. By detecting the enumType, the right text output is
 *  chosen.
 *
 * #### void PrintN2kEnumAlertType (T a, Stream *OutputStream, bool addLF=true)
 *
 *  This prints the corresponding text output to the given output stream.
 *
 * \note If you do not need enums in clear text, you do not need this library.
 *
 * ********************************************************************/

#ifndef _N2KALERTMESSAGESENUMTOSTR_h
#define _N2KALERTMESSAGESENUMTOSTR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "N2kAlertTypes.h"

/************************************************************************//**
 * \brief Default value if no string representation is found
 */
const char* N2kEnumTypeEmpty = "";

/************************************************************************//**
 * \brief Print function for the enum values
 *
 * This function template generation an text output to the defined stream.
 * Corresponding to the type of the enum value, the correct function (and
 * therefore output text) is chosen.
 *
 * @tparam T            Type of the enum
 * @param a             enum value
 * @param OutputStream  stream handler for the output
 * @param addLF         add a line feed (default = true)
 */
template<typename T> void PrintN2kEnumAlertType(T a, Stream* OutputStream, bool addLF = true) {
    const char* str = N2kEnumTypeToStr(a);
    if (str[0] != '\0') {
        if (addLF) { OutputStream->println(str); }
        else { OutputStream->print(str); }
    }
    else {
        OutputStream->print(F("unknown (")); OutputStream->print(a); OutputStream->println(F(")"));
    }
}
/************************************************************************//**
 * \brief Macro function for converting various N2k Enums to a const char
 *
 * This generic macro defines a way to use a specific version of
 * **N2kEnumTypeToStr(enumType enumVal)** depending on which enumType is
 * given as parameter.
 *
 * In NMEA2000 messages there are several enumerations defined and used
 * for the states of different systems. E.g tN2kBatType holds all the
 * available battery types like "flooded", "gel", "AGM". If you need
 * the "real" values of these enums written to a string
 * (e.g. for debugging), you can use these functions.
 *
 *
 * ### Usage of the function N2kEnumTypeToStr(enumType enumVal):
 *
 * ```
 * tN2kBatType batCem = N2kDCbt_Gel;
 * const char* tmp;
 * tmp = N2kEnumTypeToStr(batCem);
 *
 * Serial.print(tmp);     // Output to serial =>  Gel
 * ```
 *
 */
#define MakeN2kEnumAlertTypeToStrFunc(enumType,strs) \
const char * N2kEnumAlertTypeToStr(enumType enumVal) { \
  if ( enumVal<(sizeof(strs)/sizeof(const char *)) ) { \
    return strs[enumVal]; \
  } else { return N2kEnumTypeEmpty; }\
}

 /************************************************************************//**
  * \brief string representation of the N2k enum tN2kAlertType
  */
const char* tN2kAlertTypeStrs[] = { "emergency alarm", "alarm", "warning", "caution"};
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertType to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertType, tN2kAlertTypeStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertCategory
 */
const char* tN2kAlertCategoryStrs[] = { "navigational", "technical" };
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertCategory to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertCategory, tN2kAlertCategoryStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertTriggerCondition
 */
const char* tN2kAlertTriggerConditionStrs[] = { "manual", "auto", "test", "disabled"};
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertTriggerCondition to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertTriggerCondition, tN2kAlertTriggerConditionStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertThresholdStatus
 */
const char* tN2kAlertThresholdStatusStrs[] = { "normal", "exceeded", "extreme exceeded", "low exceeded", "acknowledged", "awaiting acknowledge"};
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertThresholdStatus to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertThresholdStatus, tN2kAlertThresholdStatusStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertState
 */
const char* tN2kAlertStateStrs[] = { "disable", "normal", "active", "silenced", "acknowledged", "awaiting acknowledge" };
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertState to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertState, tN2kAlertStateStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertLanguage
 */
const char* tN2kAlertLanguageStrs[] = { "English US", "English UK", "Arabic", "Chinese simplified", "Croatian", "Danish", "Dutch", "Finnish", 
                                        "French", "German", "Greek", "Italian", "Japanese", "Korean", "Norwegian", "Polish", "Portuguese", 
                                        "Russian", "Spanish", "Swedish"};
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertLanguage to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertLanguage, tN2kAlertLanguageStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertResponseCommand
 */
const char* tN2kAlertResponseCommandStrs[] = { "acknowledge", "temporary silence", "test command off", "test command on"};
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertResponseCommand to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertResponseCommand, tN2kAlertResponseCommandStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum tN2kAlertYesNo
 */
const char* tN2kAlertYesNoStrs[] = { "no", "yes" };
/************************************************************************//**
 * \brief Converting the N2k enum \ref tN2kAlertYesNo to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(tN2kAlertYesNo, tN2kAlertYesNoStrs);

/************************************************************************//**
 * \brief string representation of the N2k enum t2kNAlertThresholdMethod
 */
const char* t2kNAlertThresholdMethodStrs[] = { "equal", "lower then", "greater then" };
/************************************************************************//**
 * \brief Converting the N2k enum \ref t2kNAlertThresholdMethod to a const char
 */
MakeN2kEnumAlertTypeToStrFunc(t2kNAlertThresholdMethod, t2kNAlertThresholdMethodStrs);
#endif
