/*Queue Version 1.0 --- Реализация очереди на основе динамического массива*/

#include <iostream>
#include <queue>
#include <cassert>

void testing();

template <typename Type>
class Queue {
private:
	Type *parray;				// Динамический массив
	int size;					// Размер массива CAPACITY
	int begin;					// Начало очереди FRONT
	int end;					// Конец очереди  REAR
	int count;					// Кол-во элементов очереди
public:
	Queue(int size);			// Конструктор по умолчанию
	Queue(const Queue<Type> &); // Конструктор копирования
	~Queue();					// Деструктор

	void push(const Type &);	// Добавить элемент в очередь
	void show();				// Печать, вывод в поток (на экран)
	Type pop();					// Удалить элемент из очереди и вернуть значение
	Type get()   const;			// Получить значение 1-го элемента очереди

	int get_size()  { return size; }		// Размер очереди
	int get_count() { return count;}		// Код-во элементов
	bool empty()	{ return count == 0; }	// Пустая ли очередь
	bool full()  { return count == size; }	// Заполнилась ли очередь
};


int main() {
	setlocale(0, "Ru");
	testing();
	return 0;
}

template <typename Type>
Queue<Type>::Queue(int size) {
	// Выделили память под динамический массив
	parray = new Type[size + 1];
	this->size = size;
	begin = 0;
	end   = 0;
	count = 0;
}

template<typename Type>
Queue<Type>::~Queue() {
	delete[] parray;
}

template <typename Type>
Queue<Type>::Queue(const Queue<Type> &other) {
	size   = other.size;
	begin  = other.begin;
	end    = other.end;
	count  = other.count;
	parray = new Type[size + 1];
	// Цикл копирования очереди по-элементно
	for (int i = 0; i < size; ++i) {
		parray[i] = other.parray[i];
	}
}

template <typename Type>
void Queue<Type>::push(const Type &element) {
	assert(count < size);		// Проверить, есть ли место в очереди
	parray[end++] = element;	// В массив добавили элемент по индексу
	count++;					// Счетчик увеличился
	if (end > size) {			// Проверка кругового заполнения очереди
		end -= size + 1;		// Возвращает end на начало очереди
	}
}

template <typename Type>
Type Queue<Type>::pop() {
	assert(count > 0);				// Проверить, есть ли элементы в очереди
	Type rvalue = parray[begin++];	// Достать первый элемент из очереди
	count--;
	if (begin > size) {				// Проверка кругового заполнения очереди
		begin -= size + 1;			// Возвращаем behin на начало очереди
	}
	return rvalue;
}

template<typename Type>
Type Queue<Type>::get() const {
	assert(count > 0);
	return parray[begin];
}

template <typename Type>
void Queue<Type>::show() {
	if (end == 0 && begin == 0) { 
		std::cout << "Очередь пустая\n"; 
	}
	else {
		for (int i = begin; i < end; ++i) {
			std::cout << parray[i] << " -> ";
			if (i+1 == end) { std::cout << parray[i] << "\n"; }
		}
		//std::cout << std::endl;
	}
}

// Тест
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
    ui size = 5'000'000;
	Queue<int> my_queue(size);
	std::queue<int> stl_queue;
 
    std::cout << "Начало теста на самодельной очереди\n";
    clock_t time = clock();
    for (ui i = 0; i < size; ++i) {
        my_queue.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "Довавление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

    time = clock();
    while (!my_queue.empty()) { my_queue.pop(); }
    time = clock() - time;
    std::cout << "Удаление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
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
