//
// Created by 변승우 on 2022/10/09.
//

#ifndef WEAK4_ARRAY_H
#define WEAK4_ARRAY_H

#include <iostream>

using namespace std;

// 기본 배열
template<typename T>
class Array {
    // 타입이 T인 포인터
    T *arr;
    // 최대 사이즈
    int maxSize;
protected:
    // Array 생성자 기본 사이즈는 10, 배열 동적할당 길이 10
    Array() {
        maxSize = 10;
        arr = new T[maxSize];
    }
    // 소멸자
    virtual ~Array() {
        delete[] arr;
    };
    // index와 넣을 요소 인자로 받아서 해당 인덱스에 요소 넣어줌
    void put(int idx, T item) {
        arr[idx] = item;
    }
    // index 인자로 받아서 해당 인덱스의 값 return
    T get(int idx) {
        return arr[idx];
    }
    // 크기를 두배로 늘려줌, 기존의 배열 해제하고, maxSize를 두배로 늘려줌, 그리고 arr 재할당후 인자로 받은 포인터 arr 에 복사
    void resize(T *newArr) {
        delete[]arr;
        maxSize = maxSize << 1;
        cout << "resize!\n";
        arr = new T[maxSize];
        // 깊은 복사해줌.
        for (int i = 0; i < maxSize / 2; i++) {
            arr[i] = newArr[i];
        }
    }
    // 현재 배열의 사이즈 반환
    int getSize() {
        return maxSize;
    }
};


#endif //WEAK4_ARRAY_H
