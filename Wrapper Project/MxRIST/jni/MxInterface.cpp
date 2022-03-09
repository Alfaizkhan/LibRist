//
// Created by Alfaizkhan Pathan on 24/02/22.
// Copyright (c) 2022 Matrix ComSec Pvt. Ltd. All rights reserved.
//

#include "RISTNet.h"
#include "MxInterface.h"
#include "RISTNetInternal.h"
#include "Extentions.cpp"
#include <iostream>
#include <functional>
#include <string>
#include <any>

#include <android/log.h>
#define APPNAME "RIST"

#define DLL __declspec(dllexport)
#define __stdcall
#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------------
//
//
// RISTNetReceiver -- RECEIVER
//
//
//--------------------------------------------------------------------------------------------------

std::string lURL;
//Create a receiver.
RISTNetReceiver myRISTNetReceiver;
std::vector<std::string> interfaceListReceiver;

// Init Receiver
void initReceiver(const char* lIP, const char* lPort)
{
    try {

        __android_log_print(ANDROID_LOG_INFO, APPNAME, "Receiver: My receiver IP: %s:%s", lIP, lPort);

        //Register the callbacks
        //validate the connecting client
        myRISTNetReceiver.validateConnectionCallback =
                std::bind(&validateConnection, std::placeholders::_1, std::placeholders::_2);

        //receive data from the client
        myRISTNetReceiver.networkDataCallback =
                std::bind(&dataFromSender, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
                          std::placeholders::_4, std::placeholders::_5);

        // client has disconnected
        myRISTNetReceiver.clientDisconnectedCallback =
                std::bind(&clientDisconnect, std::placeholders::_1, std::placeholders::_2);

        if (RISTNetTools::buildRISTURL(lIP, lPort, lURL, true)) {
            interfaceListReceiver.push_back(lURL);
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Receiver: Build RIST URL1");
        }
        if (RISTNetTools::buildRISTURL("0.0.0.0", "9000", lURL, true)) {
            interfaceListReceiver.push_back(lURL);
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Receiver: Build RIST URL2");
        }

        //Populate the settings
        RISTNetReceiver::RISTNetReceiverSettings myReceiveConfiguration;
        myReceiveConfiguration.mLogLevel = RIST_LOG_WARN;

        //Initialize the receiver
        if (!myRISTNetReceiver.initReceiver(interfaceListReceiver, myReceiveConfiguration)) {
            __android_log_print(ANDROID_LOG_ERROR, APPNAME, "RECEIVER: Init Failed");
        } else
        {
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "RECEIVER: Init Success");
        }
    }
    catch (std::exception ex)
    {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Exception: Receiver");
    }
}

//--------------------------------------------------------------------------------------------------
//
//
// RISTNetSender -- SENDER
//
//
//--------------------------------------------------------------------------------------------------

//Create a sender
RISTNetSender myRISTNetSender;
std::vector<std::tuple<std::string, int>> interfaceListSender;

// Init Receiver
void initSender(const char* lIP, char* lPort)
{
    try {
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "Sender: My Sender IP: %s:%s", lIP, lPort);

        myRISTNetSender.networkOOBDataCallback = std::bind(&oobDataFromReceiver, std::placeholders::_1,
                                                           std::placeholders::_2, std::placeholders::_3,
                                                           std::placeholders::_4);

        //Generate a vector of RIST URL's,  ip(name), ports, RIST URL output, listen(true) or send mode (false)
        if (RISTNetTools::buildRISTURL(lIP, lPort, lURL, false)) {
            interfaceListSender.push_back(std::tuple<std::string, int>(lURL, 5));
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Sender: Build RIST URL");
        }

        //Populate the settings
        RISTNetSender::RISTNetSenderSettings mySendConfiguration;
        mySendConfiguration.mLogLevel = RIST_LOG_WARN;

        auto retVal = myRISTNetSender.initSender(interfaceListSender, mySendConfiguration);

        //Initialize the receiver
        if (!retVal) {
            __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Sender: Init Failed");
        }else
        {
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Sender: Init Success");
        }
    }
    catch (std::exception ex)
    {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Exception: Sender");
    }
}


// Send Data to the Receiver and get back via sender
void sendData(const unsigned char* pData, size_t lSize, uint16_t lConnectionID=0)
{
    try {
        std::vector<uint8_t> myData(pData, pData + lSize);

           __android_log_print(ANDROID_LOG_INFO, APPNAME, "Sending packets from our end: %s", pData);
           myRISTNetSender.sendData((uint8_t*)myData.data(), myData.size());

        myRISTNetReceiver.getActiveClients(
                [&](std::map<rist_peer *, std::shared_ptr<RISTNetReceiver::NetworkConnection>> &rClientList) {

            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Active Client Count : %lu", rClientList.size());
            //__android_log_print(ANDROID_LOG_INFO, APPNAME, "Getting active client...");
            for (auto &rPeer: rClientList) {
                myRISTNetReceiver.sendOOBData(rPeer.first, myData.data(), myData.size());
            }
        });
    }catch (std::exception ex)
    {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Exception: sendData");
    }
}

// Just use "Callback" here, instead of repeating
__stdcall void getDataFromSender(DataFromSenderCallback func) {

    try {
        dataFromSenderCallback = func;
    }
    catch (std::exception ex)
    {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Exception: sendData");
    }
}


#ifdef __cplusplus
}

#endif
