
/* 新增静态IP回退功能 */
static int dhcp_with_fallback(void)
{
    struct in_addr ip;
    
    if (do_dhcp() != CMD_RET_SUCCESS) {
        ip.s_addr = htonl(0xC0A80102); // 192.168.1.2
        net_set_ip(ip);
        printf("DHCP failed, using fallback IP\n");
    }
    return CMD_RET_SUCCESS;
}

/* 增强选项处理 */
static void process_options(uint8_t *opt)
{
    // 新增自定义选项解析逻辑
    while (*opt != 255) {
        if (*opt == 43) { // 厂商特定选项
            parse_vendor_option(opt+2, opt[1]);
        }
        opt += opt[1] + 2;
    }
}
