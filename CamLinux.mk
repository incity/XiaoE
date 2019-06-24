ifeq ($(TARGET_PRODUCT), tiger_cdr)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_LDFLAGS += \
        -L$(TOP)/frameworks/prebuilts \
        -lgnustl_shared \
        -lfreetype \
        -L$(LOCAL_PATH)/3rd-party/lib \
        -lmgncs4touch -lmgncs -lmgplus -lminigui_ths -lmgeff -lchipmunk

LOCAL_SHARED_LIBRARIES :=   \
        libhardware \
        libhardware_legacy \
        libcutils \
        libutils \
        libbinder \
        libstandby \
        libserial \
        libsqlite++ \
        libmedia \
        libtinyalsa \
        libts libpng12 libjpeg  \
        libRpc libSocket libHttpServer

#strict compile option
#LOCAL_CFLAGS += -Werror  -Wall -Wno-unused-parameter -Wno-reorder
compile_date=$(shell date "+%Y-%m-%d %H:%M:%S")
#compile_version=$(addprefix $(addsuffix $(compile_date), "), ")
LOCAL_CFLAGS += -DCOMPILE_VERSION="\"$(USER)@$(TARGET_PRODUCT) $(compile_date)\""
LOCAL_CFLAGS += -D$(TARGET_PRODUCT) -frtti -fexceptions

LOCAL_CFLAGS += -DUSE_ANDROID_UTILS_SINGLETON \

LOCAL_NDK_STL_VARIANT := gnustl_shared

SRC_TAG := src
INC_TAG := include

define all-dirs-under
$(shell cd $(LOCAL_PATH);find $(1) -maxdepth 0 -type d)
endef

INC_SUB_DIRS := $(addprefix $(LOCAL_PATH)/,$(call all-dirs-under, $(INC_TAG)/*))

SRC_FILES := $(call all-cpp-files-under, $(SRC_TAG))
LOCAL_SRC_FILES := $(SRC_FILES)
LOCAL_C_INCLUDES := $(INC_SUB_DIRS) \
        $(TOP)/frameworks/include/binder \
        $(TOP)/frameworks/include/standby \
        $(TOP)/frameworks/include/include_media/media \
        $(TOP)/prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/include \
        $(TOP)/prebuilts/ndk/current/sources/cxx-stl/gnu-libstdc++/libs/armeabi/include \
        $(TOP)/external/tinyalsa/include \
        $(TOP)/external/libSocket \
        $(TOP)/external/libRpc \
        $(TOP)/external/libHttpServer \
        $(LOCAL_PATH)/3rd-party/include \
        bionic \
        external/SQLiteCpp/include \

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := $(notdir $(LOCAL_PATH))
#LOCAL_MODULE_PATH := $(LOCAL_PATH)

include $(BUILD_EXECUTABLE)
endif
