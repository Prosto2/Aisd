#include <iostream>
#include <string>
using namespace std;

//список

template <typename T1>
class Node {
public:
    T1 data;
    Node<T1>* prev, * next;

    Node<T1>(double data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};
template <typename T1>
class LinkedList {
public:
    Node<T1>* head, * tail;

    LinkedList() {
        this->head = this->tail = NULL;
    }

    Node<T1>* push_front(T1 data) {
        Node<T1>* ptr = new Node<T1>(data);

        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;

        return ptr;
    }

    Node<T1>* push_back(T1 data) {
        Node<T1>* ptr = new Node<T1>(data);

        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;

        return ptr;
    }

    void del_front() {
        if (head == NULL) 
            return;

        Node<T1>* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }

    void del_back() {
        if (tail == NULL) return;

        Node<T1>* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }

    Node<T1>* getAt(int index) {
        Node<T1>* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }

        return ptr;
    }


    Node<T1>* operator [] (int index) {
        return getAt(index);
    }

    Node<T1>* insert(int index, T1 data) {
        Node<T1>* right = getAt(index);
        if (right == NULL)
            return push_back(data);

        Node<T1>* left = right->prev;
        if (left == NULL)
            return push_front(data);

        Node<T1>* ptr = new Node<T1>(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index) {
        Node<T1>* ptr = getAt(index);
        if (ptr == NULL)
            return;

        if (ptr->prev == NULL) {
            del_front();
            return;
        }

        if (ptr->next == NULL) {
            del_back();
            return;
        }

        Node<T1>* left = ptr->prev;
        Node<T1>* right = ptr->next;
        left->next = right;
        right->prev = left;

        delete ptr;
    }

    ~LinkedList() {
        while (head != NULL)
            del_front();
    }

};

//массив

template <typename T2>
class DynamicArray {
private:
    T2* array;
    int capacity;
    int size;

public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        array = new int[capacity];
    }

    ~DynamicArray() {
        delete[] array;
    }

    void resize(int newCapacity) {
        T2* newArray = new int[newCapacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

    void push_back(T2 data) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            resize(newCapacity);
        }
        array[size++] = data;
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return array[index];
    }

    int get_size() {
        return size;
    }

    void set(int index, T2 data) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        array[index] = data;
    }

    void add(int index, T2 data) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            resize(newCapacity);
        }
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        for (int i = size; i >= index; i--) {
            array[i + 1] = array[i];
        }
        array[index] = data;
        size++;
    }

    void cout_array() {
        for (int i = 0; i < size; i++)
            cout << array[i] << "\n";
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        if (index == size)
            array[index] = NULL;
        else {
            for (int i = index; i < size; i++) {
                array[i] = array[i + 1];
            }
        }
        size--;
    }
};

//стек
template <typename T3>
class Stek {
public:
    Node<T3>* head, * tail;

    Stek() {
        this->head = this->tail = NULL;
    }

    Node<T3>* push_back(T3 data) {
        Node<T3>* ptr = new Node<T3>(data);

        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;

        return ptr;
    }

    void del_back() {
        if (tail == NULL) return;

        Node<T3>* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }
};

bool is_operator(char c) 
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'cos' || c == 'sin';
}

// Получение приоритета оператора
int get_precedence(char op) 
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^' || op == 'cos' || op == 'sin')
        return 3;
    return 0;
}

string convert(string str) 
{
    Stek<char> stk;
    string post;

    for (char c : str) {
        if (isalnum(c)) {
            post += c;
        }
        else if (c == ' ') {
            continue;
        }
        else if (c == '(') {
            stk.push_back(c);
        }
        else if (c == ')') {
            while (stk.head != NULL && stk.tail->data != '(') {
                post += stk.tail->data;
                stk.del_back();
            }

            if (stk.head != NULL && stk.tail->data == '(') {
                stk.del_back();
            }
        }
        else if (is_operator(c)) {
            while (stk.head != NULL && get_precedence(c) <= get_precedence(stk.tail->data)) {
                post += stk.tail->data;
                stk.del_back();
            }
            stk.push_back(c);
        }
    }

    while (stk.head != NULL) {
        post += stk.tail->data;
        stk.del_back();
    }

    return post;
}

int main()
{
    setlocale(0, "");
    //тест списка
    LinkedList<double> lst;
    lst.push_back(1.0);
    lst.push_back(2.3);
    lst.push_back(3.0);
    lst.push_back(4.4);

    for (Node<double>* ptr = lst.head; ptr != NULL; ptr = ptr->next)
        cout << ptr->data << "\n";
    cout << endl;

    //тест массива

    DynamicArray <int> ary;

    ary.push_back(1);
    ary.push_back(2);
    ary.push_back(4);
    ary.push_back(5);
    ary.push_back(6);
    ary.push_back(7);
    ary.set(2,3);
    ary.add(3,4);
    ary.push_back(8);
    ary.push_back(9);
    ary.push_back(10);
    ary.push_back(11);
    ary.remove(1);
    ary.cout_array();

    //тест стека


    string str;
    printf("Введите выражение: ");
    getline(cin,str);
    cout << "Преобразованное выражение: " << convert(str);

    return 0;
}


//( 2 + 3 ) * 4 ^ 2 - sin ( 1 ) + cos ( 2 )