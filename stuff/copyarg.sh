


ssh root@169.254.133.27 "mount -o remount,rw /"
ssh root@169.254.133.27 "systemctl stop nodestateman*"
scp /home/yoctoadm/src/onoff/nodestatemanager_source/project/source_products/$1/exe/imp/NodeStateManager  root@169.254.133.27:/usr/bin
scp /home/yoctoadm/src/onoff/nodestatemanager_source/project/source_products/$1/exe/imp/*so  root@169.254.133.27:/usr/lib
ssh root@169.254.133.27 "sync"
