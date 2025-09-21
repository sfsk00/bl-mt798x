/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Configuration for MediaTek MT7981 SoC
 *
 * Copyright (C) 2022 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#ifndef __MT7981_H
#define __MT7981_H

/* 添加BusyBox支持 */
#define CONFIG_CMD_BUSYBOX
#define CONFIG_BUSYBOX_PATH "/bin/busybox"
#define CONFIG_BUSYBOX_CMDLIST \
    "ls", "cat", "echo", "mkdir", "rm", "cp", "mv"


#endif
