#include "binTree_test.h"

/*��������ĵݹ�ʵ��*/
template<typename T, typename VST> void Traverse(BinNodePosi(T) x, VST &visit)
{
	if (!x) return;
	visit(x->data);
	Traverse(x->lc, visit);
	Traverse(x->rc, visit);
}

/*��������ĵ���ʵ���㷨1*/
template<typename T, typename VST> void traver_i1(BinNodePosi(T) x, VST& visit)
{
	Stack <BinNodePosi(T)> S; //����ջ�����ڴ�Ÿ������ڵ�
	if (x) S.push(x); //������ڵ�
	while (!S.empty())
	{
		x = S.pop(); visit(x->data);  //top������ִ��visit���
		if (HasRChild(*x)) S.push(x->rc);  //�Һ����Ƚ����
		if (HasLChild(*x)) S.push(x->lc);  //���Ӻ���ȳ�
	}
}

/*��������ĵ���ʵ���㷨2*/  //ȥ�����㷨1�еĽ����Ӵ���ջ�еĹ���
template<typename T, typename VST> static void visitalong(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
	while (x)
	{
		visit(x->data);  //�Ե�ǰ�ڵ�ִ��visit���
		S.push(x->rc);  //�����Һ���
		x = x->lc;   //ִ������
	}
}

template<typename T, typename VST> void traver_i2(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;  //��ֵջ�����ڴ��Һ���
	while (true)
	{
		visitalong(x, visit, S);   //�Ӹ��ڵ㿪ʼִ��
		if (S.empty()) break;  //�˳��ж���䣬ջ���˾��˳�
		x = S.pop();  //����top����ִ�У���ִ���˵�ǰ��ڵ��ִ���ҽڵ�
	}
}

template<typename T>struct pr
{
	virtual void operator()(T& e) { cout << e << endl; }
};

int main()
{
	BinTree<int> tree;
	tree.insertAsRoot(0);
	auto root = tree.root();
	auto a1 = tree.insertAsLC(root, 1);
	auto a2 = tree.insertAsRC(root, 2);
	auto a3 = tree.insertAsRC(a1, 3);
	auto a4 = tree.insertAsRC(a2, 4);
	traver_i2(root, pr<int>());
}