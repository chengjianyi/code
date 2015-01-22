#!/usr/bin/env python
# coding=utf-8
import os
def feature_word(word):
    wlist = open('words1.txt').readlines()
    for w in wlist:
        sw = w.strip().split('+')
        word1 = sw[0]
        if word1 == word:
            num = int(sw[1])
            return bin(num)

def feature_bigram(bigram):
    blist = open('bigrams1.txt').readlines()
    for b in blist:
        sb = b.strip().split('+')
        bigram1 = sb[0]
        if bigram == bigram1:
            num = int(sb[1])
            return bin(num)

def feature_POS(pos):
    plist = open('dic/POS').readlines()
    for p in plist:
        sp = p.strip().split('+')
        pos1 = sp[0]
        if pos1 == pos:
            num = int(sp[1])
            return bin(num)

def feature(f, value):
    list1 = []
    if f == 'word': 
        list1 = open('words1.txt').readlines()
    elif f == 'bigram': list1 = open('bigrams1.txt').readlines()
    elif f == 'POS': list1 = open('dic/POS').readlines()
    elif f == 'syntax': list1 = open('dic/syn').readlines()
    else: list1 = open('dic/class').readlines()
    num = 0
    count = len(list1)
    bnum = ""
    for va in list1:
        sv = va.strip().split("|")
        value1 = sv[0]
        num = int(sv[1])
        if f == 'class':
            if value1 in value:
                return '%s'%num    
        else:
            if value1 == value:
                bnum = '0'*num+'1'+'0'*(count-num-1)
                return bnum
    print value,f

def format_feature(f):
    format = ''
    i = 1
    for a in f:
        if a != '0':
            format += ' %s:%s'%(i, a)
        i+=1
    format = format+'\n'
    return format

file = open('train.txt', 'a')
flist = os.listdir('train/')
for f in flist:
    print f
    lines = open('train/'+f).readlines()
    for line in lines:
        felist = line.strip().split()
        trfeature = feature('word', felist[0])+feature('POS', felist[1])+feature('syntax', felist[2])
        #print trfeature
        newline = feature('class', felist[3])+format_feature(trfeature)
        file.write(newline)
file.close()
