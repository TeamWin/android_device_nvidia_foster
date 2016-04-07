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
    unlink("/etc");
    umount("/sysint");
    unlink("/sysint");
}

int mrom_hook_after_android_mounts(__attribute__((unused))const char *busybox_path, __attribute__((unused))const char *base_path, __attribute__((unused))int type) {
    mrom_hook_before_fb_close();
    return 0;
}
#endif

#if MR_DEVICE_HOOKS >= 3
static void load_firmware(char* system_path) {
int fd_loading = -1, c = 0;
    FILE *fd_firm = NULL, *fd_data = NULL;

    // Mount internal /system to /sysinit. Mounting to /system causes problems
    mkdir("/sysint", 0755);
    wait_for_file(system_path, 10);
    mount(system_path, "/sysint", "ext4", MS_RDONLY, NULL);
    symlink("/sysint/etc", "/etc");
    ERROR("Mounted /sysint for firmware load.\n");
}

void tramp_hook_before_device_init() {
    FILE *cpuinfo = NULL, *fstab_in = NULL, *fstab_out = NULL;
    char fstab_path[20] = "", system_path[50] = "";
    char *line = NULL;
    int bytes_read = 0, ch = 0;
    size_t len = 0;

    mkdir("/sysint", 0755);

    cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo)
    {
        while ((bytes_read = getline(&line, &len, cpuinfo)) != -1)
        {
            if (strstr(line, "foster_e_hdd"))
            {
                strcpy(fstab_path, "/fstab.foster_e_hdd");
                strcpy(system_path, "/dev/block/platform/tegra-sata.0/by-name/APP");
                break;
            }
            else if (strstr(line, "foster_e"))
            {
                strcpy(fstab_path, "/fstab.foster_e");
                strcpy(system_path, "/dev/block/platform/sdhci-tegra.3/by-name/APP");
                break;
            }
        }
        fclose(cpuinfo);
        if (line)
            free(line);

    }

    if (fstab_path[0] != '\0') {
        fstab_in = fopen(fstab_path, "r");
        if (fstab_in) {
            fstab_out = fopen("/fstab.foster", "w");
            while ((ch = fgetc(fstab_in)) != EOF)
                putc(ch, fstab_out);

            fclose(fstab_in);
            fclose(fstab_out);
        }
    }

    // Load firmware thread
    signal(SIGCHLD, SIG_IGN);
    if (system_path[0] != '\0' && fork() == 0) {
        load_firmware(system_path);
        _exit(0);
    }
}
#endif

#if MR_DEVICE_HOOKS >= 4
int mrom_hook_allow_incomplete_fstab(void)
{
    return 0;
}
#endif

#if MR_DEVICE_HOOKS >= 5

void mrom_hook_fixup_bootimg_cmdline(char *bootimg_cmdline, size_t bootimg_cmdline_cap)
{
}

int mrom_hook_has_kexec(void)
{
    static const char *checkfile1 = "/sys/firmware/fdt";
    static const char *checkfile2 = "/proc/device-tree";

    // check for fdt blob
    if(access(checkfile1, R_OK) >= 0)
        return 1;

    // check for /proc/device-tree
    if(access(checkfile2, R_OK) >= 0) {
        ERROR("%s was not found, but %s was. Assuming kexec hardboot is applied.\n", checkfile1, checkfile2);
        return 1;
    }

    ERROR("Neither %s or %s were found!\n", checkfile1, checkfile2);
    return 0;
}
#endif
