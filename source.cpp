#include <iostream>

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
void tablero();
void entradas();

bool validPosition(string position, string pieceOne = "", string pieceTwo = "") {

    // - Extraer la fila y columna de la entrada en position
    char row = position[0];
    char column = toupper(position[1]);

    // - Extraer la fila y columna de la pieceOne y pieceTwo (si hay)
    if (pieceOne != "") {
        cout << pieceOne;
    }

    if (pieceTwo != "") {
        cout << pieceTwo;
    }

    bool badRow = row <= 48 || row >= 57;
    bool badColumn = column <= 64 || column >= 73;
    bool duplicate;

    if (badRow || badColumn) {
        cout << "Entrada Invalida!!" << endl;
        
        if (badRow) {
            cout << "La fila debe estar entre 1 y 8" << endl;
            system("pause");
        }
        else if (badColumn) {
            cout << "La columna debe estar entre A y H" << endl;
            system("pause");
        }
        else if (pieceOne != "") {
            cout << pieceOne << endl;
        }

        cout << "\n";
        return false;
    }

    return true;
}

int main() {
    bienvenida();

    // Validad entrada
    entradas();
}

void bienvenida() {
    system("cls");

    cout << "Bienvenido al proyecto de Ajedrez de IDS344" << endl;
    cout << "\nNomenclatura: " << endl;
    cout<<"-  X = Cuadro blanco"<<endl;
    cout<<"-  Espacio en blanco = Cuadro negro"<<endl;
    cout<<"-  TN = Torre negra"<<endl;
    cout<<"-  RB = Reina blanca"<<endl;
    cout<<"\nPara moverse :"<<endl;
    cout<<"  1ro. Escribe la fila y columna de la ficha que deseas mover."<<endl;
    cout<<"  2do. Escribe la fila y columna de hacia donde la deseas mover."<<endl;

    char opcion;

    cout << "\nListo? (y/n): ";
    cin >> opcion;

    opcion = toupper(opcion);

    if (opcion == 'Y') tablero();
    else return;
    
}

void tablero() {
    system("cls");

    cout << "Tablero:\n\n";

    int length = 8,width = 8, row, column;

    // * IMPRIMIR FILAS Y COLUMNAS DEL TABLERO *

    for(row = 0; row < length; row++)
    {
        int index = 0;
        while(index < 3) {
            if (index == 1) {
                cout << row + 1 << ".: ";
            } else {
                cout << "    ";
            }

            for(column = 0; column < width; column++)
            {
                if((row + column) % 2 == 0) {
                    cout << "[XXX]";
                }
                else {
                    cout << "[   ]";
                }
            }
            cout << "\n";

            index++;
        }
    }

    // * IMPRIMIR NUMERO DE COLUMNA DEBAJO *

    int index = 0;

    cout << "\n  ";

    while(index < 40) {
        if (index % 4 == 0) {
            switch(index/4) {
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


void entradas() {
    string torreUno, torreDos, reina;
    
    do {
        cout << "Ingrese la posicion de la primera torre: ";
        cin >> torreUno;

    } while (!validPosition(torreUno));

    do {
        cout << "Ingrese la posicion de la segunda torre: ";
        cin >> torreDos;

    } while (!validPosition(torreDos));

    do {
        cout << "Ingrese la posicion de la reina: ";
        cin >> reina;

    } while (!validPosition(reina, torreUno, torreDos));
}