#include <iostream>
#include <forward_list>
using namespace std;

const int K = 3; 
const float maxFillFactor = 0.4;

template<typename TK, typename TV>
class ChainHash{
private:    
    forward_list<pair<TK,TV>> *array; 
    int capacity;
    int size;

    hash<TK> hasher;
public:
    ChainHash(int cap = 13){
        this->capacity = cap;
        this->size = 0;
        array = new forward_list<pair<TK,TV>>[capacity];
    }

    void insert(pair<TK,TV> par){   
        if(fillFactor() > maxFillFactor) rehashing();    
        size_t hashcode = hasher(par.first);
        int index = hashcode % capacity;
        //validar la existencia de la key
        array[index].push_front(par);
        if(bucket_size(index) > K)
            rehashing();
    }

    int bucket_count(){
        return capacity;
    }

    int bucket_size(int index){
        return distance(array[index].begin(), array[index].end());
    }

    int fillFactor(){
      return number_of_elements() / (capacity * K);
    }

    int number_of_elements(){
      int elements = 0;
      for(int i = 0; i < capacity; i++){
        elements = elements + bucket_size(i);
      }
      return elements;
    }
    bool is_prime(int n) {
      if (n <= 1) return false;
      if (n <= 3) return true;
      if (n % 2 == 0 || n % 3 == 0) return false;
      int i = 5;
      while (i * i <= n) {
          if (n % i == 0 || n % (i + 2) == 0) {
              return false;
          }
          i += 6;
      }
      return true;
    }

    void rehashing(){
      int new_capacity = capacity * 2 + 1;
      while (!is_prime(new_capacity)) {
          new_capacity += 2;
      }
      forward_list<pair<TK, TV>> *new_array = new forward_list<pair<TK, TV>>[new_capacity];
      for(int i = 0; i < capacity; i++){
          for(auto it = array[i].begin(); it != array[i].end(); it++){
              size_t hashcode = hasher(it->first);
              int index = hashcode % new_capacity;
              new_array[index].push_front(*it);
          }
      }
      delete[] this->array;
      this->array = new_array;
      this->capacity = new_capacity;
    }

    string search(string remitente){
      size_t hashcode = hasher(remitente);
      int index = hashcode % capacity;
  
      for(auto it = array[index].begin(); it != array[index].end(); it++){
        cout<< it->second;
      }
      return ""; 
    }
    
    typename forward_list<pair<TK,TV>>::iterator begin(int index){
      return array[index].begin();
    }

    typename forward_list<pair<TK,TV>>::iterator end(int index){
      return array[index].end();
    }

    typename forward_list<pair<TK, TV>>::iterator find(const TK& key) {
      size_t hashcode = hasher(key);
      int index = hashcode % capacity;
  
      for (auto it = array[index].begin(); it != array[index].end(); it++) {
          if (it->first == key) {
              return it;
          }
      }
  
      return array[index].end();
    }

    void searchByRemitente(const TK& remitente) {
        size_t hashcode = hasher(remitente);
        int index = hashcode % capacity;

        for (auto it = array[index].begin(); it != array[index].end(); ++it) {
            if (it->first == remitente) {
                cout << "Registros encontrados para el remitente: " << remitente << endl;
                cout << "Remitente: " << it->second->remitente << endl;
                cout << "Destinatario: " << it->second->destinatario << endl;
                cout << "Monto: " << it->second->monto << endl;
                cout << "Fecha: " << it->second->fecha << endl;
                cout << "------------------------" << endl;
            }
        }
    }

 void searchByDestinatario(const TK& destinatario) {
        for (int i = 0; i < capacity; ++i) {
            for (auto it = array[i].begin(); it != array[i].end(); ++it) {
                if (it->second->destinatario == destinatario) {
                    cout << "Registros encontrados para el destinatario: " << destinatario << endl;
                    cout << "Remitente: " << it->second->remitente << endl;
                    cout << "Destinatario: " << it->second->destinatario << endl;
                    cout << "Monto: " << it->second->monto << endl;
                    cout << "Fecha: " << it->second->fecha << endl;
                    cout << "------------------------" << endl;
                }
            }
        }
    }
};


