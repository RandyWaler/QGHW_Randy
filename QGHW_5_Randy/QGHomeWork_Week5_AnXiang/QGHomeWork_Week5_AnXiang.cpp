// QGHomeWork_Week5_AnXiang.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "SqBinaryTree.h"
#include "LinkBinaryTree.h"
#include "Calculator.h"
using namespace std;

void testPrint(int a) {
	cout << a  <<"   ";
}
void testPrint(int *a) {
	cout << *a <<"   \n";
}

int main()
{
//计算器测试---------------------------------------------------------------------------------------------------
	Calculator *myCalculator = new Calculator();
	while (true) {
		myCalculator->getInputEx();
	}

//链式二叉树测试------------------------------------------------------------------------------------------------
/*

	LinkBinaryTree<int> *testLinkBinaryTree = new LinkBinaryTree<int>(TreeEleType::Num); 

	testLinkBinaryTree->addEleTo("0", 0, false);
	testLinkBinaryTree->addEleTo("00", 1, false);
	testLinkBinaryTree->addEleTo("01", 2, false);
	testLinkBinaryTree->addEleTo("000", 3, false);
	testLinkBinaryTree->addEleTo("001", 4, false);
	testLinkBinaryTree->addEleTo("010", 5, false);
	testLinkBinaryTree->addEleTo("011", 6, false);
	testLinkBinaryTree->addEleTo("0000", 8, false);
	testLinkBinaryTree->addEleTo("0001", 9, false);
	testLinkBinaryTree->addEleTo("0010", 10, false);
	testLinkBinaryTree->addEleTo("0011", 11, false);
	testLinkBinaryTree->addEleTo("0100", 12, false);
	testLinkBinaryTree->addEleTo("0101", 13, false);
	testLinkBinaryTree->addEleTo("0110", 14, false);
	testLinkBinaryTree->addEleTo("0111", 15, false);

	testLinkBinaryTree->removeEleAt("011", true);
	testLinkBinaryTree->removeEleAt("000", true);
	
	LinkBinaryTree<int>::InOrderTraverse(testLinkBinaryTree->getNodeAt("0"), testPrint);//使用递归的中序访问

	cout << "\n------------------------------------------------\n" << endl;

	//testLinkBinaryTree->addEleTo("0101", 19, false);
	//testLinkBinaryTree->removeEleAt("0101", false);
	//testLinkBinaryTree->addEleTo("0101", 19, false);

	//testLinkBinaryTree->removeEleAt("00", true);

	//testLinkBinaryTree->addEleTo("00", 55, false);

	LinkBinaryTree<int>::InOrderTraverseWithStack(testLinkBinaryTree->getNodeAt("0"), testPrint);//非递归的中序访问

	cout << "\n------------------------------------------------\n" << endl;
	cout << testLinkBinaryTree->getValueAt("0100") << endl;

	delete testLinkBinaryTree;
	testLinkBinaryTree = nullptr;
	*/


//顺序二叉树测试------------------------------------------------------------------------------------------------

	//SqBinaryTree<int*> *testSqBinaryTree = new SqBinaryTree<int*>(4, TreeEleType::Num);
	//testSqBinaryTree->clearBinaryTree(false);
	//int* p;

	//p = (int*)malloc(sizeof(int));
	//*p = 0;
	//testSqBinaryTree->addEleTo("0", p, false);

	//p = (int*)malloc(sizeof(int));
	//*p = 1;

	//testSqBinaryTree->addEleTo("0", p, true);

	//p = (int*)malloc(sizeof(int));
	//*p = 3;

	//testSqBinaryTree->addEleTo("00", p, true);

	//p = (int*)malloc(sizeof(int));
	//*p = 4;

	//testSqBinaryTree->addEleTo("01", p, true);

	//p = (int*)malloc(sizeof(int));
	//*p = 5;

	//testSqBinaryTree->addEleTo("0111", p, true);

	////testSqBinaryTree->removeEleAt("0111");

	//testSqBinaryTree->LevelOrderTraverse(testPrint);

//-----------------------------------------------------------------------------------------------
	cout << "\n测试结束\n" << endl;
	system("pause");
    return 0;
}

