
#include <common.h>
#include <command.h>
#include <net.h>
#include <env.h>

#define DHCP_RETRY 3

/* 网络初始化 */
static int net_init(void)
{
    if (!eth_get_dev()) {
        printf("Network not ready\n");
        return CMD_RET_FAILURE;
    }
    return CMD_RET_SUCCESS;
}

/* 静态IP设置 */
static int set_ip(const char *ip, const char *mask)
{
    env_set("ipaddr", ip);
    env_set("netmask", mask);
    eth_halt();
    return eth_init();
}

/* DHCP自动配置 */
static int dhcp_config(void)
{
    for (int i = 0; i < DHCP_RETRY; i++) {
        if (net_loop(DHCP) == 0) {
            printf("DHCP OK: %s\n", env_get("ipaddr"));
            return CMD_RET_SUCCESS;
        }
    }
    return CMD_RET_FAILURE;
}

/* 命令入口 */
static int do_netcmd(struct cmd_tbl *cmdtp, int flag,
                   int argc, char *const argv[])
{
    if (net_init() != CMD_RET_SUCCESS)
        return CMD_RET_FAILURE;

    if (argc > 1 && !strcmp(argv[1], "dhcp"))
        return dhcp_config();
    
    if (argc > 2 && !strcmp(argv[1], "static"))
        return set_ip(argv[2], argv[3]);

    printf("Usage: netcmd [dhcp|static IP MASK]\n");
    return CMD_RET_USAGE;
}

U_BOOT_CMD(
    netcmd, 4, 1, do_netcmd,
    "Network config tool",
    "dhcp - Auto config\n"
    "static IP MASK - Set static IP"
);
