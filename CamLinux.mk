ifeq ($(TARGET_PRODUCT), tiger_cdr)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_LDFLAGS += \
        -L$(TOP)/frameworks/prebuilts \
        -lfreetype \
        -L$(LOCAL_PATH)/3rd-party/lib \
        -lmgncs4touch -lmgncs -lmgplus -lminigui_ths -lmgeff -lchipmunk

LOCAL_SHARED_LIBRARIES := libstlport  libgabi++ \
                	libcutils \
                	libutils \
                                libbinder \
                                libstandby \
		libts libpng12 libjpeg 

#strict compile option
#LOCAL_CFLAGS += -Werror  -Wall -Wno-unused-parameter -Wno-reorder
compile_date=$(shell date "+%Y-%m-%d %H:%M:%S")
#compile_version=$(addprefix $(addsuffix $(compile_date), "), ")
LOCAL_CFLAGS += -DCOMPILE_VERSION="\"$(USER)@$(TARGET_PRODUCT) $(compile_date)\""
LOCAL_CFLAGS += -D$(TARGET_PRODUCT) -frtti
LOCAL_NDK_STL_VARIANT := stlport_static

SRC_TAG := src
INC_TAG := include

define list_sub_dirs
$(shell cd $(LOCAL_PATH);find $(1) -maxdepth 0 -type d)
endef

INC_SUB_DIRS := $(addprefix $(LOCAL_PATH)/,$(call list_sub_dirs, $(INC_TAG)/*))

SRC_FILES := $(call all-cpp-files-under, $(SRC_TAG))
LOCAL_SRC_FILES := $(SRC_FILES)
LOCAL_C_INCLUDES := $(INC_SUB_DIRS) \
        $(TOP)/frameworks/include/binder \
        $(TOP)/frameworks/include/standby \
        $(LOCAL_PATH)/3rd-party/include \
        abi/cpp/include \
        bionic \
        external/stlport/stlport

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := XiaoE

include $(BUILD_EXECUTABLE)
endif
