#include <iostream>
#include <algorithm>
#include <string>

using std::cout; using std::string;
using std::endl; using std::cin;
using std::transform; using std::toupper;

using namespace std;

/*
    Fecha de Inicio: 4 - 11 - 2021

    Fecha de Entrega: 6 - 11 - 2021

    Grupo #02

    * Christopher Tineo
    * Camilo Maria
    * Lya Sanchez
    * Sahira Tejada
    * Taiyab Gillani
    * José Fernandez

    * Instrucciones

    Realizar un programa C++ que dado la ubicación de 2 torres enemigas y una Reina, se produzca una salida con todas las jugadas posibles de la reina donde puede y no ser eliminada.
*/

void bienvenida();
void tablero(string* = NULL);
string *entradas();
bool validPosition(string, string = "", string = "");

string upperString(string s)
{
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return toupper(c); });
    return s;
}

int main() {
    bienvenida();

    // Mostrar tablero con jugadas
    tablero(entradas());

    system("pause");
}

void bienvenida() {
    system("cls");

    cout << "Bienvenido al proyecto de Ajedrez de IDS344" << endl;
    cout << "\nNomenclatura: " << endl;
    cout<<"-  T = Torre negra"<<endl;
    cout<<"-  R = Reina blanca"<<endl;
    cout<<"\nPara colocar fichas :"<<endl;
    cout<<"  Escribe la fila (1-9) y columna (A-H) donde colocaras la ficha."<<endl;

    char opcion;

    cout << "\nListo? (y/n): ";
    cin >> opcion;

    opcion = toupper(opcion);

    if (opcion == 'Y') {
        tablero();
    } 
    else return;
}

void tablero(string* jugada) {

    int length = 8, width = 8, row, column;

    char tablero[length][width] = {0};

    if (jugada != NULL) {
        // Si existen elementos en jugada

        int index = 0;

        while(index < 3) {
            int fila = jugada[index][0] - '1';
            int columna;
            
            switch(jugada[index][1]) {
                case 'A':
                    columna = 0;
                    break;
                case 'B':
                    columna = 1;
                    break;
                case 'C':
                    columna = 2;
                    break;
                case 'D':
                    columna = 3;
                    break;
                case 'E':
                    columna = 4;
                    break;
                case 'F':
                    columna = 5;
                    break;
                case 'G':
                    columna = 6;
                    break;
                case 'H':
                    columna = 7;
                    break;
            };

            if (index < 2) {
                tablero[fila][columna] = 'T';
            } else {
                tablero[fila][columna] = 'R';
            }

            index++;
        }
    }

    system("cls");

    cout << "Tablero:\n\n";

    // * IMPRIMIR FILAS Y COLUMNAS DEL TABLERO *

    int filaReina = -1, columnaReina = -1;

    for(row = 0; row < length; row++)
    {
        cout << row + 1 << ".: ";

        for(column = 0; column < width; column++)
        {
            bool jugadaValida = false;
            jugadaValida = (row == filaReina) || (column == columnaReina);

            if (tablero[row][column] == 'T') {
                cout << "[T]";
            }
            else if (tablero[row][column] == 'R') {
                filaReina = row;
                columnaReina = column;
                cout << "[R]";
            }
            else if (jugadaValida) {
                cout << "[V]";
            }
            // else if (jugadaNoValida) {
            //     cout << "[X]";
            // }
            else {
                cout << "[ ]";
            }    
        }
        cout << "\n";
    }

    // * IMPRIMIR COLUMNA DEBAJO *

    int index = 0;

    cout << "\n   ";

    while(index < 40) {
        if (index % 2 == 0) {
            switch(index/2) {
                case 1:
                    cout << "A";
                    break;
                case 2:
                    cout << "B";
                    break;
                case 3:
                    cout << "C";
                    break;
                case 4:
                    cout << "D";
                    break;
                case 5:
                    cout << "E";
                    break;
                case 6:
                    cout << "F";
                    break;
                case 7:
                    cout << "G";
                    break;
                case 8:
                    cout << "H";
                    break;
                default:
                    cout << "";
                    break;
            }
        }
        cout << " ";
        index++;
    }

    cout << "\n\n";

}

string *entradas() {
    string torreUno, torreDos, reina;

    string *lista = new string[3];

    do {
        cout << "Ingrese la posicion de la primera torre: ";
        cin >> torreUno;

    } while (!validPosition(torreUno));

    do {
        cout << "Ingrese la posicion de la segunda torre: ";
        cin >> torreDos;

    } while (!validPosition(torreDos, torreUno));

    do {
        cout << "Ingrese la posicion de la reina: ";
        cin >> reina;

    } while (!validPosition(reina, torreUno, torreDos));

    lista[0] = upperString(torreUno);
    lista[1] = upperString(torreDos);
    lista[2] = upperString(reina);

    return lista;
}

bool validPosition(string position, string positionTwo, string positionThree) {

    position = upperString(position);
    positionTwo = upperString(positionTwo);
    positionThree = upperString(positionThree);

    // Condicion 1. Estar en el tablero.

        // - Extraer la fila y columna de la entrada en position
    
    char row = position[0];
    char column = position[1];

    bool badRow = row <= 48 || row >= 57; // La fila esta entre 1 y 8 (En codigo ASCII)
    bool badColumn = column <= 64 || column >= 73; // La fila esta entre A y H (En codigo ASCII)

    // Condicion 2. No ser la posicion de otra ficha.

    bool duplicate = position == positionTwo || position == positionThree;

    // Condicion 3. No puede ser mayor a 2 caracteres

    bool sizeError = position.size() > 2;

    if (badRow || badColumn || duplicate || sizeError) {
        cout << "\nERROR: Entrada Invalida!!" << endl;
        
        if (badRow) {
            cout << "* La fila debe estar entre 1 y 8." << endl;
        }
        else if (badColumn) {
            cout << "* La columna debe estar entre A y H." << endl;
        }
        else if (duplicate) {
            cout << "* Dos fichas no pueden estar en la misma posicion." << endl;
        }
        else if (sizeError) {
            cout << "* La entrada no puede tener mas de 2 caracteres." << endl;
        }

        cout << "\n";
        system("pause");
        return false;
    }

    return true;
}
