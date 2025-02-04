// =====================================================================================
// Copyright (c) 2016, Electric Power Research Institute (EPRI)
// All rights reserved.
//
// libcea2045 ("this software") is licensed under BSD 3-Clause license.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// *  Neither the name of EPRI nor the names of its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
// OF SUCH DAMAGE.
//
// This EPRI software incorporates work covered by the following copyright and permission
// notices. You may not use these works except in compliance with their respective
// licenses, which are provided below.
//
// These works are provided by the copyright holders and contributors "as is" and any express or
// implied warranties, including, but not limited to, the implied warranties of merchantability
// and fitness for a particular purpose are disclaimed.
//
// This software relies on the following libraries and licenses:
//
// #########################################################################################
// Boost Software License, Version 1.0
// #########################################################################################
//
// * catch++ v1.2.1 (https://github.com/philsquared/Catch)
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// #########################################################################################
// MIT Licence
// #########################################################################################
//
// * easylogging++ Copyright (c) 2017 muflihun.com
//   https://github.com/easylogging/easyloggingpp
//   https://easylogging.muflihun.com
//   https://muflihun.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/*
 * ICEA2045DeviceUCM.h
 *
 *  Created on: Apr 26, 2016
 *      Author: dupes
 */

#ifndef CEA2045_CEA2045_DEVICE_ICEA2045DEVICEUCM_H_
#define CEA2045_CEA2045_DEVICE_ICEA2045DEVICEUCM_H_

#include <future>

namespace cea2045
{

class ICEA2045DeviceUCM
{
public:
	ICEA2045DeviceUCM() {};
	virtual ~ICEA2045DeviceUCM() {};

	virtual bool start() = 0;
	virtual void shutDown() = 0;

	virtual std::future<ResponseCodes> queryMaxPayload() = 0;

	virtual std::future<ResponseCodes> queryMessageTypeSupported(MessageCode messageCode, unsigned char messageType1, unsigned char messageType2) = 0;

	virtual std::future<ResponseCodes> querySuportDataLinkMessages() = 0;
	virtual std::future<ResponseCodes> querySuportIntermediateMessages() = 0;

	virtual std::future<ResponseCodes> intermediateGetDeviceInformation() = 0;
	virtual std::future<ResponseCodes> intermediateGetCommodity() = 0;
	virtual std::future<ResponseCodes> intermediateGetTemperatureOffset() = 0;
	virtual std::future<ResponseCodes> intermediateGetSetPoint() = 0;
	virtual std::future<ResponseCodes> intermediateGetPresentTemperature() = 0;

	virtual std::future<ResponseCodes> intermediateSetTemperatureOffset(unsigned char temperatureOffset, TemperatureUnits units) = 0;
	virtual std::future<ResponseCodes> intermediateSetSetpoints(unsigned short deviceType, TemperatureUnits units, unsigned short setpoint1, unsigned short setpoint2) = 0;
	virtual std::future<ResponseCodes> intermediateSetEnergyPrice(unsigned short currentPrice, unsigned short currencyCode,
			unsigned char digitsAfterDecimalPoint, unsigned int expirationDatetimeUTC,
			unsigned short nextPrice) = 0;
	virtual std::future<ResponseCodes> intermediateStartCycling(unsigned int eventID, unsigned int startTimeUTCSince2000, unsigned short durationInMinutes,
			unsigned char dutyCycle, unsigned char startRandomizationMinutes, unsigned char endRandomizationMintues,
			unsigned char criticality) = 0;
	virtual std::future<ResponseCodes> intermediateTerminateCycling(unsigned int eventID, unsigned char endRandomizationInMinutes) = 0;

	virtual std::future<ResponseCodes> basicCriticalPeakEvent(unsigned char eventDuration) = 0;
	virtual std::future<ResponseCodes> basicEndShed(unsigned char durationToNextEvent) = 0;
	virtual std::future<ResponseCodes> basicGridEmergency(unsigned char eventDuration) = 0;
	virtual std::future<ResponseCodes> basicLoadUp(unsigned char eventDuration) = 0;
	virtual std::future<ResponseCodes> basicOutsideCommConnectionStatus(OutsideCommuncatonStatusCode code) = 0;
	virtual std::future<ResponseCodes> basicPresentRelativePrice(unsigned char relativePriceIndicator) = 0;
	virtual std::future<ResponseCodes> basicNextRelativePrice(unsigned char relativePriceIndicator) = 0;
	virtual std::future<ResponseCodes> basicQueryOperationalState() = 0;
	virtual std::future<ResponseCodes> basicShed(unsigned char eventDuration) = 0;
	virtual std::future<ResponseCodes> basicPowerLevel(unsigned char powerLevel) = 0;
	
	
	virtual std::future<ResponseCodes> intermediateSetAdvancedLoadUp(
    unsigned short duration,
    unsigned short value,
    unsigned char units) = 0;
};

} /* namespace cea2045 */

#endif /* CEA2045_CEA2045_DEVICE_ICEA2045DEVICEUCM_H_ */
