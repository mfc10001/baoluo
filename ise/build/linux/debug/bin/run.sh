#!/bin/sh


StartServer()
{
./db_server -d
sleep 1
./main_server -d
sleep 1
./login_server -d	

}

StopServer()
{

pkill db_server -u `whoami` 
pkill main_server -u `whoami` 
pkill login_server -u `whoami` 
}
if [ $1 -eq 0 ]
then
StartServer()
fi


if [ $1 -eq 1 ]
then
StopServer()
fi

