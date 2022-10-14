#include <iostream>

using namespace std;

#include "circleQ.h"
#include "Stack.h"
#include "Queue.h"

int main() {

    cout << "4.1. 스택\n";
    Stack<int> st;
    int choice = 0;
    while(true) {
        cout << "스택 - 1.push 2.pop : ";
        cin >> choice;
        if (choice == -1) {
            break;
        }

        if (choice == 1) {
            st.push();
            st.draw();
        }
        if (choice == 2) {
            cout << st.pop() << "\n";
            st.draw();
        }
    }
    cout << "\n4.2. 큐\n";
    Queue<int> qu;
    while(true) {
        cout << "큐 - 1.addQ 2.deleteQ : ";
        cin >> choice;
        if (choice == -1) {
            break;
        }

        if (choice == 1) {
            qu.push();
            qu.draw();
        }
        if (choice == 2) {
            cout << qu.pop() << "\n";
            qu.draw();
        }
    }

    cout << "\n4.3. 원형큐\n";
    circleQ<int> cq;
    while(true) {
        cout << "원형큐 - 1.addQ 2.deleteQ : ";
        cin >> choice;
        if (choice == -1) {
            break;
        }

        if (choice == 1) {
            cq.push();
            cq.draw();
        }
        if (choice == 2) {
            cout << cq.pop() << "\n";
            cq.draw();
        }
    }

    return 0;
}
