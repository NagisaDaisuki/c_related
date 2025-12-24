#!/bin/bash 

# run g++ automatically 

exec 3> logfile

# filename=${1}

read -t 10 -p "Please enter your executable file name: " execname 

if [ -z "$execname" ]
then 
  echo "ican't endure this you know!" >&3
  exit 
fi 

while getopts g: opt
do 
  case "$opt" in 
    g) echo "executing g++ -g commands" >&3 
        g++ -g $OPTARG -o $execname ;;
    *) echo "error input but i know what you want to do"
  esac
done

shift $[ $OPTIND - 1 ]
echo "after shifting is $#"
exec 3>&-
exit 
