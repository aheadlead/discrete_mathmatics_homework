#!/usr/bin/env python
# coding: utf-8

from set import *

print "Input two integer set, separated by comma."
a = raw_input("Set A: ")
b = raw_input("Set B: ")

a = [int(x) for x in a.split(',')]
b = [int(x) for x in b.split(',')]

print "Intersection set(A*B): ", set_intersect(a, b)
print "Union set(A+B): ", set_union(a, b)
print "Difference set(A-B): ", set_difference(a, b)
print ""
print "Cartesian product(AxB): ", set_cartesian_product(a, b)
