
#include <common.h>
#include <net.h>
#include <dhcpd.h>

void dhcpd_start(struct dhcpd_ctx *ctx)
{
    // 初始化网络接口
    net_set_ipaddr(ctx->server_ip);
    net_set_netmask(ctx->netmask);
    
    // 绑定DHCP服务端口
    udp_bind(67);
    
    while(1) {
        dhcpd_process_packet(ctx);
    }
}

int dhcpd_process_packet(struct dhcpd_ctx *ctx)
{
    // 接收DHCP Discover报文
    // 验证MAC地址匹配
    // 发送DHCP Offer响应
    // 处理DHCP Request
    // 发送DHCP ACK/NACK
}
