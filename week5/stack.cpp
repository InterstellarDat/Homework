#include <fstream>
#include <string>
#include <vector>

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    return s;
}

void push(Stack &s, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
}

int pop(Stack &s) {
    if (!s.top) return -1; // Handle empty stack
    NODE* temp = s.top;
    int key = temp->key;
    s.top = s.top->p_next;
    delete temp;
    return key;
}

int size(Stack s) {
    int count = 0;
    NODE* current = s.top;
    while (current) {
        count++;
        current = current->p_next;
    }
    return count;
}

bool isEmpty(Stack s) {
    return s.top == nullptr;
}

void printStack(Stack s, std::ofstream &out) {
    if (isEmpty(s)) {
        out << "EMPTY" << std::endl;
        return;
    }
    // Collect elements in reverse order (bottom to top)
    std::vector<int> elements;
    NODE* current = s.top;
    while (current) {
        elements.push_back(current->key);
        current = current->p_next;
    }
    // Print from bottom to top
    for (int i = elements.size() - 1; i >= 0; --i) {
        out << elements[i];
        if (i > 0) out << " ";
    }
    out << std::endl;
}

int main() {
    std::ifstream inp("input.txt");
    std::ofstream out("output.txt");
    Stack* s = initializeStack();
    std::string command;

    while (inp >> command) {
        if (command == "init") {
            printStack(*s, out);
        } else if (command == "push") {
            int key;
            inp >> key;
            push(*s, key);
            printStack(*s, out);
        } else if (command == "pop") {
            pop(*s);
            printStack(*s, out);
        }
    }

    // Clean up
    while (!isEmpty(*s)) pop(*s);
    delete s;
    inp.close();
    out.close();
    return 0;
}
