#include "Main.h"
#include "SqStack.h"
#include "Calculator.h"
using namespace std;



int main() {

	Calculator * cal = new Calculator();
	while (true) {
		cal->getInputEx();
	}
	
	
	/*ForwardList* list = new ForwardList();
	list->showAllEle();
	Symbol newSymbol = { SymbolType::Number,'\0',1.5f, };
	list->push_front(newSymbol);
	Symbol newSymbol2 = { SymbolType::Operator,'-',0.0f, };
	list->push_front(newSymbol2);
	Symbol newSymbol3 = { SymbolType::Number,'\0',3.5f, };
	list->push_front(newSymbol3);

	cout << list->back()->fl<< endl;

	list->showAllEle();*/
	cout << "------²âÊÔ½áÊø------" << endl;
	system("pause");
	return 0;
}
