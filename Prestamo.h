#ifndef PRESTAMO_H_INCLUDED
#define PRESTAMO_H_INCLUDED
#include "Cliente.h"
#include "Pago.h"
#define DIMP 5

class Prestamo{
    private:
        int numeroPrestamo;
        Cliente *cliente;
        Fecha *fechaAprobacion;
        float montoAprobado;
        Pago *lstPagos[DIMP];
        float saldoPendiente;
        int contadorPagos;
    public:
        Prestamo(){
            this->numeroPrestamo = 0;
            this->montoAprobado = 0;
            this->saldoPendiente = 0;
            this->contadorPagos = 0;
        }
        Prestamo(int np, Cliente *cli, Fecha *fa, float ma){
            this->numeroPrestamo = np;
            this->cliente = cli;
            this->fechaAprobacion = fa;
            this->montoAprobado = ma;
            this->saldoPendiente = ma;
            this->contadorPagos = 0;
        }
        int getNumeroPrestamo(){
            return this->numeroPrestamo;
        }
        void setNumeroPrestamo(int np){
            this->numeroPrestamo = np;
        }
        Cliente *getCliente(){
            return this->cliente;
        }
        void setCliente(Cliente *cli){
            this->cliente = cli;
        }
        void setFechaAprobacion(Fecha *fa){
            this->fechaAprobacion = fa;
        }
        Fecha *getFechaAprobacion(){
            return this->fechaAprobacion;
        }
        void setMontoAprobado(float ma){
            this->montoAprobado = ma;
        }
        float getMontoAprobado(){
            return this->montoAprobado;
        }
        bool hacerPago(Pago *pg){
            bool retorno = false;
            if (this->contadorPagos < DIMP){
                this->lstPagos[this->contadorPagos] = pg;
                this->contadorPagos++;
                this->saldoPendiente -= pg->getMontoPago();
                retorno =  true;
            }
            return retorno;
        }
        Pago **getLstPago(){
            return this->lstPagos;
        }
        float getSaldoPendiente(){
            return this->saldoPendiente;
        }
        int getContadorPagos(){
            return this->contadorPagos;
        }
};


#endif // PRESTAMO_H_INCLUDED
