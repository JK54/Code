#!/bin/bash
#
# aria2 - this script starts and stops the aria2 daemon
#
# chkconfig:   - 85 15
# description: Aria2 - Download Manager
# processname: aria2c
# config:      /etc/aria2/aria2.conf
# pidfile:     

#modified from https://www.cnblogs.com/colder219/p/6298168.html

aria2c="/usr/bin/aria2c"
ARIA2C_CONF_FILE="/etc/aria2/aria2.conf"
options=" --conf-path=$ARIA2C_CONF_FILE"

RETVAL=0

update_bt_tracker()
{
	conf=/etc/aria2/aria2.conf
	temp=/tmp
	trackerfile=trackers_all.txt
	downloadfile=https://raw.githubusercontent.com/ngosang/trackerslist/master/$trackerfile
	
	aria2c --dir=$temp $downloadfile
	sed ":a;N;s/\n/ /; ta;" $temp/$trackerfile > $temp/trackerstemp.txt
	sed "1s/^/bt-tracker=/g; s/ /,/g; s/ $//;" $temp/trackerstemp.txt > $temp/trackers.txt

	sed "/^bt-tracker=/d" $conf > $temp/aria2n.conf
	cat $temp/trackers.txt >> $temp/aria2n.conf
	mv $temp/aria2n.conf $conf
}


start() {
		update_bt_tracker
        # code here to start the program
        echo -n "Starting aria2c daemon."
        ${aria2c} ${options}
        RETVAL=$?
        echo
}

stop() {
        echo -n "Shutting down aria2c daemon."
        /usr/bin/killall aria2c
        RETVAL=$?
        echo
}

status() {
        ID=$(/bin/ps -ef | grep 'aria2c' | grep -v 'grep' | awk '{print $2}')
        if [[ "x$ID" != "x" ]]; then
                echo "Aria2 is running."
        else
                echo "Aria2 is not running."
        fi
}

restart() {
        stop
        sleep 3
        start
}

case "$1" in
        start)
                start
                ;;
        stop)
                stop
                ;;
        status) 
                status
                ;;
        restart)
                restart
                ;;
        *)
                echo "Usage: service aria2c {start|stop|restart}"
                RETVAL=1                             
esac                                                 

exit $RETVAL
