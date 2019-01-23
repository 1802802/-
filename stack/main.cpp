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

int testID = 0; //���Ա��

/******************************************************************************************
 * ����ջ
 ******************************************************************************************/
template <typename T> //Ԫ������
void testStack ( int n ) {
   Stack<T> S;
   printf ( "\n  ==== Test %2d. Growing stack\n", testID++ );
   while ( S.size() < n ) {
      T e = rand() % ( T ) 2 * n;
      if ( S.empty() || ( 30 < ( rand() % 100 ) ) ) { //70%������ջ
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //30%���ʳ�ջ
         printf ( "poping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
   printf ( "\n  ==== Test %2d. Shrinking stack\n", testID++ );
   while ( !S.empty() ) {
      T e = dice ( ( T ) 2 * n );
      if ( 70 < dice ( 100 ) ) { //70%������ջ
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //70%���ʳ�ջ
         printf ( "poping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
}


/******************************************************************************************
 * ����ջ
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand ( ( unsigned int ) time ( NULL ) ); //�����������
   testStack<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}

void Convert(Stack<char> &S, int n, int base)   //����ת���ĵݹ鷨
{
	static char d[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (n > 0) 
	{
		S.push(d[n%base]);
		Convert(S, n / base, base);
	}
}

void Convert2(Stack<char> &S, int n, int base)  //����ת���ĵ�����  ���˾��õݹ������Ч��Զ������������Ծ�������ݹ�
{
	static char d[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		S.push(d[n%base]);
		n /= base;
	}
}

bool Paren(const char exp[], int lo, int hi)  //��˵����ſ��Լ�����   expΪ�����Ķ���
{
	Stack<char> S;
	for (int i = lo; i <= hi; i++)
		switch (exp[i])
		{
		case '(':case'{':case'[': case'+':S.push(exp[i]); break;  //��ֵ����ֱ����ջ  ��������һ��+-��Ӧ����
		case')':if ((S.empty()) || ('(' != S.pop())) return false; break;   //�����case�������ԣ���(���ŵıȶ����ջֱ�ӽ����һ��pop����top��ֵ�����˾Ͷ��ˣ��ɹ���ջ�����˾�break��false
		case'}':if ((S.empty()) || ('{' != S.pop())) return false; break;
		case']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case'-':if ((S.empty()) || ('+' != S.pop())) return false; break;
		default:break;  //�������ַ�ֱ��GG
		}
	return S.empty(); //����жϣ����SΪ�գ�ɾ���ɾ��ˣ���ô������ȫ��Ӧreturn true�����ֻ��в���������û��Ӧ��ȫ����false
}



int main1()
{
	Stack<char> S;
	Convert2(S, 1000, 8);
	S.print();
	const char exp[] = { '(','[','{','}',']',')' };
	cout << boolalpha << Paren(exp, 0, 5) << endl;  //��ʾ���boolֵ������hi��5Ϊ��
}