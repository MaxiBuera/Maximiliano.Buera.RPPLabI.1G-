#ifndef PRESTAMOS_H_INCLUDED
#define PRESTAMOS_H_INCLUDED

typedef struct{
    int id;
    int idCliente;
    float importe;
    int cantidadCuotas;
    int isEmpty;
    int estado;
}ePrestamo;

#endif // PRESTAMOS_H_INCLUDED


int prestamo_inicializarArrayPrestamos(ePrestamo* arrayPrestamos, int limite);

int prestamo_buscarLugarLibre(ePrestamo* arrayPrestamos,int limite);

int prestamo_verificarCliente(eCliente* arrayClientes, int limiteClientes, int idCliente);

int prestamo_altaForzada(ePrestamo* arrayPrestamos,int limite,int idCliente, float importe, int cantidadCuotas, int estado);

int prestamo_nuevoPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes, int indice);

int prestamo_imprimirPrestamos(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes, int limiteClientes);

int prestamo_saldarPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes);

int prestamo_reanudarPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes);
