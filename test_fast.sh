#! /bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

#make clean
#make -j4

if [ ! -d data ]; then
    echo "untarring data..."
    tar -xf data.tar.gz
fi

echo "Graph Name		Size		Time"

data_set_names="MANN_a27 p_hat300-3 p_hat500-2 p_hat700-2 san200_0.9_1 san200_0.9_2 san400_0.7_1 san400_0.7_2 san400_0.7_3 san1000 sanr200_0.7"
for i in $data_set_names
do
	data_set_name=`echo $i | sed -e "s%^data/%%g" | sed -e "s/\.graph$//g"`
    echo -n "$data_set_name		"
    bin/open-mcs --algorithm=mcs --input-file=data/$i.graph 2>&1 | grep "mcs:" | sed -e 's/mcs: Found maximum clique of size \(.*\) in \(.*\) seconds/\1		\2s/g'
done
