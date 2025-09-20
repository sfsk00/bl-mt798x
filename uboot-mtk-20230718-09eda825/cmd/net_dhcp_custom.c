
#include <common.h>
#include <command.h>
#include <net.h>
#include <dhcp_custom.h>

int do_dhcp_custom(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    printf("[DHCP-CUSTOM] Starting enhanced DHCP\n");
    
    /* 调用标准DHCP实现 */
    if (do_dhcp(cmdtp, flag, argc, argv) != CMD_RET_SUCCESS) {
        struct in_addr ip;
        ip.s_addr = htonl(0xC0A80102); // 192.168.1.2
        net_set_ip(ip);
        printf("[DHCP-CUSTOM] Using fallback IP: 192.168.1.2\n");
        return CMD_RET_SUCCESS;
    }
    
    return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
    dhcp_custom, 1, 1, do_dhcp_custom,
    "Enhanced DHCP with fallback IP",
    "[timeout]\n"
    "  - timeout: Optional timeout in milliseconds"
);
