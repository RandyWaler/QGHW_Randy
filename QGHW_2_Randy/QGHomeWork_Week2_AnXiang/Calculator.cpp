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
	char chlast='\0';
	for (int i = 0; str[i] != '\0'&&str[i] != '\n'&&i<strLength; ) {
		if (nowWillGetType == SymbolType::Number) {//��ǰӦ��ȡһ�����ֱ���
			int start = i;//��ʼλ�±�
			int end = i;//��ֹλ�±�
			int flagNum = 1;//����������
			float bitNum = 1.0f;//βλ������
			bool isPoint = false;//�Ƿ��Ѿ�����С����
			float numRes = 0.0f;//���ֽ��
			int nagCase = 0;
			bool isHaveNag = false;
			for (; str[i] != '\0'&&str[i] != '\n'&&i<strLength;i++) {//�ƶ��±�ֱ���ҵ�һ������
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
									cerr << "\n�Ƿ����ʽ������case1 ����ʹ�ö��ظ��ŷ�ת�������޷��жϷ�ת���ź����㸺��\n" << endl;
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
								cerr << "\n�Ƿ����ʽ������case1.1 ����ʹ�ö��ظ��ŷ�ת�������޷��жϷ�ת���ź����㸺��\n" << endl;
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
						cerr << "\n�Ƿ����ʽ������case2 �������ƥ��\n" << endl;
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
				
				if (str[end] - '0' < 0 || str[end] - '0' > 9) {//���ַ�����
					if (str[end] == '.') {//����С����
						if (isPoint) {//���С����
							cerr << "\n�Ƿ����ʽ������case3 ����С����\n" << endl;
							reSet();
							return;
						}
						else if (str[end + 1] - '0'<0 ||str[end+1]-'0'>9) {//С�����û������
							cerr << "\n�Ƿ����ʽ������case4 С�����������\n" << endl;
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
							cerr << "\n�Ƿ����ʽ������case5 �������\n" << endl;
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
					cerr << "\n�Ƿ����ʽ������case6 �������ƥ��\n" << endl;
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
									cerr << "\n�Ƿ����ʽ������case7 �������\n" << endl;
									reSet();
									return;
								}
							}
							if (str[j] == '\0' || str[j] == '\n' || j >= strLength) {
								cerr << "\n�Ƿ����ʽ������case8 �������ƥ��\n" << endl;
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
							cerr << "\n�Ƿ����ʽ������case9 �������\n" << endl;
							reSet();
							return;
						}
					}
				}
				else if( str[i] == '(' || str[i] == ')')
				{
					if (sigleSym&&str[i] == ')') {
						cerr << "\n�Ƿ����ʽ������case10 �������ƥ��\n" << endl;
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
					
					cerr << "\n�Ƿ����ʽ������case11 �������\n" << endl;
					reSet();
					return;
				}
			}		
		}
	
		
	}
	
	if (nowWillGetType == SymbolType::Number&&middleEx->back()->ch!=')') {

		cerr << "\n�Ƿ����ʽ������case12 �������ƥ��\n" << endl;
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
				bool haveOutleft = false;
				while (symbolStack->getSizeNow()>=1)
				{
					symbolStack->popStack(&popSym);
					if (popSym.ch == '(') {
						haveOutleft = true;
						break;
					}
					else
					{
						backEx->push_back(popSym);
					}
				}
				if (!haveOutleft) {
					cerr << "\n�Ƿ����ʽ������case13 ���Ų�ƥ��\n" << endl;
					reSet();
					return;
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
		else
		{
			cerr << "\n�Ƿ����ʽ������case14 ���Ų�ƥ��\n" << endl;
			reSet();
			return;
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
	int onceNum = 0;
	//bool isChangeNag = false;
	while (backEx->size()!=0)
	{
		exSym = backEx->front();
		if (exSym->type == SymbolType::Number) {//������ջ
			
			newSym = { SymbolType::Number,'\0',exSym->fl };
			symbolStack->pushStack(newSym);
			if (haveOper) {
				onceNum = 0;
			}
			haveOper = false;
			onceNum++;
			//isChangeNag = false;
			//cout << "����: " << exSym->fl << endl;
		}
		else
		{
			//cout << "���: " << exSym->ch<<endl;
			if (!haveOper) {//ִ������
				onceNum--;
				haveOper = true;
				//isChangeNag = false;
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
					if (onceNum == 1) {//ֻ��һ�� ���ų˸�������
						Symbol firstEle;
						symbolStack->popStack(&firstEle);
						firstEle.fl *= -1;
						symbolStack->pushStack(firstEle);
					}
					else if (onceNum >= 2)//��ֹһ��
					{
						/*
						Symbol sceEle = { SymbolType::Operator,'F',0.0f };
						backEx->getSceondEle(&sceEle);
						if (sceEle.ch == 'F' || sceEle.type == SymbolType::Number) {//β������������
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							Symbol SceEle;
							symbolStack->popStack(&SceEle);
							Symbol newCalEle;
							newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
							symbolStack->pushStack(newCalEle);
							onceNum--;
						}
						else
						{
							if (sceEle.ch == '*' || sceEle.ch == '/' || sceEle.ch == '^' || sceEle.ch == '%') {
								if (onceNum <= 2) {
									//�󷽷��ָ߽����㣬�Ƿ�ת����
									Symbol firstEle;
									symbolStack->popStack(&firstEle);
									firstEle.fl *= -1;

									symbolStack->pushStack(firstEle);
								}
								else
								{

									Symbol firstEle;
									symbolStack->popStack(&firstEle);
									Symbol SceEle;
									symbolStack->popStack(&SceEle);
									Symbol newCalEle;
									newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
									symbolStack->pushStack(newCalEle);
									onceNum--;
								}
							}
							else
							{
								if (onceNum >= 2) {

									if (sceEle.ch == '-') {
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
										if (onceNum > 2) {
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
											Symbol firstEle;
											symbolStack->popStack(&firstEle);
											firstEle.fl *= -1;
											symbolStack->pushStack(firstEle);
										}
									}

									onceNum--;
								}
								else
								{
									Symbol firstEle;
									symbolStack->popStack(&firstEle);
									firstEle.fl *= -1;
									symbolStack->pushStack(firstEle);
								}
							}
						}
						*/

						//ɨ��֮���������Աȵ�����ջ��

						int k;
						for (k = 2;; k++) {
							Symbol checkEleSym = {SymbolType::Operator,'F',0.0f};
							backEx->getNEle(&checkEleSym, k);
							if (checkEleSym.ch == 'F' || checkEleSym.type == SymbolType::Number) {
								break;
							}
						}
						if (onceNum - (k - 1) >= 1) {//����
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							Symbol SceEle;
							symbolStack->popStack(&SceEle);
							Symbol newCalEle;
							newCalEle = { SymbolType::Number,'\0',SceEle.fl - firstEle.fl };
							symbolStack->pushStack(newCalEle);
						}
						else//�����Ƿ�ת����
						{
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							firstEle.fl *= -1;
							symbolStack->pushStack(firstEle);
						}
					}
					
					//�Ѿ����굥������ ��ʼʹ��ջ������
					else
					{
						if (symbolStack->getSizeNow() >= 2) {
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
							Symbol firstEle;
							symbolStack->popStack(&firstEle);
							firstEle.fl *= -1;
							symbolStack->pushStack(firstEle);
						}
					}
				}
				else
				{
					//ջ�д�������Ԫ����������
					if (symbolStack->getSizeNow() >= 2)//��ֹһ��
					{
						onceNum--;
						//isChangeNag = false;
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
						cerr << "\n��׺ʽ���󣡣��� ������ʹ���˵��ӵĸ��ŷ�ת�����޷��жϷ�ת���ź����㸺�� \n" << exSym->ch << endl;
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
	if (symbolStack->getSizeNow() == 0) {
		return;
	}
	if (symbolStack->getSizeNow() > 1) {
		float calRes = 0.0f;
		Symbol popEle;
		while (symbolStack->getSizeNow()!=0)
		{
			symbolStack->popStack(&popEle);
			calRes += popEle.fl;
		}
		popEle = { SymbolType::Number,'\0',calRes };
		symbolStack->pushStack(popEle);
	}
	cout << "���ʽ��������" << symbolStack->getStackTopEle()->fl << endl;
}
