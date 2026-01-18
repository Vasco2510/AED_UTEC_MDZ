
int* redimensionar(int* ptr, int size, int new_size)
{
	int* temp = new int[new_size];
	for(int i=0;i<size;i++) {
		temp[i] = *(ptr + i);		
	}
	delete[] ptr;
	return temp;
}

void redimensionar(int* &ptr, int &size, int new_size)
{
	int* temp = new int[new_size];
	for(int i=0;i<size;i++) {
		temp[i] = *(ptr + i);		
	}
	delete[] ptr;
	size = new_size;
	ptr = temp;
}

class Stack{
	Stack(){
		capacity = 10;
		array = new int[capacity];
		size = 0;		
	}
	void push(int data){
		if(size == capacity)
			redimensionar(array, capacity, 2*capacity);
		array[size++] = data;		
	}
	int pop(){
		int last = array[size - 1];
		size--;
		return last;
	}
};


template<typename T>
class Queue
{
private:
	T* array;
	int capacity;
	int front, rear;
public:
	Queue(){		
		capacity=10;
		array = new int[capacity];
		front = rear = -1;
	}
	int next(int index){		
		return (index + 1) % capacity;
	}
	void enqueue(T data)
	{
		if(front == -1 || rear == -1)
		{
			front = rear = 0;
		}
		else {
			rear = next(rear);
		}
		array[rear] = data;
	}
};


