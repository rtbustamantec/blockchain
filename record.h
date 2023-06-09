#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <map>
using namespace std;

struct Record {
    string remitente;
    string destinatario;
    double monto;
    string fecha;

    string full_data() {
        std::ostringstream ss;
        ss << remitente << " " << destinatario << " " << to_string(monto) << " " << fecha;
        return ss.str();
    };
};