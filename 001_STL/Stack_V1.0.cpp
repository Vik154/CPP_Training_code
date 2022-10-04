/*STACK_VERSION_1.0*/
#include <iostream>
#include <typeinfo>
#include <new>			// Для обработчика ошибок Try/catch

template <typename Type>
class Stack {
private:
	Type* stack;						// Указатель на стек
	int count;							// Счётчик элементов
public:
	Stack();							// Конструктор инициализации (создания экземпляра)
	Stack(const Stack<Type> &stk);		// Конструктор копирования
	~Stack();							// Деструктор (освобождение памяти)
	
	void push(const Type &element);		// Добавление элемента в вершину стека
	void print();						// Отображение инфы в stdout
	Type pop();							// Удалить верхний элемент и вернуть его
	Type head();						// Получить верхний элемент  

	int  get_size() { return count; }		// Получить количество элементов в стеке
	bool is_empty() { return count == 0; }	// Проверить пустой стек или нет

	Stack<Type> operator = (Stack stk);
};


template <typename Type>
Stack<Type>::Stack() {
	stack = nullptr;
	count = 0;
}

template <typename Type>
Stack<Type>::Stack(const Stack& stk) {
	try {
		stack = new Type[stk.count];
		count = stk.count;
		for (int i = 0; i < count; i++) {
			stack[i] = stk.stack[i];
		}
	}
	catch (std::bad_alloc msg) {
		std::cout << msg.what() << std::endl;
	}
}

template <typename Type>
Stack<Type>::~Stack() {
	if (count > 0) { delete[] stack; }
}

template<typename Type>
void Stack<Type>::push(const Type& element) {
	Type* temp;
	try {
		temp = stack;
		stack = new Type[count + 1];
		count++;
		for (int i = 0; i < count - 1; ++i) {
			stack[i] = temp[i];
		}
		stack[count - 1] = element;
	}
	catch (std::bad_alloc msg) {
		std::cout << msg.what() << std::endl;
	}
}

template<typename Type>
void Stack<Type>::print() {
	Type* ptr = stack;
	std::cout << "Stack " << std::endl;
	if (count == 0) {
		std::cout << "is empty\n";
	}
	for (int i = 0; i < count; ++i) {
		std::cout << "Item[" << i << "] = " << *ptr << std::endl;
		ptr++;
	}
	std::cout << std::endl;
}

template <typename Type>
Type Stack<Type>::pop() {
	if (count == 0) { return 0; }
	count--;
	return stack[count];
}

template<typename Type>
Type Stack<Type>::head() {
	if (count == 0) { return 0; }
	return stack[count - 1];
}

template<typename Type>
Stack<Type> Stack<Type>::operator=(Stack stk) {
	if (count > 0) {
		count = 0;
		delete[] stack;
	}
	try {
		stack = new Type[stk.count];
		count = stk.count;
		for (int i = 0; i < count; i++)
			stack[i] = stk.stack[i];
	}
	catch (std::bad_alloc msg) {
		std::cout << msg.what() << std::endl;
	}
	return *this;
}

template <typename Type>
void pack(Stack<Type> &stk) {
	int choice;
	while (true) {
		std::cout << "Управление стеком: 1 - добавить элемент, 2 - удалить, 3 - напечатать, 4 - размер\n";
		std::cout << "5 - проверка на наличие элементов, 6 - Выход\n";
		do {
			std::cin >> choice;
			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout << "Введите значение повторно: ";
				std::cin >> choice;
			}
		} while (choice < 1 || choice > 6);
			
		Type tmp;
		switch (choice)	{
		case 1:
			std::cout << "Введите элемент для добавления: ";
			std::cin >> tmp;
			stk.push(tmp);
			std::cout << "Элемент " << tmp << " добавлен\n";
			break;
		case 2:
			tmp = stk.pop();
			std::cout << "Элемент " << tmp << " удалён\n";
			break;
		case 3:
			stk.print();
			break;
		case 4:
			std::cout << stk.get_size() << std::endl;
			break;
		case 5:
			if (stk.is_empty() != 0) { 
				std::cout << "Что-то есть\n";
				break;
			}
			else {
				std::cout << "Стек пуст\n";
				break;
			}
		case 6:
			return;
		}
	}
}

int main() {
	setlocale(0, "Rus");
	Stack<int> st_1;
	pack(st_1);
	//std::cout << typeid(5).name();
	return 0;
}