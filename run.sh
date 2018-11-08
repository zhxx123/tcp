# ****************************************************** 
#Author       : zhxx
# Last modified:	2017-08-02 15:44
# Filename     :	build.sh
# Description  : 
# ******************************************************
#!/bin/bash
net=$1
if [ x"$net" == x"secp256k1" ];then
	echo "++ start to compile the secp256k1"
	./gensecp.sh
else
	echo "++ ignore compile secp256k1"
fi

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}

mkdir -p $BUILD_DIR\
	&& cd $BUILD_DIR\
	&& cmake $SOURCE_DIR\
	&& make \
	&& clear\
	&& echo "./build/sever -h (for more help)"

