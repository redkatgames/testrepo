
#!/bin/bash
gcc \
-I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
-I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
gdbus_get_pid_no_proxy.c -g -o gdbus_get_pid_no_proxy \
-ldbus-glib-1 -ldbus-1 -lgobject-2.0 -lglib-2.0 -lgio-2.0 \



