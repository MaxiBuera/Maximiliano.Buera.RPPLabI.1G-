#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"
#include "prestamos.h"
#include "alquiler.h"
#define ACTIVO 0
#define SALDADO 1

#include "informes.h"
#define CLIENTES 50
#define PRESTAMOS 50
#define ALQUILERES 10
#define AMOLADORA 1
#define MEZCLADORA 2
#define TALADRO 3
#define ALQUILADO 0
#define FINALIZADO 1

int main()
{

    int menu;
    int indice;
    int auxiliarId;
    int flag = 0;
    int flagAlta;



    eCliente arrayClientes[CLIENTES];
    cliente_inicializarArrayClientes(arrayClientes,CLIENTES);
    cliente_altaForzada(arrayClientes,CLIENTES,"Alberto","Gimenez",11112222);
    cliente_altaForzada(arrayClientes,CLIENTES,"Pepe","A",22222222);
    cliente_altaForzada(arrayClientes,CLIENTES,"Jorgelina","B",66665555);

    cliente_imprimirClientes(arrayClientes,CLIENTES);

    ePrestamo arrayPrestamos[PRESTAMOS];
    prestamo_inicializarArrayPrestamos(arrayPrestamos,PRESTAMOS);
    prestamo_altaForzada(arrayPrestamos,PRESTAMOS,0,1000,3,ACTIVO);
    prestamo_altaForzada(arrayPrestamos,PRESTAMOS,0,2000,3,ACTIVO);
    prestamo_altaForzada(arrayPrestamos,PRESTAMOS,0,5000,10,SALDADO);
    prestamo_altaForzada(arrayPrestamos,PRESTAMOS,2,20000,5,SALDADO);
    prestamo_altaForzada(arrayPrestamos,PRESTAMOS,2,20000,5,SALDADO);


    printf("\n\n\n");
    printf("\t***** Prestamos *****");
    printf("\n");
    do{

        getValidInt("\n\n1.Alta Cliente"
                    "\n2.Modificar Datos del Cliente"
                    "\n3.Baja Cliente"
                    "\n4.Prestamo"
                    "\n5.Saldar Prestamo"
                    "\n6.Reanudar Prestamo"
                    "\n7.Imprimir Clientes"
                    "\n8.Imprimir Prestamos"
                    "\n9.Informes"
                    "\n10.Salir\n","\nNo valida\n",&menu,1,10,1);
        switch(menu)
        {
            case 1:
                system("cls");
                indice = cliente_buscarLugarLibre(arrayClientes,CLIENTES);
                if(indice >= 0){
                    flagAlta = cliente_agregarCliente(arrayClientes,CLIENTES,indice);
                    if(flagAlta == 0)
                        flag = 1;
                }
                cliente_imprimirClientes(arrayClientes,CLIENTES);
                break;
             case 2:
                if(flag!=0){
                    system("cls");
                    cliente_mostrarClienteID(arrayClientes,CLIENTES);
                    getValidInt("\tID de Cliente a modificar: ","\nID No valido\n",&auxiliarId,0,CLIENTES,2);
                    cliente_modificarCliente(arrayClientes,CLIENTES,auxiliarId);
               }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
             case 3:

                 if(flag!=0){
                    system("cls");
                    cliente_mostrarClienteID(arrayClientes,CLIENTES);
                    getValidInt("\nID de Cliente a eliminar: ","\nID No valido\n",&auxiliarId,0,CLIENTES,2);
                    cliente_eliminarCliente(arrayClientes,CLIENTES,auxiliarId);
                    cliente_imprimirClientes(arrayClientes,CLIENTES);
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 4:

                if(flag!=0){
                    system("cls");
                    indice = prestamo_buscarLugarLibre(arrayPrestamos,PRESTAMOS);
                    if(indice >= 0){
                        prestamo_nuevoPrestamo(arrayPrestamos,PRESTAMOS,arrayClientes,CLIENTES,indice);
                    }
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 5:

                if(flag!=0){
                    system("cls");
                    prestamo_saldarPrestamo(arrayPrestamos,PRESTAMOS,arrayClientes,CLIENTES);
               }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 6:

                if(flag!=0){
                    system("cls");
                    prestamo_reanudarPrestamo(arrayPrestamos,PRESTAMOS,arrayClientes,CLIENTES);
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 7:

                if(flag!=0){
                    system("cls");
                    cliente_imprimirClientes(arrayClientes,CLIENTES);
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 8:

                if(flag!=0){
                    system("cls");
                    prestamo_imprimirPrestamos(arrayPrestamos,PRESTAMOS,arrayClientes,CLIENTES);
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
            case 9:

                if(flag!=0){
                    system("cls");
                    informes_clienteConMasPrestamos(arrayClientes,CLIENTES,arrayPrestamos,PRESTAMOS,1);
                    informes_clienteConMasPrestamosActivos(arrayClientes,CLIENTES,arrayPrestamos,PRESTAMOS,2);
                    informes_clienteConMasPrestamosSaldados(arrayClientes,CLIENTES,arrayPrestamos,PRESTAMOS,3);
                }
                else{

                    printf("\nDebe ingresar almenos un cliente\n");
                }
                break;
        }
    }while(menu != 10);


    return 0;
}

