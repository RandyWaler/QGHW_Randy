#include "Calculator.h"

#include <iostream>
#include <malloc.h>

using namespace std;
using namespace symbolEle;

Calculator::Calculator()
{
	middleEx = new ForwardList();
	backEx = new ForwardList();
	symbolStack = new LinkStack<Symbol>();
}


Calculator::~Calculator()
{
}

void Calculator::reSet()
{
	middleEx->clear();
	backEx->clear();
	symbolStack->clearStack();
	symbolStack->initStack();
}

void Calculator::getInputEx()
{
	reSet();
	cout << "请输入一个中缀式：" << endl;
	char str[512] = { 0 };
	
	cin >> str;
	SymbolType nowWillGetType = SymbolType::Number;
	Symbol newSymbol;
	char chlast;
	for (int i = 0; str[i] != '\0'&&str[i] != '\n'&&i<strLength; ) {
		if (nowWillGetType == SymbolType::Number) {//当前应获取一个数字变量
			int start = i;//起始位下标
			int end = i;//终止位下标
			int flagNum = 1;//数字正负号
			float bitNum = 1.0f;//尾位数量级
			bool isPoint = false;//是否已经遇到小数点
			float numRes = 0.0f;//数字结果
	
			for (; str[i] != '\0'&&str[i] != '\n'&&i<strLength;i++) {//移动下标直到找到一个数字
				if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
					start = i; 
					break;
				}
				else if(str[i]=='-')//遇到的负号视为给数字的负号
				{
				
						for (int j = i+1; str[j] != '\0'&&str[j] != '\n'&&j < strLength; j++) {
							if (str[j] == '(') {
								newSymbol = { SymbolType::Operator,'-',0.0f };
								middleEx->push_back(newSymbol);
								break;
							}
							else if(str[j]-'0'>=0&&str[j]-'0'<=9)
							{
								flagNum *= -1;
								break;
							}
						}					
					//若之后没有( 视为给数字的负号否则负号入队
					
				}
				else
				{
					if (str[i] != '+'&&str[i] != '(') {
						cerr << "\n非法表达式！！！case1 运算符不匹配\n" << endl;
						reSet();
						return;
					}
					if (str[i] == '(') {
						newSymbol = { SymbolType::Operator,'(',0.0f };
						middleEx->push_back(newSymbol);
					}
				}
			}
			for (end = start+1,i=start+1; end<strLength&&str[end] != '\0'&&str[end] != '\n'; end++) {
				
				if (str[end] - '0' < 0 || str[end] - '0' > 9) {//发现非数字
					if (str[end] == '.') {//发现小数点
						if (isPoint) {//多个小数点
							cerr << "\n非法表达式！！！case2 多重小数点\n" << endl;
							reSet();
							return;
						}
						else if (str[end + 1] - '0'<0 ||str[end+1]-'0'>9) {//小数点后没有数字
							cerr << "\n非法表达式！！！case3 小数点后无数字\n" << endl;
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
							cerr << "\n非法表达式！！！case4 奇异符号\n" << endl;
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
					cerr << "\n非法表达式！！！case5 运算符不匹配\n" << endl;
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
						newSymbol = { SymbolType::Operator,str[i],0.0f };
						middleEx->push_back(newSymbol);
						nowWillGetType = SymbolType::Number;
						continue;
					}
					else
					{
						if (str[i] == '+' || str[i] == '-') {
							nowWillGetType = SymbolType::Number;
							break;
						}
						else
						{
							cerr << "\n非法表达式！！！case6 奇异符号\n" << endl;
							reSet();
							return;
						}
					}
				}
				else if( str[i] == '(' || str[i] == ')')
				{
					if (sigleSym&&str[i] == ')') {
						cerr << "\n非法表达式！！！case7 运算符不匹配\n" << endl;
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
					
					cerr << "\n非法表达式！！！case8 奇异符号\n" << endl;
					reSet();
					return;
				}
			}		
		}
	
		
	}
	
	if (nowWillGetType == SymbolType::Number&&middleEx->back()->ch!=')') {

		cerr << "\n非法表达式！！！case9 运算符不匹配\n" << endl;
		reSet();
		return;
	}
	cout << "\n输入中缀式：\n" << endl;
	middleEx->showAllEle();
	changeBackEx();
}

void Calculator::changeBackEx()
{
	symbolStack->clearStack();
	symbolStack->initStack();
	Symbol newSym;
	while (middleEx->size()!=0)
	{
		Symbol *checkSymbol = middleEx->front();

		if (checkSymbol->type == SymbolType::Number) {//数字直接入队
			newSym = { SymbolType::Number,'\0',checkSymbol->fl };
			backEx->push_back(newSym);
		}
		else
		{
			if (checkSymbol->ch == '(') {//左括号直接入栈
				newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
				symbolStack->pushStack(newSym);
			}
			else if(checkSymbol->ch == ')')//右括号，弹出栈中元素直到遇到(
			{
				Symbol popSym;
				while (true)
				{
					symbolStack->popStack(&popSym);
					if (popSym.ch == '(') {
						break;
					}
					else
					{
						backEx->push_back(popSym);
					}
				}
			}
			else if(checkSymbol->ch=='^') //求幂运算符，最高级别
			{
				if (symbolStack->isStackEmpty()) {
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					symbolStack->pushStack(newSym);
				}
				else if (symbolStack->getStackTopEle()->ch != '^') {//顶元素不是 ^ 压栈
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					symbolStack->pushStack(newSym);
				}
				else
				{
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					backEx->push_back(newSym);
				}
			}
			else if(checkSymbol->ch == '*'|| checkSymbol->ch == '/'||checkSymbol->ch == '%')//第二级别
			{
				while (true)
				{
					if (symbolStack->isStackEmpty()) {
						newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
						symbolStack->pushStack(newSym);
						break;
					}
					else if (symbolStack->getStackTopEle()->ch == '(' || symbolStack->getStackTopEle()->ch == '+' || symbolStack->getStackTopEle()->ch == '-') {
						newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
						symbolStack->pushStack(newSym);
						break;
					}
					else
					{
						Symbol popSym;
						symbolStack->popStack(&popSym);
						backEx->push_back(popSym);
					}
				}
			}
			else if(checkSymbol->ch == '+'|| checkSymbol->ch == '-')//最低级别
			{
				while (true)
				{
					if (symbolStack->isStackEmpty()) {
						newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
						symbolStack->pushStack(newSym);
						break;
					}
					else if (symbolStack->getStackTopEle()->ch == '(') {
						newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
						symbolStack->pushStack(newSym);
						break;
					}
					else
					{
						Symbol popSym;
						symbolStack->popStack(&popSym);
						backEx->push_back(popSym);
					}
				}
			}
		}
		middleEx->pop_front();
	}
	//剩余栈中元素弹出
	while (!symbolStack->isStackEmpty())
	{
		Symbol popSym;
		symbolStack->popStack(&popSym);
		if (popSym.ch != '('&&popSym.ch != ')') {
			backEx->push_back(popSym);
		}
	}
	cout << "后缀式：" << endl;
	backEx->showAllEleLink();

	Calculation();
}

void Calculator::Calculation()
{
	Symbol *exSym;
	Symbol newSym;
	symbolStack->clearStack();
	symbolStack->initStack();
	bool haveOper = false;//是否已经计算了一次运算符
	bool isZore = false;
	while (backEx->size()!=0)
	{
		exSym = backEx->front();
		if (exSym->type == SymbolType::Number) {//数字入栈
			
			newSym = { SymbolType::Number,'\0',exSym->fl };
			symbolStack->pushStack(newSym);
			haveOper = false;
			//cout << "数字: " << exSym->fl << endl;
		}
		else
		{
			//cout << "算符: " << exSym->ch<<endl;
			if (!haveOper) {//执行运算
				haveOper = true;
				Symbol firstEle;
				symbolStack->popStack(&firstEle);
				Symbol SceEle;
				symbolStack->popStack(&SceEle);
				Symbol newCalEle;
				switch (exSym->ch)
				{
				case '+':
					newCalEle = { SymbolType::Number,'\0',SceEle.fl + firstEle.fl };
					symbolStack->pushStack(newCalEle);
					break;
				case '-':
					newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
					symbolStack->pushStack(newCalEle);
					break;
				case '*':
					newCalEle = { SymbolType::Number,'\0',SceEle.fl * firstEle.fl };
					symbolStack->pushStack(newCalEle);
					break;
				case '/':
					if (firstEle.fl == 0) {
						cerr << "\n发现除0运算！！！\n" << endl;
						isZore = true;
					}
					newCalEle = { SymbolType::Number,'\0',SceEle.fl / firstEle.fl };
					symbolStack->pushStack(newCalEle);
					break;
				case '^':
					newCalEle = { SymbolType::Number,'\0',pow(SceEle.fl,firstEle.fl) };
					symbolStack->pushStack(newCalEle);
					break;
				case '%':
					newCalEle = { SymbolType::Number,'\0',(float)((int)SceEle.fl%(int)firstEle.fl) };
					symbolStack->pushStack(newCalEle);
					break;
				default:
					cerr << "\n后缀式错误！！！a\n" << endl;
					return;
				}
				
			}
			else
			{
				if (exSym->ch == '-') {
					if (symbolStack->getSizeNow() == 1) {//只有一个 负号乘给该数字
						Symbol firstEle;
						symbolStack->popStack(&firstEle);
						firstEle.fl *= -1;
						symbolStack->pushStack(firstEle);
					}
					else if(symbolStack->getSizeNow()>=2)//不止一个
					{
						Symbol sceEle = {SymbolType::Operator,'F',0.0f};
						backEx->getSceondEle(&sceEle);
						//尾负号正常运算
						if (sceEle.ch=='F' || sceEle.type == SymbolType::Number) {
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							Symbol SceEle;
							symbolStack->popStack(&SceEle);
							Symbol newCalEle;
							newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
							symbolStack->pushStack(newCalEle);
						}
						else
						{
							//非尾负号乘给第一个数字
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							firstEle.fl *= -1;
							
							symbolStack->pushStack(firstEle);
							//cout << "非尾负号  " <<symbolStack->getStackTopEle()->fl<<"  "<<symbolStack->getSizeNow()<< endl;
						}
					}
				}
				else
				{
					//栈中大于两个元素正常计算
					if (symbolStack->getSizeNow() >= 2)//不止一个
					{
						Symbol firstEle;
						symbolStack->popStack(&firstEle);
						Symbol SceEle;
						symbolStack->popStack(&SceEle);
						Symbol newCalEle;
						switch (exSym->ch)
						{
						case '+':
							newCalEle = { SymbolType::Number,'\0',SceEle.fl + firstEle.fl };
							symbolStack->pushStack(newCalEle);
							break;
						case '-':
							newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
							symbolStack->pushStack(newCalEle);
							break;
						case '*':
							newCalEle = { SymbolType::Number,'\0',SceEle.fl * firstEle.fl };
							symbolStack->pushStack(newCalEle);
							break;
						case '/':
							if (firstEle.fl == 0) {
								cerr << "\n发现除0运算！！！\n" << endl;
								return;
							}
							newCalEle = { SymbolType::Number,'\0',SceEle.fl / firstEle.fl };
							symbolStack->pushStack(newCalEle);
							break;
						case '^':
							newCalEle = { SymbolType::Number,'\0',pow(SceEle.fl,firstEle.fl) };
							symbolStack->pushStack(newCalEle);
							break;
						case '%':
							newCalEle = { SymbolType::Number,'\0',(float)((int)SceEle.fl % (int)firstEle.fl) };
							symbolStack->pushStack(newCalEle);
							break;
						default:
							cerr << "\n后缀式错误！！！a\n" << endl;
							return;
						}
					}
					else
					{

						//否则后缀式有误
						cerr << "\n后缀式错误！！！b \n" << exSym->ch << endl;
						return;
					}
				}
				
			}
		}
		backEx->pop_front();

	}
	if (isZore) {
		return;
	}
	cout << "表达式计算结果：" << symbolStack->getStackTopEle()->fl << endl;
}
