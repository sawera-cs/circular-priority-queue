#include <iostream>
using namespace std;

const int MAX = 5;

class Document {
public:
    int priority;
    int index;

    Document(int p = 0, int i = 0) {
        priority = p;
        index = i;
    }
};

class CircularPriorityQueue {
private:
    Document* arr;
    int front;
    int rear;
    int size;
    int printCount;

public:
    CircularPriorityQueue() {
        arr = new Document[MAX];
        front = rear = -1;
        size = 0;
        printCount = 0;
    }

    ~CircularPriorityQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == MAX;
    }

    void enqueue(int pri, int idx) {
        if (isFull()) {
            cout << "Queue Overflow!\n";
            return;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % MAX;
        arr[rear] = Document(pri, idx);
        size++;
    }

    Document dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return Document();
        }

        Document temp = arr[front];

        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % MAX;
        }

        size--;
        return temp;
    }

    Document peek() {
        if (isEmpty()) {
            return Document();
        }
        return arr[front];
    }

    int findMaxPriority() {
        int maxPri = -1;
        int i = front;

        for (int count = 0; count < size; count++) {
            if (arr[i].priority > maxPri) {
                maxPri = arr[i].priority;
            }
            i = (i + 1) % MAX;
        }

        return maxPri;
    }

    int getPrintOrder(int priorities[], int n, int targetIndex) {

        for (int i = 0; i < n; i++) {
            enqueue(priorities[i], i);
        }

        while (!isEmpty()) {
            int maxPri = findMaxPriority();
            Document current = peek();

            if (current.priority == maxPri) {
                Document printed = dequeue();
                printCount++;

                if (printed.index == targetIndex) {
                    return printCount;
                }
            }
            else {
                Document temp = dequeue();
                enqueue(temp.priority, temp.index);
            }
        }

        return -1;
    }
};

int main() {
    CircularPriorityQueue q;

    int priorities[] = { 2, 1, 3, 2, 5 };
    int n = 5;
    int targetIndex = 2;

    int result = q.getPrintOrder(priorities, n, targetIndex);

    cout << "Document at index " << targetIndex
        << " will be printed after "
        << result << " operations.\n";
}