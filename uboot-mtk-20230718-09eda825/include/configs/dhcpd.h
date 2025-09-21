
#ifndef __DHCPD_H__
#define __DHCPD_H__

#define FIXED_CLIENT_MAC {0x84,0x47,0x09,0x37,0x59,0x8a}
#define FIXED_CLIENT_IP "192.168.1.2"
#define DHCP_LEASE_TIME 86400  // 24小时租期
#define DHCP_SERVER_IP "192.168.1.1"
#define DHCP_NETMASK "255.255.255.0"

struct dhcpd_ctx {
    u8 client_mac[6];
    char client_ip[16];
    u32 lease_time;
    struct in_addr server_ip;
    struct in_addr netmask;
};

void dhcpd_start(struct dhcpd_ctx *ctx);
int dhcpd_process_packet(struct dhcpd_ctx *ctx);

#endif
