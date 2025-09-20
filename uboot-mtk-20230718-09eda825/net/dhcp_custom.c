
#include <common.h>
#include <command.h>
#include <net.h>
#include <malloc.h>

#define DHCP_FALLBACK_IP 0xC0A80102 // 192.168.1.2
#define DHCP_CUSTOM_CLASS "uboot-custom-v1.0"

struct dhcp_extension {
    uint8_t client_mac[6];
    uint32_t requested_ip;
    uint8_t option_buf[128];
};

static int dhcp_custom_request(void)
{
    struct dhcp_packet *packet;
    struct in_addr fallback_ip;
    
    // 构造标准DHCP请求
    packet = prepare_dhcp_packet();
    
    // 添加自定义选项
    add_option(packet, 60, DHCP_CUSTOM_CLASS, strlen(DHCP_CUSTOM_CLASS));
    
    // 发送请求
    if (net_send_udp_packet(packet, sizeof(*packet)) < 0) {
        fallback_ip.s_addr = htonl(DHCP_FALLBACK_IP);
        net_set_ip(fallback_ip);
        return CMD_RET_FAILURE;
    }
    return CMD_RET_SUCCESS;
}
