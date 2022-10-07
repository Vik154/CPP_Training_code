/*Queue Version 1.0 --- ���������� ������� �� ������ ������������� �������*/

#include <iostream>
#include <queue>
#include <cassert>

void testing();

template <typename Type>
class Queue {
private:
	Type *parray;				// ������������ ������
	int size;					// ������ ������� CAPACITY
	int begin;					// ������ ������� FRONT
	int end;					// ����� �������  REAR
	int count;					// ���-�� ��������� �������
public:
	Queue(int size);			// ����������� �� ���������
	Queue(const Queue<Type> &); // ����������� �����������
	~Queue();					// ����������

	void push(const Type &);	// �������� ������� � �������
	void show();				// ������, ����� � ����� (�� �����)
	Type pop();					// ������� ������� �� ������� � ������� ��������
	Type get()   const;			// �������� �������� 1-�� �������� �������

	int get_size()  { return size; }		// ������ �������
	int get_count() { return count;}		// ���-�� ���������
	bool empty()	{ return count == 0; }	// ������ �� �������
	bool full()  { return count == size; }	// ����������� �� �������
};


int main() {
	setlocale(0, "Ru");
	testing();
	return 0;
}

template <typename Type>
Queue<Type>::Queue(int size) {
	// �������� ������ ��� ������������ ������
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
	// ���� ����������� ������� ��-���������
	for (int i = 0; i < size; ++i) {
		parray[i] = other.parray[i];
	}
}

template <typename Type>
void Queue<Type>::push(const Type &element) {
	assert(count < size);		// ���������, ���� �� ����� � �������
	parray[end++] = element;	// � ������ �������� ������� �� �������
	count++;					// ������� ����������
	if (end > size) {			// �������� ��������� ���������� �������
		end -= size + 1;		// ���������� end �� ������ �������
	}
}

template <typename Type>
Type Queue<Type>::pop() {
	assert(count > 0);				// ���������, ���� �� �������� � �������
	Type rvalue = parray[begin++];	// ������� ������ ������� �� �������
	count--;
	if (begin > size) {				// �������� ��������� ���������� �������
		begin -= size + 1;			// ���������� behin �� ������ �������
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
		std::cout << "������� ������\n"; 
	}
	else {
		for (int i = begin; i < end; ++i) {
			std::cout << parray[i] << " -> ";
			if (i+1 == end) { std::cout << parray[i] << "\n"; }
		}
		//std::cout << std::endl;
	}
}

// ����
void testing() {
    srand(time(NULL));
    typedef unsigned int ui;
    ui size = 5'000'000;
	Queue<int> my_queue(size);
	std::queue<int> stl_queue;
 
    std::cout << "������ ����� �� ����������� �������\n";
    clock_t time = clock();
    for (ui i = 0; i < size; ++i) {
        my_queue.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "���������� ���������: " << (double)time / CLOCKS_PER_SEC << " ���." << std::endl;

    time = clock();
    while (!my_queue.empty()) { my_queue.pop(); }
    time = clock() - time;
    std::cout << "�������� ���������: " << (double)time / CLOCKS_PER_SEC << " ���." << std::endl;
    std::cout << "====================���� ����������====================\n";
  
    std::cout << "������ ����� �� ������� STL\n";
    time = clock();
    for (ui i = 0; i < size; ++i) {
        stl_queue.push(rand() % RAND_MAX);
    }
    time = clock() - time;
    std::cout << "���������� ���������: " << (double)time / CLOCKS_PER_SEC << " ���." << std::endl;

    time = clock();
    while (!stl_queue.empty()) { stl_queue.pop(); }
    time = clock() - time;
    std::cout << "�������� ���������: " << (double)time / CLOCKS_PER_SEC << " ���." << std::endl;
    std::cout << "====================���� ����������====================\n";
}
