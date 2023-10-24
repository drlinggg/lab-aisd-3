#include <iostream>

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
    int limit;
    int count_of_holding = 0;

    bool is_empty() {
        //проверка на пустоту
        return top == nullptr;
    }

    void add(int number) {
        //добавить элемент наверх
        Node *link = new Node;
        link->number = number;
        if (is_empty()) {
            top = bottom = link;
            //если он первый, то прировнять нижний к нему
        } else {
        link->prev = top;
        top->next = link;
        top = link;
        }
        count_of_holding++;
    }

    void pop_top() {
        //удалить верхний
        if (!is_empty()) {
            Node *that_top = top;
            top = top->prev;
            delete that_top;
        }
        count_of_holding--;
        //если после удаления нет элементов, почистить ссылки
        if (bottom == nullptr) {
            top = nullptr;
        }
    }
    void pop_bottom() {
        //удалить нижний
        if (!is_empty()) {
            Node *that_bottom = bottom;
            bottom = bottom->next;
            delete that_bottom;
        }
        count_of_holding--;
        //если после удаления нет элементов, почистить ссылки
        if (bottom == nullptr) {
            top = nullptr;
        }
    }
    int get_top() {
        //взять верхний
        return top->number;
        }
    int get_bottom() {
        //взять нижний
        return bottom->number;
    }
};

void insertion_sort(int* array) {
    //сортировка чтобы закинуть из 3 элементов наверх только средний и максимальный
    for (int i = 1; i < 3; i++) {
        int currect = i;
        while (array[currect] < array[currect-1] && currect > 0) {
            std::swap(array[currect], array[currect-1]);
            currect--;
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    stack1 s;
    int n,m;
    std::cin >> n >> m;
    s.limit = m;
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        if (s.count_of_holding < s.limit) {
                //если в рюкзаке есть место, то добавляем
            s.add(tmp);
        }
        else {
            //иначе сортируем нижний, верхний и текущий
            int array_of_three[3] = {s.get_bottom(), s.get_top(), tmp};
            insertion_sort(array_of_three);
            //удаляем в любом случае верхний и нижний
            s.pop_bottom();
            s.pop_top();
            //наверх идет средний и максимальный из 3
            s.add(array_of_three[1]);
            s.add(array_of_three[2]);
        }
    }
    while (!s.is_empty()) {
        //пока рюкзак не пустой, выводим нижний элемент и удаляем его
        std::cout << s.get_bottom() << ' ';
        s.pop_bottom();
    }
    return 0;
}
