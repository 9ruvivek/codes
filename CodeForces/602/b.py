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

n=input()
lis=map(int,raw_input().split())
compressed=[lis[0]]
left_index=[0]
right_index=[0]
i=1
while i<n:
	while i<n and lis[i]==lis[i-1]:
		right_index[-1]=i
		i+=1
	if i<n:
		compressed.append(lis[i])
		left_index.append(i)
		right_index.append(i)
		i+=1
# Till Now compressed given data
l=len(compressed)
f=n
res=[0]*l
nex=[0]*l
res[l-1]=right_index[l-1]-left_index[l-1]+1
nex[l-1]=0
for i in range(l-2,-1,-1):
	nex[i]=compressed[i+1]-compressed[i]
	if i+2<l:
		a=compressed[i+1]-compressed[i] # diff b/w i+1,i
		b=compressed[i+2]-compressed[i+1] # diff b/w i+1,i+2
		if (a>0 and b>0) or (a<0 and b<0):
			# If two increasing or decreasing slopes are found then all elements of i+1 and i are in set
			res[i]=right_index[i+1]-left_index[i]+1
		elif (nex[i+2]==b):
			# If a hill or trough is found and end slope continues to be same them get the complete hill or trough
			res[i]=right_index[i+2]-left_index[i]+1
		else:
			# Here Hill shapes like /\/ or \/\ are found so answer to i will be sum of hill and ans of i+2
			res[i]=res[i+2]+left_index[i+2]-left_index[i]
	else:
		res[i]=right_index[i+1]-left_index[i]+1
print max(res)
	
exit(0)
