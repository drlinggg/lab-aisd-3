#include <iostream>
int LEFT_SIDE = 0;
int RIGHT_SIDE = 1e9;

struct Node
{
        int number;
        Node* next = nullptr;
        Node* prev = nullptr;
};

struct stack1
{
    Node* top = nullptr;
    Node* bottom = nullptr;

    bool is_empty() {
        return top == nullptr;
    }

    void add(int number) {
        Node *link = new Node;
        link->number = number;
        if (is_empty()) {
            top = bottom = link;
        } else {
        link->prev = top;
        top->next = link;
        top = link;
        }
    }

    bool try_to_set(int k, int distance_between) {
        int count = 1;
        Node* last_boyarin = bottom;
        Node* currect_boyarin = bottom->next;
        while (currect_boyarin != nullptr) {
            if (currect_boyarin->number - last_boyarin->number > distance_between) {
                count++;
                last_boyarin = currect_boyarin;
            }
            currect_boyarin = currect_boyarin->next;
        }
        return count >= k;
    }

    int binary_search(int left, int right, int k) {
        while (left + 1 < right) {
                int mid = left + (right-left) / 2;
            if (try_to_set(k, mid)) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
    return right;
    }
};

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    int n, k;
    std::cin >> n >> k;
    stack1 s;
    for (int i = 0; i < n; i++) {
        int number;
        std::cin >> number;
        s.add(number);
    }
    std::cout << s.binary_search(LEFT_SIDE,RIGHT_SIDE,k);

    return 0;
}
