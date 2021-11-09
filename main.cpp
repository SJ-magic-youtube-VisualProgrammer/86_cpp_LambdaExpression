/************************************************************
■ラムダ式
	-	C++11からサポートされた
	-	ラムダ式 = 無名関数
	-	ラムダ式を使うことで、簡単に関数オブジェクトを作成することができる。
	-	std::function、または auto の型で受ける
	

■参考
	■C++ のラムダ式
		https://c.keicode.com/cpp/cpp-lambda.php
		
	■ラムダ式
		https://kaworu.jpn.org/cpp/%E3%83%A9%E3%83%A0%E3%83%80%E5%BC%8F
		
	■C++ ラムダ式の基本とキャプチャ
		https://qiita.com/AtsushiEsashika/items/87c56d5c85760db60d17
		
	■std::function
		https://kaworu.jpn.org/cpp/std::function
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

/************************************************************
function
************************************************************/

/******************************
ラムダ式 定義/ 呼び出し
******************************/
void Func_0(){
	// 定義
	[](){};
	[]{}; // 引数は省略可
	
	// 呼び出し
	[](){}();
	
	// 文法
	[]	// ラムダキャプチャー
	()	// パラメータ定義節
	{}	// 複合ステートメント
	()	// 関数呼び出し式
	;
}

/******************************
ラムダ式 定義/ 呼び出し
******************************/
void Func_1(){
	[]{ std::cout<<"Hello World"<<std::endl;}();
}

/******************************
ラムダ式を変数に代入
******************************/
void Func_2(){
	/********************
	ラムダ式によって自動的に定義される関数オブジェクトは、それぞれが一意な型名を持ち、その型名をユーザーが知る方法はない。
	そのため、ラムダ式によって定義された関数オブジェクトを変数に持つためには、autoを使用して型推論するか、
	std::functionクラスの変数に保持するかの、いずれかの方法をとることになる。
	********************/
	auto func = []{ std::cout<<"Hello world"<<std::endl;};
	// std::function<void()> func = []{ std::cout<<"Hello world"<<std::endl;};
	func();//ラムダ式の呼び出し
}

/******************************
ラムダ式を関数に渡す
******************************/
template<typename Func>
void f(Func func){
	func();
}

void Func_3(){
	f( []{ std::cout<<"Hello world"<<std::endl;} );
}

/******************************
ラムダ式に引数を与える
******************************/
void Func_4(){
	[](const string & str)		// 引数の定義
	{							// 関数本体
		cout << str << endl;
	}
	("I am Saijo!");			// 関数呼び出し with 引数
}

/******************************
ラムダ式で戻り値を返す
******************************/
void Func_5(){
	auto a = [] { return 0;} ();					// 戻り値を推測させる
	auto b = [] () -> float { return 3.14; } ();	// 明示的に戻り値を定義
	
	cout << a << endl;
	cout << b << endl;
}

/******************************
変数のキャプチャ
******************************/
void Func_6(){
	string str = "I am Saijo.";
	
	[&] { cout << str << endl; } (); // この時点で見える自動変数を「参照」でキャプチャする。
	[=] { cout << str << endl; } (); // この時点で見える自動変数を「コピー」でキャプチャする。
	
	/******************** & の場合
	class LAMBDA{
	private:
		string& str;
		
	public:
		LAMBDA(string& _str)
		: str(_str)
		{
		}
		
		void operator()() {  cout << str << endl;  }
	};
	********************/
	
	/******************** = の場合
	class LAMBDA{
	private:
		const string str;
		
	public:
		LAMBDA(string _str)
		: str(_str)
		{
		}
		
		void operator()() {  cout << str << endl;  }
	};
	********************/
}

/******************************
参照の場合の代入
******************************/
void Func_7(){
	string str = "I am Saijo.";
	
	[&] { str = "I am Nobuhiro."; } ();
	cout << str << endl;
}

/******************************
Copyの場合の代入
	Copyの場合、変数を書き換えられません(defaultでconstになる)が、mutableを使用することで、変数を変更できます。
	当然、Copyなので、元の変数の値は、変更できません。 
	また、mutableを指定したとき、ラムダ式の引数リストのカッコは、省略できません。
******************************/
void Func_8(){
	string s1 = "I am s1";
	string s2 = "I am s2";
	
	[&] { s1 = "Overwrite s1!"; } ();
	// [=] { s2 = "Overwrite s2!"; } (); // compile Error.
	[=] () mutable { s2 = "Overwrite s2!"; } ();
	// float i = [=] () mutable -> int { s2 = "Overwrite s2!"; return 1.23; } (); // mutableの場合の戻り値
	
	cout << s1 << endl;
	cout << s2 << endl;
	// cout << "return = " << i << endl;
}

/******************************
変数ごとにキャプチャ指定
******************************/
void Func_9(){
	int a = 0, b = 0;
	
	[a, &b] () mutable { a = 1; b = 1; } ();
	
	cout << a << endl;
	cout << b << endl;
}

/******************************
変数ごと & デフォルト : キャプチャ指定
******************************/
void Func_10(){
	int a = 0, b = 1, c = 2, d = 3;
	
	// a,bを参照、それ以外はコピー
	[=, &a, &b] () mutable { } ();
	
	// a,bはコピー、それ以外は参照
	[&, a, b] () mutable { } ();
	
	// [a, b] () { cout << a << "," << b << ", " << c << endl; } ();	// c はcaptureされない
	
	// デフォルトと同じキャプチャ指定はError
	/*
	[&, &a] {};	// エラー
	[=, a] {};	// エラー
	[a, a] {};	// エラー
	*/
}

/******************************
thisをキャプチャ
******************************/
struct TEMP{
	int i = 0;
	void f(){
		[=]{this->i = 1;}(); // thisは、ポインタであるため、キャプチャがコピーでも参照でも、iは、上書きされます。
	}
};

void Func_11(){
	TEMP temp;
	temp.f();
	cout << temp.i << endl;
}

/******************************
ラムダ式を返す
******************************/
std::function< void() > f() {
	string str("Hoge");
	return [=] { cout << str << endl; };
	// return [&] { cout << str << endl; };
	
	/******************** = の場合
	class LAMBDA{
	private:
		const string str;
		
	public:
		LAMBDA(string _str)
		: str(_str)
		{
		}
		
		void operator()() {  cout << str << endl;  }
	};
	********************/
}

void Func_12(){
	auto func = f();
	
	func();	// 代入して呼び出し
	
	f()();	// 代入せずに、呼び出し
}

/******************************
キャプチャ
	ラムダ式によって作成した関数オブジェクト内の状態変数に、値をコピーする
******************************/
void Func_13(){
	/********************
	********************/
	int a = 100, b = 200;
	
	/********************
	********************/
	auto lambda = [=](){ cout << a << ", " << b << endl; };
	/********************
	class lambda{
	private:
		const int a; // mutable指定した時は、constが外れる
		const int b; // mutable指定した時は、constが外れる
		
	public:
		lambda(int _a, int _b)
		: a(_a), b(_b)
		{
		}
		
		void operator()() { cout << a << ", " << b << endl; }
	};
	********************/
	
	/********************
	********************/
	lambda();
	a = 300;
	b = 400;
	lambda();
}

/******************************
******************************/
void Func_14(){
	/********************
	********************/
	int a = 100, b = 200;
	
	/********************
	********************/
	auto lambda = [&](){ cout << a << ", " << b << endl; };
	/********************
	class lambda{
	private:
		int& a;
		int& b;
		
	public:
		lambda(int& _a, int& _b)
		: a(_a), b(_b)
		{
		}
		
		void operator()() { cout << a << ", " << b << endl; }
	};
	********************/
	
	/********************
	********************/
	lambda();
	a = 300;
	b = 400;
	lambda();
}

/******************************
Global変数はcaptureできない。
******************************/
int Nobu = 99;
void Func_15(){
	int a = 199, b = 299;
	
	// auto lambda = [a, Nobu](){ cout << a << ", " << Nobu << endl; };
	auto lambda = [a](){ cout << a << ", " << Nobu << endl; };
	lambda();
}

/******************************
******************************/
int main(int argc, char *argv[]) {
	int TestId =0;
	
	if(2 <= argc){
		TestId = atoi(argv[1]);
	}
	
	switch(TestId){
		case 0:		Func_0(); break;
		case 1:		Func_1(); break;
		case 2:		Func_2(); break;
		case 3:		Func_3(); break;
		case 4:		Func_4(); break;
		case 5:		Func_5(); break;
		case 6:		Func_6(); break;
		case 7:		Func_7(); break;
		case 8:		Func_8(); break;
		case 9:		Func_9(); break;
		case 10:	Func_10(); break;
		case 11:	Func_11(); break;
		case 12:	Func_12(); break;
		case 13:	Func_13(); break;
		case 14:	Func_14(); break;
		case 15:	Func_15(); break;
	}
	
	return 0;
}

