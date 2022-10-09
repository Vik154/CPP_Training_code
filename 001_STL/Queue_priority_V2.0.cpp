/*Priority Queue V.2.0 - Очередь с приоритетом на основе односвязного списка*/

#include <iostream>

template <typename Type>
class Node {
public:
	Node(Type data, int priority) {		// Конструктор узла
		this->next = nullptr;
		this->data = data;
		this->priority = priority;
	}
	Type data;							// Поле данных
	Node* next;							// Указатель на следующий узел списка
	int priority;						// Приоритет задается пользователем
};

template <typename Type>
class Priority_queue {
private:
	Node<Type> *head;					// Начало очереди
	Node<Type> *tail;					// Конец очереди
	int count;							// Кол-во элементов
public:
	Priority_queue();					// Конструктор
	~Priority_queue();					// Деструктор
	void push(Type elm, int prior);		// Добавление в очередь элемента по приоритету
	void show();						// Вывод очереди
	void pop();							// Удалить верхний (первый) элемент
	void clear();						// Очистка очереди
	Type front();						// Вернуть 1-ый элемент
	Type back();						// Вернуть последний элемент
	int size()	 { return count; }		// Вернуть размер очереди
	bool empty() { return count == 0; } // Вернуть 0 если очередь пустая, иначе 1
};

template <typename Type>
Priority_queue<Type>::Priority_queue() {
	head  = nullptr;
	tail  = nullptr;
	count = 0;
}

template <typename Type>
Priority_queue<Type>::~Priority_queue() {
	clear();
}

template <typename Type>
void Priority_queue<Type>::push(Type elm, int prior) {
	Node<Type> *new_node = new Node<Type>(elm, prior); // Создать новый элемент очереди

	if (head == nullptr) {					// Если очередь пустая, тогда элемент будет 1-ым
		head = new_node;					// Голова указывает на новый добавленный элемент
		tail = new_node;					// Хвост указывает на новый добавленный элемент
		count++;							// Увеличить счетчик
		return;								// Вернуться
	}
	Node<Type> *temp = head;				// Временный указатель для обхода и поиска приоритета в цикле
	Node<Type> *prev = nullptr;				// Указатель на предыдущий элеменет от temp
	// Итерироваться по очереди, пока не закончится или пока не встретится меньший приоритет
	while (temp != nullptr && temp->priority > prior) {
		prev = temp;						// В предыдущий запомнить значение текущего
		temp = temp->next;					// Текущий продвинуть вперед по очереди
	}
	if (temp == nullptr) {					// Если дошли до конца очереди и не встретился приоритет ниже чем у добавляемого
		prev->next = new_node;				// Добавить элемент в конец очереди
		tail = new_node;					// Хвост указывает на последний элемент
	}
	else {
		if (prev == nullptr) {				// Если предыдущий указвает на 0, значит итераций не было т.к приоритет выше
			new_node->next = head;			// Новый элемент встает вперед очереди
			head = new_node;				// Голова указывает на новый элемент
		}
		else {								// Если итерации были, тогда настроить указатели
			new_node->next = temp;			// Новый элемент будет указывать на найденное значение
			prev->next = new_node;			// А предыдущий будет указывать на новый
		}
	}
	count++;
}

template <typename Type>
void Priority_queue<Type>::show() {
	if (count == 0) { std::cout << "Queue is empty\n"; }
	Node<Type> *tmp = head;
	for (int i = 0; i < count; ++i) {
		std::cout << tmp->data << " <- ";
		tmp = tmp->next;
	}
}

template <typename Type>
Type Priority_queue<Type>::front() {
	return (count == 0) ? 0 : head->data;
}

template <typename Type>
Type Priority_queue<Type>::back() {
	return (count == 0) ? 0 : tail->data;
}

template <typename Type>
void Priority_queue<Type>::pop() {
	if (head == nullptr) { return; }
	Node<Type> *tmp = head;
	head = head->next;
	delete tmp;
	count--;
}

template <typename Type>
void Priority_queue<Type>::clear() {
	while (count) {
		pop();
	}
}

int main() {
	setlocale(0, "Ru");
	srand(time(NULL));
	clock_t time = clock();
	Priority_queue<int> pqueue;
	std::cout << "=====Начало теста=====\n";
	for (int i = 0; i < 10'000; ++i) {
		pqueue.push(rand() % 10'000, rand() % 10);
	}
	time = clock() - time;
	std::cout << "Добавление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	pqueue.clear();
	time = clock() - time;
	std::cout << "Извлечение элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	
	return 0;
}
