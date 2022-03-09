//
// Created by Alfaizkhan Pathan on 24/02/22.
//

#ifndef MXRIST_MXINTERFACE_H
#define MXRIST_MXINTERFACE_H

#include "RISTNet.h"
#include <jni.h>

#define  __stdcall

#ifdef __cplusplus
extern "C"
{
#endif

// CallBacks
// Get Data from sender
typedef int (__stdcall *DataFromSenderCallback)(uint16_t connectionID, unsigned char* data, size_t dataSize);
DataFromSenderCallback dataFromSenderCallback;


#ifdef __cplusplus
}
#endif


#endif //MXRIST_MXINTERFACE_H
