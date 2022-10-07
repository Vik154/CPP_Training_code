/*LIST Version 1.0 ---- Реализация односвязного списка*/
#include <iostream>
#include <memory>
#include <list>

void testing();

template <typename Type>
class List {
public:
	List();								// Конструктор
	~List();							// Деструктор

	void pop_back();					// Удаляет элемент в конце списка.
	void pop_front();					// Удаляет элемент в начале списка.
	void push_back(Type data);			// Добавляет элемент в конец списка.
	void push_front(Type data);			// Добавляет элемент в начало списка.
	void clear();						// Удаление (очистка) всего списка
	void insert(Type data, int index);	// Вставка значения по индексу
	void remove_at(int index);			// Удаление по индексу
	void remove(Type data);				// Удаление по значению
	//void reverse();					// Изменяет порядок следования элементов в списке на обратный.
	//void sort();						// Упорядочивает элементы списка по возрастанию.
	void print();						// Распечатать список

	bool empty()  {return sizes == 0;}  // Проверяет, пуст ли список.
	int  size()	       {return sizes;}	// Получить кол-во элементов в списке
	auto get_head_ptr() {return head;}	// Получить указатель на 1-ый элемент списка
	auto get_tail_ptr() {return tail;}	// Получить указаьель на последний элемент списка

	Type& get_tail() { return tail->data; }	// Получить данные первого узла
	Type& get_head() { return head->data; } // Получить данные последнего узла
	Type& operator [](const int index);		// Прототип перегруженного оператора индексирования списка

private:
	//template <typename Type>
	class Node {
	public:
		// Конструктор с параметром для создания узла
		Node(Type data) {
			this->data = data;
			this->next = nullptr;
		}
		Type data;		// Абстрактные данные
		Node *next;		// Указатель на следующий узел
	};
	Node *head;			// Указатель на 1-ый элемент списка (на голову)
	Node *tail;			// Указатель на последний эл списка (на хвост)
	int sizes;			// Кол-во элементов в списке
};


int main() {
	setlocale(LC_ALL, "Ru");
	testing();
	return 0;
}


template<typename Type>
List<Type>::List() {
	head = nullptr;
	tail = nullptr;
	sizes = 0;
}

template<typename Type>
List<Type>::~List() {
	clear();
}

template<typename Type>
void List<Type>::push_back(Type data) {
	// Проверить выделилась ли память
	try {
		// Создать указатель на новый объект узла
		Node* ptr = new Node(data);

		if (head == nullptr) {			// Если список пуст, тогда оба указателя новго узла указывают на него
			head = ptr;
			tail = ptr;
			sizes++;
			return;
		}
		tail->next = ptr;			// Предыдущий элемент списка теперь указывает на новый добавленный элемент
		tail = ptr;					// Хвост указвает на добавленный элемент, он теперь последний
		sizes++;					// Счётчик элементов
	}
	catch (std::bad_alloc msg) {
		// Если память выделить не удалось, то вывести системное сообщение
		std::cout << msg.what() << std::endl;
	}
}

template <typename Type>
void List<Type>::push_front(Type data) {
	Node *node = new Node(data);
	if (head == nullptr) {
		head = tail = node;
		sizes++;
		return;
	}
	node->next = head;
	head = node;
	sizes++;
}

template<typename T>
void List<T>::pop_front() {
	if (sizes == 0) { return; }
	Node* tmp = head;
	head = head->next;
	delete tmp;
	sizes--;
}

// Сложность О(n) - из-за итераций по всей длине списка
// Пока нет знаний, как сделать побыстрее, пока что :-)
template <typename Type>
void List<Type>::pop_back() {
	if (sizes == 0) { return; }
	Node *first = head;
	Node *last  = head;
	
	while (first->next) {
		last = first;
		first = first->next;
	}
	if (last == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		delete first->next;
		last->next = nullptr;
	}
	sizes--;
}

template<typename Type>
void List<Type>::clear() {
	while (sizes) {
		pop_front();
	}
}

template<typename Type>
void List<Type>::print() {
	if (sizes == 0) {
		std::cout << "List is empty." << std::endl;
		return;
	}
	std::cout << std::endl;
	Node* tmp = head;
	while (tmp != nullptr) {
		std::cout << tmp->data << " -> ";
		tmp = tmp->next;
	}
	delete tmp;
	std::cout << std::endl;
}

template<typename Type>
void List<Type>::remove_at(int index) {
	if (index == 0) {
		pop_front();
	}
	else {
		Node* previos = this->head;
		for (int i = 0; i < index - 1; i++) {
			previos = previos->next;
		}
		Node* to_delete = previos->next;
		previos->next = to_delete->next;
		delete to_delete;
		sizes--;
	}
}

template <typename Type>
void List<Type>::remove(Type data) {
	if (sizes == 0) { return; }
	if (head->data == data) { 
		pop_front();
		sizes--;
		return;
	}
	if (tail->data == data) {
		pop_back();
		sizes--;
		return;
	}
	Node *slow = head;
	Node *fast = head->next;
	while (fast && fast->data != data) {
		fast = fast->next;
		slow = slow->next;
	}
	if (!fast) { return; }
	slow->next = fast->next;
	delete fast;
	sizes--;
}

template <typename Type>
void List<Type>::insert(Type data, int index) {
	if (index < 0 || index > sizes) { return; }
	if (index == 0) { push_front(data); }

	Node* new_node = new Node(data);
	Node* tmp = head;
	for (int i = 0; i < index-1; i++) {
		tmp = tmp->next;
	}
	new_node->next = tmp->next;
	tmp->next = new_node;
	sizes++;
}

template<typename Type>
Type& List<Type>::operator[](const int index) {
	if (index < 0 || index - 1 > sizes) { 
		std::cout << "Invalid index\n";
		Type x = 0;
		return x;
		//throw out_of_range("Invalid index\n");
	}
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			return current->data;
		}
		current = current->next;
		counter++;
	}
}


// Функция для мини-теста
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
	// Если тестить на больших числах, отключить тест с pop_BACK() из-за О(n) долгая операция
    ui list_size = 20'000;
	List<int> my_list;
	std::list<int> stl_list;

    std::cout << "Начало теста собственный список\n";
    clock_t time = clock();
    for (ui i = 0; i < list_size; ++i) {
        my_list.push_front(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов в начало списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	time = clock();
	while (my_list.size()) { my_list.pop_front(); }
	time = clock() - time;
	std::cout << "Удаление элементов c начала списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "====================Тест завершился====================\n";

	std::cout << "Начало теста собственный список\n";
	time = clock();
	for (ui i = 0; i < list_size; ++i) {
		my_list.push_back(rand() % RAND_MAX);
	}
	time = clock() - time;
	std::cout << "Довавление элементов в конец списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (my_list.size()) { my_list.pop_back(); }
    time = clock() - time;
    std::cout << "Удаление элементов с конца списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    std::cout << "====================Тест завершился====================\n";
  
	std::cout << "\n===STL===STL===STL===STL===STL===STL===STL===STL===STL===STL===\n\n";
	std::cout << "Начало теста STL (List) список\n";
	time = clock();
	for (ui i = 0; i < list_size; ++i) {
		stl_list.push_front(rand() % RAND_MAX);
	}
	time = clock() - time;
	std::cout << "Довавление элементов в начало списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	time = clock();
	while (stl_list.size()) { stl_list.pop_front(); }
	time = clock() - time;
	std::cout << "Удаление элементов c начала списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "====================Тест завершился====================\n";

	std::cout << "Начало теста STL (List) список\n";
	time = clock();
	for (ui i = 0; i < list_size; ++i) {
		stl_list.push_back(rand() % RAND_MAX);
	}
	time = clock() - time;
	std::cout << "Довавление элементов в конец списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	time = clock();
	while (stl_list.size()) { stl_list.pop_back(); }
	time = clock() - time;
	std::cout << "Удаление элементов с конца списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "====================Тест завершился====================\n";

}
