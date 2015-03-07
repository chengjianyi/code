#coding=utf-8
import os
import datetime


starttime = datetime.datetime.now()   

if __name__ == '__main__':
	llist = open('lexicon.txt').readlines()
	wlist = []
	tlist = []
	slist = []
	count = 0
	wdic = {}
	bdic = {}
	for l in llist: 
		wlist.append(((l.strip().split())[0]).decode('utf-8'))
	# path = u'rmrb/'
	path = 'utf/'
	#path = 'a/'
	for f in os.listdir(path):
		tlist = open(path+f).read().strip().decode('utf-8').split()
		for t in tlist:
                        if count == 1000:print count
			i, j = 0, 6 
			while i < len(t):
				if j > len(t): j = len(t)
				str = t[i:j]
				if str in wlist or i == j - 1: 
					slist.append(str)
					i = j
					j += 6
				else: j -= 1
			count+=1
	fw = open('word_freq.txt', 'w')
	fb = open('Bigram_freq.txt', 'w')
	i = 0
	while i < len(slist):
	    if wdic.has_key(slist[i]): wdic[slist[i]] += 1
	    else: wdic[slist[i]] = 1
	    if i < len(slist) - 1:
	        if bdic.has_key(slist[i]+' '+slist[i+1]):
	            bdic[slist[i]+' '+slist[i+1]] += 1
	        else:
	            bdic[slist[i]+' '+slist[i+1]] = 1
	    i += 1
	wdic = sorted(wdic.iteritems(), key=lambda d:d[1], reverse=True)
	bdic = sorted(bdic.iteritems(), key=lambda d:d[1], reverse=True)
	for k,v in wdic:
	    fw.write((('%s %s\n'%(k,v))).encode('utf-8'))
	for k,v in bdic:
	    fb.write((('%s %s\n'%(k,v))).encode('utf-8'))
	fw.close()
	fb.close()
	endtime = datetime.datetime.now()   
	print (endtime - starttime).seconds   
