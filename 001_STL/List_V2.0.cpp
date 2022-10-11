/*List version 2.0 -- Реализация двусвязного списка*/

#include <iostream>
#include <list>

void testing();

template <typename Type>
class Node {
public:
	Node(Type data) {						// Конструктор узла
		this->data = data;					// Данные
		this->next = nullptr;				// Следующий узел
		this->prev = nullptr;				// Предыдущий узел
	}
	Type data;								// Данные
	Node<Type> *next;						// Указатель на следующий узел
	Node<Type> *prev;						// Указатель на предыдущий узел
};

template <typename Type>
class List {
private:
	Node<Type> *head;						// Начало списка
	Node<Type> *tail;						// Конец списка
	int count;								// Кол-во элементов
public:
	List();									// Конструктор без параметров
	List(Type data);						// Конструктор с параметром
	List(const List<Type> &list);			// Конструктор копирования
	~List();								// Деструктор

	void push_front(Type data);				// Добавить элемент в начало списка
	void push_back(Type data);				// Добавить элемент в конец списка
	void insert(Type data, int id);			// Вставить элемент в список по индексу
	void show();							// Вывод на экран
	void pop_front();						// Удалить элемент из начала списка
	void pop_back();						// Удалить элемент с конца списка
	void clear();							// Удалить все элементы списка
	void remove_index(int id);				// Удалить элемент по индексу
	void remove_value(Type value);			// Удалить элемент по значению (По первому найденному совпадению)
	void reverse();							// Развернуть список в обратном порядке
	void sort_bubble();						// Сортировка пузырьком
	void sort_insertion();					// Сортировка вставками
	void sort_selection();					// Сортировка выбором

	Type& front() { return head->data; }	// Получить значение первого элемента списка
	Type& back()  { return tail->data; }	// Получить значение последнего элемента
	Type& size()  { return count; }			// Получить кол-во элементов в списке
	Node<Type>* begin() { return head; }	// Получить указатель на первый элемент
	Node<Type>* end()   { return tail; }	// Получить указатель на последний элемент
	Node<Type>* find_value(Type value);		// Вернуть указатель на искомый элемент, поиск по значению
	Node<Type>* find_index(int index);		// Вернуть указатель на искомый элемент, поиск по индексу

	Type& operator [] (const int index);				// Вернуть значение по индексу
	List<Type>& operator + (const List<Type> &list);	// Сложение списков
	List<Type>& operator = (const List<Type> &list);	// Присваивание списков
	bool operator == (const List<Type>& list);			// Проверка на равенство
	bool operator != (const List<Type>& list);			// Проверка на неравенство
	bool operator >= (const List<Type>& list);			// Больше или равно 
	bool operator <= (const List<Type>& list);			// Меньше или равно
	bool operator >  (const List<Type>& list);			// Больше
	bool operator <  (const List<Type>& list);			// Меньше 
};


int main() {
	setlocale(LC_ALL, "Russian");
	testing();
	return 0;
}

template <typename Type>
List<Type>::List() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename Type>
List<Type>::List(Type data) {
	Node<Type> *new_node = new Node<Type>(data);
	head = new_node;
	tail = new_node;
	count = 1;
}

template <typename Type>
List<Type>::List(const List<Type>& list) {
	clear();
	Node<Type> *copy_node = list.head;
	while (copy_node != nullptr) {
		push_back(copy_node->data);
		copy_node = copy_node->next;
	}
}

template <typename Type>
List<Type>::~List() {
	clear();
}

template <typename Type>
void List<Type>::push_front(Type data) {
	Node<Type> *new_node = new Node<Type>(data);
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	count++;
}

template <typename Type>
void List<Type>::push_back(Type data) {
	Node<Type>* new_node = new Node<Type>(data);
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	count++;
}

template <typename Type>
void List<Type>::show() {
	if (count == 0) {
		std::cout << "List is empty\n";
		return;
	}
	Node<Type> *tmp = head;
	while (tmp) {
		if (tmp->next != nullptr) {
			std::cout << tmp->data << " -> ";
			tmp = tmp->next;
		}
		else {
			std::cout << tmp->data << "\n";
			tmp = tmp->next;
		}
	}
}

template <typename Type>
void List<Type>::insert(Type data, int id) {
	if (id >= count+1 || id < 0) {
		std::cout << "Некорректный индекс\n";
		return;
	}
	Node<Type> *new_node = new Node<Type>(data);
	Node<Type> *tmp = head;
	for (int i = 0; i < id; ++i) {
		tmp = tmp->next;
	}
	if (tmp == head) {
		new_node->next = tmp;
		tmp->prev = new_node;
		head = new_node;
	}
	else if (tmp == nullptr) {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
	else {
		new_node->next = tmp;
		new_node->prev = tmp->prev;
		tmp->prev->next = new_node;
		tmp->prev = new_node;
	}
	count++;
	
}

template <typename Type>
void List<Type>::pop_front() {
	if (count == 0) { return; }
	if (count == 1) {
		delete head;
		head = nullptr;
		count--;
		return;
	}
	Node<Type> *tmp = head->next;
	tmp->prev = nullptr;
	delete head;
	head = tmp;
	count--;
}

template <typename Type>
void List<Type>::pop_back() {
	if (count == 0) { return; }
	if (count == 1) {
		delete head;
		head = nullptr;
		count--;
		return;
	}
	Node<Type> *tmp = tail->prev;
	tmp->next = nullptr;
	delete tail;
	tail = tmp;
	count--;
}

template <typename Type>
void List<Type>::clear() {
	while (count) {
		pop_front();
	}
}

template <typename Type>
void List<Type>::remove_index(int id) {
	if (id >= count || id < 0 || count == 0) { return; }
	Node<Type> *tmp = head;
	for (int i = 0; i < id; ++i) {
		tmp = tmp->next;
	}
	if (tmp == head) {
		if (head == tail) {
			delete tmp;
			count--;
			return;
		}
		else {
			head = head->next;
			head->prev = nullptr;
			delete tmp;
		}
	}
	else if (tmp == tail) {
		if (head == tail) {
			delete tmp;
			count--;
			return;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
			delete tmp;
		}
	}
	else {
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete tmp;
	}
	count--;
}

template <typename Type>
void List<Type>::remove_value(Type value) {
	if (count == 0) { return; }
	
	Node<Type> *tmp = head;
	while (tmp != nullptr) {
		if (tmp->data != value) {
			tmp = tmp->next;
		}
		else {
			break;
		}
	}
	if (tmp == nullptr) { return; }
	if (tmp == head) {
		if (head == tail) {
			delete tmp;
			count--;
			return;
		}
		else {
			head = head->next;
			head->prev = nullptr;
			delete tmp;
		}
	}
	else if (tmp == tail) {
		if (head == tail) {
			delete tmp;
			count--;
			return;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
			delete tmp;
		}
	}
	else {
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		delete tmp;
	}
	count--;
}

template <typename Type>
Node<Type>* List<Type>::find_value(Type value) {
	if (count == 0) {
		std::cout << "Список пуст\n";
		return nullptr;
	}
	Node<Type> *tmp = head;
	while (tmp) {
		if (tmp->data != value) { tmp = tmp->next; }
		else { break; }
	}
	if (tmp == nullptr) {
		std::cout << "Элемента нет в списке\n";
	}
	return tmp;
}

template <typename Type>
Node<Type>* List<Type>::find_index(int index) {
	if (count == 0) {
		std::cout << "Список пуст\n";
		return nullptr;
	}
	if (index < 0 || index >= count) {
		std::cout << "Некорректный индекс\n";
		return nullptr;
	}
	Node<Type>* tmp = head;
	for (int i = 0; i < index; ++i) {
		tmp = tmp->next;
	}
	return tmp;
}

template <typename Type>
List<Type>& List<Type>::operator = (const List<Type>& list) {
	clear();
	Node<Type>* copy_node = list.head;
	while (copy_node != nullptr) {
		push_back(copy_node->data);
		copy_node = copy_node->next;
	}
	return *this;
}

template <typename Type>
List<Type>& List<Type>::operator + (const List<Type>& list) {
	Node<Type> *new_node = list.head;
	while (new_node) {
		push_back(new_node->data);
		new_node = new_node->next;
	}
	return *this;
}

template <typename Type>
void List<Type>::reverse() {
	if (count == 0) { return; }

	List<Type> new_list;
	Node<Type> *tmp_node = head;
	while (tmp_node != nullptr) {
		new_list.push_front(tmp_node->data);
		tmp_node = tmp_node->next;
	}
	*this = new_list;
}

template <typename Type>
void List<Type>::sort_bubble() {
	if (count < 1) { return; }
	Node<Type>* left  = head;
	Node<Type>* rigth = head->next;
	Node<Type>* temp  = new Node<Type>(0);

	while (left->next) {
		while (rigth) {
			if (left->data > rigth->data) {
				temp->data = left->data;
				left->data = rigth->data;
				rigth->data = temp->data;
			}
			rigth = rigth->next;
		}
		left  = left->next;
		rigth = left->next;
	}
}

template <typename Type>
void List<Type>::sort_insertion() {
	if (count < 2) { return; }
	Node<Type> *current  = head->next;
	Node<Type> *previous = head;
	// Взял исходник из сортировок массива,и под указатели адаптировал вроде норм
	for (int i = 1; i < count; ++i) {
		Type tmp = current->data;
		previous = current->prev;
		Node<Type> *tmp_prev = previous;

		while (tmp_prev && tmp <= tmp_prev->data) {
			tmp_prev->next->data = tmp_prev->data;
			tmp_prev->data = tmp;
			tmp_prev = tmp_prev->prev;
		}
		current  = current->next;
		previous = previous->next;
	}
}

template <typename Type>
void List<Type>::sort_selection() {
	if (count < 2) { return; }
	Node<Type> *current = head;
	Node<Type> *min_id  = head;
	Node<Type> *src_id  = head;
	Node<Type> *iterator = head;
	Type tmp_data;
	// Лень комментировать каждую строку - алгоритм взял с массива и переписал на указатели
	for (current; current != nullptr; current = current->next) {
		min_id = current;
		for (src_id = iterator; src_id != nullptr; src_id = src_id->next) {
			if (src_id->data < min_id->data) {
				min_id = src_id;
			}
		}
		if (current->data != min_id->data) {
			tmp_data = current->data;
			current->data = min_id->data;
			min_id->data = tmp_data;
		}
		iterator = iterator->next;
	}
}

template <typename Type>
Type& List<Type>::operator [] (const int index) {
	if (index < 0 || index >= count) { 
		Type x = 0;
		return x;
	}
	Node<Type> *find = head;
	for (int i = 0; i < index; ++i) {
		find = find->next;
	}
	return find->data;
}

template <typename Type>
bool List<Type>::operator == (const List<Type>& list) {
	if (count != list.count) { return false; }
	Node<Type> *tmp_old = head;
	Node<Type> *tmp_new = list.head;
	while (tmp_old) {
		if (tmp_old->data != tmp_new->data) { return false; }
		tmp_old = tmp_old->next;
		tmp_new = tmp_new->next;
	}
	return true;
}

template <typename Type>
bool List<Type>::operator != (const List<Type>& list) {
	return !(*this == list);
}

template <typename Type>
bool List<Type>::operator >= (const List<Type>& list) {
	if (count > list.count) { return true; }
	if (*this == list) { return true; }
	return false;
}

template <typename Type>
bool List<Type>::operator <= (const List<Type>& list) {
	if (count < list.count) { return true; }
	if (*this == list) { return true; }
	return false;
}

template <typename Type>
bool List<Type>::operator > (const List<Type>& list) {
	if (count > list.count) { return true; }
	return false;
}

template <typename Type>
bool List<Type>::operator < (const List<Type>& list) {
	if (count < list.count) { return true; }
	return false;
}

// Функция для мини-теста
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
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
	std::cout << "Удаление элементов из начала списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
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

	std::cout << "\n********************Тесты сортировок********************\n";
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
	for (ui i = 0; i < list_size; ++i) {
		my_list.push_back(rand() % RAND_MAX);
	}
	std::cout << "\nИдёт сортировка пузырьком (bubble sort) --> ";
	time = clock();
	my_list.sort_bubble();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "Идёт очистка списка\n";
	my_list.clear();
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
	for (ui i = 0; i < list_size; ++i) {
		my_list.push_back(rand() % RAND_MAX);
	}
	std::cout << "\nИдёт сортировка вставками (insertion sort) --> ";
	time = clock();
	my_list.sort_insertion();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	
	std::cout << "Идёт очистка списка\n";
	my_list.clear();
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
	for (ui i = 0; i < list_size; ++i) {
		my_list.push_back(rand() % RAND_MAX);
	}
	std::cout << "\nИдёт сортировка выбором (selection sort) --> ";
	time = clock();
	my_list.sort_selection();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	std::cout << "Тест функции реверса (разворота) списка: ";
	time = clock();
	my_list.reverse();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	my_list.clear();

	std::cout << "\n==================Тест STL сортировки==================\n";
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
	for (ui i = 0; i < list_size; ++i) {
		stl_list.push_back(rand() % RAND_MAX);
	}
	std::cout << "\nИдёт сортировка встроенная в класс list (sort) --> ";
	time = clock();
	stl_list.sort();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	stl_list.clear();
}
