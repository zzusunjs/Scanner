#ifndef _saomiaoqi_cpp
#define _saomiaoqi_cpp
#include "saomiaoqi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;
/*
	Name: saomiaoqi.cpp 
	Copyright: 
	Author: jss
	Date: 17/03/17 16:32
	Description: ʵ�� 
*/

// ���캯������ָ����Ϊ��ֵ, ��Ա������ʼ�� 
saomiaoqi::saomiaoqi(){
	this->inputFile = NULL;
	this->outputFile = NULL;
	memset(str1, 0, sizeof(str1));
	memset(str2, 0, sizeof(str2));
	
}
// fclose the file read/write pointer
saomiaoqi::~saomiaoqi(){
	if(inputFile != NULL){
	  fclose(inputFile);
	}
	if(outputFile != NULL){
	  fclose(outputFile);
	}

}
// ���������������ɨ�����Ĺ��� 
bool saomiaoqi::go(char* in, char* out){
    
    if(in == NULL || out == NULL){
    	return false;
    } else{
    	return(init(in, out) && preprocess(in, out) && scanner(str1, this->outputFile, out));
    }
	
}
// Ԥ���������ļ���ɾ���ո񣬻س������У��Ʊ�� 
bool saomiaoqi::preprocess(char* in ,char * out){
	if(in == NULL || out == NULL){
	 	return  false;
	 }else{
	 	deletenote_space(str0.c_str(), str1);
	 }
	 /*
	 if(this->outputFile != NULL){
	 	fputs(str1, outputFile);
		fputs("********************************line*********************************\n", outputFile);	
	 } */
	 cout << "Ԥ����Ľ����:\n" << str1 << endl;
	return true;
}
//��ʼɨ�裬����token���е��ļ� 
bool saomiaoqi::scanner(const char *src, FILE * output, char * out){
	
	token tok;
	int ans = 0;
	string res = "";
	 if(src == NULL || output == NULL){
	 	return false;
	 }else{
	 	int len = strlen(src), prepointer = 0;
	 	for(int i=0; i<len; ++i){
	 		
	 	//	cout << "test in for loop " << i << endl;
	 		if(isAlpha(src[i])){                 //����һ����ʶ���������ǹؼ���,����ĸ����ĸ�����»��� 
	 			int j=i+1;
	 			while(j<len && isAlpha(src[j]) || (j<len && isNum(src[j]))){
	 				j++;
	 			}
	
	 			if((ans = isKeyword(src, i, j-1)) >= 0){ //�ؼ��� 
	 		        tok.id = ans;
					tok.name = "";
					tok.name += keys[ans];
					res += tok.toString();
					res += "  ";
					res += tok.name;
					res += "\n";		
	 			}else{                                   //��ʶ�� 
	 				tok.id = 25;
	 				tok.name = "";
	 				for(int k=i; k<j; ++k){
	 					tok.name += src[k];
	 				}
	 				res += tok.toString();
					res += "  ";
					res += tok.name;
					res += "\n";
	 			}
	 			i = j-1; 
	 			
	 		}else if(isNum(src[i])){              // ����ĸ������ 
	 			int j=i+1;
	 			while( (j<len && isNum(src[j])) ){  //�����ֵĻ� 
	 				j++;
	 			}
	 			tok.id = toInt(src, i, j-1);
	 			tok.name = "26  ";
	 			res += tok.name;
	 			res += tok.toString();
	 			res += "\n";
				 
				i = j; 
	 		}else if(isOperator(src[i])){                 //����ĸ������� 
	 		
	 		    //cout << src[i] << " operator" << endl;
	 			int j=i+1;
	 			if(j<len && isOperator(src[j])){           //�����ַ�������� 
	 			  tok.id = hashtable(src, i, j);
	 			  tok.name = "";
				  tok.name += src[i];
				  tok.name += src[j];
				  
				  res += tok.name;
				  res += "  ";
				  res += tok.toString();
				  res += "\n";
	 			  i = j;  	
	 			}else{                                     // �����ַ�������� 
	 			
	 			  tok.id = hashtable(src, i, i);           //�����ϣ��ֱ�ӷ�����Ӧ�Ĵ��� 
	 			  tok.name = "";
				  tok.name += src[i];
				  
				  res += tok.toString();
				  res += "  ";
				  res += tok.name;
				  res += "\n";	 
	 			}
	 			
	 		}else if(isDelimiter(src[i])){                //�ָ������ǵ����ַ� 
	 			
	 			//cout << src[i] << " delimiter " << endl; 
	 			tok.id = hashtable(src, i, i);
	 			tok.name =  "";
	 			tok.name += src[i];
	 			
	 			  res += tok.toString();
	 			  res += "  ";
	 			  res += tok.name; 
				  res += "\n";
				
	 		}else if(isSpecial(src[i])){
	 			  
	 			   
	 			
	 		}else{
	 		    //cout << src[i] << "  undeal " << endl;
	 		}
	 	} 
	 	fputs(res.c_str(), output);
	 	
	 }//else if end
	 cout << "ɨ�����Ѿ�д���ļ� " <<  out << endl;
     return true; 
}
// build the read  file pointer;
bool saomiaoqi::readfile(char * dir){
      
	if(dir == NULL){
	   return false;
	}else{
	   inputFile = fopen(dir, "r");
	   if(inputFile == NULL){
	      return false;
	   }else{
	      return true;
	   }
	}
}
// build the output file pointer;
bool saomiaoqi::writefile(char * dir){
	if(dir == NULL){
	   return false;
	}else{
	   outputFile = fopen(dir, "w+");
	   if(outputFile == NULL){
	      return false;
	   }else{
	      return true;
	   }
	}
}
//���ļ��ж������ 
bool saomiaoqi::init(char * inputdir, char* outputdir){
	
	if(inputdir == NULL || outputdir == NULL){
	   return false;
	}else{
	     bool read = false, write = false;
		 read = this->readfile( inputdir );
		 write = this->writefile( outputdir );
		 if(read && write){
              while(fgets(this->str1, maxn-1, inputFile) != NULL){
                     str0 += str1;
              }      
		     return true;
		 }else{
		     return false;
		 }
	}
	return false;
}

bool saomiaoqi::deletenote_space(const char* src, char* dest){
     
     if(src == NULL || dest == NULL){
     	return false;
     }
     int wrpointer = 0, len = str0.length();
     for(int i=0; i<str0.length(); i++){
         if(src[i] == '/'){                                      // ɾ��ע�� 
            if(i+1 < strlen(src) && src[i+1] == '/'){            // ��ע�� 
                   i += 2;
                   while(src[i] != '\n'){
                   i++;
                   }
            }else if(i+1 < strlen(src) && src[i+1] == '*'){       // ��ע�ͣ����ƥ��ԭ�� 
                  i += 2;
                  while(i < strlen(src) && src[i] != '*'){
                      i++;              
                  }
                  if(i < strlen(src) && src[i] == '*'){
                     if(i+1 < strlen(src) && src[i+1] == '/'){
                          i+=2;       
                     }     
                  }
            }       
         }else if(src[i] == ' '){                                  // ɾ��' ', '\t' '\n' 
	  	        dest[wrpointer++] = src[i];
	  	        while( (i+1 < len && src[i+1] == ' ') || (i+1 < len && src[i+1] == '\n') || (i+1 < len && src[i+1] == '\t')){
	  	  	   	i++;
	  	  	    }
		 }else if(src[i] == '\n'){
				dest[wrpointer++] = ' ';
				while( (i+1 < len && src[i+1] == ' ') || (i+1 < len && src[i+1] == '\n') || (i+1 < len && src[i+1] == '\t') ){
	  	  	   	i++;
	  	  	   }
		 }else if(src[i] == '\t'){
				dest[wrpointer++] = ' ';
				while( (i+1 < len && src[i+1] == ' ') || (i+1 < len && src[i+1] == '\n') || (i+1 < len && src[i+1] == '\t')){
	  	  	   	i++;
			    }
	  	 }else{
            dest[wrpointer++] =  src[i];   
         }        
     }
     return true;
}
// �ж��Ƿ���һ����ʶ�� 
bool saomiaoqi::isIdentifier(char* src, int s, int e){
	
	  if(src == NULL || (e - s + 1) < 0){
	  	return false;
	  }else{
	        int len = e - s + 1;	
	  	    if(!isAlpha(src[s]) && src[s] != '_'){   //�ж����ַ��Ƿ�Ϸ� 
	  			return false;
	     	}else{
	     	    for(int i=s+1; i<=e; ++i){
	  	 	       if( src[i] != '_' && !isNum(src[i]) && !isAlpha(src[i])){
	  	 	   	   return false;
	  	 	     }
	  	    }
	  }
	  	    return true;
	  }
}
// �ж��Ƿ�Ϊ�ؼ��ֲ����ر��� -1Ϊ������� 
int saomiaoqi::isKeyword(const char * src, int s, int e){
	if(src == NULL || (e - s + 1) < 0){
	  	return false;
	}else{
	    int len = e - s + 1, res = 0;
	    char temp[100] = "";
	    for(int i=s, j=0; i<=e; i++){
	    	temp[j++] = src[i];
	    }
	    for(int i=0; i<=43; ++i){
	    	if(strcmp(temp, this->keys[i]) == 0){
	    		return i;
	    	}
	    }
	} 
	return -2;   // �ǹؼ��� 
} 
/****************************tool**************************/
bool saomiaoqi::isAlpha(char ch){
	 if(ch >= 'a' && ch <= 'z'){
	 	return true;
	 }else if(ch >= 'A' && ch <= 'Z'){
	 	return true;
	 }else if(ch == '_'){
	 	return true;
	 } 
	return false;
}
bool saomiaoqi::isNum(char ch){
	if(ch >= '0' && ch <= '9'){
		return true;
	} 
    return false;
}
int saomiaoqi::toInt(const char *src, int s, int e){
	
	if(src == NULL || (e-s+1) < 1){
		return 0;
	}else{
		 int ss = 0 ;
		for(int i=s; i<=e; ++i){
			ss = ss * 10 + (int)(src[i] - '0');
		}
	   return ss;
	} 
}
// �ָ����ж� 
bool saomiaoqi::isDelimiter(char ch){
	 if(ch == '{' || ch == '}' || ch == '(' || ch == ')'){
	 	return true;
	 } 
	 if(ch == ';' || ch == '#'){
	 	return true;
	 } 
	 
	return false;
}
// �ж�һ���ַ��ǲ�������� 
bool saomiaoqi::isOperator(char ch){
	
	 	if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
		 	return true;
		} 
		if(ch == '=' || ch == ':' || ch == '<' || ch == '>'){
		 	return true;
		}
	 
	return false;
}
bool saomiaoqi::isSpecial(char ch){
	return false;
}
int saomiaoqi::hashtable(const char *src, int s, int e){
	
	if(src == NULL || (e-s+1) < 1){
		return -1;
	}
	char temp[100] = "";
	strncpy(temp, &src[s], e-s+1);
	for(int i=0; i<46; i++){
		if(strcmp(temp, keys[i]) == 0){
			return i;	
		}
	}
	return 0;
}		
#endif
