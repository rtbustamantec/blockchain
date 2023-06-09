#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "blockchain.h"
#include "stl/maxheap.h"
#include "stl/bst.h"

using namespace std;

tm parse_date(const string& date){
    tm tm_date = {};
    stringstream ss(date);
    ss >> get_time(&tm_date, "%m/%d/%Y");
    return tm_date;
}
void printMenu() {
    cout << "======================================" << endl;
    cout << "            MENÚ PRINCIPAL            " << endl;
    cout << "======================================" << endl;
    cout << "0. Cargar datos desde csv" << endl;
    cout << "1. Buscar registros por rango de monto" << endl;
    cout << "2. Buscar registros por rango de fechas" << endl;
    cout << "3. Buscar registros por remitente" << endl;
    cout << "4. Buscar registros por destinatario" << endl;
    cout << "5. Extraer registro con el monto más alto" << endl;
    cout << "6. Actualizar registro" << endl;
    cout << "7. Salir" << endl;
    cout << "======================================" << endl;
    cout << "Seleccione una opción: ";
}


void searchByAmountRange(BSTree<float,Record*> &mytree) {
    float rango_ini, rango_fin;
    cout << "Ingrese el rango inicial de monto: ";
    cin >> rango_ini;
    cout << "Ingrese el rango final de monto: ";
    cin >> rango_fin;

    cout << "Búsqueda por rango de monto" << endl;
    mytree.search_in_range(rango_ini, rango_fin);
}

void searchByDateRange(BSTree<time_t,Record*> &mytree) {
    string fecha_ini, fecha_fin;
    tm fecha_ini_parse, fecha_fin_parse;
    time_t fecha_ini_r, fecha_fin_r;
    cout << "Ingrese la fecha inicial (mm/dd/yyyy): ";
    cin >> fecha_ini;
    fecha_ini_parse = parse_date(fecha_ini);
    fecha_ini_r = mktime(&fecha_ini_parse);
    cout << "Ingrese la fecha final (mm/dd/yyyy): ";
    cin >> fecha_fin;
    fecha_fin_parse = parse_date(fecha_fin);
    fecha_fin_r = mktime(&fecha_fin_parse);

    cout << "Búsqueda por rango de fechas" << endl;
    mytree.search_in_range_date(fecha_ini_r,fecha_fin_r);
}

void searchByRemitente(ChainHash<string, Record*>& hash) {
    string remitente;
    cout << "Ingrese el nombre del remitente: ";
    cin.ignore();
    getline(cin, remitente);

    cout << "Búsqueda por remitente" << endl;
    hash.searchByRemitente(remitente);
}

void searchByDestinatario(ChainHash<string, Record*>& hash) {
    string destinatario;
    cout << "Ingrese el nombre del destinatario: ";
    cin.ignore();
    getline(cin, destinatario);

    cout << "Búsqueda por destinatario" << endl;
    hash.searchByDestinatario(destinatario);
}

void extractMaxRecord(MaxHeap<Record*>& maxHeap) {
    cout << "Búsqueda del registro con el monto más alto" << endl;
    maxHeap.extraerMaximo();
}

void updateRecord(Blockchain<Record>& chain) {
    int blockIndex, recordIndex;
    string remitente, destinatario, fecha;
    float monto;

    cout << "Ingrese el ID del nodo a modificar: ";
    cin >> blockIndex;
    cout << "Ingrese el ID del registro a modificar en el nodo: ";
    cin >> recordIndex;
    cout << "--" << endl;
    cout << "Ingrese el nombre del remitente: ";
    cin >> remitente;
    cout << "Ingrese el nombre del destinatario: ";
    cin >> destinatario;
    cout << "Ingrese el monto: ";
    cin >> monto;
    cout << "Ingrese fecha: ";
    cin >> fecha;

    chain.updateRecord(blockIndex, recordIndex, remitente, destinatario, monto, fecha);
}

int loadData(Blockchain<Record>& chain, ChainHash<string, Record*> myhash, ChainHash<string, Record*> &myhash_dest, MaxHeap<Record*> &maxHeap, BSTree<float,Record*> &mytree_monto,BSTree<time_t,Record*> &mytree_fecha) {
    Block<Record>* block = new Block<Record>();

    std::vector<std::vector<std::string>> data;
    std::ifstream file("datos_proyecto.csv");
    if (!file) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return false;
    }
    std::string line;

    Record* record;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }

        if (block->getSize() == block->getCapacity()) {
            chain.addBlock(block);
            block = new Block<Record>();
        } else {
            Record* new_record = new Record();
            new_record->remitente = row[0];
            new_record->destinatario = row[1];
            new_record->monto = stod(row[2]);
            new_record->fecha = row[3];

            block->insert(new_record);


            mytree_monto.insert_r(make_pair(new_record->monto, new_record));

            string fecha_f = row[3];
            tm fecha_parse = parse_date(fecha_f);
            time_t fecha_t = mktime(&fecha_parse);
            mytree_fecha.insert_r(make_pair(fecha_t, new_record));

            myhash.insert(make_pair(new_record->remitente, new_record));
            myhash_dest.insert(make_pair(new_record->destinatario, new_record));
            maxHeap.insertar(new_record->monto, new_record);
        }
    }

    delete block;
    return true;
}


int main() {
    Blockchain<Record>* chain = new Blockchain<Record>();
    ChainHash<string, Record*> myhash;
    ChainHash<string, Record*> myhash_dest;
    MaxHeap<Record*> maxHeap;
    BSTree<float,Record*> mytree_monto;
    BSTree<time_t,Record*> mytree_fecha;
    bool data_loaded = false;

    int option = 0;
    while (option != 7) {
        printMenu();
        cin >> option;
        if (option == 0) {
            data_loaded = loadData(*chain, myhash,myhash_dest, maxHeap, mytree_monto, mytree_fecha);
        } else if (option == 1 && data_loaded) {
            searchByAmountRange(mytree_monto);
        } else if (option == 2 && data_loaded) {
            searchByDateRange(mytree_fecha);
        } else if (option == 3 && data_loaded) {
            searchByRemitente(myhash);
        } else if (option == 4 && data_loaded) {
            searchByDestinatario(myhash_dest);
        } else if (option == 5 && data_loaded) {
            extractMaxRecord(maxHeap);
        } else if (option == 6 && data_loaded) {
            updateRecord(*chain);
        } else if (option == 7 && data_loaded) {
            cout << "Saliendo del programa..." << endl;
        } else if (!data_loaded) {
            cout << "Los datos no fueron cargados." << endl;
        } else {
            cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
        }

        cout << "--------------------------" << endl;
    }

    delete chain;

    return 0;
}
