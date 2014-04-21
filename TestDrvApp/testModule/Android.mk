LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	testmodule.cpp

LOCAL_SHARED_LIBRARIES := \
            liblog \
        	libcutils \
        	libutils \

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= testmodule
LOCAL_PRELINK_MODULE:=false
include $(BUILD_STATIC_LIBRARY)
#############
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= testmodule


LOCAL_SHARED_LIBRARIES := \
            liblog \
        	libcutils \
        	libutils \

LOCAL_WHOLE_STATIC_LIBRARIES := testmodule

LOCAL_PRELINK_MODULE:=false
include $(BUILD_SHARED_LIBRARY)
############
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= testmain


LOCAL_SHARED_LIBRARIES := \
            liblog \
        	libcutils \
        	libutils \

LOCAL_SRC_FILES:= \
	testmain.cpp
	
LOCAL_WHOLE_STATIC_LIBRARIES := testmodule

include $(BUILD_EXECUTABLE)	