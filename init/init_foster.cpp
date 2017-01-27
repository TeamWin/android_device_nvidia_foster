/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void vendor_load_properties()
{
    std::string platform = "";
    std::string model = "";
    char int_path[14] = { '\0' };
    char dev_path[49] = { '\0' };
    char ln_path[18] = { '\0' };
    char devs[][7] = { "APP", "CAC", "LNX", "MSC", "UDA", "USP", "MDA", "SOS", "BMP", "vendor", "" };
    int i = 0;

    platform = property_get("ro.board.platform");
    if (strncmp(platform.c_str(), ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    model = property_get("ro.hardware");
    if (!model.compare("foster_e_hdd")) { // check cpuinfo hardware identifier
        /* SATA Model */
        property_set("ro.build.fingerprint", "NVIDIA/foster_e_hdd/foster:7.0/NRD90M/1915764_910.7870:user/release-keys");
        property_set("ro.build.description", "foster_e_hdd-user 7.0 NRD90M 1915764_910.7870 release-keys");
        property_set("ro.product.name", "foster_e_hdd");
        property_set("ro.product.device", "foster");
        symlink("/etc/twrp.fstab.sata", "/etc/twrp.fstab");
        strcpy(int_path, "tegra-sata.0");
    } else if (!model.compare("darcy")) {
        /* New EMMC Model */
        property_set("ro.build.fingerprint", "NVIDIA/darcy/darcy:7.0/NRD90M/1915764_910.7870:user/release-keys");
        property_set("ro.build.description", "darcy-user 7.0 NRD90M 1915764_910.7870 release-keys");
        property_set("ro.product.name", "darcy");
        property_set("ro.product.device", "darcy");
        symlink("/etc/twrp.fstab.emmc", "/etc/twrp.fstab");
        strcpy(int_path, "sdhci-tegra.3");
    } else if (!model.compare("jetson_cv")) {
        /* Jetson TX1 */
        property_set("ro.build.fingerprint", "NVIDIA/jetson_cv/jetson_cv:7.0/NRD90M/1915764_910.7870:user/release-keys");
        property_set("ro.build.description", "jetson_cv-user 7.0 NRD90M 1915764_910.7870 release-keys");
        property_set("ro.product.name", "jetson_cv");
        property_set("ro.product.device", "foster");
        symlink("/etc/twrp.fstab.emmc", "/etc/twrp.fstab");
        strcpy(int_path, "sdhci-tegra.3");
    } else {
        /* Old EMMC Model and catch-all for unknown models */
        property_set("ro.build.fingerprint", "NVIDIA/foster_e/foster:7.0/NRD90M/1915764_910.7870:user/release-keys");
        property_set("ro.build.description", "foster_e-user 7.0 NRD90M 1915764_910.7870 release-keys");
        property_set("ro.product.name", "foster_e");
        property_set("ro.product.device", "foster");
        symlink("/etc/twrp.fstab.emmc", "/etc/twrp.fstab");
        strcpy(int_path, "sdhci-tegra.3");
    }

    // Symlink paths for unified ROM installs.
    for (i = 0; devs[i][0]; i++) {
        strcpy(dev_path, "/dev/block/platform/");
        strcat(dev_path, int_path);
        strcat(dev_path, "/by-name/");
        strcat(dev_path, devs[i]);
        strcpy(ln_path, "/dev/block/");
        strcat(ln_path, devs[i]);
        symlink(dev_path, ln_path);
    }

    property_set("ro.build.product", "foster");
    property_set("ro.product.model", "SHIELD Android TV");
    ERROR("Setting build properties for %s model\n", model.c_str());
}
