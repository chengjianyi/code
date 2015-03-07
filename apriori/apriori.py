def tranform_tuple(t):
	t = list(t)
	t.sort()
	s = ''
	for i in t:
		s += '%s '%i
	return s.strip()

def count_key(key, items_set):
	count = 0
	for item in items_set:
		flag = True
		istr = item[5:len(item)].strip()
		for k in key.split():
			if not k in istr: 
				flag = False
				break
		if flag: count+=1  
	return count


def check_stop(dic):
	for k in dic:
		if not dic[k] == 0: return False
	return True

def aprori_gen(dic, min_support, items_set):
	i, j = 0, 0
	newdict = {} 
	while i < len(dic):
		if not dic.items()[i][1] == 0:
			j = i + 1
			while j < len(dic):
				if not dic.items()[j][1] == 0:
					li = list(dic.items()[i][0]+dic.items()[j][0])
					li={}.fromkeys(li).keys()
					key = tranform_tuple(li)
					newdict[key] = count_key(key, items_set)
				j+=1
		i+=1
	for k in newdict:
		if newdict[k] < 2: newdict[k] = 0
 	return newdict



if __name__ == '__main__':
	min_sup_count = 2
	items_set = open('data.txt').readlines()
	idict = {}
	items_set_list = []
	for item in items_set:
		#istr = item[5:len(item)].strip()
		ilist = item.split()[1:len(item.split())]
		for i in ilist:
			if idict.has_key(i): idict[i] += 1
			else: idict[i] = 1
	for k in idict:
		if idict[k] < 2: idict[k] = 0
	newdict = aprori_gen(idict, min_sup_count, items_set )
	while not check_stop(newdict):
		items_set_list.append(newdict)
		newdict = aprori_gen(newdict, min_sup_count, items_set )
	finallsit = []
	for k in items_set_list[len(items_set_list) - 1]:
		if not items_set_list[len(items_set_list) - 1][k] == 0: 
			finallsit.append('%s: %s'%(k,items_set_list[len(items_set_list) - 1][k]))
	print finallsit
