#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<string.h>	
#include "vector" 
using namespace std;
#define NUM 4			//表达式元数
#define regist_num 2

string record;		//记录结果
/*
	寄存器数组
	name:名字
	used:是否使用
	contin:寄存器内存放的内容
*/
class regist {
public:
	string name;
	bool used;
	string contin;
};

/*
	类似JAVA中的split方法
*/
vector<string> split(string str, string separator) {
	vector<string> result;
	int cutAt;
	while ((cutAt = str.find_first_of(separator)) != str.npos) {
		if (cutAt>0) {
			result.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length()>0) {
		result.push_back(str);
	}
	return result;
}

/*
	标记 J 表达式所跳位置
	name：重命名
	second：序号
*/
class signal {
public:
	string name;
	int second;
};

/*
	保存每一条四元表达式
	second：序号
	code：四项元
*/
class middlecode {
public:
	int second;
	vector<string> Code;
	string code[NUM];
};

/*
	记录重复变量出现的次数及变量名
	value:变量名
	num:次数
*/
class revalue {
public:
	string value;
	int num;
};
/*
	ScanSourceCode():扫描并重新记录四元表达式
	renamesig()：标记J表达式所转移地址
	find();//寻找某个数组中是否存在某个元素，返回值为负值代表不存在
	getvaluenum()：返回非J表达式中变量个数
	Isinregist() ：查看变量是否在寄存器中，返回值代表出现次数，0代表不存在
	getregist() ：返回当前合适的寄存器序号
	initregist(): 初始化寄存器
	main(): 生成汇编语言
*/
class middle2finale {
public:
	int Count;		//四元表达式条数
	int J_count;	//跳转地址数量
	middlecode *code;	//新的四元表达式
	signal *sig;		//J表达式所转移的位置
	int signum;			//转移地址个数
	revalue* value;		//变量
	int valuenum;		//变量个数
	regist *reg;		//寄存器数组
	void ScanSourceCode()
	{
		int pos,i,count=0;
		char c;
		Count = 0;
		string s;
		ifstream fin;
		fin.open("out2.txt", ios::in);
		while (!fin.eof()) {
			Count++;
			getline(fin, s);
		}
		Count--;
		fin.close();
		fin.open("out2.txt", ios::in);
		code = new middlecode[Count];
		for (; count < Count;count++)
		{
			int begin = 0;		//标记四元表达式中每一项开始位置
			char temp = ':';
			getline(fin, s);
			for (i = 0; i < s.length();i++) {
				if(s[i]==temp)
					break;
			}
			code[count].second = atoi(s.substr(0, i).c_str());
			code[count].Code = split(s.substr(i + 3),",");
			i = 0;
			vector<string>::iterator it;
			for (vector<string>::size_type ix = 0; ix != code[count].Code.size(); ix++)
			{
				code[count].code[ix] = code[count].Code[ix];
			}
		}
		fin.close();
/*
//调试
		for (int i = 0; i < Count; i++) {
			printf("%d:%s,%s,%s,%s\n", code[i].second, code[i].code[0].c_str(), code[i].code[1].c_str(), code[i].code[2].c_str(), code[i].code[3].c_str());
		}
*/
		return;
	}

	void renamesig() {
		J_count = 0;
		int *temp=new int[Count];		//描述哪个表达式为J,call,ret
		for (int i = 0; i < Count; i++) {
			if (code[i].code[0][0] == 'j'|| code[i].code[0] == "call") {
				J_count++;
				temp[i] = 1;
			}
			else
				temp[i] = 0;
		}
		sig = new signal[J_count];
		int j = 0;	//循环初始sig
		for (int i = 0; i < Count; i++) {
			if (temp[i] == 1) {
				int temp = atoi(code[i].code[3].c_str());
				sig[j].second = temp;
				j++;
			}
		}
		for (int i = j-1; i >0; i--)
			for (int t = i-1; t >=0; t--) {
				if (sig[i].second < sig[t].second) {
					int swap = sig[i].second;
					sig[i].second = sig[t].second;
					sig[t].second = swap;
				}
			}
		for (int i = 0; i < j; i++) {
		}
		int temp_count=0;
		signum = J_count;
		for (int i = 0; i < j;i++) {
			if (i==0||i==j-1||sig[temp_count +1].second>sig[temp_count].second) {
				string NUMBER;
				NUMBER = to_string(temp_count);
				sig[temp_count++].name = "L" + NUMBER;
			}
			else {
				for (int t = i; t < signum - 1; t++) {
					sig[t].second = sig[t + 1].second;
				}
				signum--;
			}
		}
		delete []temp;
/*
//测试
		cout << signum << endl;
		for (int i = 0; i < signum; i++) {
			printf("%d:%s\n", sig[i].second, sig[i].name.c_str());
		}
		system("pause");
		*/
	}

	void getvaluenum() {
		string *temp = new string[Count - J_count];
		int i = 0, j = 0;
		for (i = 0; i < Count; i++)
		{
			if (code[i].code[0][0] != 'j'&&code[i].code[0] != "call")
			{
				//printf("temp[%d]=code[%d].code[3].c_str,%s\n",j,i,code[i].code[3].c_str());
				temp[j++] = code[i].code[3].c_str();
			}
		}
		valuenum = j;
		for (i = 0; i < Count - J_count-1; i++)
			for (j = i+1; j < Count - J_count; j++) {
				if (temp[i].compare(temp[j])==0) {
				//	printf("temp[%d]=temp[%d]\n", i, j);
					valuenum--;
					break;
				}
			}
		delete []temp;
	}

	int find(revalue *arr,int count,string value) {
		for (int i = 0; i < count; i++) {
			if (arr[i].value == value)
				return i;
		}
		return -1;
	}

	void initvalue() {
		int temp = 0;	//循环初始化value
		value = new revalue[valuenum];
		for (int i = 0; i < Count; i++) {
			if (code[i].code[0][0] == 'j'||code[i].code[0] =="call")
				continue;
			int	ret =find(value, temp, code[i].code[3]);
			if (temp == 0||ret<0)
			{
				value[temp].value = code[i].code[3].c_str();
				value[temp++].num = 1;

			}
			else {
				value[ret].num++;
			}
		}
		/*
//测试
		for (int i = 0; i < 10; i++) {
			printf("%d---%d:%s\n", i, value[i].num, value[i].value.c_str());
		}
		*/
	}

	int Isinregist(regist* reg, string r_value) {
		for (int i = 0; i < regist_num; i++) {
			if (reg[i].used = 1) {
				if (reg[i].contin == r_value) {
					return i+1;
				}
				break;
			}
		}
		return 0;
	}

	int getregist(regist* reg,int count) {
		for (int i = 0; i < regist_num; i++) {
			if (value[find(value, valuenum, reg[(count + i) % regist_num].contin)].num == 1) {
				reg[(count + i) % regist_num].used= 0;
				reg[(count + i) % regist_num].contin = "";
		}
		for (int i = 0; i < regist_num; i++) {
			if (reg[(count + i) % regist_num].used == 0)
				return (count + i) % regist_num;
			}
		}
		return count % regist_num;
	}

	void initregist() {
		reg = new regist[regist_num];
		for (int i = 0; i < regist_num; i++) {
			reg[i].used = 0;
			string temp = to_string(i);
			reg[i].name = "R" + temp;
			reg[i].contin = "";
			//printf("reg%d:%s\n", i, reg[i].name.c_str());
		}
	}

	void _main() {
		//cout << "begin" << endl;

		ScanSourceCode();
		renamesig();
		getvaluenum();
		initvalue();
		initregist();
		record = "";
		int j_c = 0;		//与J_count有关，循环达到j_count
		int count = 0;		//计数，使得选取寄存器时尽量分散
		int tem_reg;
		for (int i = 0; i < Count; i++) {
			if (code[i].second == sig[j_c].second) {
				printf("%s\n", sig[j_c++].name.c_str());
				record += sig[j_c++].name + '\n';
			}
			string temp = code[i].code[0].c_str();
			if (temp == ":=") {
				tem_reg = getregist(reg, count++);
				if (reg[tem_reg].used) {
					printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
					record += "  ST," + reg[tem_reg].name + "," +reg[tem_reg].contin.c_str() + '\n';
				}
				reg[tem_reg].used = 1;
				reg[tem_reg].contin = code[i].code[3];
				printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
				record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
				printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[3].c_str());
				record += "  ST," + reg[tem_reg].name + "," + code[i].code[3].c_str() + '\n';
				value[find(value, valuenum, code[i].code[3])].num--;
			}
			else if (temp == "ret" || code[i].code[3] == "NULL") {
				string value1;
				int ret1;
				if (ret1 = Isinregist(reg, code[i].code[1])) {
					value1 = reg[ret1 - 1].name;
					value[find(value, valuenum, code[i].code[1])].num--;
					printf("  ret,%s\n", value1.c_str());
					record += "  ret," + value1 + '\n';
				}
				else {
					tem_reg = getregist(reg, count++);
					if (reg[tem_reg].used) {
						printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
						record += "  ST," + reg[tem_reg].name + "," + reg[tem_reg].contin.c_str() + '\n';
					}
					printf("  ret,%s\n", reg[tem_reg].name.c_str());
					record += "  ret," + reg[tem_reg].name + '\n';
				}
			}
			else if (temp == "*" || temp == "+" || temp == "-") {
				string value1, value2;
				int ret1, ret2;
				if (ret1 = Isinregist(reg, code[i].code[1])) {
					value1 = reg[ret1 - 1].name;
					value[find(value, valuenum, code[i].code[1])].num--;
				}
				if (ret2 = Isinregist(reg, code[i].code[2])) {
					value2 = reg[ret2 - 1].name;
					value[find(value, valuenum, code[i].code[2])].num--;
				}
				tem_reg = getregist(reg, count++);
				if (reg[tem_reg].used) {
					printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
					record += "  ST," + reg[tem_reg].name + "," + reg[tem_reg].contin.c_str() + '\n';
				}
				string symble;			//判断是*或+或-
				if (temp == "*")
					symble = "MUL";
				else if (temp == "+")
					symble = "ADD";
				else
					symble = "SUB";
				if (ret1 > 0) {
					if (ret2 > 0)			//形如 *,T0,T1,T2
					{
						printf("  %s,%s,%s\n", symble.c_str(), value1.c_str(), value2.c_str());
						record += "  " + symble + "," + value1 + "," + value2 + '\n';
						reg[ret1 - 1].contin = code[i].code[3];
					}
					else
					{
						int re2 = find(value, valuenum, code[i].code[2]);
						if (re2 >= 0) {		//形如*,T0,a,T2
							int tem_reg2 = getregist(reg, count++);
							if (reg[tem_reg2].used) {
								printf("  ST,%s,%s\n", reg[tem_reg2].name.c_str(), reg[tem_reg2].contin.c_str());
								record += "  ST," + reg[tem_reg2].name + "," + reg[tem_reg2].contin.c_str() + '\n';
							}
							printf("  LD,%s,%s\n", reg[tem_reg2].name.c_str(), code[i].code[2].c_str());
							record += "  LD," + reg[tem_reg2].name + "," + code[i].code[2].c_str() + '\n';
							printf("  %s,%s,%s\n", symble.c_str(), value1.c_str(), reg[tem_reg2].name.c_str());
							record += "  " + symble + "," + value1 + "," + value2 + '\n';
							reg[ret1 - 1].contin = code[i].code[3];
							reg[tem_reg2].contin = code[i].code[2];
						}
						else {				//形如*,T0,1,T2
							printf("  %s,%s,%s\n", symble.c_str(), value1.c_str(), code[i].code[2].c_str());
							record += "  " + symble + "," + value1 + "," + code[i].code[2].c_str() + '\n';
							reg[ret1 - 1].contin = code[i].code[3];
						}
					}
				}
				else if (ret2 > 0) {
					int re1 = find(value, valuenum, code[i].code[1]);
					if (re1 >= 0) {					//形如 *,a,T0,T1
						printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
						record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
						printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), value2.c_str());
						record += "  " + symble + "," + reg[tem_reg].name + "," + value2 + '\n';
						reg[tem_reg].contin = code[i].code[3];
					}
					else {							//形如 *,1,T0,T1
						if (symble == "MUL" || symble == "ADD") {
							printf("  %s,%s,%s\n", symble.c_str(), value2.c_str(), code[i].code[1].c_str());
							record += "  " + symble + "," + value2 + "," + code[i].code[1].c_str();
							reg[ret2 - 1].contin = code[i].code[3].c_str();
						}
						else {
							printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
							record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
							printf("  SUB,%s,%s\n", reg[tem_reg].name.c_str(), value2.c_str());
							record += "  SUB," + reg[tem_reg].name + "," + value2 + '\n';
							reg[tem_reg].contin = code[i].code[3];
						}
					}
				}
				else {
					int re1 = find(value, valuenum, code[i].code[1]);
					int re2 = find(value, valuenum, code[i].code[2]);
					if (re1 >= 0) {
						printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
						record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
						if (re2 >= 0) {					//形如 *,a,b,T0
							int tem_reg2 = getregist(reg, count++);
							if (reg[tem_reg2].used) {
								printf("  ST,%s,%s\n", reg[tem_reg2].name.c_str(), reg[tem_reg2].contin.c_str());
								record += "  ST," + reg[tem_reg2].name + "," + reg[tem_reg2].contin.c_str() + '\n';
							}
							printf("  LD,%s,%s\n", reg[tem_reg2].name.c_str(), code[i].code[2].c_str());
							record += "  LD," + reg[tem_reg2].name + "," + code[i].code[2].c_str() + '\n';
							printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), reg[tem_reg2].name.c_str());
							record += "  " + symble + "," + reg[tem_reg].name + "," + reg[tem_reg2].name + '\n';
							reg[tem_reg].contin = code[i].code[3];
							reg[tem_reg2].contin = code[i].code[2];
						}
						else {							//形如 *,a,1,T0
							printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), code[i].code[2].c_str());
							record += "  " + symble + "," + reg[tem_reg].name + "," + code[i].code[2] + '\n';
							reg[tem_reg].contin = code[i].code[3];
						}
					}
					else {
						if (symble == "SUB") {
							printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
							record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
							if (re2 >= 0) {				//形如 -,1,a,t0
								int tem_reg2 = getregist(reg, count++);
								if (reg[tem_reg2].used) {
									printf("  ST,%s,%s\n", reg[tem_reg2].name.c_str(), reg[tem_reg2].contin.c_str());
									record += "  ST," + reg[tem_reg2].name + "," + reg[tem_reg2].contin.c_str() + '\n';
								}
								printf("  LD,%s,%s\n", reg[tem_reg2].name.c_str(), code[i].code[2].c_str());
								record += "  LD," + reg[tem_reg2].name + "," + code[i].code[2].c_str() + '\n';
								printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), reg[tem_reg2].name.c_str());
								record += "  " + symble + "," + reg[tem_reg].name + "," + reg[tem_reg2].name + '\n';
								reg[tem_reg].contin = code[i].code[3];
								reg[tem_reg2].contin = code[i].code[2];
							}
							else {						//形如 -,2,1,T0
								printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), code[i].code[2].c_str());
								record += "  " + symble + "," + reg[tem_reg].name + "," + code[i].code[2] + '\n';
								reg[tem_reg].contin = code[i].code[3];
							}
						}
						else {							//+或者*
							if (re2 >= 0) {				//形如 *,1,a,T0
								printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[2].c_str());
								record += "  LD," + reg[tem_reg].name + "," + code[i].code[2].c_str() + '\n';
								printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), code[i].code[1].c_str());
								record += "  " + symble + "," + reg[tem_reg].name + "," + code[i].code[1] + '\n';
							}
							else {						//形如 *,2,3,T0
								printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
								record += "  LD," + reg[tem_reg].name + "," + code[i].code[1].c_str() + '\n';
								printf("  %s,%s,%s\n", symble.c_str(), reg[tem_reg].name.c_str(), code[i].code[2].c_str());
								record += "  " + symble + "," + reg[tem_reg].name + "," + code[i].code[2] + '\n';
							}
							reg[tem_reg].contin = code[i].code[3];
						}
					}
				}
			}
			else if (temp == "j" || temp == "call") {
				string tem_str;
				for (int t = 0; t < signum; t++) {
					if (atoi(code[i].code[3].c_str()) == sig[t].second) {
						tem_str = sig[t].name;
						break;
					}
				}
				if (temp == "j") {
					record += "  JMP," + tem_str + '\n';
					printf("  JMP,%s\n", tem_str.c_str());
				}

				else {
					record += "  " + temp + "," + tem_str + '\n';
					printf("  %s,%s\n", temp.c_str(), tem_str.c_str());
				}
			}
			else if (temp == "j>" || temp == "j>=" || temp == "j<" || temp == "j<=") {
				string tem_str;					//跳转地址
				for (int t = 0; t < J_count; t++) {
					if (atoi(code[i].code[3].c_str()) == sig[t].second) {
						tem_str = sig[t].name;
						break;
					}
				}
				string value1, value2;
				int ret1, ret2;				//测试两个操作数是否都在寄存器中
				if (ret1 = Isinregist(reg, code[i].code[1])) {
					value1 = reg[ret1 - 1].name;
					value[find(value, valuenum, code[i].code[1])].num--;
				}
				if (ret2 = Isinregist(reg, code[i].code[2])) {
					value2 = reg[ret2 - 1].name;
					value[find(value, valuenum, code[i].code[2])].num--;
				}
				tem_reg = getregist(reg, count++);
				if (reg[tem_reg].used) {
					printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
					record += "  ST," + reg[tem_reg].name + "," + reg[tem_reg].contin + '\n';
				}
				string symble;			//判断是什么符号
				if (temp == "j>")
					symble = "JG";
				else if (temp == "j>=")
					symble = "JGE";
				else if (temp == "j<")
					symble = "JNGE";
				else
					symble = "JNG";
				if (ret1 > 0) {
					if (ret2 > 0)			//形如 j<,T0,T1,3
					{
						printf("  %s,%s,%s\n", "CMP", value1.c_str(), value2.c_str());
						record += "  CMP," + value1 + "," + value2 + '\n';
						printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
						record += "  " + symble + "," + tem_str + '\n';
					}
					else
					{
						int re2 = find(value, valuenum, code[i].code[2]);
						if (re2 >= 0) {		//形如j<,T0,a,3
							int tem_reg2 = getregist(reg, count++);
							if (reg[tem_reg2].used) {
								printf("  ST,%s,%s\n", reg[tem_reg2].name.c_str(), reg[tem_reg2].contin.c_str());
								record += "  ST," + reg[tem_reg2].name + "," + reg[tem_reg2].contin + '\n';
							}
							printf("  LD,%s,%s\n", reg[tem_reg2].name.c_str(), code[i].code[2].c_str());
							record += "  LD," + reg[tem_reg2].name + "," + code[i].code[2] + '\n';
							printf("  %s,%s,%s\n", "CMP", value1.c_str(), reg[tem_reg2].name.c_str());
							record += "  CMP," + value1 + "," + reg[tem_reg2].name + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
							reg[tem_reg2].contin = code[i].code[2];
						}
						else {				//形如j<,T0,1,3
							printf("  %s,%s,%s\n", "CMP", value1.c_str(), code[i].code[2].c_str());
							record += "  CMP," + value1 + "," + code[i].code[2] + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
						}
					}
				}
				else if (ret2 > 0) {
					int re1 = find(value, valuenum, code[i].code[1]);
					if (re1 >= 0) {					//形如 j<,a,T0,3
						printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
						record += "  LD," + reg[tem_reg].name + "," + code[i].code[1] + '\n';
						printf("  %s,%s,%s\n", "CMP", reg[tem_reg].name.c_str(), value2.c_str());
						record += "  CMP," + reg[tem_reg].name + "," + value2 + '\n';
						printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
						record += "  " + symble + "," + tem_str + '\n';
						reg[tem_reg].contin = code[i].code[1];
					}
					else {							//形如 j<,3,T0,3
						printf("  %s,%s,%s\n", "CMP", code[i].code[1].c_str(), value2.c_str());
						record += "  CMP," + code[i].code[1] + "," + value2 + '\n';
						printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
						record += "  " + symble + "," + tem_str + '\n';
					}
				}
				else {
					int re1 = find(value, valuenum, code[i].code[1]);
					int re2 = find(value, valuenum, code[i].code[2]);
					if (re1 >= 0) {
						if (reg[tem_reg].used) {
							record += "  LD," + reg[tem_reg].name + "," + code[i].code[1] + '\n';
							printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[1].c_str());
						}
						if (re2 >= 0) {					//形如 j<,a,b,3
							int tem_reg2 = getregist(reg, count++);
							if (reg[tem_reg2].used) {
								record += "  ST," + reg[tem_reg2].name + "," + reg[tem_reg2].contin + '\n';
								printf("  ST,%s,%s\n", reg[tem_reg2].name.c_str(), reg[tem_reg2].contin.c_str());
							}
							printf("  %s,%s,%s\n", "CMP", reg[tem_reg].name.c_str(), reg[tem_reg2].name.c_str());
							record += "  CMP," + reg[tem_reg].name + "," + reg[tem_reg2].name + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
							reg[tem_reg].contin = code[i].code[1];
							reg[tem_reg2].contin = code[i].code[2];
						}
						else {							//形如 j<,a,1,3
							printf("  %s,%s,%s\n", "CMP", reg[tem_reg].name.c_str(), code[i].code[2].c_str());
							record += "  CMP," + reg[tem_reg].name + "," + code[i].code[2] + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
							reg[tem_reg].contin = code[i].code[1];
						}
					}
					else {

						if (re2 >= 0) {				//形如 j<,1,a,3
							if (reg[tem_reg].used) {
								printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
								record += "  ST," + reg[tem_reg].name + "," + reg[tem_reg].contin + '\n';
							}
							printf("  %s,%s,%s\n", "CMP", code[i].code[1].c_str(), reg[tem_reg].name.c_str());
							record += "  CMP," + code[i].code[1] + "," + reg[tem_reg].name + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
							reg[tem_reg].contin = code[i].code[2];
						}
						else {						//形如 j<,2,1,3
							printf("  %s,%s,%s\n", "CMP", code[i].code[1].c_str(), code[i].code[2].c_str());
							record += "  CMP," + code[i].code[1] + "," + code[i].code[2] + '\n';
							printf("  %s,%s\n", symble.c_str(), tem_str.c_str());
							record += "  " + symble + "," + tem_str + '\n';
						}
					}
				}
			}
			else if (temp == "pop" || temp == "push") {
				string value1;
				int ret1;
				if (ret1 = Isinregist(reg, code[i].code[3])) {
					value1 = reg[ret1 - 1].name;
					value[find(value, valuenum, code[i].code[1])].num--;
				}
				if (ret1 > 0)			//形如pop/push NULL NULL T0
				{
					printf("  %s,%s\n", temp.c_str(), value1.c_str());
					record += "  " + temp + "," + value1 + '\n';
					reg[ret1 - 1].used = 0;
				}
				else {					//形如pop/push NULL NULL a
					tem_reg = getregist(reg, count++);
					if (reg[tem_reg].used) {
						printf("  ST,%s,%s\n", reg[tem_reg].name.c_str(), reg[tem_reg].contin.c_str());
						record += "  ST," + reg[tem_reg].name + "," + reg[tem_reg].contin + '\n';
					}
					printf("  LD,%s,%s\n", reg[tem_reg].name.c_str(), code[i].code[3].c_str());
					record += "  LD," + reg[tem_reg].name + "," + code[i].code[3] + '\n';
					printf("  %s,%s\n", temp.c_str(), reg[tem_reg].name.c_str());
					record += "  " + temp + "," + reg[tem_reg].name + '\n';
					reg[tem_reg].contin = code[i].code[2];
					value[find(value, valuenum, code[i].code[1])].num--;
				}

			}
			else {
				cout << "ERROR!" << temp << endl;
				break;
			}
		}
		if (j_c < J_count)				//防止跳出程序
		{
			printf("%s\n", sig[j_c++].name.c_str());
			record += sig[j_c++].name.c_str() + '\n';
		}
	}
};
