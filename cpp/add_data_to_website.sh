#!/bin/bash
HOST_NAME=`hostname`

./rk4_output $1 $2 | sudo tee /var/www/$HOST_NAME.com/public_html/data.txt
./time_test $1 $2 | sudo tee /var/www/$HOST_NAME.com/public_html/time.txt