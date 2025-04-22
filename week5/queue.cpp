#include <fstream>
#include <string>

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = q->tail = nullptr;
    return q;
}

void enqueue(Queue &q, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = nullptr;
    if (!q.tail) {
        q.head = q.tail = newNode;
    } else {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue &q) {
    if (!q.head) return -1; // Handle empty queue
    NODE* temp = q.head;
    int key = temp->key;
    q.head = q.head->p_next;
    if (!q.head) q.tail = nullptr;
    delete temp;
    return key;
}

int size(Queue q) {
    int count = 0;
    NODE* current = q.head;
    while (current) {
        count++;
        current = current->p_next;
    }
    return count;
}

bool isEmpty(Queue q) {
    return q.head == nullptr;
}

void printQueue(Queue q, std::ofstream &out) {
    if (isEmpty(q)) {
        out << "EMPTY" << std::endl;
        return;
    }
    NODE* current = q.head;
    while (current) {
        out << current->key;
        current = current->p_next;
        if (current) out << " ";
    }
    out << std::endl;
}

int main() {
    std::ifstream inp("input.txt");
    std::ofstream out("output.txt");
    Queue* q = initializeQueue();
    std::string command;

    while (inp >> command) {
        if (command == "init") {
            printQueue(*q, out);
        } else if (command == "enqueue") {
            int key;
            inp >> key;
            enqueue(*q, key);
            printQueue(*q, out);
        } else if (command == "dequeue") {
            dequeue(*q);
            printQueue(*q, out);
        }
    }

    // Clean up
    while (!isEmpty(*q)) dequeue(*q);
    delete q;
    inp.close();
    out.close();
    return 0;
}
