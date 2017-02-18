#
# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PRODUCT_CHARACTERISTICS := tv
TARGET_TEGRA_VERSION := t210

PRODUCT_AAPT_CONFIG += xlarge large
TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

$(call inherit-product, frameworks/native/build/tablet-10in-xhdpi-2048-dalvik-heap.mk)

$(call inherit-product-if-exists, vendor/nvidia/foster/foster-vendor.mk)

PRODUCT_SYSTEM_PROPERTY_BLACKLIST := ro.product.name

# Overlay
DEVICE_PACKAGE_OVERLAYS += \
    device/nvidia/foster/overlay

# Ramdisk
PRODUCT_PACKAGES += \
    fstab.foster \
    fstab.foster_e \
    fstab.foster_e_hdd \
    init.foster_e.rc \
    init.foster_e_hdd.rc \
    init.recovery.foster.rc \
    init.foster_e_common.rc \
    init.loki_foster_e_common.rc \
    power.foster_e.rc \
    power.foster_e_hdd.rc \
    ueventd.foster_e.rc \
    ueventd.foster_e_hdd.rc

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.hdmi.cec.xml:system/etc/permissions/android.hardware.hdmi.cec.xml \
    frameworks/native/data/etc/android.software.device_admin.xml:system/etc/permissions/android.software.device_admin.xml \
    frameworks/native/data/etc/android.software.managed_users.xml:system/etc/permissions/android.software.managed_users.xml

# NVIDIA
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/permissions/tv_core_hardware.xml:system/etc/permissions/tv_core_hardware.xml \
    $(LOCAL_PATH)/permissions/android.hardware.type.television.xml:system/etc/permissions/android.hardware.type.television.xml \
    $(LOCAL_PATH)/permissions/com.google.android.tv.installed.xml:system/etc/permissions/com.google.android.tv.installed.xml \
    $(LOCAL_PATH)/permissions/com.nvidia.feature.xml:system/etc/permissions/com.nvidia.feature.xml \
    $(LOCAL_PATH)/permissions/com.nvidia.feature.opengl4.xml:system/etc/permissions/com.nvidia.feature.opengl4.xml \
    $(LOCAL_PATH)/permissions/com.nvidia.nvsi.xml:system/etc/permissions/com.nvidia.nvsi.xml


# Media config
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml \
    $(LOCAL_PATH)/media/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/media/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/media/media_codecs_performance.xml:system/etc/media_codecs_performance.xml \
    $(LOCAL_PATH)/media/media_profiles.xml:system/etc/media_profiles.xml

# Audio
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/nvaudio_conf.xml:system/etc/nvaudio_conf.xml \
    $(LOCAL_PATH)/audio/nvaudio_fx.xml:system/etc/nvaudio_fx.xml

# Bluetooth
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/bluetooth/bt_vendor.conf:system/etc/bluetooth/bt_vendor.conf

# Wireless Controller
#$(call inherit-product-if-exists, vendor/nvidia/shield_common/blake64-blobs.mk)

# Leanback Keyboard
PRODUCT_PACKAGES += LeanbackIme

# TvSettings for android tv
#PRODUCT_PACKAGES += TvSettings

# Needed in recovery
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/twrp/twrp.fstab.emmc:recovery/root/etc/twrp.fstab.emmc \
    $(LOCAL_PATH)/twrp/twrp.fstab.sata:recovery/root/etc/twrp.fstab.sata \
    $(LOCAL_PATH)/twrp/tegra21x_xusb_firmware:recovery/root/etc/firmware/tegra21x_xusb_firmware

$(call inherit-product, device/nvidia/shield-common/shield.mk)
