/*STACK Version 2.0 на основе односвязного списка*/
#include <iostream>
#include <stack>

template <typename Type>
class Node {
public:
	Type data;				// Какие-либо абстрактные данные, произвольного типа
	Node <Type> *next;		// Указатель на следующий узел списка
	// Конструктор узла, принимает на вход данные и указатель на следующий элемент
	Node(Type new_data, Node<Type> *next_node) {
		data = new_data;
		next = next_node;
	}
};

template <typename Type>
class Stack {
private:
	size_t size;			// Размер стека, кол-во элементов
	Node<Type> *ptop;		// Указатель на текущий элемент стека, т.е. на самый верхний
public:
	Stack() {
		size = 0;
		ptop = nullptr;
	}
	~Stack() {
		while (sizes()) {
			pop();
		}
	}
	// Добавление элемента в стек
	void push(const Type node) {
		// Создаётся новый объект (узел) произвольного типа и выделяется память и присваивается адрес 
		Node<Type> *new_object = new Node<Type>(node, ptop);
		++size;				// Увеличили счётчик
		ptop = new_object;	// Теперь текущий указатель (голова), указывает на новый (добавленный) элемент.
	}
	void pop() {
		//if (size == 0) { return; }
		--size;
		Node<Type> *tmp = ptop;
		ptop = ptop->next;
		delete tmp;
	}
	// Получить значение (абстрактные данные верхнего элемента стека)
	Type top() { return ptop->data; }
	// Количество элементов в стеке
	size_t sizes() { return size; }
};

// Функция для мини-теста
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
    ui stack_size = 5'000'000;
    Stack<int> my_stack;
    std::stack<int> stl_stack;
    
    std::cout << "Начало теста на самописном стеке\n";
    clock_t time = clock();
    for (ui i = 0; i < stack_size; ++i) {
        my_stack.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов в самодельный стек: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (my_stack.sizes()) { my_stack.pop(); }
    time = clock() - time;
    std::cout << "Удаление элементов из самодельного стека: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    std::cout << "====================Тест завершился====================\n";
  
    std::cout << "Начало теста на стеке STL\n";
    time = clock();
    for (ui i = 0; i < stack_size; ++i) {
        stl_stack.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов в стек STL: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (stl_stack.size()) { stl_stack.pop(); }
    time = clock() - time;
    std::cout << "Удаление элементов из стека STL: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    std::cout << "====================Тест завершился====================\n";
}


int main() {
	setlocale(LC_ALL, "Russian");

	testing();

	return 0;
}