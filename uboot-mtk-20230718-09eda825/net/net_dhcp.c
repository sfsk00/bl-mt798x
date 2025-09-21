
#include <common.h>
#include <net.h>
#include <command.h>

int dhcp_with_fallback(void)
{
    int ret;
    char cmd[64];
    
    /* 尝试DHCP */
    ret = run_command("dhcp", 0);
    if (ret == 0) {
        printf("DHCP assigned IP: %s\n", getenv("ipaddr"));
        return 0;
    }

    /* 回退静态IP */
    sprintf(cmd, "setenv ipaddr %s", CONFIG_FALLBACK_IPADDR);
    run_command(cmd, 0);
    sprintf(cmd, "setenv netmask %s", CONFIG_FALLBACK_NETMASK);
    run_command(cmd, 0);
    sprintf(cmd, "setenv gatewayip %s", CONFIG_FALLBACK_GATEWAY);
    run_command(cmd, 0);
    
    return 1;
}
