
#include <common.h>
#include <command.h>

static int do_busybox(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    char cmd[CONFIG_SYS_CBSIZE];
    snprintf(cmd, sizeof(cmd), "%s %s", CONFIG_BUSYBOX_PATH, argv[1]);
    return run_command(cmd, 0);
}

U_BOOT_CMD(
    busybox, CONFIG_SYS_MAXARGS, 1, do_busybox,
    "BusyBox command wrapper",
    "[busybox_command] [args...]"
);
