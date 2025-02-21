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
 * ProcessMessageSGD.cpp
 *
 *  Created on: Aug 24, 2015
 *      Author: dupes
 */

#include "ProcessMessageSGD.h"
#include "../util/Checksum.h"
#include "../message/ConvertEnums.h"
#include "../message/CEA2045MessageIntermediate.h"
#include "../message/CEA2045MessageBasic.h"

namespace cea2045 {

ProcessMessageSGD::ProcessMessageSGD() : m_currentState(0)  // Initialize to Idle Normal
{
}

ProcessMessageSGD::~ProcessMessageSGD()
{
}

void ProcessMessageSGD::processLinkLayerAckNak(ILinkLayerCommSend *linkLayer, 
                                              cea2045MessageHeader *message,
                                              MessageCode messageCode)
{
    std::cout << "ProcessMessageSGD::processLinkLayerAckNak entered" << std::endl;
}

void ProcessMessageSGD::processMessageTypeSupported(ILinkLayerCommSend *linkLayer, 
                                                  cea2045MessageHeader *message)
{
    std::cout << "ProcessMessageSGD::processMessageTypeSupported entered" << std::endl;
}


void ProcessMessageSGD::processBasicMessage(ILinkLayerCommSend *linkLayer, 
                                          cea2045Basic *basic)
{
    std::cout << "ProcessMessageSGD::processBasicMessage entered" << std::endl;
}

void ProcessMessageSGD::processIntermediateMessage(ILinkLayerCommSend *linkLayer, cea2045MessageHeader *message)
{
    std::cout << "ProcessMessageSGD::processIntermediateMessage entered" << std::endl;
    cea2045Intermediate *intermediate = (cea2045Intermediate *)message;
    
    std::cout << "Message validation:" << std::endl
              << "msgType1: 0x" << std::hex << (int)message->msgType1 
              << " (expected: 0x" << INTERMEDIATE_MSG_TYP1 << ")" << std::endl
              << "msgType2: 0x" << (int)message->msgType2 
              << " (expected: 0x" << INTERMEDIATE_MSG_TYP2 << ")" << std::endl
              << "opCode1: 0x" << (int)intermediate->opCode1 
              << " (Advanced Load Up: 0x0C)" << std::endl
              << "opCode2: 0x" << (int)intermediate->opCode2 << std::dec << std::endl;

    if (message->msgType1 == INTERMEDIATE_MSG_TYP1 &&
        message->msgType2 == INTERMEDIATE_MSG_TYP2)
    {
        if (intermediate->opCode1 == 0x0C) {  // Advanced Load Up
            std::cout << "Advanced Load Up message received" << std::endl;
            std::cout << "Current state before change: " << (int)m_currentState << std::endl;
           
            // Send immediate ACK
            linkLayer->sendLinkLayerAck();
            std::cout << "Link Layer ACK sent" << std::endl;

            // Send response
            cea2045IntermediateResponse response;
            response.msgType1 = INTERMEDIATE_MSG_TYP1;
            response.msgType2 = INTERMEDIATE_MSG_TYP2;
            response.length = htobe16(3);  // opCode1, opCode2, responseCode
            response.opCode1 = 0x0C;
            response.opCode2 = 0x80;
            response.responseCode = 0x00;
            response.setChecksum();
            linkLayer->sendResponse((unsigned char*)&response, sizeof(response));
            std::cout << "Intermediate Response sent" << std::endl;
           
            // Change state
            m_currentState = 3;  // Running Heightened
            std::cout << "State changed to: " << (int)m_currentState << std::endl;

            // Send state change notification
            cea2045Basic stateResponse;
            stateResponse.msgType1 = BASIC_MSG_TYP1;
            stateResponse.msgType2 = BASIC_MSG_TYP2;
            stateResponse.length = htobe16(2);
            stateResponse.opCode1 = OPER_STATE_RESP;
            stateResponse.opCode2 = m_currentState;
            stateResponse.setChecksum();
            
            // Here's the fix - use stateResponse instead of response
            linkLayer->sendResponse((unsigned char*)&stateResponse, sizeof(stateResponse));
            std::cout << "State change notification sent" << std::endl;
        }
    }
}


void ProcessMessageSGD::processDataLinkMessage(ILinkLayerCommSend *linkLayer, 
                                             cea2045MessageHeader *message)
{
    std::cout << "ProcessMessageSGD::processDataLinkMessage entered" << std::endl;
}

void ProcessMessageSGD::processInvalidMessage(ILinkLayerCommSend *linkLayer, 
                                            cea2045MessageHeader *message)
{
    std::cout << "ProcessMessageSGD::processInvalidMessage entered" << std::endl;
    std::cout << "Invalid message details:" << std::hex
              << " msgType1: 0x" << (int)message->msgType1
              << " msgType2: 0x" << (int)message->msgType2
              << " length: 0x" << message->getLength() << std::dec << std::endl;
}

void ProcessMessageSGD::processIncompleteMessage(ILinkLayerCommSend *linkLayer,
                                               const unsigned char *buffer,
                                               unsigned int numBytes)
{
    std::cout << "ProcessMessageSGD::processIncompleteMessage entered" << std::endl;
}

} /* namespace cea2045 */