//
// Created by Alfaizkhan Pathan on 24/02/22.
// Copyright (c) 2022 Matrix ComSec Pvt. Ltd. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <thread>
#include "RISTNet.h"
#include "RISTNetInternal.h"
#include "MxInterface.h"
#include <android/log.h>
#include "inttypes.h"

#define APPNAME "RIST"

class RISTClass {
public:
    RISTClass() {
        testVar = 10;
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "RIST class is created");

    };

    virtual ~RISTClass() {
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "RIST class is destroyed now.");

    };

    int testVar = 0;
};

//Return a connection object. (Return nullptr if you don't want to connect to that client)
std::shared_ptr<RISTNetReceiver::NetworkConnection> validateConnection(const std::string &ipAddress, uint16_t port) {

    __android_log_print(ANDROID_LOG_INFO, APPNAME, "Connecting IP: %s:%d", ipAddress.c_str(), port);
    //Do we want to allow this connection?
    //Do we have enough resources to accept this connection...

    // if not then -> return nullptr;
    // else return a ptr to a NetworkConnection.
    // this NetworkConnection may contain a pointer to any C++ object you provide.
    // That object ptr will be passed to you when the client communicates with you.
    // If the network connection is dropped the destructor in your class is called as long
    // as you do not also hold a reference to that pointer since it's shared.

    auto netConn = std::make_shared<RISTNetReceiver::NetworkConnection>(); // Create the network connection
    netConn->mObject = std::make_shared<RISTClass>(); // Attach your object.
    return netConn;
}

int dataFromSender(const uint8_t *buf, size_t len, std::shared_ptr<RISTNetReceiver::NetworkConnection> &connection,
               rist_peer *pPeer, uint16_t connectionID) {
    if (connection->mObject.has_value()) {

        dataFromSenderCallback(connectionID, (unsigned char *) (buf), len);
        __android_log_print(ANDROID_LOG_INFO, APPNAME,
                            "Get Data From Sender with Connection ID %d: %s",
                            unsigned(connectionID), buf);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "Did not receive the correct data");
    }

    return 0; //Keep connection
}

void oobDataFromReceiver(const uint8_t *buf, size_t len, std::shared_ptr<RISTNetSender::NetworkConnection> &connection,
                         rist_peer *pPeer) {

    if (connection->mObject.has_value()) {
        //You are the server so the connection has a Context
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "Got %d bytes of oob data from the receiver: %s", unsigned(len), buf);
    } else {
        //You are not the server so the connection does not have a context (meaning you connected to the server and the server sends OOB to you).
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "Got %d bytes of oob data from the receiver: %s", unsigned(len), buf);
    }
}

void clientDisconnect(const std::shared_ptr<RISTNetReceiver::NetworkConnection>& connection, const rist_peer& peer) {
    __android_log_print(ANDROID_LOG_INFO, APPNAME, "Client disconnected from receiver");

    if (connection) {
        auto v = std::any_cast<std::shared_ptr<RISTClass> &>(connection->mObject);
        if (v) {
            __android_log_print(ANDROID_LOG_INFO, APPNAME, "Connection object found");
        } else {
            __android_log_print(ANDROID_LOG_ERROR, APPNAME,", ERROR: no object found!");
        }
    } else {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, ", ERROR: no connection object." );
    }
}

