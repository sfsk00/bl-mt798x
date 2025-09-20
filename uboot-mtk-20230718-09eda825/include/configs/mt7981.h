/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Configuration for MediaTek MT7981 SoC
 *
 * Copyright (C) 2022 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#ifndef __MT7981_H
#define __MT7981_H

/* 网络基础配置 */
#define CONFIG_NET
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_NET_RANDOM_ETHADDR

/* 静态IP回退配置 */
#define CONFIG_IPADDR     192.168.1.100
#define CONFIG_NETMASK    255.255.255.0
#define CONFIG_SERVERIP   192.168.1.1
#define CONFIG_GATEWAYIP  192.168.1.254

/* 环境变量设置 */
#define CONFIG_EXTRA_ENV_SETTINGS \
    "autoload=no\0" \
    "ipaddr=" __stringify(CONFIG_IPADDR) "\0" \
    "netmask=" __stringify(CONFIG_NETMASK) "\0" \
    "serverip=" __stringify(CONFIG_SERVERIP) "\0" \
    "gatewayip=" __stringify(CONFIG_GATEWAYIP) "\0" \
    "ethaddr=00:40:5c:26:0a:5b\0" \
    "bootcmd=run dhcp_boot || run static_boot\0" \
    "dhcp_boot=dhcp; setenv autoload no; tftpboot\0" \
    "static_boot=echo Using static IP; ping $serverip\0"

#endif
