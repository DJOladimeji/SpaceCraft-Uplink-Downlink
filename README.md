# SpaceCraft-Uplink-Downlink
Spacecraft Uplink/downlink 

To run this application you musgh have git install on your application 
https://git-scm.com/downloads
(For windows systems install the X64 bit)

Using git in command link, clone this repository.
git clone (this repository)

For this application to work please follow these steps:
docker run -ti --name newimage myserver bash
apt-get update
apt-get install g++
apt-get install cmake
apt-get install libboost-all-dev
exit
docker commit newimage webserver_dev

Open a new  command prompt/terminal and run this:
docker run -ti -p 23500:23500 -v "Path to repository":/SharedWebserver webserver_dev bash
mkdir build
cd SharedWebserver
cd build
cmake .. (if there is an error in this stage, run: cd .., then cd .., then apt-get install cmake)
make
./SC_Uplink_Downlink
