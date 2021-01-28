#pragma once

#include "LexicalAnalyzer.h"
#include "head.h"
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

namespace 编译原理12 {



	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
		/*	if (!Directory::Exists("input.txt"))
				Directory::CreateDirectory("input.txt");
			if (!Directory::Exists("grammar.txt"))
				Directory::CreateDirectory("grammar.txt");
			if (!Directory::Exists("out1.txt"))
				Directory::CreateDirectory("out1.txt");
			if (!Directory::Exists("out2.txt"))
				Directory::CreateDirectory("out2.txt");*/
			//
		}
	private:StreamWriter^WriFile1;
	private:StreamReader^readFile1;
	private: System::Windows::Forms::Button^  button5;
	private:StreamWriter^WriFile2;

	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private:StreamReader^readFile2;
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::TextBox^  textBox1;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(332, 54);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(88, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"文法输入";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(332, 118);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(88, 25);
			this->button2->TabIndex = 1;
			this->button2->Text = L"程序输入";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBox1->Location = System::Drawing::Point(438, 44);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(580, 187);
			this->textBox1->TabIndex = 4;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(181, 187);
			this->button5->Margin = System::Windows::Forms::Padding(4);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(100, 29);
			this->button5->TabIndex = 5;
			this->button5->Text = L"开始";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(94, 54);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(217, 25);
			this->textBox2->TabIndex = 7;
			this->textBox2->Text = L"grammar.txt";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(94, 120);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(217, 25);
			this->textBox3->TabIndex = 8;
			this->textBox3->Text = L"input.txt";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(69, 304);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox4->Size = System::Drawing::Size(238, 310);
			this->textBox4->TabIndex = 9;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(393, 304);
			this->textBox5->Multiline = true;
			this->textBox5->Name = L"textBox5";
			this->textBox5->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox5->Size = System::Drawing::Size(243, 310);
			this->textBox5->TabIndex = 10;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(728, 304);
			this->textBox6->Multiline = true;
			this->textBox6->Name = L"textBox6";
			this->textBox6->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox6->Size = System::Drawing::Size(234, 310);
			this->textBox6->TabIndex = 11;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(66, 274);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(82, 15);
			this->label1->TabIndex = 12;
			this->label1->Text = L"三地址语句";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(390, 273);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 15);
			this->label2->TabIndex = 13;
			this->label2->Text = L"四元表达式";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(728, 273);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(67, 15);
			this->label3->TabIndex = 14;
			this->label3->Text = L"汇编代码";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(21, 57);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(67, 15);
			this->label4->TabIndex = 15;
			this->label4->Text = L"文法文件";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(24, 129);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 15);
			this->label5->TabIndex = 16;
			this->label5->Text = L"程序文件";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(435, 25);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(37, 15);
			this->label6->TabIndex = 17;
			this->label6->Text = L"过程";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1044, 660);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"类C编译器";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ grammar_input = this->textBox2->Text;
		WriFile1 = gcnew StreamWriter(grammar_input, true);
		String^ dat = "";
		dat = textBox1->Text->Trim();
		WriFile1->Write(dat);
		WriFile1->Close();
		textBox1->Text = "";
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ source_input = this->textBox3->Text;
	WriFile2 = gcnew StreamWriter(source_input, true);
	String^ dat = "";
	dat = textBox1->Text->Trim();
	WriFile2->Write(dat);
	WriFile2->Close();
	textBox1->Text = "";
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	textBox1->Text = "";
	
	readFile1 = File::OpenText("out1.txt");
	String^line;
	while (line = readFile1->ReadLine())
	{
		textBox1->Text += (line+"\r\n");
	}
	readFile1->Close();
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	LexicalAnalyzer Test1;
	GrammaticalAnalyzer Test2;
	middle2finale Test3;
	Test1.main();
	Test2.main();
	int i, j;
	ofstream fout0("out0.txt");
	fout0 << tree_num << endl;
	for (i = 0; i<tree_num; i++)
	{
		fout0 << i << ' ' << gtree[i].s << ' ' << gtree[i].num << " ~~~ ";
		for (j = 0; j<gtree[i].num; j++)
			fout0 << gtree[gtree[i].son[j]].s << ' ';
		fout0 << endl;
	}
	is_main = true;
	ok(0);
	is_main = false;
	ok(0);
	fout0 << endl << "中间代码：" << endl;
	fout0 << mcode << endl;
	fout0.close();
	MessageBox::Show("中间代码生成成功");
	textBox1->Text = "";
	readFile2 = File::OpenText("out0.txt");
	String^line;
	while (line = readFile2->ReadLine())
	{
		textBox1->Text += (line + "\r\n");
	}
	readFile2->Close();
	ofstream fout("out1.txt");
	fout << mcode << endl;
	//system("pause");
	fout.close();
	MessageBox::Show("三地址语句生成成功");
	textBox4->Text = "";
	readFile2 = File::OpenText("out1.txt");
	while (line = readFile2->ReadLine())
	{
		textBox4->Text += (line + "\r\n");
	}
	readFile2->Close();
	//cout << endl;
	ofstream fout2("out2.txt");
	for (i = 0; i < mlist_num; i++)
	{
		//cout << i << ":  " << mlist[i][0] << ',' << mlist[i][1] << ',' << mlist[i][2] << ',' << mlist[i][3] << endl;
		fout2 << i << ":  " << mlist[i][0] << ',' << mlist[i][1] << ',' << mlist[i][2] << ',' << mlist[i][3] << endl;
	}//system("pause");
	fout2.close();
	MessageBox::Show("四元表达式生成成功");
	textBox5->Text = "";
	readFile2 = File::OpenText("out2.txt");
	while (line = readFile2->ReadLine())
	{
		textBox5->Text += (line + "\r\n");
	}

	readFile2->Close();
	Test3._main();
	ofstream fout3("out3.txt");
	middle2finale mid2fi;
	mid2fi._main();
	fout3 << record ;
	fout3.close();
	MessageBox::Show("目标代码生成成功");
	textBox6->Text = "";
	readFile2 = File::OpenText("out3.txt");
	while (line = readFile2->ReadLine())
	{
		textBox6->Text += (line + "\r\n");
	}

	readFile2->Close();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	textBox1->Text = "";
	readFile2 = File::OpenText("out2.txt");
	String^line;
	while (line = readFile2->ReadLine())
	{
		textBox1->Text += (line+"\r\n");
	}
	
	readFile2->Close();
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	textBox1->Text = "";
	readFile2 = File::OpenText("out3.txt");
	String^line;
	while (line = readFile2->ReadLine())
	{
		textBox1->Text += (line + "\r\n");
	}

	readFile2->Close();
}

};
}

