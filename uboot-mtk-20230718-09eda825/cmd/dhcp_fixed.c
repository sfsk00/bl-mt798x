
#include <common.h>
#include <command.h>
#include <net.h>
#include <env.h>

#define FIXED_IP 0xC0A80101  // 192.168.1.1

static int do_dhcp_fixed(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    struct in_addr ip;
    int ret;
    
    // 先尝试标准DHCP
    ret = do_dhcp(cmdtp, flag, argc, argv);
    if (ret != CMD_RET_SUCCESS) {
        ip.s_addr = htonl(FIXED_IP);
        net_set_ip(ip);
        env_set_ip("ipaddr", ip);
        printf("DHCP failed, using fixed IP: 192.168.1.1\n");
    }
    return ret;
}

U_BOOT_CMD(
    dhcp_fixed, 1, 1, do_dhcp_fixed,
    "DHCP with fixed IP fallback (192.168.1.1)",
    "[timeout]\n"
    "  - timeout: Optional timeout in milliseconds"
);
