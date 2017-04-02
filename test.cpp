#include <stdio.h>
#include "saomiaoqi.h"
#include "saomiaoqi.cpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

//mian 函数参数为需要扫描的文件的地址 和 扫描结果输出文件的地址 
int main(char *, char *){
    

    char in[100] = "";
    char out[100] = "";
    cout << "请输入要扫描的文件地址 和扫描结果的地址："  << endl;
    scanf("%s %s", in, out);
    saomiaoqi * ss = new saomiaoqi();
    ss->go(in, out);  
    system("pause");

    return 0;
}
