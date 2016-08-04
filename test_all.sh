#! /bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

make clean
make -j4

if [ ! -d data ]; then
    echo "untarring data..."
    tar -xf data.tar.gz
fi

echo "Graph Name		Size		Time"
for i in data/*
do
	data_set_name=`echo $i | sed -e "s%^data/%%g" | sed -e "s/\.graph$//g"`
    echo -n "$data_set_name		"
    bin/open-mcs --algorithm=mcs --input-file=$i 2>&1 | grep "mcs:" | sed -e 's/mcs: Found maximum clique of size \(.*\) in \(.*\) seconds/\1		\2s/g'
done
