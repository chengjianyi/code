import pandas as pd
from math import log
import operator

#load dataset
def load_data(filename):
    df = pd.read_csv(filename)
    return df

#calculate shannon entropy
def calc_ent(dataset):
    num_entities = len(dataset)
    label_dict = dict()
    for data in dataset:
        if label_dict.has_key(data[-1]): label_dict[data[-1]] += 1
        else: label_dict[data[-1]] = 1 
        ent = 0.0
    for k,v in label_dict.items():
        plabel = float(v)/float(num_entities)
        ent -= plabel * log(plabel, 2)
    return ent

#splitdataset
def split_dataset(dataset, index, value):
    ret_dataset = list()
    for data in dataset:
        if data[index] == value:
            reduced_dataset = data[:index]
            reduced_dataset.extend(data[index+1:])
            ret_dataset.append(reduced_dataset)
    return ret_dataset

#find best feature to split
def find_best_feature(dataset):
    base_ent = calc_ent(dataset)
    best_gain = 0.0
    best_feature = -1
    for i in range(len(dataset[0]) - 1):
        feature_value = [data[i] for data in dataset]
        unique_feature_value = set(feature_value)
        fea_ent = 0.0
        for value in unique_feature_value: 
            sub_dataset = split_dataset(dataset, i, value)
            print sub_dataset
            prob = len(sub_dataset)/float(len(dataset))
            fea_ent += prob * calc_ent(sub_dataset)
        info_gain = base_ent - fea_ent
        if info_gain > best_gain:
            best_gain = info_gain 
            best_feature = i
    return best_feature

#find most voted label
def most_voted_label(label_list):
    label_dict = dict()
    for label in label_list:
        if not label_dict.has_key(label): label_dict[label] = 0
        label_dict[label] += 1
    sorted_label_list = sorted(label_dict.iteritems(), key = operator.itemgetter(1), reverse = True)
    return sorted_label_list[0][0]

#build tree
def build_tree(dataset, feature_type):
    label_list = [data[-1] for data in dataset]
    if label_list.count(label_list[0]) == len(label_list): return label_list[0]
    if len(dataset[0]) == 1: return most_voted_label(label_list)
    best_feature = find_best_feature(dataset)
    best_feature_type = feature_type[best_feature]
    del(feature_type[best_feature])
    feature_value = [data[best_feature] for data in dataset]
    unique_feature_value = set(feature_value)
    tree = {best_feature_type: {}}
    for ufv in unique_feature_value: 
        sub_dataset = split_dataset(dataset, best_feature, ufv)
        sub_feature = feature_type[:]
        tree[best_feature_type][ufv] = build_tree(sub_dataset, sub_feature)
    return tree

#classify
def classify(tree, feature_type, test_sample):
    root = tree.keys()[0]
    branches = tree[root]
    feature_index = feature_type.index(root)
    for key in branches.keys():
        if key == test_sample[feature_index]: 
            if type(branches[key]).__name__ == 'dict':
                label = classify(branches[key], feature_type, test_sample)
            else: label = branches[key]
    return label


def main():
    dataset = [[1,1,1],[1,1,1],[1,0,-1],[0,1,-1],[0,1,-1]]
    feature_type = ['a', 'b']
    tree = build_tree(dataset, feature_type)
    print tree
    feature_type = ['a', 'b']
    print classify(tree, feature_type, [1,1])

if __name__ == '__main__':
	main()
