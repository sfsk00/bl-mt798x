
#include <common.h>
#include <command.h>
#include <net.h>
#include <dm.h>
#include <env.h>

#define DHCP_RETRY_MAX 3
#define DHCP_TIMEOUT_MS 5000

static int do_dhcp_autoconfig(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    struct udevice *dev;
    char ip_str[16];
    
    /* 硬件初始化 */
    ret = uclass_get_device(UCLASS_ETH, 0, &dev);
    if (ret) {
        printf("Ethernet init failed (err=%d)\n", ret);
        return CMD_RET_FAILURE;
    }

    /* DHCP参数设置 */
    env_set_ulong("netretry", DHCP_RETRY_MAX);
    net_dhcp_timeout = DHCP_TIMEOUT_MS;

    /* DHCP主流程 */
    for (int i = 0; i < DHCP_RETRY_MAX; i++) {
        printf("DHCP attempt %d/%d\n", i+1, DHCP_RETRY_MAX);
        ret = net_loop(DHCP);
        
        if (ret == 0) {
            ip_to_string(net_ip_addr, ip_str);
            printf("DHCP success: IP=%s\n", ip_str);
            env_set_ip("ipaddr", net_ip_addr);
            env_set_ip("serverip", net_server_ip);
            return CMD_RET_SUCCESS;
        }
        mdelay(100);
    }

    /* 失败回退处理 */
    printf("DHCP failed, using fallback IP\n");
    env_set("ipaddr", "192.168.1.100");
    env_set("netmask", "255.255.255.0");
    return CMD_RET_FAILURE;
}

U_BOOT_CMD(
    dhcp_auto, 1, 1, do_dhcp_autoconfig,
    "Auto DHCP configuration with fallback",
    ""
);
