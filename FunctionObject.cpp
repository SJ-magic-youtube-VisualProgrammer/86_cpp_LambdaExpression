/************************************************************
■関数オブジェクト(functor)
	関数オブジェクト（function object）は、関数のように振る舞うことのできるオブジェクトのこと。
	多くの場合、クラスに対して関数呼び出し演算子を定義することで実現されます。
	C++ではoperator()メンバ関数のオーバロードによってそれを実現します。
	
	関数がオブジェクトになっていることによって、関数は情報（データ）を持つことができます。
	変数に保存したり、他の関数に渡したりという用途でいえば、関数ポインタによる方法がありますが、
	関数ポインタは文字どおり、関数を指し示すポインタがあるだけですから、状態を表現できません。
	

■参考 : 関数オブジェクト
	■関数オブジェクト | Programming Place Plus　C++編【言語解説】　第３４章
		https://programming-place.net/ppp/contents/cpp/language/034.html
		
	■【C++】色々な関数オブジェクト【ラムダ ファンクタ 関数ポインタ】
		https://marycore.jp/prog/cpp/function-object/
************************************************************/
#include <stdio.h>

/************************************************************
************************************************************/

class FUNCTOR_0{
private:
	int counter;
	
public:
	FUNCTOR_0() : counter(0) {}

	void operator()(){
		printf("FUNCTOR_0 : %d\n", counter);
		counter++;
	}
};

class FUNCTOR_1{
public:
	FUNCTOR_1(){}

	int operator()(int i){
		printf("FUNCTOR_1 : %d\n", i);
		return i;
	}
};

/******************************
******************************/
int main(int argc, char *argv[]) {
	FUNCTOR_0 Functor_0;
	FUNCTOR_1 Functor_1;
	
	Functor_0();
	Functor_0();
	Functor_1(99);
	
	return 0;
}

