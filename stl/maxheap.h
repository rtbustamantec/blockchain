#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>

template<typename T>
class MaxHeap {
private:
    struct HeapNode {
        double maxAmount;
        T record;

        HeapNode(double amount, const T& rec) : maxAmount(amount), record(rec) {}
    };

    std::vector<HeapNode> heap;

    void heapifyup(int indice);
    void heapifydown(int indice);

public:
    MaxHeap() {}

    void insertar(double amount, const T& record);
    void extraerMaximo();
    T obtenerMaximo() const;
    bool empty() const;
    int size() const;
};

template<typename T>
void MaxHeap<T>::heapifyup(int indice) {
    int padre = (indice - 1) / 2;
    HeapNode nodoActual = heap[indice];
    while (indice > 0 && nodoActual.maxAmount > heap[padre].maxAmount) {
        heap[indice] = heap[padre];
        indice = padre;
        padre = (indice - 1) / 2;
    }
    heap[indice] = nodoActual;
}

template<typename T>
void MaxHeap<T>::heapifydown(int indice) {
    int hijoIzquierdo = 2 * indice + 1;
    int hijoDerecho = 2 * indice + 2;
    int mayor = indice;

    if (hijoIzquierdo < heap.size() && heap[hijoIzquierdo].maxAmount > heap[mayor].maxAmount) {
        mayor = hijoIzquierdo;
    }

    if (hijoDerecho < heap.size() && heap[hijoDerecho].maxAmount > heap[mayor].maxAmount) {
        mayor = hijoDerecho;
    }

    if (mayor != indice) {
        HeapNode nodoActual = heap[indice];
        heap[indice] = heap[mayor];
        heap[mayor] = nodoActual;
        heapifydown(mayor);
    }
}

template<typename T>
void MaxHeap<T>::insertar(double amount, const T& record) {
    HeapNode node(amount, record);
    heap.push_back(node);
    heapifyup(heap.size() - 1);
}

template<typename T>
void MaxHeap<T>::extraerMaximo() {
  
    std::cout << "Registro máximo encontrado:" << std::endl;
    std::cout << "Remitente: " << heap[0].record->remitente << std::endl;
    std::cout << "Destinatario: " << heap[0].record->destinatario << std::endl;
    std::cout << "Monto: " << heap[0].record->monto << std::endl;
    std::cout << "Fecha: " << heap[0].record->fecha << std::endl;

    heap[0] = heap.back();
    heap.pop_back();
    heapifydown(0);
}

template<typename T>
T MaxHeap<T>::obtenerMaximo() const {
    if (empty()) {
        throw std::out_of_range("El MaxHeap está vacío.");
    }

    return heap[0].record;
}

template<typename T>
bool MaxHeap<T>::empty() const {
    return heap.empty();
}

template<typename T>
int MaxHeap<T>::size() const {
    return heap.size();
}

#endif
