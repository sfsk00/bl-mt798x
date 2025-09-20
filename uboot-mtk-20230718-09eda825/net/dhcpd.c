
#include <common.h>
#include <command.h>
#include <net.h>
#include <malloc.h>

#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68

struct dhcpd_lease {
    uint8_t chaddr[16];
    uint32_t yiaddr;
    uint32_t expires;
};

static struct dhcpd_lease leases[10];

int do_dhcpd(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    struct dhcp_packet packet;
    struct in_addr server_ip;
    
    // 设置服务器IP池
    server_ip.s_addr = htonl(0xC0A80101); // 192.168.1.1
    net_set_ip(server_ip);
    
    // 初始化租约池
    memset(leases, 0, sizeof(leases));
    
    // 启动DHCP服务
    return net_loop(DHCPD);
}
