#
# Regular cron jobs for the fcitx5-demo package
#
0 4	* * *	root	[ -x /usr/bin/fcitx5-demo_maintenance ] && /usr/bin/fcitx5-demo_maintenance
