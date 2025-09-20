#ifndef __DHCP_CUSTOM_H__
#define __DHCP_CUSTOM_H__

#include <command.h>

int do_dhcp_custom(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[]);
extern int do_dhcp(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[]);
extern void net_set_ip(struct in_addr ip);

#endif
