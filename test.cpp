#include <stdio.h>
#include "saomiaoqi.h"
#include "saomiaoqi.cpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

//mian ��������Ϊ��Ҫɨ����ļ��ĵ�ַ �� ɨ��������ļ��ĵ�ַ 
int main(char *, char *){
    

    char in[100] = "";
    char out[100] = "";
    cout << "������Ҫɨ����ļ���ַ ��ɨ�����ĵ�ַ��"  << endl;
    scanf("%s %s", in, out);
    saomiaoqi * ss = new saomiaoqi();
    ss->go(in, out);  
    system("pause");

    return 0;
}
