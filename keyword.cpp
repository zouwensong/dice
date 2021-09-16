#include<iostream>
#include<fstream>
#include<string>
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
// case 2  switch 25
int obj[100];
int KeySearch(string str) {//记得要试一试折半查找，返回值下标 
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
void CutWord(string str) {
	string newword;
	int i = 0,index;
	while (!isalpha(str[i])) {//使word以英文开头 
		i++;
	}
	for ( ; i < str.size(); i++) {
		if (!isalpha(str[i]) && str[i]!='_' && !isalnum(str[i])){//不是字母、数字、下划线时
			if (newword.size()>=2){//word长度大等2，原因关键字最短为do，长度2 
				//cout<<"__________ "<<newword<<" __________"<<endl;
				index = KeySearch(newword);
				if (keytab[25].count > 0 && index == 2) {//存在switch时，有case找到即加1 
					obj[keytab[25].count-1]++;
				}
			} 
			newword = "";
		}
		else{
			//cout<<"~"<<str[i]<<"~"<<endl;
			newword += str[i];
		}
	}
	if (newword != "") {//结尾时注意字符串是否为空 
		if (newword.size()>=2){
			//cout<<"__________  "<<newword<<"  _______"<<endl;
			index = KeySearch(newword);
			if (keytab[25].count > 0 && index == 2){
				obj[keytab[25].count-1]++;
	    	}
		}
	}
}
void SearchFile(const char *file, int level) {
	ifstream fin(file); //infile.open(file, ios::in);
	if (!fin.is_open()) {
		cout << "error!" << endl;
	} else {
		string str;
		while (fin >> str) { //以空格回车区分读取
			//cout << str << endl; // KeySearch(str) no!
			CutWord(str); //更细致的切割各小块 
		} 
		fin.close();
	}
}
void Print() {
	int sum = 0;
	for (int i = 0; i < 32; i++){ //统计总数 
		if(keytab[i].count != 0){
			if (i != 2) {
				cout << keytab[i].word << " num: " << keytab[i].count << endl;
			} else {
				cout << keytab[i].word << " num: ";
				for(int j=0; j < keytab[25].count; j++){
					cout << obj[j] << " ";
				}
				cout << endl;
			} 
		}
		sum += keytab[i].count;
	}
	cout << "total num：" << sum << endl;
	
}

int main() {
	string file_path;
	int level=1;
	cout<<"欢迎来到代码关键词提取"<<endl<<"完成等级：2"<<endl<<"(注：等级从低到高为1-4)"<<endl;
	cout<<"请输入文件名："<<endl;
	cin>>file_path;
	//cin>>level;
	SearchFile(file_path.c_str(), level); //file_path.c_str(): string to const char*
	Print();
	return 0;
}
