
#include <common.h>
#include <command.h>
#include <dhcpd.h>

static int do_dhcpd(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    struct dhcpd_ctx ctx = {
        .client_mac = FIXED_CLIENT_MAC,
        .client_ip = FIXED_CLIENT_IP,
        .lease_time = DHCP_LEASE_TIME,
        .server_ip.s_addr = inet_addr(DHCP_SERVER_IP),
        .netmask.s_addr = inet_addr(DHCP_NETMASK)
    };
    
    dhcpd_start(&ctx);
    return 0;
}

U_BOOT_CMD(
    dhcpd, 1, 1, do_dhcpd,
    "Start DHCP server with fixed IP assignment",
    ""
);
