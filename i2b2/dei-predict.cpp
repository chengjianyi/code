#include <iostream>
#include <fstream>
#include <malloc.h>
#include <stdlib.h>
#include "svm.h"

using namespace std;

int main()
{
    int num_features = 64, num_samples = 0, i = 0, j = 0;
    double count = 0;
    ifstream infile("dna.scale.t", ios::in);
    svm_model *model = svm_load_model("dei.model");
    if (!infile)
    {
        cout<<"can't open file."<<endl;
        exit(0);
    }
    string line;
    getline(infile, line);
    //string fstr = line;
    svm_node* x = (svm_node*)malloc(num_features*sizeof(svm_node));
    while (line != "")
    {
        i = 0;
        double target_label, predict_label;
        int pl = line.find_first_of(" \t\n");
        string label = line.substr(0, pl+1);
        string fstr = line.substr(pl+1);
        target_label = atof(label.c_str());
        while (1)
        {
            if (i > num_features - 1)
            {
                num_features*=2; 
                x = (svm_node*) realloc(x, num_features*sizeof(svm_node));
            }
            if (fstr == "") break;
            int pf = fstr.find_first_of(" \t\n");
            string cf = fstr.substr(0, pf+1);
            fstr = fstr.substr(pf+1);
            int pi = cf.find_first_of(":");
            string istr = cf.substr(0, pi+1);
            string vstr = cf.substr(pi+1);
            x[i].index = atoi(istr.c_str());
            x[i].value = atof(vstr.c_str());
            ++i;
        }
        x[i].index = -1;
        predict_label = svm_predict(model, x);
        if (predict_label == target_label) ++count;
        ++num_samples;
        getline(infile, line);
    }
    free(x);
    infile.close();
    svm_free_and_destroy_model(&model);
    cout<<"Accuracy:"<<count/(double)num_samples<<endl;
}
