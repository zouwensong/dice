#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
struct key { 
  string word;
  int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0, //2
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,//25
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};
int casenum[100]={0};
void Print(int level);
void FileSearch(const char *file, int level);
int KeySearch(string str);
int main(){
	string file_path;
	int level;
	cout << "欢迎来到C语言代码关键字统计" << endl;
	cout << "请输入文件名与完成等级:" << endl;
	cin >> file_path >> level;
	FileSearch(file_path.c_str(), level);
	Print(level);
	return 0; 
}
void Print(int level){
	int sum = 0;
	for (int i = 0; i < 32; i++) {
		if(keytab[i].count != 0){
			if (level == 1) {
				cout << keytab[i].word << " num: " << keytab[i].count << endl;
			}
		}
		sum += keytab[i].count;
	}
	cout << "total num: " << sum << endl;
		if (level == 2) {
		  cout << "switch num: " << keytab[25].count << endl;
			cout << "case num: ";
		  for(int i = 0; i < keytab[25].count; i++)
			cout << casenum[i] << " " ;
		}
}
int KeySearch(string str){
	int index = -1;
	for (int i = 0; i < 32; i++) {
		if(keytab[i].word == str){
			keytab[i].count++;
			index = i;
			break;
		}
	}
	return index;
}
void FileSearch(const char *file, int level) {
	int index;
	FILE *fin;
	fin = fopen(file,"r"); 
	if (fin == NULL) {
		cout << "error!" << endl;
	}
  char c;
  string str;
  c = fgetc(fin);
	while (c != EOF) { //以单个字符读取,忽略空格回车 
	  //cout << c << endl;
	  if (c == '#') { //处理 头文件，快进 ——宏定义呢？？？ 
	  	while(c!='>'){
	  		c = fgetc(fin);
	  		if(c == '\n') break;
			}
		}
//		else if (c == ' ') { //处理 空格
//		  ;
//  	}
//		else if (c == '\n') { //处理 回车 
//		  ;
//		}
		else if (c == '\'' ) {//处理 单引号，快进
			c = fgetc(fin);
			while(c!= '\''){
				c = fgetc(fin);
			}
			c = fgetc(fin); 
		}
		else if (c == '"') {//处理双引号，快进 
		  c = fgetc(fin);
			while(c!='"'){
				c = fgetc(fin);
			}
			c = fgetc(fin);
		}
		else if (isalpha(c) || c=='_' || isalnum(c)) {//处理单词,这可以数字开头 
			string str;
			while(isalpha(c) && c=='_' || isalnum(c)){
				str += c;
				c = fgetc(fin);
			}
			//cout<<"THE WORD:"<<str<<endl;
			index = KeySearch(str);
			if (level == 2 ) {
				if (keytab[25].count!=0) {
					if(index == 2)casenum[keytab[25].count-1]++;
				}
			}
		}
		else if (c == '/') { //处理 注释行//和/* */ 
			c = fgetc(fin);
			if(c == '/'){
				while(c != '\n')
				  c = fgetc(fin);
			}
			if(c == '*'){
				while(c != '/')
				  c = fgetc(fin);
			}
		}
		else{
			c = fgetc(fin);
		}
	}
	fclose(fin);
}
