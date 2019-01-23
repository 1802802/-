#include "binTree_test.h"

/*先序遍历的递归实现*/
template<typename T, typename VST> void Traverse(BinNodePosi(T) x, VST &visit)
{
	if (!x) return;
	visit(x->data);
	Traverse(x->lc, visit);
	Traverse(x->rc, visit);
}

/*先序遍历的迭代实现算法1*/
template<typename T, typename VST> void traver_i1(BinNodePosi(T) x, VST& visit)
{
	Stack <BinNodePosi(T)> S; //辅助栈，往内存放各个树节点
	if (x) S.push(x); //存入根节点
	while (!S.empty())
	{
		x = S.pop(); visit(x->data);  //top弹出，执行visit语句
		if (HasRChild(*x)) S.push(x->rc);  //右孩子先进后出
		if (HasLChild(*x)) S.push(x->lc);  //左孩子后进先出
	}
}

/*先序遍历的迭代实现算法2*/  //去除了算法1中的将左孩子存入栈中的过程
template<typename T, typename VST> static void visitalong(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
	while (x)
	{
		visit(x->data);  //对当前节点执行visit语句
		S.push(x->rc);  //存入右孩子
		x = x->lc;   //执行左孩子
	}
}

template<typename T, typename VST> void traver_i2(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;  //赋值栈，用于存右孩子
	while (true)
	{
		visitalong(x, visit, S);   //从根节点开始执行
		if (S.empty()) break;  //退出判断语句，栈空了就退出
		x = S.pop();  //弹出top进行执行，即执行了当前左节点后，执行右节点
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