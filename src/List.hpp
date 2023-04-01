#pragma once

#include <iostream>

template <typename T>
class List {
   private:
    template <typename N>
    class Node {
       public:
        N data;
        Node* next;
        Node* prev;

        Node() {
            next = nullptr;
            prev = nullptr;
        }

        Node(const N& data) {
            this->data = data;
            next = nullptr;
            prev = nullptr;
        }

        Node(N&& data) {
            this->data = std::move(data);
            next = nullptr;
            prev = nullptr;
        }
    };

    Node<T>* head;

    Node<T>* tail;

    Node<T>* getByIndex(int index);

   public:
    List();

    List(const List<T>& other);

    List<T>& operator=(const List<T>& other);

    List(List<T>&& other);

    List<T>& operator=(List<T>&& other);

    ~List();

    void append(const T& newdata);

    void append(T&& newdata);

    void prepend(const T& newdata);

    void prepend(T&& newdata);

    void insertAt(int index, const T& newdata);

    void insertAt(int index, T&& newdata);

    void removeFirst();

    void removeLast();

    void removeAt(int index);

    int getSize() const;

    T getAt(int index);

    void destroy();
};

template <typename T>
List<T>::Node<T>* List<T>::getByIndex(int index) {
    if (index < 0 || index >= getSize()) {
        return nullptr;
    }
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
List<T>::List(const List<T>& other) {
    head = nullptr;
    tail = nullptr;
    Node<T>* tmp = other.head;
    while (tmp != nullptr) {
        append(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }
    destroy();
    head = nullptr;
    tail = nullptr;
    Node<T>* tmp = other.head;
    while (tmp != nullptr) {
        append(tmp->data);
        tmp = tmp->next;
    }

    return *this;
}

template <typename T>
List<T>::List(List<T>&& other) {
    Node<T>* tmp = head;
    this->head = other.head;
    other.head = tmp;

    tmp = tail;
    this->tail = other.tail;
    other.tail = tmp;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other) {
    if (this == &other) {
        return *this;
    }
    Node<T>* tmp = head;
    this->head = other.head;
    other.head = tmp;

    tmp = tail;
    this->tail = other.tail;
    other.tail = tmp;
    return *this;
}

template <typename T>
List<T>::~List() {
    destroy();
}

template <typename T>
void List<T>::append(const T& newdata) {
    Node<T>* tmp = new Node(newdata);
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
}

template <typename T>
void List<T>::append(T&& newdata) {
    Node<T>* tmp = new Node(std::move(newdata));
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
}

template <typename T>
void List<T>::prepend(const T& newdata) {
    Node<T>* tmp = new Node(newdata);
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
}

template <typename T>
void List<T>::prepend(T&& newdata) {
    Node<T>* tmp = new Node(std::move(newdata));
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
}

template <typename T>
void List<T>::insertAt(int index, const T& newdata) {
    if (index == 0) {
        prepend(newdata);
        return;
    }
    if (index == getSize()) {
        append(newdata);
        return;
    }
    Node<T>* current = getByIndex(index);
    Node<T>* tmp = new Node<T>(newdata);

    current->prev->next = tmp;
    tmp->next = current;
    tmp->prev = current->prev;
    current->prev = tmp;
}

template <typename T>
void List<T>::insertAt(int index, T&& newdata) {
    if (index == 0) {
        prepend(std::move(newdata));
        return;
    }
    if (index == getSize()) {
        append(std::move(newdata));
        return;
    }
    Node<T>* current = getByIndex(index);
    Node<T>* tmp = new Node(std::move(newdata));

    current->prev->next = tmp;
    tmp->next = current;
    tmp->prev = current->prev;
    current->prev = tmp;
}

template <typename T>
void List<T>::removeFirst() {
    if (head == tail) {
        delete head;
        return;
    }
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}

template <typename T>
void List<T>::removeLast() {
    if (head == tail) {
        delete head;
        return;
    }
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

template <typename T>
void List<T>::removeAt(int index) {
    if (index == 0) {
        removeFirst();
        return;
    }
    if (index == getSize() - 1) {
        removeLast();
        return;
    }
    Node<T>* current = getByIndex(index);
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

template <typename T>
int List<T>::getSize() const {
    Node<T>* tmp = head;
    int size = 0;
    while (tmp != nullptr) {
        size++;
        tmp = tmp->next;
    }
    return size;
}

template <typename T>
T List<T>::getAt(int index) {
    if (index < 0 || index >= getSize()) {
        throw "Trying to get element out of bound.";
    }
    return getByIndex(index)->data;
}

template <typename T>
void List<T>::destroy() {
    Node<T>* tmp = head;
    if (tmp == nullptr) {
        return;
    }
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        delete tmp->prev;
    }

    delete tail;
    head = nullptr;
    tail = nullptr;
}