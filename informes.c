#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "cliente.h"

#include "prestamos.h"

#include "alquiler.h"
#include "informes.h"
#define OCUPADO 0
#define LIBRE 1
#define ACTIVO 0
#define SALDADO 1
#define ALQUILADO 0
#define FINALIZADO 1



void resultadoMasPrestamos(eCliente* arrayClientes, int limiteClientes,ePrestamo* arrayPrestamos, int limitePrestamos ,int contMasPrestamosMAX,int informe){

    int i,j;
    int contador=0;

    if(informe == 1){
       printf("\nCliente(s) con mas cantidad de prestamos: ");
    }
    else if(informe == 2){
        printf("\nCliente(s) con mas cantidad de prestamos Activos: ");
    }
    else{
        printf("\nCliente(s) con mas cantidad de prestamos Saldados: ");
    }


    for(i=0;i<limiteClientes;i++){

        if(arrayClientes[i].isEmpty == OCUPADO){

            for(j=0;j<limitePrestamos;j++){

                if(arrayClientes[i].id == arrayPrestamos[j].idCliente && arrayPrestamos[j].isEmpty == OCUPADO){

                    contador++;
                }
            }
            if(contador == contMasPrestamosMAX){

                printf("%s %s,",arrayClientes[i].nombre,arrayClientes[i].apellido);

            }

            contador = 0;
        }
    }

    printf("- %d prestamo(s)",contMasPrestamosMAX);
}

int informes_clienteConMasPrestamos(eCliente* arrayClientes, int limiteClientes,ePrestamo* arrayPrestamos, int limitePrestamos,int informe){

    int retorno = -1;
    int i,j;
    int contMasPrestamos=0;
    int contMasPrestamosMAX=-1;

    if(arrayClientes != NULL && limiteClientes > 0){

        for(i=0;i<limiteClientes;i++){

            if(arrayClientes[i].isEmpty == OCUPADO){

                for(j=0;j<limitePrestamos;j++){

                    if(arrayClientes[i].id == arrayPrestamos[j].idCliente && arrayPrestamos[j].isEmpty == OCUPADO){

                        contMasPrestamos++;
                    }
                }
                if(contMasPrestamos > contMasPrestamosMAX){

                    contMasPrestamosMAX = contMasPrestamos;
                }
                contMasPrestamos = 0;
            }
        }
        resultadoMasPrestamos(arrayClientes,limiteClientes,arrayPrestamos,limitePrestamos,contMasPrestamosMAX,informe);
    }

    return retorno;
}

int informes_clienteConMasPrestamosActivos(eCliente* arrayClientes, int limiteClientes,ePrestamo* arrayPrestamos, int limitePrestamos, int informe){

    int retorno = -1;
    int i,j;
    int contMasPrestamos=0;
    int contMasPrestamosMAX=-1;

    if(arrayClientes != NULL && limiteClientes > 0){

        for(i=0;i<limiteClientes;i++){

            if(arrayClientes[i].isEmpty == OCUPADO){

                for(j=0;j<limitePrestamos;j++){

                    if(arrayClientes[i].id == arrayPrestamos[j].idCliente && arrayPrestamos[j].estado == ACTIVO){

                        contMasPrestamos++;
                    }
                }
                if(contMasPrestamos > contMasPrestamosMAX){

                    contMasPrestamosMAX = contMasPrestamos;
                }
                contMasPrestamos = 0;
            }
        }
        resultadoMasPrestamos(arrayClientes,limiteClientes,arrayPrestamos,limitePrestamos,contMasPrestamosMAX,informe);
    }

    return retorno;
}

int informes_clienteConMasPrestamosSaldados(eCliente* arrayClientes, int limiteClientes,ePrestamo* arrayPrestamos, int limitePrestamos, int informe){

    int retorno = -1;
    int i,j;
    int contMasPrestamos=0;
    int contMasPrestamosMAX=-1;

    if(arrayClientes != NULL && limiteClientes > 0){

        for(i=0;i<limiteClientes;i++){

            if(arrayClientes[i].isEmpty == OCUPADO){

                for(j=0;j<limitePrestamos;j++){

                    if(arrayClientes[i].id == arrayPrestamos[j].idCliente && arrayPrestamos[j].estado == SALDADO){

                        contMasPrestamos++;
                    }
                }
                if(contMasPrestamos > contMasPrestamosMAX){

                    contMasPrestamosMAX = contMasPrestamos;
                }
                contMasPrestamos = 0;
            }
        }
        resultadoMasPrestamos(arrayClientes,limiteClientes,arrayPrestamos,limitePrestamos,contMasPrestamosMAX,informe);
    }

    return retorno;
}
