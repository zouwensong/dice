#include<iostream>
#include<fstream>
#include<string>
//#include<vector>
using namespace std;

struct key {
	string word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
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
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

void KeySearch(string str) {
	int n;
	for (int i = 0; i < 32; i++) {
		if ((n = str.find(keytab[i].word)) != string::npos) {
			keytab[i].count++;
			if (keytab[i].word == "double") {
				keytab[7].count--;
			}
		}
	}
}

void SearchFile(const char *file, int level) {
	ifstream infile;
	infile.open(file, ios::in);
	//instream infile(file);
	if(!infile.is_open()) {
		cout << "error! TAT" << endl;
	} else {
		/*char c;
		while((c=infile.get()) != EOF){
			cout << c <<endl; 
		}//一个个字符读取 
		infile.close();
		cout<<"HAPPY to Here.";*/
		string str;
		while(infile >> str) {
			KeySearch(str);
			cout << str << endl; 
		}//空格回车区分 
		infile.close();
	}
	/*
	string str; 
	while(getline(infile,str)) {
		cout << str << endl;
	}//以行读取，字符串
	
	char str[100];
	while(infile.getline(str, 100)) {
        cout << str << endl; 	
    }//字符数组 
	*/
}

void Print() {
	int sum = 0;
	for (int i = 0; i < 32; i++){
		if(keytab[i].count != 0)
		cout << keytab[i].word << " num: " << keytab[i].count << endl;
		sum += keytab[i].count;
	}
	cout << "total num：" << sum << endl;
}

int main() {
	string file_path;
	int level;
	cout<<"欢迎来到代码关键词提取 QAQ"<<endl<<"请输入文件名："<<endl;
	cin>>file_path;
	cout<<"请输入完成等级："<<endl<<"(注：等级从低到高为1-4)"<<endl; 
	cin>>level;
	SearchFile(file_path.c_str(), level); //c_str(): string to const char*
	Print();
	return 0;
}
