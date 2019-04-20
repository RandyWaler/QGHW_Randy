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
	changeFrontEx();
}

void Calculator::changeFrontEx()
{
	symbolStack->clearStack();//��Ϊ����ջ
	symbolStack->initStack();
	symbolStack2->clearStack();//��Ϊ���ջ ��󵯳�ת��Ϊǰ׺ʽ
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
	cout << "������飺\n" << endl;
	for (int i = 0; i < exSize; i++) {
		checkSymbol(&symbolMiddleEx[i]);
	}
	//�Ӻ���ǰ����
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
					cerr << "Error�����ʽ���Ų�ƥ�䣡����a\n" <<i<< endl;
					reSet();
					return;
				}
			}
			else if (check.ch == '^') {//��߼����������� ǿ��ѹջ
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

	//��������ջ��ʣ��Ԫ��
	while(symbolStack->getSizeNow() > 0) {
		symbolStack->popStack(&newCalEle);
		if (newCalEle.ch == '(' || newCalEle.ch == ')') {
			cerr << "Error�����ʽ���Ų�ƥ�䣡����b\n" << endl;
			reSet();
			return;
		}
		symbolStack2->pushStack(newCalEle);
	}

	while(symbolStack2->getSizeNow() > 0) {
		symbolStack2->popStack(&newCalEle);
		frontEx->push_back(newCalEle);
	}
	
	cout << "\nǰ׺ʽ��" << endl;
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
			cerr << "Error�����ʽ���󣡣���\n" << endl;
			delete posStack;
			reSet();
			return;
		}
	}
	cout << "\nǰ����ʼ������" << endl;
	LinkBinaryTree<Symbol*>::PreOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;
	cout << "\n������ʼ������" << endl;
	LinkBinaryTree<Symbol*>::InOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;

	cout << "\n������ʼ������" << endl;
	LinkBinaryTree<Symbol*>::PostOrderTraverse(symbolTree->getNodeAt("0"), checkSymbol);
	cout << "\n" << endl;
	delete posStack;
	Calculation();
}

void Calculator::Calculation()//������ʽ��
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
			cerr << "Error������˳�����󣡣���\n" << endl;
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
			cerr << "Error�����ʽ���󣡣���" << endl;
			break;
		}
		
		eNode->eleValue->type = SymbolType::Number;
		eNode->eleValue->fl = result;
		cout << "\n�������" << eNode->eleValue->ch << endl;
		cout << "��������" << result << endl;
		if (eNode == symbolTree->getNodeAt("0")) {
			cout << "\n����ȡ�������" << result <<'\n'<<endl;
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

