#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <map>

#include "block.h"

using namespace std;

template<typename T>
class Blockchain{
private:
    map<size_t, Block<T>*> block_map;
    string string_records;

    Block<Record>* last_block;

    int record_index;
    int block_index;

public:
    Blockchain() {
        block_index = 0;
        record_index = 0;
        string_records = "";
    };
    void addRecord(Record* new_record);
    void addBlock(Block<Record>* new_block);
    void mine(Block<Record>* block);
    Block<T> getBlock(int block_index);
    void searchByAmountRange(double min_amount, double max_amount);
    Record* getRecord(int block_index, int record_index);
    void searchByDateRange(const string& min_date, const string& max_date);
    //Record* getRecord(int block_index, int record_index);
    bool isDateInRange(const string& date, const string& min_date, const string& max_date);
    tm parseDate(const string& date);
    void searchByRemitente(const string& remitente);
    void searchByDestinatario(const string& destinatario);
    
};


template <typename T>
Block<T> Blockchain<T>::getBlock(int block_index) {
    auto it = block_map.find(block_index);
    if (it != block_map.end()) {
        return it->second;
    }
    return nullptr;
}

template <typename T>
void Blockchain<T>::mine(Block<Record>* block) {
  string previous_hash_code = last_block !=nullptr ? last_block->getHashCode() : "";
  block->setIndex(block_index);
  block->setPreviousHashCode(previous_hash_code);
  block->proofOfWork();

  last_block = block;
  block_index += 1;

  cout << "ID " << block->getIndex() << endl;
  cout << "PreviousHashCode " << block->getPreviousHashCode() << endl;
  cout << "CurrentHashCode " << block->getHashCode() << endl;
  cout << "--" << endl;
}

template <typename T>
void Blockchain<T>:: addBlock(Block<Record>* new_block) {
  mine(new_block);
  
  block_map[new_block->getIndex()] = new_block;
}

template <typename T>
void Blockchain<T>::searchByAmountRange(double min_amount, double max_amount) {
    cout << "Registros encontrados en el rango de monto $" << min_amount << " - $" << max_amount << ":" << endl;

    for (const auto& block_pair : block_map) {
        Block<Record>* block = block_pair.second;

        for (int i = 0; i < block->getSize(); i++) {
            Record* record = block->getRecord(i);
            if (record->monto >= min_amount && record->monto <= max_amount) {
                cout << "Remitente: " << record->remitente << endl;
                cout << "Destinatario: " << record->destinatario << endl;
                cout << "Monto: " << record->monto << endl;
                cout << "Fecha: " << record->fecha << endl;
                cout << "------------------------" << endl;
            }
        }
    }
}

template <typename T>
void Blockchain<T>::searchByDateRange(const string& min_date, const string& max_date) {
    cout << "Registros encontrados en el rango de fechas " << min_date << " - " << max_date << ":" << endl;

    for (const auto& block_pair : block_map) {
        Block<Record>* block = block_pair.second;

        for (int i = 0; i < block->getSize(); i++) {
            Record* record = block->getRecord(i);
            if (isDateInRange(record->fecha, min_date, max_date)) {
                cout << "Remitente: " << record->remitente << endl;
                cout << "Destinatario: " << record->destinatario << endl;
                cout << "Monto: " << record->monto << endl;
                cout << "Fecha: " << record->fecha << endl;
                cout << "------------------------" << endl;
            }
        }
    }
}

template <typename T>
bool Blockchain<T>::isDateInRange(const string& date, const string& min_date, const string& max_date) {
    tm min_tm = parseDate(min_date);
    tm max_tm = parseDate(max_date);
    tm record_tm = parseDate(date);

    time_t min_time = mktime(&min_tm);
    time_t max_time = mktime(&max_tm);
    time_t record_time = mktime(&record_tm);

    if (record_time >= min_time && record_time <= max_time) {
        return true;
    }
    return false;
}

template <typename T>
tm Blockchain<T>::parseDate(const string& date) {
    tm tm_date = {};
    stringstream ss(date);
    ss >> get_time(&tm_date, "%m/%d/%Y");
    return tm_date;
}

template <typename T>
void Blockchain<T>::searchByRemitente(const string& remitente) {
    cout << "Registros encontrados para el remitente \"" << remitente << "\":" << endl;

    for (const auto& block_pair : block_map) {
        Block<Record>* block = block_pair.second;

        for (int i = 0; i < block->getSize(); i++) {
            Record* record = block->getRecord(i);
            if (record->remitente == remitente) {
                cout << "Remitente: " << record->remitente << endl;
                cout << "Destinatario: " << record->destinatario << endl;
                cout << "Monto: " << record->monto << endl;
                cout << "Fecha: " << record->fecha << endl;
                cout << "------------------------" << endl;
            }
        }
    }
}

template <typename T>
void Blockchain<T>::searchByDestinatario(const string& destinatario) {
    cout << "Registros encontrados para el destinatario \"" << destinatario << "\":" << endl;

    for (const auto& block_pair : block_map) {
        Block<Record>* block = block_pair.second;

        for (int i = 0; i < block->getSize(); i++) {
            Record* record = block->getRecord(i);
            if (record->destinatario == destinatario) {
                cout << "Remitente: " << record->remitente << endl;
                cout << "Destinatario: " << record->destinatario << endl;
                cout << "Monto: " << record->monto << endl;
                cout << "Fecha: " << record->fecha << endl;
                cout << "------------------------" << endl;
            }
        }
    }
}

// template <typename T>
// void Blockchain<T>::updateRecord(int block_index, int record_index, const string& remitente, const string& destinatario, float monto, const string& fecha) {
//     Block<Record>* block = getBlock(block_index);
//     if (block != nullptr) {
//         Record* record = block->getRecord(record_index);
//         if (record != nullptr) {
//             record->remitente = remitente;
//             record->destinatario = destinatario;
//             record->monto = monto;
//             record->fecha = fecha;
//         } else {
//             cout << "No se encontró el registro en el índice especificado." << endl;
//         }
//     } else {
//         cout << "No se encontró el bloque en el índice especificado." << endl;
//     }
// }