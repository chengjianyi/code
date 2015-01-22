#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "svm.h"

const int num_feature = 0;
const int num_train = 0;

using namespace std;

int main()
{
    svm_problem prob;
    prob.l = num_train;
    double *labels = new double[num_train];
    svm_node **train_data = new svm_node*[num_train];
    for (int i = 0; i < num_train; ++i)
        train_data[i] = new svm_node[num_feature+1];
    ifstream trfile("train.txt", ios::in);
    for (int i = 0; i < num_train; ++i)
    {
        string line;
        getline(trfile, line);
        labels[i] = atoi(line.substr(0, 1).c_str());
        string feature_str = line.substr(2);
        for (int j = 0; j < num_feature; ++j)
        {
            int partition = feature_str.find(' ');
            string str1 = feature_str.substr(0, partition);
            int index = atoi(str1.substr(0, str1.find(':')).c_str());
            int value = atoi(str1.substr(str1.find(':')+1).c_str());
            if (index == j)
            {
                train_data[i][j].index = index;
                train_data[i][j].value = value;
                feature_str = feature_str.substr(partition+1);
            }
            else
            {
                train_data[i][j].index = j;
                train_data[i][j].value = 0;
            }
        }
        train_data[i][num_feature].index = -1;
        train_data[i][num_feature].value = 0;
    }
    svm_parameter param;
    param.svm_type = C_SVC;
    param.kernel_type = LINEAR;
    param.C = 10;
    param.cache_size = 100;
    svm_model *model = svm_train(&prob, &param);
    return 0;
}
