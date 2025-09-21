
#include <configs/dhcp_ip.h>
#define CONFIG_BOOTCOMMAND "run netboot"
#define CONFIG_EXTRA_ENV_SETTINGS \
    "netboot=dhcp_with_fallback; tftp ${loadaddr} ${bootfile}; bootm\0"
