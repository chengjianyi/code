#include <iostream>
#include "traveler.h"
//#include <conio.h>

using namespace std;

int main()
{
    clock_t start, end;
    cout<<"Input amount of nodes:";
    int num = 0;
    cin>>num;
    start = clock();
    Traveler t(num);
    t.travel();
    end = clock();
    cout<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
}

