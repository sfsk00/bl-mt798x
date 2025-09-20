/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Configuration for MediaTek MT7981 SoC
 *
 * Copyright (C) 2022 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#ifndef __MT7981_H
#define __MT7981_H

CONFIG_NET=y
CONFIG_CMD_NET=y
CONFIG_CMD_DHCP=y # 如需DHCP功能
CONFIG_CMD_PING=y # 如需ping功能
#endif
