#include <iostream>
using namespace std;

template <typename T>
class Forward_list {
private:
    struct Node {
        T val;
        Node* next;
        Node(T x) : val(x), next(nullptr){}
    };

    Node* head;

public:
    Forward_list() : head(nullptr) {}

    T front() {
        if (head == nullptr) {
            return T();
        }
        return head->val;
    }


    T back() {
        if (head == nullptr) {
            return T();
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->val;
    }

    void push_front(T x) {
      Node* temp = new Node(x);
      temp->next = head;
      head = temp;
    }


    void push_back(T x) {
        Node* newNode = new Node(x);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void pop_front() {
      if (head == nullptr)
        return;
      Node* temp = head;
      head = head->next;
      delete temp;
    }

    void pop_back() {
        if (head == nullptr) return;

        if (head->next==nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        else {
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    T operator[](int index) {
      Node* temp = head;
      int i=0;
      while(temp && i<index) {
        temp = temp->next;
        i++;
      }
      if(temp == nullptr)
        return T();

      return temp->val;
    }

    bool empty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }

    int size() {
        int k = 1;
        Node* temp = head;
        if (temp == NULL) {
            return 0;
        }
        while (temp->next != NULL) {
            temp = temp->next;
            k++;
        }
        return k;
    }

    void clear() {
        if (head != nullptr) {
            Node* temp = head;
            while (temp->next != nullptr) {
                head = temp->next;
                delete temp;
                temp = head;
            }
            head =  nullptr;
            delete temp;
        }
    }

    void mergeSort(Node*& head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* slow = head;
        Node* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* middle = slow;
        Node* nextHalf = middle->next;
        middle->next = nullptr;

        mergeSort(head);
        mergeSort(nextHalf);

        Node* mergedList = nullptr;
        Node* last = nullptr;

        while (head != nullptr && nextHalf != nullptr) {
            if (head->val <= nextHalf->val) {
                if (mergedList == nullptr) {
                    mergedList = head;
                    last = mergedList;
                } else {
                    last->next = head;
                    last = last->next;
                }
                head = head->next;
            } else {
                if (mergedList == nullptr) {
                    mergedList = nextHalf;
                    last = mergedList;
                } else {
                    last->next = nextHalf;
                    last = last->next;
                }
                nextHalf = nextHalf->next;
            }
        }

        if (head != nullptr) {
            last->next = head;
        }

        if (nextHalf != nullptr) {
            last->next = nextHalf;
        }

        head = mergedList;
    }

    void sort() {
        mergeSort(head);
    }

    void reverse(){
      Node* prev = nullptr;
      Node* curr = head;
      while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
      }
      head = prev;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Forward_list() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main() {
    Forward_list<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    cout<<"LISTA ORIGINAL"<<endl;
    list.print();     // 10 20 30 40
    cout<<endl;

    cout << "Primer elemento (front): " << list.front() << endl;  // 10

    cout << "Último elemento (back): " << list.back() << endl;    // 40

    cout << "La lista esta vacia? (empty)(0->FALSE)(1->TRUE): " << list.empty() << endl;

    cout << "Size de la lista (size): " << list.size() << endl;

    cout<<"Eliminar ultimo elemento (pop_back): ";
    list.pop_back();
    list.print();

    list.clear();
    cout<<"Elimincar toda la lista (clear) (empty): "<<list.empty() << endl;

    list.push_back(5);
    list.push_back(3);
    list.push_back(8);
    list.push_back(1);

    cout << "Lista con elementos desordenados:" << endl;
    list.print();
    cout << endl;

    list.sort();
    cout << "Lista ordenada:" << endl;
    list.print();
    cout << endl;

    list.reverse();
    cout << "Lista invertida:" << endl;
    list.print();
    cout << endl;

    cout << "Elemento en el indice 2: " << list[2] << endl;


    return 0;
}
