//
// Created by 변승우 on 2022/10/09.
//

#include "Queue.h"
#include <iostream>

using namespace std;

// Queue 생성자 rear, front 초기화
template<typename T>
Queue<T>::Queue() :Array<T>() {
    rear = 0;
    front = 0;
}

// Queue 배열이 꽉차면 true 반환
template<typename T>
bool Queue<T>::isFull() {
    if (rear+1 == Array<T>::getSize()) {
        return true;
    }
    return false;
}

// Queue 배열이 비었으면 true return
template<typename T>
bool Queue<T>::isEmpty() {
    if (rear == front) {
        return true;
    }
    return false;
}

template<typename T>
void Queue<T>::push() {
    // item을 입력받음
    T item;
    cin >> item;
    // Queue 가 꽉차면
    if (isFull()) {
        // 새로운 임시 배열 생성
        T *newArr = new T[Array<T>::getSize()];
        int i;
        // front 부터 rear까지 newArr에 값 복사
        for (i = 0; front < rear; i++) {
            newArr[i] = Array<T>::get(front++);
        }
        rear = i;
        front = 0;
        // newArr을 resize함수로 보냄
        Array<T>::resize(newArr);
        // 동적할당 해제
        delete[] newArr;
    }
    Array<T>::put(rear++, item);
}

// Queue의 배열이 비었으면 -1반환
template<typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        cout << "is Empty!" << endl;
        return -1;
    }
    return Array<T>::get(front++);
}

template<typename T>
void Queue<T>::draw() {
    cout << " index : item\n";
    // front ~ rear-1 까지 출력
    for (int i = front; i < rear; i++) {
        cout << "     " << i << " :  " << Array<T>::get(i) << "\n";
    }
}
