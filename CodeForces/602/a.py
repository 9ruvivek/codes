#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 vivek9ru <vivek9ru@Vivek9RU>
#
# Distributed under terms of the MIT license.

from math import acos,asin,atan,sqrt,pi,sin,cos,tan,ceil,floor
import re
from operator import itemgetter as ig


# convert both to same base and check

n,b=map(int,raw_input().split())
x=map(int,raw_input().split())
rx=0
m=1
for i in x[::-1]:
	rx+=m*i
	m*=b
n,b=map(int,raw_input().split())
y=map(int,raw_input().split())
ry=0
m=1
for i in y[::-1]:
	ry+=m*i
	m*=b
print rx,ry
if rx<ry:
	print "<"
elif rx==ry:
	print "="
else:
	print ">"

exit(0)
