#ifndef PAGO_H_INCLUDED
#define PAGO_H_INCLUDED
#include "Fecha.h"

class Pago{
    private:
        Fecha *fechaPago;
        float montoPago;
    public:
        Pago(Fecha *fp, float mp){
            this->fechaPago = fp;
            this->montoPago = mp;
        }
        Fecha *getFechaPago(){
            return this->fechaPago;
        }
        float getMontoPago(){
            return this->montoPago;
        }
};


#endif // PAGO_H_INCLUDED
