#include <unistd.h>
#include <log.h>
#include <trampoline/devices.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <pthread.h>
#include <fcntl.h>
#include <util.h>
#include <string.h>
//#include "property_service.h"

#if MR_DEVICE_HOOKS >= 1
void mrom_hook_before_fb_close() {
}

int mrom_hook_after_android_mounts(__attribute__((unused))const char *busybox_path, __attribute__((unused))const char *base_path, __attribute__((unused))int type) {
	return 0;
}
#endif

#if MR_DEVICE_HOOKS >= 3
void tramp_hook_before_device_init() {
    //char model[PROP_VALUE_MAX];

    //property_get("ro.hardware", model);
    //if (!strcmp(model, "foster_e")) { // check cpuinfo hardware identifier
        /* EMMC Model */
    //    symlink("/fstab.foster_e", "/fstab.foster");
    //} else {
        /* SATA Model */
        symlink("/fstab.foster_e_hdd", "/fstab.foster");
    //}
}
#endif
