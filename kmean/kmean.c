#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

#define SAMPLES_NUM 25     //样本数
#define DIMENSION 2        //样本维度
#define CLUSTER_NUM 4      //聚类数
#define THREHOLD 0.000001        //收敛阈值

/*样本结构体*/
typedef struct Sample
{
    double vector[DIMENSION];   //样本向量
    int cluster;           //所属类别
}Sample;

/*聚类中心结构体*/
typedef struct Center
{
    double vector[DIMENSION];
}Center;

/*检查聚类中心是否重复*/
int check(int crand[], int k, int n)
{
    int i = 0, flag = 0;
    for (i = 0; i < n; i++)
    {
       if (crand[i] == k) flag = 1;
    }
    return flag;
}

/*计算样本到聚类中心的距离*/
double calc_distance( double x[], double y[], int n)
{
    int i;
    double sum=0;
    for(i = 0; i < n; i++)
        sum += (x[i]-y[i])*(x[i]-y[i]);    //计算样本到样本中心的欧几里德距离
    return sum;
}

/*判断样本x是否在类别cluster中*/
int  is_incluster(int x, int cluster)
{
    return (x==cluster)?1:0;
}

/*计算聚类中心*/
int calc_center(Sample *s, Center *center)
{
    int i, j, k = 0;
    double c = 0;
    double sum1 = 0, sum2 = 0;
    double diff = 1;
    int convergence = 0;
    for (i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < CLUSTER_NUM; j++)
        {
            sum1 = 0;
            sum2 = 0;
            for (k = 0; k < SAMPLES_NUM; k++)
            {
                sum1 += ((*(s+k)).vector[i])*is_incluster((*(s+k)).cluster, j);     //样本x属于类别j则将样本值加入sum1
                sum2 += is_incluster((*(s+k)).cluster, j);            //样本x属于类别j则sum2加1
            }
            c = sum1/sum2;       //计算聚类中心的值
            diff = fabs((*(center+j)).vector[i] - c);    //新产生的聚类中心与原聚类中心差值的绝对值
            if (diff > THREHOLD)
            {
                (*(center+j)).vector[i] = c;
                convergence++;
            }
        }
    }
    return convergence;
}

/*聚类函数*/
void cluster(Center *center, int x[], Sample *s)
{
    double distance = 0;
    int i,j,k = 0;
    double min = 0;
    int minc = 0;
    for (i = 0; i < SAMPLES_NUM; i++)
    {
        min = calc_distance((*(s+i)).vector, (*(center)).vector, DIMENSION);
        minc = 0;
        for(k = 0; k < CLUSTER_NUM; k++)
        {
            distance = calc_distance((*(s+i)).vector, (*(center+k)).vector, DIMENSION);
            if (min > distance)
            {
                min = distance;
                minc = k;
            }
        }
        (*(s+i)).cluster = minc;    //分别比较样本x到各个聚类中心的距离，取最小值作为样本x的类别
    }
}

int main()
{
    int x[DIMENSION]= {0};
    Center* center = (Center*)malloc(CLUSTER_NUM*sizeof(Center));
    Sample* s = (Sample*)malloc(SAMPLES_NUM*sizeof(Sample));
    double distance = 0;
    int i,j,k = 0;
    double min = 0;
    int minc = 0;
    int crand[CLUSTER_NUM];
    FILE *fp;
    FILE *fw;

    if((fp = fopen("data.txt", "r"))==NULL)
    {
        printf("cannot open file");
        exit(1);
    }
    //读取样本
    for(i=0; i<SAMPLES_NUM; i++)
    {
        for(j=0; j<DIMENSION; j++)
        {
            fscanf(fp, "%d", &x[j]);
            (*(s+i)).vector[j] = x[j];
        }
    }
    //随机选择样本作为初始聚类中心
    srand((unsigned int)time(0));
    for (i = 0; i < CLUSTER_NUM; i++)
    {
        do
        {
            k = rand()%SAMPLES_NUM;
        }while(check(crand, k, i+1));
        crand[i] = k;
        for (j = 0; j < DIMENSION; j++)
        {
            (*(center+i)).vector[j] = (*(s+k)).vector[j];
        }
    }
    i = 1;
    //迭代计算
    do
    {
        cluster(center, x, s);
        printf("Iteration %d\n",i);
        i++;
    }while(calc_center(s, center) > 0);
    fclose(fp);
    if( (fw = fopen("out.txt", "w")) == NULL)
    {
        printf("eorror\n");
        exit(0);
    }
    for (i = 0; i < SAMPLES_NUM; i++)
    {
        fprintf(fw, "%d\n", (*(s+i)).cluster);
    }
    fclose(fw);
    free(s);
    free(center);
    printf("complete!\n");
    return 0;
}
