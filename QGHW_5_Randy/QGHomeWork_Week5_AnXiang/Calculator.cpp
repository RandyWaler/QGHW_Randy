#include "Calculator.h"

#include <iostream>
#include <malloc.h>

using namespace std;
using namespace symbolEle;

int Calculator::arryFlag = 0;
int Calculator::exSize = 0;
//float* Calculator::eleNodeArry = nullptr;
LinkBinaryTree<Symbol*>* Calculator::symbolTree = nullptr;
Calculator::Calculator()
{
	middleEx = new ForwardList();
	frontEx = new ForwardList();

	symbolStack = new LinkStack<Symbol>();
	symbolStack2 = new LinkStack<Symbol>();


	symbolTree = new LinkBinaryTree<Symbol*>(TreeEleType::Ptr);
	symbolMiddleEx = nullptr;
	//eleNodeArry = nullptr;

}


Calculator::~Calculator()
{
}

void Calculator::reSet()
{
	middleEx->clear();
	frontEx->clear();

	symbolStack->clearStack();
	symbolStack->initStack();
	symbolStack2->clearStack();
	symbolStack2->initStack();

	symbolTree->ClearTree();

	if (symbolMiddleEx) {
		free(symbolMiddleEx);
	}
	symbolMiddleEx = nullptr;

	//if (eleNodeArry) {
	//	free(eleNodeArry);
	//}
	//eleNodeArry = nullptr;


}

void Calculator::getInputEx()
{
	reSet();
	cout << "请输入一个中缀式：" << endl;
	char str[512] = { 0 };
	
	cin >> str;
	SymbolType nowWillGetType = SymbolType::Number;
	Symbol newSymbol;
	char chlast='\0';
	for (int i = 0; str[i] != '\0'&&str[i] != '\n'&&i<strLength; ) {
		if (nowWillGetType == SymbolType::Number) {//当前应获取一个数字变量
			int start = i;//起始位下标
			int end = i;//终止位下标
			int flagNum = 1;//数字正负号
			float bitNum = 1.0f;//尾位数量级
			bool isPoint = false;//是否已经遇到小数点
			float numRes = 0.0f;//数字结果
			int nagCase = 0;
			bool isHaveNag = false;
			for (; str[i] != '\0'&&str[i] != '\n'&&i<strLength;i++) {//移动下标直到找到一个数字
				if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
					start = i; 
					break;
				}
				else if(str[i]=='-')
				{
					    
					if (nagCase == 0) {
						for (int j = i + 1; str[j] != '\0'&&str[j] != '\n'&&j < strLength; j++) {
							if (str[j] == '(') {
								nagCase = 1;
								if (chlast == '-') {
									cerr << "\n非法表达式！！！case1 请勿使用多重负号翻转，否则无法判断翻转负号和运算负号\n" << endl;
									reSet();
									return;
								}
									
								break;
							}
							else if (str[j] - '0' >= 0 && str[j] - '0' <= 9)
							{
								nagCase = 2;
								break;
							}
						}
						if (nagCase == 1) {
							if (!isHaveNag) {
								isHaveNag = true;

								int nagTime = -1;
								for (int j = i + 1; str[j] != '\0'&&str[j] != '\n'&&j < strLength; j++) {
									if (str[j] == '(') {
										break;
									}
									else if (str[j] == '-') {
										nagTime *= -1;
									}
								}
								if (nagTime == -1) {
									newSymbol = { SymbolType::Operator,'-',0.0f };
									middleEx->push_back(newSymbol);
								}
							}
							else
							{
								cerr << "\n非法表达式！！！case1.1 请勿使用多重负号翻转，否则无法判断翻转负号和运算负号\n" << endl;
								reSet();
								return;
							}
						}
					}
					if(nagCase==2)
					{
						flagNum *= -1;
					}
					
					
				}
				else
				{
					if (str[i] != '+'&&str[i] != '(') {
						cerr << "\n非法表达式！！！case2 运算符不匹配\n" << endl;
						reSet();
						return;
					}
					if (str[i] == '(') {
						newSymbol = { SymbolType::Operator,'(',0.0f };
						middleEx->push_back(newSymbol);
						nagCase = 0;
					}
				}
			}
			for (end = start+1,i=start+1; end<strLength&&str[end] != '\0'&&str[end] != '\n'; end++) {
				
				if (str[end] - '0' < 0 || str[end] - '0' > 9) {//发现非数字
					if (str[end] == '.') {//发现小数点
						if (isPoint) {//多个小数点
							cerr << "\n非法表达式！！！case3 多重小数点\n" << endl;
							reSet();
							return;
						}
						else if (str[end + 1] - '0'<0 ||str[end+1]-'0'>9) {//小数点后没有数字
							cerr << "\n非法表达式！！！case4 小数点后无数字\n" << endl;
							reSet(); 
							return;
						}
						isPoint = true;
					}
					else
					{
						if (str[end] == '+'||str[end] == '-'|| str[end] == '*' || str[end] == '/'||str[end] == '(' || str[end] == ')'|| str[end] == '^' || str[end] == '%') {
							i = end;
							break;
						}
						else//奇异符号
						{
							cerr << "\n非法表达式！！！case5 奇异符号\n" << endl;
							reSet();
							return;
						}
					}
				}
				else
				{
					if (isPoint) {
						bitNum *= 0.1f;
					}
				}
			}
			for (int j = end - 1; j >= start; j -- ) {
				if (str[j] - '0' >= 0 && str[j] - '0' <= 9) {
					numRes += (str[j] - '0')*bitNum;
					bitNum *= 10;
				}
			}
			numRes *= flagNum;
			newSymbol = { SymbolType::Number,'\0',numRes };
			middleEx->push_back(newSymbol);
			//准备符号获取
			nowWillGetType = SymbolType::Operator;
			if (str[end] == '\0' || str[end] == '\n' || end  >= strLength) {
				if (str[end-1] - '0' >= 0 && str[end-1] - '0' <= 9) {
					break;//数字结尾
				}
				else
				{
					cerr << "\n非法表达式！！！case6 运算符不匹配\n" << endl;
					reSet();
					return;
				}
			}

		}
		else
		{
			bool sigleSym = false;
			for (; str[i] != '\0'&&str[i] != '\n'&&i < strLength; i++) {		
				if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'||str[i] == '^' || str[i] == '%') {		
					if (!sigleSym) {
						sigleSym = true;
						if (str[i] == '-') {
							
							int nagTime = -1;
							int j;
							for (j = i + 1; str[j] != '\0'&&str[j] != '\n'&&j < strLength; j++) {
								if (str[j] == '-') {
									nagTime *= -1;
								}
								else if(str[j]=='('|| (str[j] - '0' >= 0 && str[j] - '0' <= 9))
								{
									break;
								}
								else if (str[j] != '+'&&str[j] != '(')
								{
									cerr << "\n非法表达式！！！case7 奇异符号\n" << endl;
									reSet();
									return;
								}
							}
							if (str[j] == '\0' || str[j] == '\n' || j >= strLength) {
								cerr << "\n非法表达式！！！case8 运算符不匹配\n" << endl;
								reSet();
								return;
							}
							if (nagTime == -1) {
								newSymbol = { SymbolType::Operator,'-',0.0f };
								middleEx->push_back(newSymbol);
								chlast = '-';
							}
							else
							{
								newSymbol = { SymbolType::Operator,'+',0.0f };
								middleEx->push_back(newSymbol);
								chlast = '+';
							}
							i = j - 1;
							continue;
						}
						else
						{
							newSymbol = { SymbolType::Operator,str[i],0.0f };
							middleEx->push_back(newSymbol);
							nowWillGetType = SymbolType::Number;
							chlast = str[i];
							continue;
						}

					}
					else
					{
						if (str[i] == '+' || str[i] == '-') {
							nowWillGetType = SymbolType::Number;
							break;
						}
						else
						{
							cerr << "\n非法表达式！！！case9 奇异符号\n" << endl;
							reSet();
							return;
						}
					}
				}
				else if( str[i] == '(' || str[i] == ')')
				{
					if (sigleSym&&str[i] == ')') {
						cerr << "\n非法表达式！！！case10 运算符不匹配\n" << endl;
						reSet();
						return;
					}
					newSymbol = { SymbolType::Operator,str[i],0.0f };
					middleEx->push_back(newSymbol);
					nowWillGetType = SymbolType::Number;
					continue;
				}
				else if(str[i] - '0' >= 0 && str[i] - '0' <= 9)
				{
					nowWillGetType = SymbolType::Number;
					break;
					
				}
				else
				{
					
					cerr << "\n非法表达式！！！case11 奇异符号\n" << endl;
					reSet();
					return;
				}
			}		
		}
	
		
	}
	
	if (nowWillGetType == SymbolType::Number&&middleEx->back()->ch!=')') {

		cerr << "\n非法表达式！！！case12 运算符不匹配\n" << endl;
		reSet();
		return;
	}
	cout << "\n输入中缀式：\n" << endl;
	middleEx->showAllEle();
	changeFrontEx();
}

void Calculator::changeFrontEx()
{
	symbolStack->clearStack();//作为辅助栈
	symbolStack->initStack();
	symbolStack2->clearStack();//作为结果栈 最后弹出转换为前缀式
	symbolStack2->initStack();

	Symbol newCalEle;
	Symbol check;
	if (symbolMiddleEx) {
		free(symbolMiddleEx);
	}
	symbolMiddleEx = (Symbol*)malloc(sizeof(Symbol)*middleEx->size());

	//if (eleNodeArry) {
	//	free(eleNodeArry);
	//}
	//eleNodeArry = (float*)malloc(sizeof(float)*middleEx->size());

	exSize = middleEx->size();
	for (int i=0; middleEx->size() > 0;i++) {
		symbolMiddleEx[i] = *middleEx->front();
		middleEx->pop_front();
	}
	cout << "检查数组：\n" << endl;
	for (int i = 0; i < exSize; i++) {
		checkSymbol(&symbolMiddleEx[i]);
	}
	//从后向前遍历
	for (int i = exSize - 1; i >= 0; i--) {
		check = symbolMiddleEx[i];
		if (check.type == SymbolType::Number) {
			newCalEle = { SymbolType::Number,'\0',check.fl };
			symbolStack2->pushStack(newCalEle);
		}
		else
		{
			if (check.ch == ')') {
				newCalEle = { SymbolType::Operator,check.ch,0.0f };
				symbolStack->pushStack(newCalEle);
			}
			else if (check.ch == '(') {
				bool haveget = false;
				for (; symbolStack->getSizeNow() > 0;) {
					symbolStack->popStack(&newCalEle);
					if (newCalEle.ch == ')') {
						haveget = true;
						break;
					}
					else
					{
						symbolStack2->pushStack(newCalEle);
					}
				}

				if (!haveget) {
					cerr << "Error：表达式括号不匹配！！！a\n" <<i<< endl;
					reSet();
					return;
				}
			}
			else if (check.ch == '^') {//最高级别求幂运算 强制压栈
				newCalEle = { SymbolType::Operator,check.ch,0.0f };
				symbolStack->pushStack(newCalEle);
			}
			else if (check.ch == '*' || check.ch == '/' || check.ch == '%') {
				while (true)
				{
					if (symbolStack->isStackEmpty()) {
						newCalEle = { SymbolType::Operator,check.ch,0.0f };
						symbolStack->pushStack(newCalEle);
						break;
					}
					else if (symbolStack->getStackTopEle()->ch != '^') {
						newCalEle = { SymbolType::Operator,check.ch,0.0f };
						symbolStack->pushStack(newCalEle);
						break;
					}
					else
					{
						symbolStack->popStack(&newCalEle);
						symbolStack2->pushStack(newCalEle);
					}
				}
				
			}
			else if (check.ch == '+' || check.ch == '-') {
				while (true)
				{
					if (symbolStack->isStackEmpty()) {
						newCalEle = { SymbolType::Operator,check.ch,0.0f };
						symbolStack->pushStack(newCalEle);
						break;
					}
					else if (symbolStack->getStackTopEle()->ch != '^'&&symbolStack->getStackTopEle()->ch != '*'&&symbolStack->getStackTopEle()->ch != '/'&&symbolStack->getStackTopEle()->ch != '%') {
						newCalEle = { SymbolType::Operator,check.ch,0.0f };
						symbolStack->pushStack(newCalEle);
						break;
					}
					else
					{
						symbolStack->popStack(&newCalEle);
						symbolStack2->pushStack(newCalEle);
					}
				}
			}
		}
	}

	//弹出辅助栈中剩余元素
	while(symbolStack->getSizeNow() > 0) {
		symbolStack->popStack(&newCalEle);
		if (newCalEle.ch == '(' || newCalEle.ch == ')') {
			cerr << "Error：表达式括号不匹配！！！b\n" << endl;
			reSet();
			return;
		}
		symbolStack2->pushStack(newCalEle);
	}

	while(symbolStack2->getSizeNow() > 0) {
		symbolStack2->popStack(&newCalEle);
		frontEx->push_back(newCalEle);
	}
	
	cout << "\n前缀式：" << endl;
	frontEx->showAllEleLink();

	free(symbolMiddleEx);
	symbolMiddleEx = nullptr;

	changeTree();

}

void Calculator::changeTree()
{
	stack<string>* posStack = new stack<string>();

	symbolTree->ClearTree();

	string posString="0";
	posStack->push(posString);

	Symbol* newSymbol;
	Symbol check;
	string addPos;



	while (frontEx->size()>0)
	{
		check = *frontEx->front();
		frontEx->pop_front();
		addPos.clear();
		addPos = posStack->top();
		posStack->pop();


		if (addPos.length()>0) {
			newSymbol = (Symbol*)malloc(sizeof(Symbol));

			newSymbol->ch = check.ch;
			newSymbol->fl = check.fl;
			newSymbol->type = check.type;

			symbolTree->addEleTo(addPos.c_str(), newSymbol, false);

			if (newSymbol->type == SymbolType::Operator) {
				string newPos = addPos;
				string newPos2 = addPos;
				newPos += "1";
				newPos2 += "0";
				posStack->push(newPos);
				posStack->push(newPos2);
			}
		}
		else
		{
			cerr << "Error：表达式有误！！！\n" << endl;
			delete posStack;
			reSet();
			return;
		}
	}
	cout << "\n前序访问检查树：" << endl;
	LinkBinaryTree<Symbol*>::PreOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;
	cout << "\n中序访问检查树：" << endl;
	LinkBinaryTree<Symbol*>::InOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;

	cout << "\n后序访问检查树：" << endl;
	LinkBinaryTree<Symbol*>::PostOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;
	delete posStack;
	Calculation();
}

void Calculator::Calculation()//计算表达式树
{
	arryFlag = 0;
	LinkBinaryTree<Symbol*>::PostOrderTraverse(symbolTree->getNodeAt("0"), this->CalCulationTree);
	//if (eleNodeArry) {
	//	free(eleNodeArry);
	//}
	//eleNodeArry = nullptr;
}

void Calculator::CalCulationTree(LinkBinaryTree<Symbol*>::EleNode * eNode)
{
	if (eNode->eleValue->type == SymbolType::Number) {
		return;
	}
	else
	{
		if (eNode->left->eleValue->type != SymbolType::Number || eNode->right->eleValue->type != SymbolType::Number) {
			cerr << "Error：计算顺序有误！！！\n" << endl;
			return;
		}
		float result;
		float f1 = eNode->left->eleValue->fl;
		float f2 = eNode->right->eleValue->fl;
		switch (eNode->eleValue->ch)
		{
		case '^':
			result = pow(f1, f2);
			break;
		case '%':
			result = (float)((int)f1%(int)f2);
			break;
		case '*':
			result = f1 * f2;
			break;
		case '/':
			result = f1 / f2;
			break;
		case '+':
			result = f1 + f2;
			break;
		case '-':
			result = f1 - f2;
			break;
		default:
			cerr << "Error：表达式有误！！！" << endl;
			break;
		}
		
		eNode->eleValue->type = SymbolType::Number;
		eNode->eleValue->fl = result;
		cout << "\n运算符：" << eNode->eleValue->ch << endl;
		cout << "计算结果：" << result << endl;
		if (eNode == symbolTree->getNodeAt("0")) {
			cout << "\n根处取到结果：" << result <<'\n'<<endl;
		}
	}
}

void checkSymbol(Symbol* sym)
{
	if (sym->type == SymbolType::Number) {
		cout << sym->fl;
	}
	else
	{
		cout << sym->ch;
	}

}

