#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "svm.h"

const int num_feature = 180;
const int num_train = 1400;

using namespace std;

int main()
{
    svm_problem prob;
    prob.l = num_train;
    //double *labels = new double[num_train];
    //svm_node **train_data = new svm_node*[num_train];
    prob.y = new double[num_train];
    prob.x = new svm_node*[num_train];
    for (int i = 0; i < num_train; ++i)
        //train_data[i] = new svm_node[num_feature+1];
        prob.x[i] = new svm_node[num_feature+1];
    ifstream trfile("dna.scale.tr", ios::in);
    for (int i = 0; i < num_train; ++i)
    {
        string line;
        getline(trfile, line);
        //labels[i]
        prob.y[i] = atoi(line.substr(0, 1).c_str());
        string feature_str = line.substr(2);
        for (int j = 0; j < num_feature; ++j)
        {
            int partition = feature_str.find(' ');
            string str1 = feature_str.substr(0, partition);
            int index = atoi(str1.substr(0, str1.find(':')).c_str());
            int value = atoi(str1.substr(str1.find(':')+1).c_str());
            if (index == j+1)
            {
                //train_data[i][j].index = index;
                //train_data[i][j].value = value;
                prob.x[i][j].index = index;
                prob.x[i][j].value = value;
                feature_str = feature_str.substr(partition+1);
            }
            else
            {
                //train_data[i][j].index = j+1;
                //train_data[i][j].value = 0;
                prob.x[i][j].index = j + 1;
                prob.x[i][j].value = 0;
            }
        }
        //train_data[i][num_feature].index = -1;
        //train_data[i][num_feature].value = 0;
        prob.x[i][num_feature].index = -1;
        prob.x[i][num_feature].value = 0;
    }
    //cout<<"here"<<endl;
    trfile.close();
    svm_parameter param;
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.C = 2;
    param.gamma = 0.03125;
    param.cache_size = 32;
    param.weight_label = NULL;
    param.weight = NULL;
    param.eps = 1e-5;
    svm_model *model = svm_train(&prob, &param);
    if (!svm_save_model("dei.model", model)) cout<<"Model has been saved in dei.model."<<endl;
    else cout<<"Failed to save model."<<endl;
    //delete []train_data;
    //delete labels;
    delete[] prob.x;
    delete prob.y;
    return 0;
}
