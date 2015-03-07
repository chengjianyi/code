#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "svm.h"

//const int num_feature = 180;
//const int num_test = 1186;

using namespace std;

int main()
{
    int num_features = 64, num_samples = 0;
    double *labels = new double[num_test];
    ifstream tfile("dna.scale.t", ios::in);
    svm_model *model = svm_load_model("dei.model");
    double count = 0;
    
    
    
    
    
    
    
    
    
    for (int i = 0; i < num_test; ++i)
    {
        string line;
        getline(tfile, line);
        labels[i] = atoi(line.substr(0, 1).c_str());
        string feature_str = line.substr(2);
        svm_node *test_data = new svm_node[num_feature+1];
        for (int j = 0; j < num_feature; ++j)
        {
            int partition = feature_str.find(' ');
            string str1 = feature_str.substr(0, partition);
            int index = atoi(str1.substr(0, str1.find(':')).c_str());
            int value = atoi(str1.substr(str1.find(':')+1).c_str());
            if (index == j + 1)
            {
                test_data[j].index = index;
                test_data[j].value = value;
                feature_str = feature_str.substr(partition+1);
            }
            else
            {
                test_data[j].index = j + 1;
                test_data[j].value = 0;
            }
        }
        test_data[num_feature].index = -1;
        test_data[num_feature].value = 0;
        int label = svm_predict(model, test_data);
        if (label == labels[i]) ++count;
    }
    cout<<"precision is "<<count/(double)num_test<<endl;
    return 0;
}
