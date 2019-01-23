/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/******************************************************************************************
 * Test of stack
 ******************************************************************************************/
#include "stack_test.h"

int testID = 0; //测试编号

/******************************************************************************************
 * 测试栈
 ******************************************************************************************/
template <typename T> //元素类型
void testStack ( int n ) {
   Stack<T> S;
   printf ( "\n  ==== Test %2d. Growing stack\n", testID++ );
   while ( S.size() < n ) {
      T e = rand() % ( T ) 2 * n;
      if ( S.empty() || ( 30 < ( rand() % 100 ) ) ) { //70%概率入栈
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //30%概率出栈
         printf ( "poping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
   printf ( "\n  ==== Test %2d. Shrinking stack\n", testID++ );
   while ( !S.empty() ) {
      T e = dice ( ( T ) 2 * n );
      if ( 70 < dice ( 100 ) ) { //70%概率入栈
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //70%概率出栈
         printf ( "poping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
}


/******************************************************************************************
 * 测试栈
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
   testStack<int> ( atoi ( argv[1] ) ); //元素类型可以在这里任意选择
   return 0;
}

void Convert(Stack<char> &S, int n, int base)   //进制转换的递归法
{
	static char d[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (n > 0) 
	{
		S.push(d[n%base]);
		Convert(S, n / base, base);
	}
}

void Convert2(Stack<char> &S, int n, int base)  //进制转换的迭代法  个人觉得递归的运算效率远不如迭代，所以尽量避免递归
{
	static char d[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		S.push(d[n%base]);
		n /= base;
	}
}

bool Paren(const char exp[], int lo, int hi)  //兼顾的括号可自己扩充   exp为被检查的对象
{
	Stack<char> S;
	for (int i = lo; i <= hi; i++)
		switch (exp[i])
		{
		case '(':case'{':case'[': case'+':S.push(exp[i]); break;  //左值括号直接入栈  这里扩充一个+-对应试试
		case')':if ((S.empty()) || ('(' != S.pop())) return false; break;   //这里的case语句很灵性，把(括号的比对与出栈直接结合在一起，pop返回top的值，对了就对了，成功出栈，错了就break出false
		case'}':if ((S.empty()) || ('{' != S.pop())) return false; break;
		case']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case'-':if ((S.empty()) || ('+' != S.pop())) return false; break;
		default:break;  //非括号字符直接GG
		}
	return S.empty(); //最后判断，如果S为空（删除干净了）那么就是完全对应return true；发现还有残留，就是没对应完全，出false
}



int main1()
{
	Stack<char> S;
	Convert2(S, 1000, 8);
	S.print();
	const char exp[] = { '(','[','{','}',']',')' };
	cout << boolalpha << Paren(exp, 0, 5) << endl;  //显示输出bool值，这里hi到5为顶
}