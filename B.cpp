#include <iostream>

struct Node
{
        int number;
        Node* next = nullptr;
};

struct Queue1
{
    Node* head = nullptr;
    Node* tail = nullptr;

    bool is_empty() {
        return head == nullptr;
    }

    void add(int number) {
        Node *link = new Node;
        link->number = number;
        if (is_empty()) {
            head = tail = link;
        } else {
        tail->next = link;
        tail = link;
        }

    }

    void pop() {
        if (is_empty()) {
            return;
        }
        std::cout << head->number << '\n';
        Node *link = head;
        head = head->next;
        delete link;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
};

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;
    Queue1 q;
    for (int i = 0; i < n; i++) {
        char tmp;
        std::cin >> tmp;
        if (tmp == '+') {
            int tmp1;
            std::cin >> tmp1;
            q.add(tmp1);
        }
        else {
            q.pop();
        }
    }
    return 0;
}
