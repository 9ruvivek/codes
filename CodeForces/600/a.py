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
from re import split as msplit

s=msplit(";|,",raw_input())
a=[]
b=[]
for i in s:
	try:
		if len(str(int(i)))==len(i):
			a.append(i)
		else:
			b.append(i)
	except:
		b.append(i)
if len(a):
	print "\""+",".join(a)+"\""
else:
	print "-"
if len(b):
	print "\""+",".join(b)+"\""
else:
	print "-"
exit(0)
