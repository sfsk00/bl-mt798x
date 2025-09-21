
#include <common.h>
#include <net.h>
#include <command.h>

int dhcp_network_init(void)
{
    int ret;
    char cmd[64];

    /* 1. 硬件初始化 */
    if (eth_init() < 0) {
        printf("Ethernet init failed\n");
        return -1;
    }

    /* 2. 执行DHCP请求 */
    ret = run_command("dhcp", 0);
    if (ret) {
        printf("DHCP failed (code:%d)\n", ret);
        return -2;
    }

    /* 3. 保存关键参数 */
    run_command("setenv serverip ${dhcp_server}", 0);
    run_command("setenv netmask ${netmask}", 0);
    run_command("setenv gatewayip ${gatewayip}", 0);
    
    return 0;
}
