
#include <iostream>

using namespace std;

template<class T>
class DoubleList {
    struct Node {
        Node* previous = nullptr;
        Node* next = nullptr;
        T* data = nullptr;
        Node(T* data) {
            this->data = data;
        }
    };

    Node* node = nullptr;

public:
    DoubleList(T* data) {
        node = new Node(data);
    }
    bool hasNext() {
        return node->next != nullptr;
    }

    bool hasPrev() {
        return node->previous != nullptr;
    }

    void goPrev() {
        if(hasPrev()) {
            node = node->previous;
        }
    }

    void goNext() {
        if(hasNext()) {
            node = node->next;
        }
    }

    //adds a new node with @param data after the current node
    void addNode(T* data) {
        if(node) {
            Node* toAdd = new Node(data); //delete @ removeNode()
            toAdd->previous = this->node;
            toAdd->next = node->next;
            node->next = toAdd;
        } else {
            this->node = new Node(data);
        }
        goNext();
    }

    //removes the current node and sets "node" to
    void removeNode() {
        Node* temp = node;
        if(hasNext()) {
            node->next->previous = node->previous; //correct next node
        }
        if(hasPrev()) {
            node->previous->next = node->next; //correct previous node
        }
        if(hasNext()) {
            goNext();
        } else if (hasPrev()) {
            goPrev();
        }
        delete temp; //remove node

    }

    T *getData() const {
        return node->data;
    }
    void setData(T *newData) {
        node->data = newData;
    }

    void display(){
        while(hasPrev()) {
            goPrev();
        }
        while(node) {
            cout << *node->data << endl;
            if(hasNext()) {
                goNext();
            } else {
                break;
            }
        }
    }
};

int main() {
    int starter = 5;
    int testValue = 888;
    DoubleList<int> dll(&starter);
    for(int i=0; i<10; ++i) {
        int *data = new int(i);
        dll.addNode(data);
    }

    //test cases
    cout << "Initial Data" << endl;
    dll.display(); //display test
    cout << endl;
    while(dll.hasNext()) {
        dll.goNext();
    }
    dll.goPrev();
    dll.removeNode(); //remove a node
    cout << "Node removal test" << endl;
    dll.display();
    cout << endl;

    dll.addNode(&testValue); //add a test value
    cout << "Node add test" << endl;
    dll.display();

    return 0;
}

