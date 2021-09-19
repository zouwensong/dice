#include<iostream>
#include<string>
#include<cstdio>
#include<stack>
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
	"else", 0,//9 
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,//15
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
stack<int>s;
int ie_count=0;
int iee_count=0;
//void text();
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
	    while(!s.empty()){
				cout << s.top() << endl;
				s.pop();
			}
	Print(level);
	return 0;
}
/*void text(){//已经压了新东西进栈，做检查
	if(s.top() == 2){//是else时判断 
		s.pop();//把2拿出来
		if(s.top()==1){
			s.pop();
			iee_count+=1;
		}
		if(s.top()==3){
			while(s.top()!=1) s.pop();
			s.pop();
			ie_count+=1;
		}
	}
}*/
void Print(int level){
	int sum = 0;
	cout << "详情：" << endl; 
	for (int i = 0; i < 32; i++) {
		if(keytab[i].count != 0){
				cout << keytab[i].word << " num: " << keytab[i].count << endl;
		}
		sum += keytab[i].count;
	}
	cout << "------------------------------" << endl;
	cout << "total num: " << sum << endl;
	if (level >= 2) {
		  cout << "switch num: " << keytab[25].count << endl << "case num: ";
		  if(keytab[25].count == 0) {
		  	cout << "0" << endl;
			}
			else{
				for(int i = 0; i < keytab[25].count; i++)
				cout << casenum[i] << " " ;
				cout << endl;
			}
			if(level >= 3){
				cout <<"if-else num: ";
				cout << ie_count << endl;
			}
			if(level >= 4){
				cout<<"if-elseif-else num: ";
				cout<<iee_count<<endl;
			}
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
	  if (c == '#') { //处理 头文件,宏定义，快进 
	  	while(c!='>'){
	  		c = fgetc(fin);
	  		if(c == '\n') break;
			}
		}
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
			index = KeySearch(str);
			//cout<<"THE WORD:"<<index<<" "<<str<<endl;
			if (level >= 2) { //进阶、拔高和终极要求 
				if (keytab[25].count != 0) {
					if(index == 2) casenum[keytab[25].count-1]++;
				}
				if (index == 15){//匹配到if-1
					s.push(1);
				}
				if (index == 9) {//准备检查匹配到哪个 else-2;else if-3
				//此时c已经不是字母、数字、下划线了呢，很可能是空格哦
				  int flag=0;
				  //cout<<"THAT:"<<c;
				  while(c==' ' || c=='\n' || c=='\t') c=fgetc(fin);
				  //cout<<"AND:"<<c;
					if(c=='i'){
						if((c=fgetc(fin))=='f'){ //匹配到else if
							if(!s.empty()&&(s.top()!=3)) s.push(3);
							flag=1;
							keytab[15].count++;
						}
						//cout<<"THIS: "<<c<<endl;
					}
					if(flag==0){ //匹配到else 
						//s.push(2);
						if(!s.empty()&&(s.top()==1)){
							ie_count++;
							s.pop();
						}
						else if(!s.empty()&&(s.top()==3)){
							s.pop();
							if(!s.empty()&&(s.top()==1)){
								iee_count++;
								s.pop();
							}
						}
					}
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
		else{ //处理  空格、回车等等 fseek(fin,-1L,SEEK_CUR);fseek(source,-1L,1); //回退,读到了下一个字符
			c = fgetc(fin);
		}
	}
	fclose(fin);
}
