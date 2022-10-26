
template <typename T>
class stackasarray {
 private:
  int size;
  T *arr;
  int top;

 public:
  stackasarray();
  ~stackasarray();
  void push(int);
  int pop();
  int peek() const { return arr[top]; };
  int getSize() const { return size; };
  bool isEmpty() const { return top == -1; };
  bool isFull() const { return top == size - 1; };
};

template <typename T>
stackasarray<T>::stackasarray() {
  size = 10;
  arr = new int[10];
  top = -1;
}
template <typename T>
stackasarray<T>::~stackasarray() {
  delete[] arr;
}
void stackasarray<T>::push(T n) {
  if (!isFull()) {
    arr[++top] = n;
  }
}
template <typename T>
int stackasarray<T>::pop() {
  if (!isEmpty()) return arr[top--];
}

int main() { return 0; }