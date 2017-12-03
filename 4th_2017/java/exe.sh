#!/bin/sh

source /etc/profile

. JDK jdk1.8.0_66

echo "status:running" >> coder_info

java MainFrame $1 $2 > exe_result 2>&1