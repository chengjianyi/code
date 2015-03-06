#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "svm.h"


using namespace std;

void read_problem(string filename);

struct svm_parameter param;
struct svm_problem prob;
struct svm_model *model;
struct svm_node *x_space;

int main()
{
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    //param.degree = 3;
    param.gamma = 0.03125;
    param.coef0 = 0;
    //param.nu = 0.5;
    param.cache_size = 100;
    param.C = 2;
    param.eps = 1e-5;
    param.weight_label = NULL;
    param.weight = NULL;
    read_problem("dna.scale.tr");
    cout<<"1"<<endl;
    model = svm_train(&prob, &param);
    if (!svm_save_model("dei.model", model)) cout<<"Model has been saved."<<endl;
    else cout<<"Failed to save model."<<endl;
    delete prob.y;
    delete[] prob.x;
    return 0;
}

void read_problem(string filename)
{
    ifstream infile(filename.c_str(), ios::in);
    if (!infile) 
    {
        cout<<"can't open file."<<endl;
        exit(0);
    }
    int num_features = 0, i = 0, j = 0;
    string line;
    getline(infile, line);
    while (line != "")
    {
        int p = line.find_first_of(" \t\n");
        string fstr = line;
        while (1)
        {
            if (fstr == "") break;
            fstr = fstr.substr(p+1);
            p = fstr.find_first_of(" \t\n");
            ++num_features;
        }
        ++num_features;
        ++prob.l;
        getline(infile, line);
    }
    infile.clear();
    infile.seekg(0, ios::beg);

    prob.y = new double[prob.l];
    prob.x = new svm_node*[prob.l];
    x_space = new svm_node[num_features];
    
    for (int i = 0; i < prob.l; ++i)
    {
        getline(infile, line);
        int pl = line.find_first_of(" \t\n");
        string lstr = line.substr(0, pl+1);
        string fstr = line.substr(pl+1);
        prob.y[i] = atoi(lstr.c_str());
        prob.x[i] = &x_space[j];
        while(1)
        {
            if (fstr == "") break;
            int pfl = fstr.find_first_of(" \t\n");
            string cf = fstr.substr(0, pfl+1);
            //string str2 = fstr.substr(plf+1);
            int pi = cf.find_first_of(":");
            string istr = cf.substr(0, pi+1);
            string vstr = cf.substr(pi+1);
            svm_node node;
            node.index = atoi(istr.c_str());
            node.value = atof(vstr.c_str());
            x_space[j] = node;
            ///cout<<x_space[j].index<<":"<<x_space[j].value<<" ";
            ++j;
            fstr = fstr.substr(pfl+1);
        }
        x_space[j++].index = -1;
        //cout<<x_space[j-1].index<<":"<<endl;
        //cout<<line<<endl;
    }
    infile.close();
}


