#ifndef _saomiaoqi_h
#define _saomiaoqi_h
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

// 定义保存单个扫描结果的数据结构 
struct token{
	
	short id;                 // token编码 
	string name;              // token符号或者是值 
	public:
		string toString(){
			string temp = "";
			short te = id;
			if(te > 0){
				 while(te){
					temp += ((te%10) + '0');
				    te = te / 10;
				}	
			}else if(te == 0){
				temp = "0";
			}else{
				temp = "-1"; // error code
			}
			
			reverse(temp.begin(), temp.end());
			return temp;
		}
};

class saomiaoqi{
	
	private:
		FILE * inputFile;
		FILE * outputFile;
		static const int maxn = 1000;
		char str1[maxn];
		char str2[maxn];
		string str0;             
		// 定义关键字表，其中关键字编码为其数组下标 
		const char keys[50][10] = {"#", "main", "if", "then", "while", "do", "static", "int", "double", "struct", "break", "else", "long", "switch", "case", "typedef", "char", "return", "const", "float", "short", "continue", "for", "void", "sizeof", "ID", "NUM", "+", "-", "*", "/", ";", ":=", "<", "<>", "<=", ">", ">=", "=", "default", "do", ":", "(", ")", "{", "}"};
		
		
	public:
		bool go(char* in, char* out);
		bool init(char * inputdir, char * outputdir);
		bool preprocess(char* in, char* out);
		bool scanner(const char * src, FILE * output, char * out);
		
		bool readfile(char * dir);
		bool writefile(char * dir);
		
		bool deletenote_space(const char* , char*);
		bool isIdentifier(char *, int s, int e);
		int isKeyword(const char *, int s, int e);
	public:
		//tools
		bool isAlpha(char c);
		bool isNum(char c);
		bool isDelimiter(char c);
		bool isOperator(char c); 
		bool isSpecial(char c);
		int hashtable(const char *src, int s, int e);		
	    int toInt(const char *src, int s, int e);
	
	public:
		saomiaoqi();
		~saomiaoqi();
};
#endif
/**/
