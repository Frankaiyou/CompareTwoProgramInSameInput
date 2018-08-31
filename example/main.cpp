#include<algorithm>
#include<cstdio>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<windows.h>
#define N 1000
using namespace std;

struct File{
	string str,name,type;
	File(){}
	File(string n,string t){name=n,type=t,str=name+type;}
	void input(){
		string temp;
		cin>>temp;cin>>temp;
		bool flag=0;
		for(int i=0;i<temp.size();++i)
			if(temp[i]=='.')
				name=temp.substr(0,i),type=temp.substr(i,temp.size()-i),flag=true;
		if(!flag){name=temp;type=".cpp";}
		str=name+type;
	}
};

File data, Std, My, Infile, Outfile, Tempfile;

void Compile(File file){
	string Mingling;
	Mingling="g++ "+file.str+" -O2 -o "+file.name;
	cout<<Mingling<<endl;
	system(Mingling.c_str());
}
int RunProgram(File n,File in,File out){
	string Ml=n.name+" >"+out.str+" <"+in.str;
	cout<<Ml<<endl;
	return system(Ml.c_str());
}
int RunProgram(File n, File out) {
	string Ml=n.name+" >"+out.str;
	cout<<Ml<<endl;
	return system(Ml.c_str());
}
bool FC(File my, File std) {
	string ml = "fc "+my.str+" "+std.str;
	return system(ml.c_str());
}
void init(){
	data.input(),Std.input(), My.input();
	Infile.input(),Outfile.input();
	Compile(data);Compile(Std);Compile(My);
}

void Make(){
	string id;File ouf1,ouf2,inf;
	ouf1=File(Outfile.name+"std",Outfile.type);
	ouf2=File(Outfile.name+"my",Outfile.type);
	inf=File(Infile.name,Infile.type);
	while (true) {
		RunProgram(data,inf);
		RunProgram(Std,inf,ouf1);
		RunProgram(My, inf,ouf2);
		if (FC(ouf1, ouf2)) break;
	}
}

int main(){
	freopen("settings.txt","r",stdin);
	init(),Make();
	return 0;
}