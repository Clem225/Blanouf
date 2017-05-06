#$CC -o main main.c
#scp main root@192.168.7.2:/home/root/

$CC -o main main.c -I/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/include/xenomai -L/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib -lxenomai -lnative
scp main root@192.168.7.2:/home/root/

$CC -o synchro synchro.c -I/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/include/xenomai -L/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib -lxenomai -lnative
scp synchro root@192.168.7.2:/home/root/

$CC -o latence latence.c -I/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/include/xenomai -L/opt/poky/1.7.3/sysroots/armv7a-vfp-neon-poky-linux-gnueabi/usr/lib -lxenomai -lnative 
scp latence root@192.168.7.2:/home/root
