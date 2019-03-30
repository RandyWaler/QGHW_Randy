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
	cout << "������һ����׺ʽ��" << endl;
	char str[512] = { 0 };
	
	cin >> str;
	SymbolType nowWillGetType = SymbolType::Number;
	Symbol newSymbol;
	char chlast;
	for (int i = 0; str[i] != '\0'&&str[i] != '\n'&&i<strLength; ) {
		if (nowWillGetType == SymbolType::Number) {//��ǰӦ��ȡһ�����ֱ���
			int start = i;//��ʼλ�±�
			int end = i;//��ֹλ�±�
			int flagNum = 1;//����������
			float bitNum = 1.0f;//βλ������
			bool isPoint = false;//�Ƿ��Ѿ�����С����
			float numRes = 0.0f;//���ֽ��
	
			for (; str[i] != '\0'&&str[i] != '\n'&&i<strLength;i++) {//�ƶ��±�ֱ���ҵ�һ������
				if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
					start = i; 
					break;
				}
				else if(str[i]=='-')//�����ĸ�����Ϊ�����ֵĸ���
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
					//��֮��û��( ��Ϊ�����ֵĸ��ŷ��򸺺����
					
				}
				else
				{
					if (str[i] != '+'&&str[i] != '(') {
						cerr << "\n�Ƿ����ʽ������case1 �������ƥ��\n" << endl;
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
				
				if (str[end] - '0' < 0 || str[end] - '0' > 9) {//���ַ�����
					if (str[end] == '.') {//����С����
						if (isPoint) {//���С����
							cerr << "\n�Ƿ����ʽ������case2 ����С����\n" << endl;
							reSet();
							return;
						}
						else if (str[end + 1] - '0'<0 ||str[end+1]-'0'>9) {//С�����û������
							cerr << "\n�Ƿ����ʽ������case3 С�����������\n" << endl;
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
						else//�������
						{
							cerr << "\n�Ƿ����ʽ������case4 �������\n" << endl;
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
			//׼�����Ż�ȡ
			nowWillGetType = SymbolType::Operator;
			if (str[end] == '\0' || str[end] == '\n' || end  >= strLength) {
				if (str[end-1] - '0' >= 0 && str[end-1] - '0' <= 9) {
					break;//���ֽ�β
				}
				else
				{
					cerr << "\n�Ƿ����ʽ������case5 �������ƥ��\n" << endl;
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
							cerr << "\n�Ƿ����ʽ������case6 �������\n" << endl;
							reSet();
							return;
						}
					}
				}
				else if( str[i] == '(' || str[i] == ')')
				{
					if (sigleSym&&str[i] == ')') {
						cerr << "\n�Ƿ����ʽ������case7 �������ƥ��\n" << endl;
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
					
					cerr << "\n�Ƿ����ʽ������case8 �������\n" << endl;
					reSet();
					return;
				}
			}		
		}
	
		
	}
	
	if (nowWillGetType == SymbolType::Number&&middleEx->back()->ch!=')') {

		cerr << "\n�Ƿ����ʽ������case9 �������ƥ��\n" << endl;
		reSet();
		return;
	}
	cout << "\n������׺ʽ��\n" << endl;
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

		if (checkSymbol->type == SymbolType::Number) {//����ֱ�����
			newSym = { SymbolType::Number,'\0',checkSymbol->fl };
			backEx->push_back(newSym);
		}
		else
		{
			if (checkSymbol->ch == '(') {//������ֱ����ջ
				newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
				symbolStack->pushStack(newSym);
			}
			else if(checkSymbol->ch == ')')//�����ţ�����ջ��Ԫ��ֱ������(
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
			else if(checkSymbol->ch=='^') //�������������߼���
			{
				if (symbolStack->isStackEmpty()) {
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					symbolStack->pushStack(newSym);
				}
				else if (symbolStack->getStackTopEle()->ch != '^') {//��Ԫ�ز��� ^ ѹջ
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					symbolStack->pushStack(newSym);
				}
				else
				{
					newSym = { SymbolType::Operator,checkSymbol->ch,0.0f };
					backEx->push_back(newSym);
				}
			}
			else if(checkSymbol->ch == '*'|| checkSymbol->ch == '/'||checkSymbol->ch == '%')//�ڶ�����
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
			else if(checkSymbol->ch == '+'|| checkSymbol->ch == '-')//��ͼ���
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
	//ʣ��ջ��Ԫ�ص���
	while (!symbolStack->isStackEmpty())
	{
		Symbol popSym;
		symbolStack->popStack(&popSym);
		if (popSym.ch != '('&&popSym.ch != ')') {
			backEx->push_back(popSym);
		}
	}
	cout << "��׺ʽ��" << endl;
	backEx->showAllEleLink();

	Calculation();
}

void Calculator::Calculation()
{
	Symbol *exSym;
	Symbol newSym;
	symbolStack->clearStack();
	symbolStack->initStack();
	bool haveOper = false;//�Ƿ��Ѿ�������һ�������
	bool isZore = false;
	while (backEx->size()!=0)
	{
		exSym = backEx->front();
		if (exSym->type == SymbolType::Number) {//������ջ
			
			newSym = { SymbolType::Number,'\0',exSym->fl };
			symbolStack->pushStack(newSym);
			haveOper = false;
			//cout << "����: " << exSym->fl << endl;
		}
		else
		{
			//cout << "���: " << exSym->ch<<endl;
			if (!haveOper) {//ִ������
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
						cerr << "\n���ֳ�0���㣡����\n" << endl;
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
					cerr << "\n��׺ʽ���󣡣���a\n" << endl;
					return;
				}
				
			}
			else
			{
				if (exSym->ch == '-') {
					if (symbolStack->getSizeNow() == 1) {//ֻ��һ�� ���ų˸�������
						Symbol firstEle;
						symbolStack->popStack(&firstEle);
						firstEle.fl *= -1;
						symbolStack->pushStack(firstEle);
					}
					else if(symbolStack->getSizeNow()>=2)//��ֹһ��
					{
						Symbol sceEle = {SymbolType::Operator,'F',0.0f};
						backEx->getSceondEle(&sceEle);
						//β������������
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
							//��β���ų˸���һ������
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							firstEle.fl *= -1;
							
							symbolStack->pushStack(firstEle);
							//cout << "��β����  " <<symbolStack->getStackTopEle()->fl<<"  "<<symbolStack->getSizeNow()<< endl;
						}
					}
				}
				else
				{
					//ջ�д�������Ԫ����������
					if (symbolStack->getSizeNow() >= 2)//��ֹһ��
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
								cerr << "\n���ֳ�0���㣡����\n" << endl;
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
							cerr << "\n��׺ʽ���󣡣���a\n" << endl;
							return;
						}
					}
					else
					{

						//�����׺ʽ����
						cerr << "\n��׺ʽ���󣡣���b \n" << exSym->ch << endl;
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
	cout << "���ʽ��������" << symbolStack->getStackTopEle()->fl << endl;
}
