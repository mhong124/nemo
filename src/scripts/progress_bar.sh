#! /usr/bin/env  bash
#

# usage:   progress_bar.sh progress table column-number max-value
#
#  progress=0     none
#           1     zenity
#           2     qt5 (not implemented yet)

pro=$1
tab=$2
col=$3
max=$4
sleep=1

if [ $# -ne 4 ]; then
    echo "$0: need 4 arguments, got $#:"
    echo "pro:    progress mode (0=none, 1=zenity 2=qt5)"
    echo "tab:    ascii table file"
    echo "col:    column to use to measure progress"
    echo "max:    max value in this column which is 100%"
    exit 0
fi

echo "$0: $pro $tab $col $max"

#  some programs take some startup time to create the progress file
for i in $(seq 5); do
    if [ ! -e $tab ]; then
	echo "SLEEPING for $tab"
	sleep $sleep
    else
	echo "Finally saw $tab"
	break
    fi
done

#   if progress table still doesn't exist, give up
if [ ! -e $tab ]; then
    echo "$tab does not exist, giving up"
    exit 0
fi

#    another minor sleep
sleep $sleep

#    looping to check progress, passing on the percentage completeness to zenity
(while [ 1 = 1 ]; do
 now=$(tail -1 $tab | tabcols - $col);
 p=$(nemoinp "100*${now}/${max}" format=%d);
 printf "%d\n"  $p;
 sleep $sleep;
done)   | zenity --progress --auto-close --time-remaining --title "NEMO: $tab" --text "$tab" --percentage=0 
 

