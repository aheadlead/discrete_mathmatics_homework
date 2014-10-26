#!/usr/bin/env python
# coding: utf-8

def set_intersect(a, b):
    a.sort()
    b.sort()
    c = []
    ia = ib = 0
    while ia < len(a) and ib < len(b):
        if a[ia] == b[ib]:
            c.append(a[ia])
            ia = ia+1
            ib = ib+1
        elif a[ia] < b[ib]:
            ia = ia+1
        elif a[ia] > b[ib]:
            ib = ib+1
    return c

def set_union(a, b):
    L = a+b
    L.sort()
    return [L[i] for i in range(len(L)) if i == 0 or L[i] != L[i-1]]

def set_difference(a, b):
    for i in b:
        try:
            a.remove(i)
        except:
            pass
    return a

def set_cartesian_product(a, b):
    c = []
    for pa in a:
        for pb in b:
            c.append((pa, pb))
    return c
