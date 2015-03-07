#!/usr/bin/env python
# coding=utf-8

llist = open('word_freq1.txt').readlines()
blist = open('Bigram_freq1.txt').readlines()
ucount = 0
bcount = 0
for l in llist:
    str = l.strip()
    slist = l.split()
    if len(slist[0]) == 3 and int(slist[1]) > 1000: 
        #print slist[0]
        print int(slist[1])
        ucount+=1
        #for b in blist:
            #if b.strip().split()[0] == slist[0] and len(b.strip().split()[1]) == 3:
                #bcount+=1
                #print slist[0], b.strip().split()[0], b.strip().split()[1]
#print ucount,bcount

for b in blist:
    str = b.strip()
    bblist = str.split()
    if len(bblist[0]) == 3 :
        bcount+=1
print ucount, bcount
