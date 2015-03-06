#!/usr/bin/env python
# coding=utf-8
import os

wlist = []
plist = []
slist = []
clist = []
blist = []
for file in os.listdir('all'):
    lines = open('all/'+file).readlines()
    for line in lines:
        if line != '\r\n':
            list1 = line.strip().split()
            wlist.append(list1[0]+'\n')
            plist.append(list1[1])
            slist.append(list1[2])
    #        clist.append(list1[3])
    i = 0
    while i < len(lines)-1:
        if lines[i] != '\r\n' and lines[i+1]!='\r\n':
            list2 = lines[i].strip().split()
            list3 = lines[i+1].strip().split()
            blist.append(list2[0]+' '+list3[0]+'\n')
        i+=1
wlist = {}.fromkeys(wlist).keys()
blist = {}.fromkeys(blist).keys()
open('words2', 'w').writelines(wlist)
open('bigrams2', 'w').writelines(blist)
#clist = {}.fromkeys(clist).keys()

'''
file1 = open('words1.txt','w') #.writelines(wlist)
num = 0
#for w in wlist:
#file1.writeline('%s+%s'%(w,num))
while num < len(wlist):    
    wlist[num] = wlist[num] + '|%s\n'%num 
    num+=1
num = 0
file1.writelines(wlist)
file2 = open('bigrams1.txt', 'w') #.writelines(blist)
while num < len(blist):
    #file2.writeline('%s+%s'%(b, num))
    blist[num] = '%s|%d\n'%(blist[num], num)
    num+=1
file2.writelines(blist)
num = 0
#plist+=open('dic/POS').readlines()
plist = {}.fromkeys(plist).keys()
#slist+=open('dic/syn').readlines()
slist = {}.fromkeys(slist).keys()
for line in open('dic/POS').readlines():
    if not line.strip().split('|')[0] in plist: plist.append(line.strip().split('|')[0])
for line in open('dic/syn').readlines():
    if not line.strip().split('|')[0] in slist: slist.append(line.strip().split('|')[0])
print plist
while num < len(plist):
    plist[num] = plist[num] + '|%s\n'%num
    num+=1
num = 0
while num < len(slist):
    slist[num] = slist[num] + '|%s\n'%num
    num+=1
num = 0
#while num < len(clist):
#    clist[num] = clist[num] + '|%s\n'%num
#    num+=1
open('dic/POS', 'w').writelines(plist)
open('dic/syn', 'w').writelines(slist)
open('dic/class', 'w').writelines(clist)'''
