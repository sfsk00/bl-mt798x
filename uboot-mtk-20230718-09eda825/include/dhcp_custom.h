
#ifndef __DHCP_CUSTOM_H__
#define __DHCP_CUSTOM_H__

struct dhcp_extension {
    uint8_t client_mac[6];
    uint32_t requested_ip;
    uint8_t option_buf[128];
};

int dhcp_custom_request(void);
void dhcp_set_fallback_ip(uint32_t ip);

#endif
