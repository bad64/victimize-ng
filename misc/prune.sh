#!/bin/bash

sed -i -e 's/^[\t]//' $1
sed -i -e 's/ /,/' $1
sed -i -e 's/[\t]//' $1
sed -i -e 's/ /,/' $1
sed -i -e 's/@supinfo.com//' $1
sed -i -e '/^$/d' $1

cat $1
echo ""
