//
// Created by 변승우 on 2022/10/09.
//

#include "circleQ.h"

// circleQ 생성자 rear, front 초기화
template<typename T>
circleQ<T>::circleQ() : Array<T>() {
    rear = 0;
    front = 0;
}

// circleQ 배열 비었는 지 확인하는 함수
template<typename T>
bool circleQ<T>::isEmpty() {
    // 비었으면 true 반환
    if (front == rear) {
        return true;
    }
    return false;
}

// circleQ 배열 꽉찼는지 확인하는 함수
template<typename T>
bool circleQ<T>::isFull() {
    // rear 다음이 front 면 꽉참 true 반환
    if ((rear + 1) % Array<T>::getSize() == front) {
        return true;
    }
    return false;
}

// circleQ 배열에 push
template<typename T>
void circleQ<T>::push() {
    // 템플릿 T 변수 입력
    T item;
    cin >> item;
    // rear 값 % size

    // circleQ 가 꽉차면
    if (isFull()) {
        // 임시 새로운 큐 생성
        T *newArr = new T[Array<T>::getSize()];
        int i;
        // 새로운 큐에 front 부터 rear-1 까지 값 복사
        for (i = 0; front != rear; i++) {
            front %= Array<T>::getSize();
            newArr[i] = Array<T>::get(front++);
        }
        rear = i;
        front = 0;
        // 재배열한 큐 resize 함수로 보냄
        Array<T>::resize(newArr);
        // 할당해제
        delete[] newArr;
    }
    Array<T>::put(rear, item);
    rear = (rear + 1) % Array<T>::getSize();
};

template<typename T>
T circleQ<T>::pop() {
    // circleQ가 비었으면 empty출력, -1반환
    if (isEmpty()) {
        cout << "is Empty" << endl;
        return -1;
    }
    front %= Array<T>::getSize();
    return Array<T>::get(front++);
}

template<typename T>
void circleQ<T>::draw() {
    cout << " index : item\n";
    // front ~ rear-1 까지 출력
    for (int i = front; i % Array<T>::getSize() != rear; i++) {
        i %= Array<T>::getSize();
        cout << "     " << i << " :  " << Array<T>::get(i) << "\n";
    }
}