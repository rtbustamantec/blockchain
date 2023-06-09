#include <iostream>
#include <utility>
#include <stack>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <functional>
using namespace std;
template <typename TK, typename TV>
struct NodeBT {
    pair<TK,TV> data;
    NodeBT *left;
    NodeBT *right;
};

template <typename TK, typename TV>
class BSTIterator{
private:
    NodeBT<TK,TV> *current;
    stack<NodeBT<TK,TV>*> stack;

public:
    BSTIterator(): current(nullptr){};

    BSTIterator(NodeBT<TK,TV>* node){
        while(node != nullptr){
            this->stack.push(node);
            node = node->left;
        }
        this->current = this->stack.empty() ? nullptr : stack.top();
    }

    BSTIterator<TK,TV> &operator++(){
        if(this->stack.empty())
            throw out_of_range("It's not possible");

        NodeBT<TK,TV> *node = this->stack.top();
        this->stack.pop();
        node = node->right;

        while(node != nullptr){
            this->stack.push(node);
            node = node->left;
        }

        this->currrent = this->stack.empty() ? nullptr : stack.pop();
        return *this;
    }

    BSTIterator<TK,TV> &operator=(BSTIterator<TK,TV> other){
        this->current = other->current;
        this->stack = other.stack;
        return (*this);
    }

    BSTIterator<TK,TV> &operator!=(BSTIterator<TK,TV> other){
        this->current != other->current;
        this->stack != other.stack;
        return (*this);
    }
};
template <typename TK, typename TV>
class BSTree {
public:
    typedef BSTIterator<TK,TV> iterator;

private:
    NodeBT<TK,TV> *root;
    friend class BSTIterator<TK, TV>;

public:

    BSTree() {
        root = nullptr;
    }


    void insert_r(pair<TK,TV> data) {
        insert_r(root, data);
    }


    void display_inorder_r() {
        display_inorder_r(root);
    }

    void display_preorder_r() {
        display_preorder_r(root);
    }

    void display_postorder_r() {
        display_postorder_r(root);
    }
    bool find_r(pair<TK,TV> data){
        find_r(root, data);
    }

    pair<TK,TV> get_minimum_r(){
        return get_minimum_r(root);
    }

    void display_inorder_i(){
        display_inorder_i(root);
    }

    void display_preorder_i(){
        display_preorder_i(root);
    }

    void display_postorder_i(){
        display_postorder_i(root);
    }
    pair<TK,TV> succesor_i(pair<TK,TV> data){
        succesor_i(root, data);
    }

    void search_in_range(float monto_min, float monto_max) {
        search_in_range(root, monto_min, monto_max);
    }

    void search_in_range_date(time_t fecha_min,time_t fecha_max) {
        search_in_range_date(root, fecha_min, fecha_max);
    }
private:
    bool find_r(NodeBT<TK,TV>* node, pair<TK,TV> data){
        if (node == nullptr){
            return false;
        }
        else if (data.first < node->data.first){
            return find_recursive(node->left, data);
        }
        else if(data.first > node->data.first){
            return find_recursive(node->right, data);
        }
        else
            return true;
    }

    void insert_r(NodeBT<TK,TV>* &node, pair<TK,TV> data) {
        if (node == nullptr) {
            NodeBT<TK,TV>* nuevo = new NodeBT<TK,TV>();
            nuevo->data = data;
            nuevo->left = nuevo->right = nullptr;
            node = nuevo;
        } else if(data.first < node->data.first) {
            insert_r(node->left, data);
        } else if(data.first > node->data.first) {
            insert_r(node->right, data);
        }
    }


    void display_inorder_r(NodeBT<TK,TV>* node) {
        if (node == nullptr) return;
        display_inorder_r(node->left);
        cout<<node->data.first << ": " << node->data.second<<endl;
        display_inorder_r(node->right);
    }

    void display_preorder_r(NodeBT<TK,TV>* node) {
        if (node == nullptr) return;
        cout<<node->data.first << ": " << node->data.second<<endl;
        display_preorder_r(node->left);
        display_preorder_r(node->right);
    }

    void display_postorder_r(NodeBT<TK,TV>* node) {
        if (node == nullptr) return;
        display_postorder_r(node->left);
        display_postorder_r(node->right);
        cout<<node->data.first << ": " << node->data.second<<endl;
    }

    pair<TK,TV> get_minimum_r(NodeBT<TK,TV>* node){
        if(node == nullptr) throw "BST with no elements";
        if(node->left == nullptr) return node->data;
        return get_minimum_r(node->left);
    }

    void display_inorder_i(NodeBT<TK,TV>* current){
        stack<NodeBT<TK,TV>*> mstack;
        while(current != nullptr || !mstack.empty()){
            while(current != nullptr){
                mstack.push(current);
                current = current->left;
            }
            NodeBT<TK,TV>* temp = mstack.top();
            mstack.pop();
            cout<<temp->data.first<<": "<<temp->data.second<<endl;
            current = temp->right;
        }
    }

    void display_preorder_i(NodeBT<TK,TV>* current){
        stack<NodeBT<TK,TV>*> mstack;
        mstack.push(current);
        while(!mstack.empty()){
            NodeBT<TK,TV>* temp = mstack.top();
            mstack.pop();
            cout<<temp->data.first<<": "<<temp->data.second<<endl;
            if(temp->right != nullptr){
                mstack.push(temp->right);
            }
            if(temp->left != nullptr){
                mstack.push(temp->left);
            }
        }
    }

    void display_postorder_i(NodeBT<TK,TV>* root) {
        if (root == nullptr) {
            return;
        }

        stack<NodeBT<TK,TV>*> mstack;
        mstack.push(root);

        while (!mstack.empty()) {
            NodeBT<TK,TV>* current = mstack.top();

            if (current->left != nullptr && current->left != root && current->right != root) {
                mstack.push(current->left);
            }
            else if (current->right != nullptr && current->right != root) {
                mstack.push(current->right);
            }
            else {
                cout << current->data.first << ": " << current->data.second << endl;
                mstack.pop();
                root = current;
            }
        }
    }

    int height(NodeBT<TK,TV>* node){
        if(node == nullptr) return -1;
        return max(height(node->left),height(node->right)) + 1;
    }

    pair<TK,TV> succesor_i(NodeBT<TK,TV>* current, pair<TK,TV> data){
        stack<NodeBT<TK,TV>*> mstack;
        while(current != nullptr){
            if(data.first < current->data.first){
                mstack.push(current);
                current = current->left;
            }
            else if (data.first > current->data.first){
                mstack.push(current);
                current = current->right;
            }
            else{
                break;
            }
        }

        if(current == nullptr){
            throw std::out_of_range("No element");
        }

        if(current->right != nullptr){
            return get_minimum_r(current->right);
        }
        else{
            while(!mstack.empty()){
                NodeBT<TK,TV>* prev = mstack.top();
                mstack.pop();
                if(prev->data.first > current->data.first){
                    return prev->data;
                }
            }
        }
    }
    void search_in_range(NodeBT<TK, TV>* node, float monto_min, float monto_max) {
        if (node == nullptr) {
            return;
        }

        if (node->data.first >= monto_min && node->data.first <= monto_max) {
            // Imprimir o realizar alguna operación con el registro
            cout << "Remitente: " << node->data.second->remitente << endl;
            cout << "Destinatario: " << node->data.second->destinatario << endl;
            cout << "Monto: " << node->data.second->monto << endl;
            cout << "Fecha: " << node->data.second->fecha << endl;
            cout << "------------------------" << endl;
        }

        if (node->data.first >= monto_min) {
            search_in_range(node->left, monto_min, monto_max);
        }

        if (node->data.first <= monto_max) {
            search_in_range(node->right, monto_min, monto_max);
        }
    }

    void search_in_range_date(NodeBT<TK, TV>* node, time_t fecha_min, time_t fecha_max) {
        if (node == nullptr) {
            return;
        }

        if (node->data.first >= fecha_min && node->data.first <= fecha_max) {
            // Imprimir o realizar alguna operación con el registro
            cout << "Remitente: " << node->data.second->remitente << endl;
            cout << "Destinatario: " << node->data.second->destinatario << endl;
            cout << "Monto: " << node->data.second->monto << endl;
            cout << "Fecha: " << node->data.second->fecha << endl;
            cout << "------------------------" << endl;
        }

        if (node->data.first >= fecha_min) {
            search_in_range_date(node->left, fecha_min, fecha_max);
        }

        if (node->data.first <= fecha_max) {
            search_in_range_date(node->right, fecha_min, fecha_max);
        }
    }


};