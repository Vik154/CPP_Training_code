/*Queue version 2.0 -  Очередь на основе односвязного списка*/

#include <iostream>
#include <queue>

void testing();

template <typename Type>
class Node {
public:
	Node<Type> *next;			// Указатель на следующий узел
	Type data;					// Абстраткные данные (пользовательские)
	Node(Type data) {			// Конструктор создания
		this->data = data;		// Текущему созданному объекту присвоить данные
		this->next = nullptr;	// Текущему созданному объекту присвоить адрес
	}
};

template <typename Type>
class Queue {
private:
	Node<Type> *head;					// Указатель на первый элемент очереди
	Node<Type> *tail;					// Указатель на последний элемент очереди
	int count;							// Счетчик элементов
public:
	Queue();							// Конструктор по умолчанию
	Queue(const Queue<Type> &other);	// Конструктор копирования
	~Queue();							// Деструктор
	void push_back(const Type &elm);	// Добавление элемента в конец очереди
	void push_front(const Type &elm);	// Добавление элемента в начало очереди
	void pop_front();					// Удаляет элемент из начала очереди
	void pop_back();					// Удаляет элемент с конца очереди
	void clear();						// Удалить все элементы в очереди
	void show();						// Печать очереди
	void set_tail(const Type &data);	// Заменить значение последнего элемента
	void set_head(const Type& data);	// Заменить значение первого элемента
	bool empty() { return count == 0; } // Возвращает тру или фолсе если в очереди есть или нет элементом
	int size()   { return count;}		// Возвращает кол-во элементов в очереди
	Node<Type>* get_head();				// Возвращает указатель на первый элемент в очереди
	Node<Type>* get_tail();				// Возвращает указатель на последний элемент в очереди
	const Type& front();				// Возвращает первый элемент очереди
	const Type& back();					// Возвращает последний элемент очереди

	bool operator == (const Queue<Type> &obj) const;	// Проверка на равенство двух очередей
	bool operator != (const Queue<Type> &obj) const;	// Проверка на неравенство
	Queue<Type>& operator = (const Queue<Type> &obj);	// Присваивание
	Type operator [] (int id);							// Возвращает поле data по индексу
};

int main() {
	setlocale(0, "Ru");
	testing();
	return 0;
}

template <typename Type>
Queue<Type>::Queue() {
	this->head  = nullptr;
	this->tail  = nullptr;
	this->count = 0;
}

template <typename Type>
Queue<Type>::~Queue() {
	clear();
}

template <typename Type>
Queue<Type>::Queue(const Queue<Type> &other) {
	head = tail = nullptr;
	*this = other;
}

template<typename Type>
Node<Type>* Queue<Type>::get_head() {
	return head;
}

template<typename Type>
Node<Type>* Queue<Type>::get_tail() {
	return tail;
}

template <typename Type>
const Type& Queue<Type>::front() {
	return (head) ? head->data : 0 ;	// Если head пуст вернуть 0, иначе значение поля data
}

template <typename Type>
const Type& Queue<Type>::back() {
	if (tail == nullptr) { return 0; }	// Если tail пуст вернуть 0, иначе значение поля data
	return tail->data;
}

template<typename Type>
void Queue<Type>::push_back(const Type &elm) {
	Node<Type> *node = new Node<Type>(elm);	// Создается новый узел очереди	
	if (head == nullptr) {					// Если новый элемент 1-ый, тогда
		head = node;						// Добаленный элемент становится первым в очереди
		tail = node;						// И в то же время он и последний, т.к. единственный
	}
	else {									// Если элементы в очереди уже есть, то
		tail->next = node;					// Текущий последний узел станет указывать на новый добаленный
		tail = node;						// Последним элементом станет в очереди новый добавленный узел
	}
	count++;								// Зафиксировали добавленный элемент
}

template <typename Type>
void Queue<Type>::push_front(const Type& elm) {
	Node<Type>* node = new Node<Type>(elm);	// Создается новый элемент очереди
	if (head == nullptr) {					// Если очередь пустая, тогда
		head = node;						// Первым элементом становится новый созданный узел
		tail = node;						// Он же и последний, т.к. пока что единственный
	}
	else {
		node->next = head;					// В поле next нового узла, положить адрес 1-го элемента
		head = node;						// Теперь 1-ый элемент - это новый добавленный узел
	}
	count++;								// Счётчик увеличить
}

template <typename Type>
void Queue<Type>::pop_front() {
	if (head == nullptr) { return; }		// Если очередь пуста - вернуться
	Node<Type> *temp = head->next;			// Создать временный указатель на следующий элемет после 1-го
	delete head;							// Освободить память (удалить указатель)
	if (temp == nullptr) {					// Если во временном указатели NULL значит элеметы закончились
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = temp;
	}
	count--;
}

template <typename Type>
void Queue<Type>::pop_back() {
	if (head == nullptr) { return; }	// Если очередь пуста - вернуться
	Node<Type> *tmp_next    = head;		// Временный указатель на следующий элемент после первого
	Node<Type> *tmp_current = head;		// Временный указатель на текущий элемент для итераций

	while (tmp_next->next != nullptr) {		// Пока следующий указатель не будет равен 0, итерироваться по очереди
		tmp_current = tmp_next;				// В текущем запоминается 1 ый элемент
		tmp_next = tmp_next->next;			// Тут запоминаем следующий за ним элемент
		// Для отладки (оставлю на память)
		//std::cout << "current = " << tmp_current << std::endl;
		//std::cout << "next = " << tmp_next << std::endl;
	}
	if (tmp_next == head) {				// Если последний элемент равен 1-му, значит в очереди 1 элемент
		delete head;					// Удаляем ссылку (можно через любое имя указателя это сделать)
		head = nullptr;					// Запишем 0, чтобы при вызове геттера не крашилась программа
		tail = nullptr;					// Запоминаем 0, чтобы не обращаться к рандомному мусорному значению через get
		tmp_current = nullptr;			// Просто так, можно и не писать, они удалятся при выходе из области видимости функции
		tmp_next = nullptr;
	}
	else {								// Если элементов в очереди больше 1-го, тогда
		tail = tmp_current;				// Передвинем указатель последнего элемента на предпоследний
		tmp_current->next = nullptr;	// В поле некст сотрем ссылку на следующий узел
		delete tmp_next;				// Удалим ссылку на последний элемент (освободим память, ссылку сотрем)
	}
	count--;							// Счётчик элементов уменьшить
	// Отладочная инфа, оставлю на память
	//std::cout << "После while\n";
	//std::cout << "current = " << tmp_current->data << std::endl;
	//std::cout << "next = " << tmp_next->data << std::endl;
}

template <typename Type>
void Queue<Type>::clear() {
	while (count > 0) {
		pop_front();
	}
}

template <typename Type>
void Queue<Type>::show() {
	if (count == 0) { std::cout << "Queue is empty\n"; }
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
void Queue<Type>::set_tail(const Type &data) {
	if (tail == nullptr) { return; }
	tail->data = data;
}

template <typename Type>
void Queue<Type>::set_head(const Type& data) {
	if (tail == nullptr) { return; }
	head->data = data;
}

template <typename Type>
bool Queue<Type>::operator==(const Queue<Type>& obj) const {
	if (this == &obj) {	return true; }			// Если адреса ==
	if (count != obj.count) { return false; }	// Если размеры очередей не равны

	Node<Type> *tmp = head;						// Указатель на 1-ый элм левого операнда
	Node<Type> *ntmp = obj.head;				// Указатель на 1-ый элм правого операнда
	while (tmp) {
		if (tmp->data != ntmp->data) { return false; }
		tmp  = tmp->next;
		ntmp = ntmp->next;
	}
	return true;	
}

template <typename Type>
bool Queue<Type>::operator!=(const Queue<Type>& obj) const {
	return !(*this == obj);
}

template<typename Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& obj) {

	if (*this == obj) { return *this; }		// Если очереди полностью одинаковы, вернуть текущую
	clear();								// Освободить память в текущей очереди
	Node<Type> *new_node = obj.head;		// Создать указатель на голову присваеваемой очереди
	while (new_node) {
		push_back(new_node->data);			// Добавить элемент в очередь
		new_node = new_node->next;			// Перейти к следующему узлу
	}
	return *this;							// Вернуть текущую очередь
}

template <typename Type>
Type Queue<Type>:: operator [] (int id) {
	if (id < 0 || id >= count) { return 0; }
	Node<Type>* tmp = head;
	for (int i = 0; i != id; ++i) {
		tmp = tmp->next;
	}
	return tmp->data;
}

// Тест
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
    ui size = 5'000'000;
	Queue<int> my_queue;
	std::queue<int> stl_queue;
 
    std::cout << "Начало теста на самодельной очереди\n";
    clock_t time = clock();
    for (ui i = 0; i < size; ++i) {
        my_queue.push_back(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов в конец: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (!my_queue.empty()) { my_queue.pop_front(); }
    time = clock() - time;
    std::cout << "Удаление элементов из начала очереди: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    std::cout << "====================Тест завершился====================\n";
  
    std::cout << "Начало теста на очереди STL\n";
    time = clock();
    for (ui i = 0; i < size; ++i) {
        stl_queue.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (!stl_queue.empty()) { stl_queue.pop(); }
    time = clock() - time;
    std::cout << "Удаление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    std::cout << "====================Тест завершился====================\n";
}

