
#include <common.h>
#include <command.h>
#include <net.h>
#include <dm.h>
#include <env.h>
#include <linux/delay.h>

#define DHCP_RETRY_MAX 3
#define DHCP_TIMEOUT_MS 5000

static int do_dhcp_autoconfig(struct cmd_tbl *cmdtp, int flag, int argc,
                             char *const argv[])
{
    int ret;
    struct udevice *dev;
    char ip_str[16];
    
    /* 硬件初始化 */
    if (uclass_get_device(UCLASS_ETH, 0, &dev)) {
        printf("Ethernet device not found\n");
        return CMD_RET_FAILURE;
    }

    /* 设置DHCP参数 */
    env_set_ulong("netretry", DHCP_RETRY_MAX);
    env_set_ulong("timeout", DHCP_TIMEOUT_MS);

    /* DHCP主流程 */
    for (int i = 0; i < DHCP_RETRY_MAX; i++) {
        printf("DHCP attempt %d/%d\n", i+1, DHCP_RETRY_MAX);
        ret = net_loop(DHCP);
        
        if (!ret) {
            /* 使用环境变量直接获取IP */
            printf("DHCP success: IP=%s\n", env_get("ipaddr"));
            return CMD_RET_SUCCESS;
        }
        mdelay(100);
    }

    /* 失败回退处理 */
    printf("Using fallback IP 192.168.1.100\n");
    env_set("ipaddr", "192.168.1.100");
    env_set("netmask", "255.255.255.0");
    return CMD_RET_FAILURE;
}

U_BOOT_CMD(
    dhcp_auto, 1, 1, do_dhcp_autoconfig,
    "Auto DHCP configuration with fallback",
    ""
);
