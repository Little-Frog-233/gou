#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
int main()
{
    double data[3] = {0.0};
    ifstream infile;//定义读取文件流，相对于程序来说是in
    infile.open("./TP.dat");//打开文件
    for(int i = 0; i < 3; i++)
    {
        infile >> data[i];//读取一个值（空格、制表符、换行隔开）就写入到矩阵中，行列不断循环进行
    }
    int length = (int)data[2];
    double * pt = (double*)malloc(sizeof(double)*2*length);
    for(int i = 0; i < 2*length; i++)
    {
        infile>>pt[i];
    }
    infile.close();//读取完成之后关闭文件

    cout <<fixed<<data[0]<<","<< data[1] <<','<<data[2]<< endl;//以下代码是用来验证读取到的值是否正确
    for(int i = 0; i < length; i++)
    {
        cout <<fixed<< pt[2*i] << "\t\t" << pt[2*i+1] << endl;
    }
    free(pt);
    return 0;
}
