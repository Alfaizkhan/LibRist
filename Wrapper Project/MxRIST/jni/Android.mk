#LibRIST

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := librist
LOCAL_SRC_FILES := rist/lib/librist.so
#LOCAL_SRC_FILES := rist/lib/librist-armv7.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/rist/include/librist
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := MxRIST
LOCAL_SRC_FILES := RISTNet.cpp \
				   MxInterface.cpp \

LOCAL_SHARED_LIBRARIES := librist
LOCAL_CPPFLAGS += -std=c++17
LOCAL_LDFLAGS += -ljnigraphics
LOCAL_LDLIBS := -lm -lc -lz -lstdc++ -llog
include $(BUILD_SHARED_LIBRARY)