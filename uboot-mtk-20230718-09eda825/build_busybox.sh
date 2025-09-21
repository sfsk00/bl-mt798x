
#!/bin/bash
# U-Boot环境自动编译BusyBox脚本

set -e

# 配置参数
BUSYBOX_REPO="git://busybox.net/busybox.git"
INSTALL_DIR="$(pwd)/rootfs"
CROSS_COMPILE="arm-linux-gnueabihf-"
ARCH="arm"

# 目录结构
mkdir -p ${INSTALL_DIR}/{bin,sbin,etc,proc,sys,dev,usr}

# 克隆源码
echo "Cloning BusyBox repository..."
git clone ${BUSYBOX_REPO} busybox
cd busybox

# 配置编译选项
make defconfig
sed -i 's/.*CONFIG_STATIC.*/CONFIG_STATIC=y/' .config
sed -i 's/.*CONFIG_UDHCPD.*/CONFIG_UDHCPD=y/' .config
sed -i 's/.*CONFIG_FEATURE_UDHCPD_WRITE_LEASES.*/CONFIG_FEATURE_UDHCPD_WRITE_LEASES=y/' .config

# 交叉编译
echo "Building BusyBox..."
make CROSS_COMPILE=${CROSS_COMPILE} ARCH=${ARCH} -j$(nproc)
make CROSS_COMPILE=${CROSS_COMPILE} CONFIG_PREFIX=${INSTALL_DIR} install

# 生成初始化脚本
cat > ${INSTALL_DIR}/etc/init.d/rcS <<EOF
#!/bin/sh
mount -t proc proc /proc
mount -t sysfs sysfs /sys
/sbin/ifconfig lo 127.0.0.1
EOF
chmod +x ${INSTALL_DIR}/etc/init.d/rcS

echo "Build completed at ${INSTALL_DIR}"
