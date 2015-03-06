#!/usr/bin/env python
# coding=utf-8
import os

wlist = open('words2').readlines()
wdict = {}
index = 0
for w in wlist:
    wdict[w.strip()] = index
    index += 1

files = os.listdir('train/')
flist = []
for f in files:
    felist = open('train/'+f).readlines()
    for fe in felist:
        word = fe.strip().split()[0]
        flist.append('%s\n'%wdict[word])

open('train1.data', 'w').writelines(flist)
