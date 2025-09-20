
/*
 * U-Boot网络配置模块
 * 功能：提供静态IP设置和DHCP自动获取功能
 */

#include <common.h>
#include <command.h>
#include <net.h>
#include <env.h>
#include <linux/delay.h>

#define DHCP_RETRY_MAX 3
#define DHCP_TIMEOUT_MS 5000

/* 网络状态检测 */
static int check_network_status(void)
{
    struct udevice *dev;
    if (uclass_get_device(UCLASS_ETH, 0, &dev)) {
        printf("Error: Ethernet device not found\n");
        return CMD_RET_FAILURE;
    }
    return CMD_RET_SUCCESS;
}

/* 静态IP配置实现 */
static int set_static_ip(const char *ip, const char *mask, 
                        const char *gateway, const char *server)
{
    if (!ip || !mask || !gateway) {
        printf("Invalid parameters\n");
        return CMD_RET_FAILURE;
    }

    env_set("ipaddr", ip);
    env_set("netmask", mask);
    env_set("gatewayip", gateway);
    env_set("serverip", server ? server : "192.168.1.1");
    
    printf("Static IP configured:\n"
           "IP: %s\nMask: %s\nGateway: %s\nServer: %s\n",
           ip, mask, gateway, env_get("serverip"));
    
    return net_restart();
}

/* DHCP配置实现 */
static int dhcp_autoconfig(void)
{
    int ret;
    char *ipaddr;
    
    env_set_ulong("netretry", DHCP_RETRY_MAX);
    env_set_ulong("timeout", DHCP_TIMEOUT_MS);

    for (int i = 0; i < DHCP_RETRY_MAX; i++) {
        printf("DHCP attempt %d/%d...\n", i+1, DHCP_RETRY_MAX);
        ret = net_loop(DHCP);
        
        if (ret == 0) {
            ipaddr = env_get("ipaddr");
            printf("DHCP success: IP=%s\n", ipaddr);
            return CMD_RET_SUCCESS;
        }
        mdelay(100);
    }
    return CMD_RET_FAILURE;
}

/* 命令处理函数 */
static int do_net_config(struct cmd_tbl *cmdtp, int flag,
                        int argc, char *const argv[])
{
    if (argc < 2) {
        printf("Usage:\n"
               "  netconfig static <ip> <mask> <gateway> [server]\n"
               "  netconfig dhcp\n");
        return CMD_RET_USAGE;
    }

    if (check_network_status() != CMD_RET_SUCCESS)
        return CMD_RET_FAILURE;

    if (strcmp(argv[1], "static") == 0) {
        if (argc < 5) {
            printf("Missing parameters for static IP\n");
            return CMD_RET_USAGE;
        }
        return set_static_ip(argv[2], argv[3], argv[4], 
                           (argc > 5) ? argv[5] : NULL);
    }
    else if (strcmp(argv[1], "dhcp") == 0) {
        int ret = dhcp_autoconfig();
        if (ret != CMD_RET_SUCCESS) {
            printf("DHCP failed, using fallback IP\n");
            set_static_ip("192.168.1.100", "255.255.255.0", 
                         "192.168.1.1", NULL);
        }
        return ret;
    }

    printf("Invalid operation\n");
    return CMD_RET_USAGE;
}

U_BOOT_CMD(
    netconfig, 6, 1, do_net_config,
    "Network configuration tool",
    "static <ip> <mask> <gateway> [server] - Set static IP\n"
    "dhcp - Configure via DHCP"
);
