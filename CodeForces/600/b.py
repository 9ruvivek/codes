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

n,m=map(int,raw_input().split())
a=map(int,raw_input().split())
c=map(int,raw_input().split())
l=len(c)
e=len(a)
b=[]
for i in range(l):
	b.append([c[i],i])
a.sort()
b.sort()
c=[0]*l
j=0
for i in range(l):
	while j<e and a[j]<=b[i][0]:
		j+=1
	c[b[i][1]]=j

for i in c:
	print i,
print
