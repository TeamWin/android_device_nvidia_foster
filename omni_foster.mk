# Inherit device configuration for foster.
$(call inherit-product, device/nvidia/foster/full_foster.mk)

# Inherit some common Omni stuff.
$(call inherit-product, vendor/omni/config/common_tablet.mk)

PRODUCT_NAME := omni_foster
PRODUCT_DEVICE := foster
