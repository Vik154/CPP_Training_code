/*Priority Queue Versio  3.0 --- Очередь с приоритетом на основе динамического массива*/

#include <iostream>
#include <queue>

template <typename Type>
class Pqueue {
private:
	Type *darray;							// Динамический массив элементов произвольного типа
	int	 *parray;							// Массив приоритетов
	int  count;								// Счетчик элементов массива
public:
	Pqueue() { count = 0; }					// Конструктор без параметров
	Pqueue(const Pqueue<Type> &object);		// Конструктор копирования
	~Pqueue();								// Деструктор
	void push(Type element,int priority);	// Добавление элемента по приоритету
	Type pop();								// Вытягивает 1-ый элемент из очереди
	void clear();							// Удаляет очередь
	void shows();							// Распечатать очередь
	int size() { return count; }			// Получить размер
	Pqueue<Type> operator = (const Pqueue<Type>& obj);	// Копирование (присваивание)
};

template <typename Type>
Pqueue<Type>::Pqueue(const Pqueue<Type> &object) {
	darray = new Type[object.count];
	parray = new int[object.count];
	count  = object.count;
	for (int i = 0; i < count; ++i) {
		darray[i] = object.darray[i];
	}
	for (int i = 0; i < count; ++i) {
		parray[i] = object.parray[i];
	}
}

template <typename Type>
Pqueue<Type>::~Pqueue() {
	if (count > 0) {
		delete[] parray;
		delete[] darray;
	}
}

template<typename Type>
Pqueue<Type> Pqueue<Type>::operator=(const Pqueue<Type>& obj) {
	
	if (count > 0) {					// Если очередь не пуста, тогда
		delete darray;					// Освободить память текущего массива, т.к. туда присвоится новый
		delete parray;					// Массив приоритетов тоже очистить
	}
	darray = new Type[obj.count];		// Выделить память
	parray = new int[obj.count];		// Выделить память
	count  = obj.count;					// Скопировать счетчик
	
	for (int i = 0; i < count; ++i) {	// Скопировать элементы присваиваемого массива
		darray[i] = obj.darray[i];
	}
	for (int i = 0; i < count; ++i) {
		parray[i] = obj.parray[i];
	}
	return *this;
}

template <typename Type>
void Pqueue<Type>::push(Type element, int priority) {

	Type *new_darr = new Type[count+1];		// Создание нового массива под добавляемый элемент
	int  *new_parr = new int[count+1];		// Создание нового массива под приоритет элемента

	int pos;								// Позиция (индекс) элемента в массиве
	if (count == 0) { pos = 0; }			// Если элементов в очереди нет, то добавляемый станет 1-ым
	else {
		pos = 0;
		while (pos < count) {				// Пройти по массиву приоритетов и сравнить приоритеты
			if (parray[pos] < priority) {	// Если приоритет начального массива меньше приоритета добавляемого
				break;						// Выйти
			}
			pos++;
		}
	}
	for (int i = 0; i < pos; i++) {
		new_darr[i] = darray[i];
		new_parr[i] = parray[i];
	}
	new_darr[pos] = element;
	new_parr[pos] = priority;
	for (int i = pos + 1; i < count + 1; i++) {
		new_darr[i] = darray[i - 1];
		new_parr[i] = parray[i - 1];
	}
	if (count > 0) {
		delete[] parray;
		delete[] darray;
	}
	parray = new_parr;
	darray = new_darr;
	count++;
}

template <typename Type>
Type Pqueue<Type>::pop() {
	if (count == 0) { return 0; }
	Type *tmp_darray = new Type[count-1];	// Временный массив данных на 1 элемент меньше текущего
	int  *tmp_parray = new int[count-1];	// Временный массив приоритетов на 1 элемент меньше текущего
	Type item = darray[0];					// Запомнить первый элемент существующего массивы
	for (int i = 0; i < count - 1; ++i) {	// Скопировать все элементы кроме первого из текущего в новый массив
		tmp_darray[i] = darray[i + 1];
		tmp_parray[i] = parray[i + 1];
	}
	if (count > 0) {
		delete[] darray;					// Освободить память, для старых массивов
		delete[] parray;
	}
	count--;								// Уменьшили счетчик на удаленный элемент
	darray = tmp_darray;					// Запомнить указатели на новый массивы, без элемента
	parray = tmp_parray;					// Запомнить указатели на новый массивы, без элемента

	return item;							// Вернуть удаленный элемент
}

template <typename Type>
void Pqueue<Type>::shows() {
	if (count == 0) { 
		std::cout << "Массив пуст\n";
		return;
	}
	for (int i = 0; i < count; ++i) {
		std::cout << "i[" << i << "] = (" << darray[i] << ";" << parray[i] << ")\n";
	}
	std::cout << "\n";
}

template <typename Type>
void Pqueue<Type>::clear() {
	if (count > 0) {
		delete[] darray;
		delete[] parray;
		count = 0;
	}
}

int main() {
	setlocale(0, "Ru");
	srand(time(NULL));
	clock_t time = clock();
	Pqueue<int> pqueue;
	std::cout << "=====Начало теста=====\n";
	for (int i = 0; i < 10'000; ++i) {
		pqueue.push(rand() % 10'000, rand() % 10);
	}
	time = clock() - time;
	std::cout << "Добавление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	for (int i = 0; i < 10'000; ++i) {
		pqueue.pop();
	}
	time = clock() - time;
	std::cout << "Извлечение элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	return 0;
}
