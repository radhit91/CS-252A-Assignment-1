#!/bin/bash
./client
size=0
arr[$size]='<!DOCTYPE html>'
let size=size+1
arr[$size]='<html>'
let size=size+1
arr[$size]='<body>'
let size=size+1
arr[$size]='<table style="width:100%">'
let size=size+1
arr[$size]='<tr>'
let size=size+1
i=0
width=4
while [ $i -lt $width ]; do
	arr[$size]='<th></th>'
	let size=size+1	
        let i=i+1			
done
arr[$size]='</tr>'
let size=size+1
i=0
while [ $i -lt $width ]; do
	arr[$size]='<tr>'
	let size=size+1
	if [ $i == 0 ]; then
		str='cat'
	elif [ $i == 1 ]; then
		str='dog'
	elif [ $i == 2 ]; then
		str='car'
	else
		str='truck'
	fi
		
	for j in $(ls $str*); do
		arr[$size]='<td><img src='"$j"'></td>'
		let size=size+1
	done
	arr[$size]='</tr>'
	let size=size+1
	let i=i+1
done
arr[$size]='</table>'
	let size=size+1
arr[$size]='</body>'
	let size=size+1
arr[$size]='</html>'
	let size=size+1
i=0
while [ $i -lt $size ]; do
	echo ${arr[$i]}
	let i=i+1
done
