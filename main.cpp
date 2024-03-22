#include <iostream>
using namespace std;
#include <stdlib.h>
#define TML 5
#include "Cliente.h"
#include "Prestamo.h"

int menu(){
    int op;
    cout << "************\n";
    cout << "MENU DE OPCIONES\n";
    cout << "************\n";
    cout << "1. Agregar clientes a la lista\n";
    cout << "2. Agregar prestamo a la lista\n";
    cout << "3. Hacer pagos de prestamos\n";
    cout << "4. Mostrar lista de clientes\n";
    cout << "5. Mostrar lista de prestamos\n";
    cout << "6. Mostrar detalles de prestamo\n";
    cout << "7. Salir\n";
    cout << "************\n";
    cout << "Digite una opcion:";
    cin >> op;
    return op;
}

Cliente *BuscarCliente(Cliente *lst[], int cont, int db){
    bool encontrado = false;
    int contador =0;
    Cliente *cli = NULL;
    while (contador < cont && !encontrado){
        if (lst[contador]->getIdCliente() == db){
            encontrado = true;
            cli = lst[contador];
        }
        else{
            contador++;
        }
    }
    return cli;
}
Prestamo *BuscarPrestamo(Prestamo *lst[], int cont, int db){
    bool encontrado = false;
    int contador =0;
    Prestamo *ptmo = NULL;
    while (contador < cont && !encontrado){
        if (lst[contador]->getNumeroPrestamo() == db){
            encontrado = true;
            ptmo = lst[contador];
        }
        else{
            contador++;
        }
    }
    return ptmo;
}

Cliente *agregarCliente(){
    int id;
    string n,a;
    Cliente *cli;
    cout << "Digite el id del cliente: ";
    cin >> id;
    cout << "Digite el nombre del cliente: ";
    cin >> n;
    cout << "Digite el apellido del cliente: ";
    cin >> a;
    cli = new Cliente(id, n,a);
    return cli;
}
Prestamo *agregarPrestamo(Cliente *cli){
    int np;
    int d, m, a;
    Fecha *fa;
    float ma;
    Prestamo *ptmo;
    cout << "Digite el numero del prestamo: ";
    cin >> np;
    cout << "Digite la fecha de aprobacion (dd/mm/aa) : \n";
    cin >> d;
    cin >> m;
    cin >> a;
    fa = new Fecha(d,m,a);
    cout << "Digite el monto aprobado: ";
    cin >> ma;
    ptmo = new Prestamo(np, cli, fa, ma);
    return ptmo;
}

void registrarPago(Prestamo *ptmo){
    int d, m, a;
    Fecha *fp;
    float mp;
    Pago *pg;
    cout << "Digite la fecha de pago (dd/mm/aa) : \n";
    cin >> d;
    cin >> m;
    cin >> a;
    cout << "Digite el monto del pago: ";
    cin >> mp;
    fp = new Fecha(d, m, a);
    pg = new Pago(fp, mp);
    ptmo->hacerPago(pg);
}
void verDetalles(Prestamo *ptmo){
    cout << "El numero : " << ptmo->getNumeroPrestamo() <<endl;
    cout << "Cliente : " << ptmo->getCliente()->getNombre() << " " << ptmo->getCliente()->getApellido() << endl;
    cout << "Fecha Aprobacion : ";
    ptmo->getFechaAprobacion()->mostrarFecha();
    cout << "\nMonto aprobado : " << ptmo->getMontoAprobado() <<endl;
    cout << "Saldo pendiente : " << ptmo->getSaldoPendiente() << endl;
    if (ptmo->getContadorPagos() == 0){
        cout << "No tiene pagos registrados\n";
    }
    else{
        Pago **lista = ptmo->getLstPago();
        cout << "No\tFecha\tMonto\n";
        for (int i=0; i<ptmo->getContadorPagos();i++){
            cout << (i+1) << "\t";
            lista[i]->getFechaPago()->mostrarFecha();
            cout << "\t" << lista[i]->getMontoPago() << endl;
        }
    }
}

int main(){
    Cliente *lstCliente[TML];
    Prestamo *lstPrestamo[TML];
    Cliente *cli=NULL;
    Prestamo *ptmo = NULL;
    int opc, contCli = 0, contPtmo = 0, idCli, idPtmo;
    do{
        system("cls");
        opc = menu();
        switch (opc){
            case 1:
                ///Agregar clientes
                if (contCli < TML){
                    lstCliente[contCli] = agregarCliente();
                    contCli++;
                    cout << "El cliente se agrago con exito\n";
                }else{
                    cout << "La lista esta llena\n";
                }
                break;
            case 2:
                ///Agregar prestamo
                if(contPtmo < TML){
                    cout << "Digite el id del cliente: ";
                    cin >> idCli;
                    cli = BuscarCliente(lstCliente, contCli, idCli);
                    if (cli){
                        lstPrestamo[contPtmo] = agregarPrestamo(cli);
                        contPtmo++;
                        cout << "El prestamo se registro con exito\n";
                    }
                    else{
                        cout << "El cliente no existe, no se puede agregar el prestamo";
                    }
                }
                else{
                    cout << "La lista esta llena\n";
                }
                break;
            case 3:
                ///Hacer pagos
                cout << "Digite el numero de prestamo: ";
                cin >> idPtmo;
                ptmo = BuscarPrestamo(lstPrestamo, contPtmo, idPtmo);
                if(ptmo){
                    registrarPago(ptmo);
                    cout << "El pago se registro con exito\n";
                }
                else{
                    cout << "El prestamo no existe, no se puede registrar el pago";
                }
                break;
            case 4:
                ///Mostrar lista clientes
                if (contCli == 0){
                    cout << "La lista esta vacia\n";
                }
                else{
                    cout << "Id\tNombre\tApellido\n";
                    for (int i=0;i<contCli;i++){
                        cout <<lstCliente[i]->getIdCliente() << "\t";
                        cout <<lstCliente[i]->getNombre() << "\t";
                        cout <<lstCliente[i]->getApellido() << "\n";
                    }
                }
                break;
            case 5:
                ///Mostrar lista prestamos
                if (contPtmo == 0){
                    cout << "La lista esta vacia\n";
                }
                else{
                    cout << "No\tCliente\t\tFecha\tMonto\tSaldo\n";
                    for (int i=0;i<contPtmo;i++){
                        cout <<lstPrestamo[i]->getNumeroPrestamo() << "\t";
                        cout <<lstPrestamo[i]->getCliente()->getNombre() << " " << lstPrestamo[i]->getCliente()->getApellido() << "\t";
                        lstPrestamo[i]->getFechaAprobacion()->mostrarFecha();
                        cout << "\t" << lstPrestamo[i]->getMontoAprobado() << "\t";
                        cout << lstPrestamo[i]->getSaldoPendiente() <<endl;
                    }
                }

                break;
            case 6:
                ///Mostrar detalles del prestamo
                cout << "Digite el numero de prestamo: ";
                cin >> idPtmo;
                ptmo = BuscarPrestamo(lstPrestamo, contPtmo, idPtmo);
                if(ptmo){
                    verDetalles(ptmo);
                }
                else{
                    cout << "El prestamo no existe, no se puede visualizar los detalles";
                }
                break;
            case 7:
                ///Salir
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Error, opcion no definida\n";
                break;
        }
        system ("pause");
    }while (opc !=7);

    return 0;
}
