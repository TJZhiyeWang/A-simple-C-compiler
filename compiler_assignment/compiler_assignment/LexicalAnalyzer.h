#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;

const int MaxWord=5000;
const int KeyNum=6;
const string Keyword[7]={"","int","void","if","else","while","return"};
const int BasicGramNum=27,emptyID=27,endID=26;

struct WordList {
	int id,value,line;
	string s;
} Word[MaxWord+1];

class LexicalAnalyzer {
	int Counter;
	string s;
	
	void ScanSourceCode()
	{
		int pos;
		char c;
		ifstream fin;
		fin.open("input.txt",ios::in);
		
		while (!fin.eof())
		{
			fin.get(c);
			s+=c;
		}
		
		fin.close();
		return;
	}
	
	bool ischar(char c)
	{
		return (c>='a' && c<='z' || c>='A' && c<='Z');
	}
	bool isnum(char c)
	{
		return (c>='0' && c<='9');
	}
	
	void getWordList()
	{
		int pos,end,i,temp,line;
		bool isKey,isExist;
		string temps;
		
		line=1;
		for (pos=0;pos<s.length();pos++)
		{
			if (ischar(s[pos]))
			{
				end=pos+1;
				temps=s[pos];
				while (ischar(s[end]) || isnum(s[end]))
				{
					temps+=s[end];
					end++;
				}
				end--;
				
				isKey=false;
				for (i=1;i<=KeyNum;i++)
					if (temps==Keyword[i])
					{
						Word[++Counter].id=i;
						isKey=true;
						break;
					}
				
				if (!isKey)
				{
					Word[++Counter].id=7;
					Word[Counter].s=temps;
				}
				Word[Counter].line=line;
				
				pos=end;
			}
			else if (isnum(s[pos]))
			{
				end=pos+1;
				temp=(int)(s[pos]-'0');
				while (isnum(s[end]))
				{
					temp=temp*10+(int)(s[end]-'0');
					end++;
				}
				end--;
				
				Counter++;
				Word[Counter].id=8;
				Word[Counter].value=temp;
				Word[Counter].line=line;
				
				pos=end;
			}
			else if (s[pos]=='=')
			{
				if (s[pos+1]=='=')
				{
					Word[++Counter].id=10;
					pos++;
				}
				else Word[++Counter].id=9;
				Word[Counter].line=line;
			}
			else if (s[pos]=='<')
			{
				if (s[pos+1]=='=')
				{
					Word[++Counter].id=12;
					pos++;
				}
				else Word[++Counter].id=11;
				Word[Counter].line=line;
			}
			else if (s[pos]=='>')
			{
				if (s[pos+1]=='=')
				{
					Word[++Counter].id=14;
					pos++;
				}
				else Word[++Counter].id=13;
				Word[Counter].line=line;
			}
			else if (s[pos]=='!')
			{
				if (s[pos+1]=='=')
				{
					Word[++Counter].id=15;
					pos++;
				}
				else {
					cout<<"词义错误：第"<<line<<"行，非法单词'!'"<<endl;
					system("pause");
				}
				Word[Counter].line=line;
			}
			else if (s[pos]=='*')
			{
				if (s[pos+1]=='/')
				{
					cout<<"语义错误：第"<<line<<"行，'*/'匹配错误";
					system("pause");
				}
				else Word[++Counter].id=16;
				Word[Counter].line=line;
			}
			else if (s[pos]=='/')
			{
				if (s[pos+1]=='/')
				{
					for (pos=pos+2;pos++;pos<s.length() && s[pos]!='\n');
				}
				else if (s[pos+1]=='*')
				{
					for (pos=pos+2;pos++;pos+1<s.length() && !(s[pos]=='*' && s[pos+1]=='/'));
				}
				else {
					Word[++Counter].id=17;
					Word[Counter].line=line;
				}
			}
			else if (s[pos]=='+') {Word[++Counter].id=18; Word[Counter].line=line;}
			else if (s[pos]=='-') {Word[++Counter].id=19; Word[Counter].line=line;}
			else if (s[pos]=='(') {Word[++Counter].id=20; Word[Counter].line=line;}
			else if (s[pos]==')') {Word[++Counter].id=21; Word[Counter].line=line;}
			else if (s[pos]=='{') {Word[++Counter].id=22; Word[Counter].line=line;}
			else if (s[pos]=='}') {Word[++Counter].id=23; Word[Counter].line=line;}
			else if (s[pos]==';') {Word[++Counter].id=24; Word[Counter].line=line;}
			else if (s[pos]==',') {Word[++Counter].id=25; Word[Counter].line=line;}
			else if (s[pos]=='\n') line++;
			else if (s[pos]!=' ' && s[pos]!='\t'){
				cout<<"词义错误：第"<<line<<"行，出现非法字符"<<endl;
				system("pause");
			}
		}
		
		Word[++Counter].id=endID;Word[Counter].line=line;
		Word[++Counter].id=0;
		
		return;
	}
	
	void PrintWordList()
	{
		for (int i=1;Word[i].id!=0;i++)
		{
			cout<<Word[i].id<<' '<<Word[i].value<<' '<<Word[i].s<<endl;
		}
		//system("pause");
		return;
	}
	
public:
	void main()
	{
		Counter=0;
		
		ScanSourceCode();
		getWordList();
		PrintWordList();
		
		return;
	}
} Test1;

struct Set {
	int num,data[50];
	bool extEmpty;
	Set()
	{
		num=0;
		extEmpty=false;
	}
};

struct _Stack {
	int top,data[2000];
	int tree_id[2000];
};

int GramNum;
struct Grammar {
	string s;
	int num,id[50][50],len[50];
	bool firstDone,followDone,followDoing;
	bool isBasic;
	struct Set first,follow,first_sub[50];
	int saveNum,save[50];
} gram[200];

int form[100][50];

void add_son(int father,string s);
void add_son_data(int son,string s);
int tree_num;
struct GTREE{
	string s;
	string data;
	int num,son[10];
	int father;
	string ans;
	int back;
} gtree[2000];

string num_to_str(int x)
{
	int temp[20],i,len;
	string ans="";
	if (x==0)
		return "0";
	if (x<0)
	{
		x=-x;
		ans+="-";
	}
	
	for (i=0;x>0;i++)
	{
		temp[i]=x%10;
		x/=10;
	}
	for (i=i-1;i>=0;i--)
		ans+=(char)(temp[i]+'0');
	
	return ans;
}

class GrammaticalAnalyzer {
	
	void setBasic()
	{
		GramNum=BasicGramNum+1;
		
		gram[1].s="int";
		gram[2].s="void";
		gram[3].s="if";
		gram[4].s="else";
		gram[5].s="while";
		gram[6].s="return";
		gram[7].s="ID";
		gram[8].s="NUM";
		gram[9].s="=";
		gram[10].s="==";
		gram[11].s="<";
		gram[12].s="<=";
		gram[13].s=">";
		gram[14].s=">=";
		gram[15].s="!=";
		gram[16].s="*";
		gram[17].s="/";
		gram[18].s="+";
		gram[19].s="-";
		gram[20].s="'('";
		gram[21].s="')'";
		gram[22].s="'{'";
		gram[23].s="'}'";
		gram[24].s=";";
		gram[25].s=",";
		gram[26].s="#";
		gram[27].s="Empty";
		
		for (int i=1;i<=27;i++)
		{
			gram[i].isBasic=true;
			gram[i].firstDone=true;
			gram[i].first.num=1;
			gram[i].first.data[1]=i;
			gram[i].first.extEmpty=(i==27);
		}
		
		gram[28].isBasic=false;
		gram[28].s="Program";
		gram[28].num=0;
		gram[28].firstDone=gram[28].followDone=false;
		return;
	}
	
	int getSymbol(string s)
	{	
		for (int i=1;i<=GramNum;i++)
		{
			if (gram[i].s==s)
				return i;
		}
		GramNum++;
		gram[GramNum].s=s;
		gram[GramNum].isBasic=false;
		gram[GramNum].num=0;
		gram[GramNum].firstDone=gram[GramNum].followDone=false;
		
		return GramNum;
	}
	
	void adder(struct Set *setA,struct Set setB,bool addEmpty=true)
	{
		int i,j,numA;
		bool isExt;
		
		numA=setA->num;
		for (i=1;i<=setB.num;i++)
			if (!(!addEmpty && setB.data[i]==emptyID))
			{
				isExt=false;
				for (j=1;j<=numA;j++)
					if (setB.data[i]==setA->data[j])
					{
						isExt=true;
						break;
					}
				if (!isExt)
				{
					setA->num++;
					setA->data[setA->num]=setB.data[i];
				}
			}
		if (addEmpty && setB.extEmpty)
			setA->extEmpty=true;
		return;
	}
	
	void scanGrammar()
	{
		ifstream fin;
		fin.open("grammar.txt",ios::in);
		
		string s[1000];
		char c,last_c,new_c;
		int i,title,pos,numS=1;
		bool bol;
		
		last_c=' ';
		bol=false;
		while (!fin.eof())
		{
			fin.get(c);
			if ((c==' ' || c=='\n') && !(last_c==' ' || last_c=='\n'))
			{
				numS++;
				s[numS]="";
				bol=false;
			}
			if (!(c==' ' || c=='\n'))
			{
				s[numS]+=c;
				bol=true;
			}
			
			last_c=c;
		}
		if (!bol) numS--;
		
		for (i=1;i<=numS;i++)
			if (s[i][0]!=':')
			{
				if (s[i+1][0]==':')
				{
					title=getSymbol(s[i]);
					pos=gram[title].num=1;
					gram[title].len[1]=0;
				}
				else {
					if (s[i][0]=='|')
						{
							gram[title].num++;
							pos=gram[title].num;
							gram[title].len[pos]=0;
						}
						else {
							gram[title].len[pos]++;
							gram[title].id[pos][gram[title].len[pos]]=getSymbol(s[i]);
						}
				}
			}
		
		return;
	}
	
	void getFirst_sub(int title,int pos,int head,struct Set *ans)
	{
		int i;
		struct Set first,temp;
		bool extEmpty;
		
		extEmpty=true;
		for (i=head;i<=gram[title].len[pos];i++)
		{
			getFirst(gram[title].id[pos][i],&temp);
			adder(&first,temp,false);
			if (!temp.extEmpty)
			{
				extEmpty=false;
				break;
			}
		}
		if (extEmpty)
		{
			first.num++;
			first.data[first.num]=emptyID;
			first.extEmpty=true;
		}
		
		*ans=first;
		return;
	}
	
	void getFirst(int title,struct Set *ans=NULL)
	{
		if (gram[title].firstDone)
		{
			if (ans!=NULL)
				*ans=gram[title].first;
				
			return;
		}
		
		int pos;
		struct Set first,temp;
		first.extEmpty=false;
		first.num=0;
		
		for (pos=1;pos<=gram[title].num;pos++)
		{
			getFirst_sub(title,pos,1,&temp);
			
			adder(&first,temp);
			
			gram[title].first_sub[pos]=temp;
			
			/*int i;
			cout<<gram[title].s<<' '<<pos<<':';
			for (i=1;i<=first.num;i++)
				cout<<gram[first.data[i]].s<<' ';
			cout<<'|';
			for (i=1;i<=temp.num;i++)
				cout<<gram[temp.data[i]].s<<' ';
			cout<<endl;*/
		}
		
		gram[title].first=first;
		gram[title].firstDone=true;
		if (ans!=NULL)
			*ans=gram[title].first;
		return;
	}
	
	void getFollow_sub(int title,struct Set *ans=NULL)
	{
		if (gram[title].followDone)
		{
			if (ans!=NULL)
				*ans=gram[title].follow;
			return;
		}
		
		int i;
		struct Set temp;
		
		gram[title].followDoing=true;
		for (i=1;i<=gram[title].saveNum;i++)
			if (!gram[gram[title].save[i]].followDoing)
			{
				getFollow_sub(gram[title].save[i],&temp);
				adder(&(gram[title].follow),temp);
			}
			/*else {
				cout<<"重复"<<endl;
				cout<<gram[title].s<<' '<<gram[gram[title].save[i]].s<<endl;
				system("pause"); 
			}*/
		gram[title].followDoing=false;
		
		gram[title].followDone=true;
		if (ans!=NULL)
			*ans=gram[title].follow;
		return;
	}
	
	void getFollow()
	{
		int title,pos,i,id;
		struct Set temp;
		
		gram[BasicGramNum+1].follow.num=1;
		gram[BasicGramNum+1].follow.data[1]=endID;
		
		for (title=BasicGramNum+1;title<=GramNum;title++)
		{
			for (pos=1;pos<=gram[title].num;pos++)
			{
				for (i=1;i<gram[title].len[pos];i++)
				{
					id=gram[title].id[pos][i];
					if (!gram[id].isBasic)
					{
						getFirst_sub(title,pos,i+1,&temp);
						
						adder(&(gram[id].follow),temp,false);
						
						if (temp.extEmpty)
						{
							gram[id].saveNum++;
							gram[id].save[gram[id].saveNum]=title;
						}
					}
				}
				id=gram[title].id[pos][gram[title].len[pos]];
				if (!gram[id].isBasic)
				{
					gram[id].saveNum++;
					gram[id].save[gram[id].saveNum]=title;
				}
			}
		}
		
		for (title=BasicGramNum+1;title<=GramNum;title++)
			gram[title].followDoing=false;
		for (title=BasicGramNum+1;title<=GramNum;title++)
			getFollow_sub(title);
			
		return;
	}
	
	void getForm()
	{
		int title,pos,i;
		
		memset(form,0,sizeof(form));
		
		for (title=BasicGramNum+1;title<=GramNum;title++)
		{
			for (pos=1;pos<=gram[title].num;pos++)
				for (i=1;i<=gram[title].first_sub[pos].num;i++)
					form[title][gram[title].first_sub[pos].data[i]]=pos;
		
			if (gram[title].first.extEmpty)
			{
				for (i=1;i<=gram[title].follow.num;i++)
					form[title][gram[title].follow.data[i]]=-1;
			}
		}
		
		return;
	}
	
	void checkGrammar()
	{
		struct _Stack stack;
		int posW,title,pos,i,step;
		int father;
		
		stack.top=2;
		stack.data[1]=endID;
		stack.tree_id[1]=0;
		
		tree_num=1;
		
		stack.data[2]=BasicGramNum+1;
		stack.tree_id[2]=1;
		add_son(0,"Program");
		
		step=0;
		posW=1;
		while (stack.top>0)
		{
			step++;
			cout<<"第"<<step<<"步，第"<<Word[posW].line<<"行：栈中元素={ ";
			for (i=1;i<=stack.top;i++)
				cout<<gram[stack.data[i]].s<<' ';
			cout<<"}"<<endl;
			cout<<"    当前单词为“"<<gram[Word[posW].id].s<<"”   "; 
			
			title=stack.data[stack.top];
			if (gram[title].isBasic)
			{
				if (Word[posW].id==title)
				{
					cout<<"单词匹配成功";
					if (gram[Word[posW].id].s=="ID")
						add_son_data(stack.tree_id[stack.top],Word[posW].s);
					if (gram[Word[posW].id].s=="NUM")
					{
						//cout<<"我在这里！！"<<Word[posW].value;
						add_son_data(stack.tree_id[stack.top],num_to_str(Word[posW].value));
					}
						
					stack.top--;
					posW++;
				}
				else {
					cout<<"单词匹配错误"<<endl;
					//system("pause");
				}
			}
			else {
				pos=form[title][Word[posW].id];
				if (pos>0)
				{
					father=stack.tree_id[stack.top];
					cout<<"father="<<gtree[father].s<<endl;
					
					cout<<"产生式为 "<<gram[title].s<<" ::="; 
					for (i=1;i<=gram[title].len[pos];i++)
					{
						
						cout<<' '<<gram[gram[title].id[pos][i]].s;
						add_son(father,gram[gram[title].id[pos][i]].s);
					}
					
					//cout<<" ~son="<<gtree[father].num<<endl;
					
					stack.top--;
					
					for (i=gram[title].len[pos];i>=1;i--)
					{
						stack.top++;
						stack.data[stack.top]=gram[title].id[pos][i];
						stack.tree_id[stack.top]=gtree[father].son[i-1];
					}
				}
				else if (pos==-1)
				{
					cout<<"栈顶的产生式结束"; 
					stack.top--;
				}
				else {
					cout<<"语法错误"<<endl;
					system("pause");
				}
			}
			cout<<endl;
		}
		
		cout<<"语法分析正确!"<<endl;
		//system("pause");
		
		return;
	}
	
public:
	void main()
	{
		int title,i;
		
		setBasic();
		
		scanGrammar();
		
		for (title=BasicGramNum+1;title<=GramNum;title++)
			getFirst(title);
		for (title=BasicGramNum+1;title<=GramNum;title++)
		{
			cout<<gram[title].s<<"={ ";
			for (i=1;i<=gram[title].first.num;i++)
				cout<<gram[gram[title].first.data[i]].s<<' ';
			cout<<" }"<<endl;
		}
		//system("pause");
		
		getFollow();
		for (title=BasicGramNum+1;title<=GramNum;title++)
		{
			cout<<gram[title].s<<"={ ";
			for (i=1;i<=gram[title].follow.num;i++)
				cout<<gram[gram[title].follow.data[i]].s<<' ';
			cout<<" }"<<endl;
		}
		//system("pause");
		
		getForm();
		
		for (title=BasicGramNum+1;title<=GramNum;title++)
		{
			cout<<gram[title].s<<' ';
			for (i=1;i<=BasicGramNum-1;i++)
				cout<<form[title][i]<<' ';
			cout<<endl;
		}
		
		checkGrammar();
		
		return;
	}
	
	
} Test2;

string mcode="";
int mlist_num=0;
string mlist[1000][5];

void add_son(int father,string s)
{
	
	gtree[father].son[gtree[father].num]=tree_num;
	gtree[tree_num].father=father;
	
	gtree[tree_num].s=s;
	gtree[tree_num].num=0;
	gtree[tree_num].ans="";
	
	tree_num++;
	gtree[father].num++;
	
	return;
}
void add_son_data(int son,string s)
{
	gtree[son].data=s;
	return;
}

void add_mlist(string a,string b,string c,string d)
{
	mlist[mlist_num][0]=a;
	mlist[mlist_num][1]=b;
	mlist[mlist_num][2]=c;
	mlist[mlist_num][3]=d;
	mlist_num++;
	
	//cout<<mlist[mlist_num-1][0]<<' '<<mlist[mlist_num-1][1]<<' '<<mlist[mlist_num-1][2]<<' '<<mlist[mlist_num-1][3]<<endl;
	//system("pause");
	
	return;
}
void readd_mlist(int pos,int pos2,string s)
{
	mlist[pos][pos2]=s;
	return;
}


struct FUNC{
	string ID,head_code,head_list;
} func[50];
int func_num;
void add_func(string ID, string head_code, string head_list)
{
	func_num++;
	func[func_num].ID=ID;
	func[func_num].head_code=head_code;
	func[func_num].head_list=head_list;
	return;
}
void get_func(string ID, string *head_code, string *head_list)
{
	for (int i=1;i<=func_num;i++)
		if (ID==func[i].ID)
		{
			*head_code=func[i].head_code;
			*head_list=func[i].head_list;
			return;
		}
	return;
}


int label_num=0;
string newlabel()
{
	string temp;
	temp="L"+num_to_str(label_num);
	label_num++;
	return temp;
}

int temp_num=0;
string newtemp()
{
	string temp;
	temp="T"+num_to_str(temp_num);
	temp_num++;
	return temp;
}

string func_name;
int pos_main;
bool is_main;
void ok(int pos)
{
	string s;
	string temp_true,temp_false,temp_next,temp_body,temp_head,temp_return;
	int con,label_head;
	int pos_true,pos_false,pos_next,pos_body;
	int father;
	int i;
	string head_code,head_list;
	
	s=gtree[pos].s;
	father=gtree[pos].father;
	
	/*
	cout<<"mlist_num="<<mlist_num<<endl;
	if (mlist_num>0)
		cout<<mlist[mlist_num-1][0]<<' '<<mlist[mlist_num-1][1]<<' '<<mlist[mlist_num-1][2]<<' '<<mlist[mlist_num-1][3]<<endl;
	cout<<pos<<' '<<s<<" ~~~ "<<father<<' '<<gtree[father].s<<endl;
	cout<<gtree[pos].num<<endl;
	for (i=0;i<gtree[pos].num;i++)
		cout<<gtree[pos].son[i]<<' '<<gtree[gtree[pos].son[i]].s<<endl;
	system("pause");
	*/
	
	if (s=="<声明>")
	{
		if (gtree[gtree[pos].son[1]].data=="main" && is_main==false)
			return;
		if (gtree[gtree[pos].son[1]].data!="main" && is_main==true)
			return;
		
		if (gtree[gtree[pos].son[2]].s=="<函数声明>" || gtree[gtree[gtree[pos].son[2]].son[0]].s=="<函数声明>")
		{
			func_name='('+gtree[gtree[pos].son[1]].data+')';
			if (gtree[gtree[pos].son[1]].data=="main")
			{
				pos_main=mlist_num;
			}
			
			for (int i=0;i<mlist_num;i++)
			{
				if (mlist[i][4]==gtree[gtree[pos].son[1]].data)
					mlist[i][3]=num_to_str(mlist_num);
			}
			
			head_code=newlabel();
			mcode+=head_code+':'+'\n';
			
			add_func(gtree[gtree[pos].son[1]].data,head_code,num_to_str(mlist_num));
		}
	}
	if (s=="<参数列表>")
	{
		ok(gtree[pos].son[1]);
		ok(gtree[pos].son[0]);
		return;
	}
	if (s=="<参数列表sub>")
	{
		if (gtree[gtree[pos].son[0]].s==",")
		{
			ok(gtree[pos].son[2]);
			ok(gtree[pos].son[1]);
		}
		return;
	}
	if (s=="<参数>")
	{
		mcode+="pop "+gtree[gtree[pos].son[1]].data+'\n';
		add_mlist("pop", "NULL", "NULL", gtree[gtree[pos].son[1]].data+func_name);
	}
	if (s=="<return语句>")
	{
		//temp_return=newtemp();
		//mcode+="pop "+temp_return+'\n';
		//add_mlist("pop", "NULL", "NULL", temp_return);
		
		ok(gtree[pos].son[1]);
		
		//mcode+="ret\n";
		//add_mlist("ret", "NULL", "NULL", "NULL");
		
		return;
	}
	if (s=="<return语句sub>")
	{
		if (gtree[gtree[pos].son[0]].s=="<表达式>")
		{
			ok(gtree[pos].son[0]);
			
			mcode+="ret "+gtree[gtree[pos].son[0]].ans+'\n';
			add_mlist("ret", "NULL", "NULL",gtree[gtree[pos].son[0]].ans);
		}
		else {
			mcode+="ret \n";
			add_mlist("ret", "NULL", "NULL","NULL" );
		}
		return;
	}
	if (s=="<实参列表>")
	{
		ok(gtree[pos].son[0]);
		mcode+="push "+gtree[gtree[pos].son[0]].ans+'\n';
		add_mlist("push", "NULL", "NULL", gtree[gtree[pos].son[0]].ans);
		ok(gtree[pos].son[1]);
		return;
	}
	if (s=="<实参列表sub>")
	{
		if (gtree[gtree[pos].son[0]].s==",")
		{
			ok(gtree[pos].son[1]);
			mcode+="push "+gtree[gtree[pos].son[1]].ans+'\n';
			add_mlist("push", "NULL", "NULL", gtree[gtree[pos].son[1]].ans);
			ok(gtree[pos].son[2]);
		}
		return;
	}
	
	
	if (s=="<if语句>")
	{
		temp_true=newlabel();
		temp_false=newlabel();
		temp_next=newlabel();
		
		con=gtree[pos].son[2];
		
		ok(gtree[con].son[0]);
		ok(gtree[con].son[1]);
		
		
		mcode+="if "+gtree[gtree[con].son[0]].ans+gtree[gtree[gtree[gtree[con].son[1]].son[0]].son[0]].s+gtree[gtree[con].son[1]].ans+" goto "+temp_true+"\n";
		pos_true=mlist_num;
		add_mlist("j"+gtree[gtree[gtree[gtree[con].son[1]].son[0]].son[0]].s, gtree[gtree[con].son[0]].ans, gtree[gtree[con].son[1]].ans, "");
		
		mcode+="goto "+temp_false+"\n";
		pos_false=mlist_num;
		add_mlist("j", "NULL", "NULL", "");
		
		mcode+=temp_true+':';
		readd_mlist(pos_true,3,num_to_str(mlist_num));
		ok(gtree[pos].son[4]);
		
		mcode+="goto "+temp_next+"\n";
		pos_next=mlist_num;
		add_mlist("j", "NULL", "NULL", "");
		
		mcode+=temp_false+':';
		readd_mlist(pos_false,3,num_to_str(mlist_num));
		ok(gtree[pos].son[5]);
		
		mcode+=temp_next+':';
		readd_mlist(pos_next,3,num_to_str(mlist_num));
		return;
	}
	if (s=="<while语句>")
	{
		temp_head=newlabel();
		temp_body=newlabel();
		temp_next=newlabel();
		
		mcode+=temp_head+':';
		label_head=mlist_num;
		
		con=gtree[pos].son[2];
		//cout<<"con其实是"<<gtree[con].s<<endl;
		ok(gtree[con].son[0]);
		ok(gtree[con].son[1]);
		
		mcode+="if "+gtree[gtree[con].son[0]].ans+gtree[gtree[gtree[gtree[con].son[1]].son[0]].son[0]].s+gtree[gtree[con].son[1]].ans+" goto "+temp_body+"\n";
		pos_body=mlist_num;
		add_mlist("j"+gtree[gtree[gtree[gtree[con].son[1]].son[0]].son[0]].s, gtree[gtree[con].son[0]].ans, gtree[gtree[con].son[1]].ans, "");
		
		mcode+="goto "+temp_next+"\n";
		pos_next=mlist_num;
		add_mlist("j", "NULL", "NULL", "");
		
		mcode+=temp_body+':';
		readd_mlist(pos_body,3,num_to_str(mlist_num));
		
		ok(gtree[pos].son[4]);
		
		mcode+="goto "+temp_head+"\n";
		add_mlist("j", "NULL", "NULL", num_to_str(label_head));
		
		mcode+=temp_next+':';
		readd_mlist(pos_next,3,num_to_str(mlist_num));
		return;
	}
	if (s=="<赋值语句>")
	{
		ok(gtree[pos].son[0]);
		ok(gtree[pos].son[2]);
		mcode+=gtree[gtree[pos].son[0]].ans+":="+gtree[gtree[pos].son[2]].ans+"\n";
		add_mlist(":=", gtree[gtree[pos].son[2]].ans, "NULL", gtree[gtree[pos].son[0]].ans);
		return;
	}
	
	if (s=="<因子>")
	{
		//cout<<"进入因子！！ "<<gtree[gtree[pos].son[0]].s<<endl;
		
		if (gtree[gtree[pos].son[1]].s=="<表达式>")
		{
			ok(gtree[pos].son[1]);
			gtree[pos].ans=gtree[gtree[pos].son[1]].ans;
		}
		else {
			if (gtree[gtree[pos].son[0]].s=="ID" && gtree[gtree[gtree[pos].son[1]].son[0]].s=="<call>")
			{
				
				pos_next=mlist_num;
				//add_mlist("push","NULL","NULL","");
				
				
				ok(gtree[pos].son[1]);
				
				get_func(gtree[gtree[pos].son[0]].data, &head_code,&head_list);
				mlist[mlist_num][4]=gtree[gtree[pos].son[0]].data;
				//cout<<endl<<endl<<endl<<gtree[gtree[pos].son[0]].data<<endl<<endl;
				add_mlist("call","NULL","NULL",head_list);
				
				
				//readd_mlist(pos_next,3,num_to_str(mlist_num+1));
				
				//get_func(gtree[gtree[pos].son[0]].data, &head_code,&head_list);
				//mcode+="goto "+head_code+'\n';
				//add_mlist("j","NULL","NULL",head_list);
				
				temp_return=newtemp();
				mcode+="pop "+temp_return+'\n';
				add_mlist("pop","NULL","NULL",temp_return);
				
				gtree[pos].ans=temp_return;
				
				return;
			}
			
			ok(gtree[pos].son[0]);
			gtree[pos].ans=gtree[gtree[pos].son[0]].ans;
		}
		return;
	}
	if (s=="<项>" || s=="<加法表达式>")
	{
		
		ok(gtree[pos].son[0]);
		gtree[pos].ans=gtree[gtree[pos].son[0]].ans;
		
		ok(gtree[pos].son[1]);
		gtree[pos].ans=gtree[gtree[pos].son[1]].ans;
		return;
	}
	if (s=="<项sub>" || s=="<加法表达式sub>")
	{
		father=gtree[pos].father;
		if (gtree[pos].num==0)
		{
			gtree[pos].ans=gtree[father].ans;
		}
		else {
			ok(gtree[pos].son[1]);
			
			gtree[pos].ans=newtemp();
			mcode+=gtree[pos].ans+":="+gtree[father].ans+gtree[gtree[pos].son[0]].s+gtree[gtree[pos].son[1]].ans+"\n";
			add_mlist(gtree[gtree[pos].son[0]].s, gtree[father].ans, gtree[gtree[pos].son[1]].ans, gtree[pos].ans);
			
			ok(gtree[pos].son[2]);
			gtree[pos].ans=gtree[gtree[pos].son[2]].ans;
		}
		return;
	}
	if (s=="<表达式>")
	{
		ok(gtree[pos].son[0]);
		gtree[pos].ans=gtree[gtree[pos].son[0]].ans;
		return;
	}
	if (s=="<表达式sub>")
	{
		if (gtree[pos].num>0)
		{
			ok(gtree[pos].son[1]);
			gtree[pos].ans=gtree[gtree[pos].son[1]].ans;
		}
		
		return;
	}
	if (s=="NUM")
	{
		gtree[pos].ans=gtree[pos].data;
		return;
	}
	if (s=="ID")
	{
		gtree[pos].ans=gtree[pos].data+func_name;
		return;
	}
	
	for (i=0;i<gtree[pos].num;i++)
		if (gtree[pos].son[i]>0)
			ok(gtree[pos].son[i]);
		
	return;
}

/*
int main()
{
	Test1.main();
	
	Test2.main();
	
	int i,j;
	cout<<tree_num<<endl;
	for (i=0;i<tree_num;i++)
	{
		cout<<i<<' '<<gtree[i].s<<' '<<gtree[i].num<<" ~~~ ";
		for (j=0;j<gtree[i].num;j++)
			cout<<gtree[gtree[i].son[j]].s<<' ';
		cout<<endl;
	}
	
	//add_mlist("j","NULL","NULL","");
	is_main=true;
	ok(0);
	is_main=false;
	ok(0);
	//readd_mlist(0,3,num_to_str(pos_main));
	
	cout<<endl<<"中间代码："<<endl;
	cout<<mcode<<endl;
	system("pause");
	
	cout<<endl;
	for (i=0;i<mlist_num;i++)
	 	cout<<i<<":  "<<mlist[i][0]<<','<<mlist[i][1]<<','<<mlist[i][2]<<','<<mlist[i][3]<<endl; 
	system("pause");
	
	return 0;
}
*/