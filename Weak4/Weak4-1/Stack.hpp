//
// Created by 변승우 on 2022/10/09.
//

#include "Stack.h"
#include <iostream>

using namespace std;

// 스택 생성자 top 초기화
template<typename T>
Stack<T>::Stack(): Array<T>() {
    top = 0;
};

// 스택이 꽉차면 true 반환
template<typename T>
bool Stack<T>::isFull() {
    if (top + 1 == Array<T>::getSize()) {
        cout << "Stack is full\n";
        return true;
    }
    return false;
}

// 스택이 비었으면 true 반환
template<typename T>
bool Stack<T>::isEmpty() {
    if (top == -1) {
        return true;
    }
    return false;
}

template<typename T>
void Stack<T>::push() {
    T item;
    cin >> item;
    // stack이 꽉찼으면 새로운 임시 배열을 만들어서 넣고 새로 재배열시킴
    if (isFull()) {
        T *newArr = new T[Array<T>::getSize()];
        for (int i = 0; i <= top; i++) {
            newArr[i] = Array<T>::get(i);
        }
        Array<T>::resize( newArr);
        delete[] newArr;
    }
    Array<T>::put(top++, item);
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        cout << "empty!" << endl;
        return -1;
    }
    return Array<T>::get(top--);
}

template<typename T>
void Stack<T>::draw() {
    cout << " index : item\n";
    // front ~ rear-1 까지 출력
    for (int i = 0; i < top; i++) {
        cout << "     " << i << " :  " << Array<T>::get(i) << "\n";
    }
}
