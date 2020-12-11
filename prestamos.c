#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "cliente.h"
#include "prestamos.h"
#define OCUPADO 0
#define LIBRE 1
#define PRESTAMO_MAX 1000000
#define CUOTAS_MAX 48
#define ACTIVO 0
#define SALDADO 1
#define EQUIPOS 3
#define AMOLADORA 1
#define MEZCLADORA 2
#define TALADRO 3
#define ALQUILADO 0
#define FINALIZADO 1

static int nextId();

/** \brief  Para indicar que todas las posiciones estan vacias,
 *          esta funcion coloca el flag (isEmpty) en True en
 *          todas las posiciones del array
 *
 * \param   array de Prestamos
 * \param   limite del array de Prestamos
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int prestamo_inicializarArrayPrestamos(ePrestamo* arrayPrestamos, int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayPrestamos != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            arrayPrestamos[i].id = -1;
            arrayPrestamos[i].idCliente = -1;
            arrayPrestamos[i].importe = -1;
            arrayPrestamos[i].cantidadCuotas = -1;
            arrayPrestamos[i].estado = -1;
            arrayPrestamos[i].isEmpty = LIBRE;
        }
    }
    return retorno;
}

/** \brief  Busca un espacio libre en el array
 *
 * \param   array de Prestamos
 * \param   limite del array
 * \return  -1 o -2 si hay algun error, 0 si no
 *
 */
int prestamo_buscarLugarLibre(ePrestamo* arrayPrestamos,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPrestamos != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayPrestamos[i].isEmpty == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief  Alta de un prestamo, usando datos de los parametros
 *
 * \param   array de clientes
 * \param   limite del array de clientes
 * \param   nombre
 * \param   idColor
 * \param   idTipo
 * \param   edad
 * \return  -1 si hay algun error, 0 si no
 *
 */
int prestamo_altaForzada(ePrestamo* arrayPrestamos,int limite,int idCliente, float importe, int cantidadCuotas, int estado)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayPrestamos != NULL)
    {
        i = prestamo_buscarLugarLibre(arrayPrestamos,limite);
        if(i >= 0)
        {
            retorno = 0;
            arrayPrestamos[i].idCliente = idCliente;
            arrayPrestamos[i].importe = importe;
            arrayPrestamos[i].cantidadCuotas = cantidadCuotas;
            arrayPrestamos[i].estado = estado;
            //------------------------------
            //------------------------------
            arrayPrestamos[i].id = nextId();
            arrayPrestamos[i].isEmpty = OCUPADO;
        }
        retorno = 0;
    }
    return retorno;
}

/** \brief Verifica si el id pasado por parametro se encuentra en el array
 *
 * \param   array de clientes
 * \param   limite del array de clientes
 * \param   id a buscar
 * \return  -1 si hay algun error, 0 si no
 *
 */
int prestamo_verificarCliente(eCliente* arrayClientes, int limiteClientes, int idCliente){

    int i;
    int retorno = -1;

    for(i=0;i<limiteClientes;i++){

        if(idCliente == arrayClientes[i].id){

            retorno = 0;
            return retorno;
        }
    }

    return retorno;
}



int prestamo_nuevoPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes, int indice){

    int retorno = -1;
    int idClienteAux;
    float importeAux;
    int cantidadCuotasAux;
    int id;

    if(limite > 0 && arrayPrestamos != NULL){

        retorno = -2;
        id = nextId();

        cliente_mostrarClienteID(arrayClientes,limiteClientes);
        if(!getValidInt("\nIngrese ID de Cliente: ","\nError\n",&idClienteAux,0,limiteClientes,1) && (!prestamo_verificarCliente(arrayClientes,limiteClientes,idClienteAux))){

            //mostrarEquipos();
            if(!getValidFloat("\nIngrese importe del Prestamo: ","\nError\n",&importeAux,1,PRESTAMO_MAX,1)){

                if(!getValidInt("\nIngrese cantidad de cuotas: ","\nError\n",&cantidadCuotasAux,1,CUOTAS_MAX,1)){

                    arrayPrestamos[indice].idCliente = idClienteAux;
                    arrayPrestamos[indice].isEmpty = OCUPADO;
                    arrayPrestamos[indice].importe = importeAux;
                    arrayPrestamos[indice].cantidadCuotas = cantidadCuotasAux;
                    arrayPrestamos[indice].id = id;
                    arrayPrestamos[indice].estado = ACTIVO;
                    printf("\nPrestamo Agregado ...\n\n");
                    retorno = 0;
                }
            }
        }
    }

    return retorno;
}

int prestamo_printCliente(eCliente* arrayClientes,int limite,int indice){

    int retorno = -1;
    int i;

    if(arrayClientes != NULL && limite > 0) {

        for(i=0;i<limite;i++){

            if(arrayClientes[i].id == indice){

                printf("\t\t%s %s",arrayClientes[i].nombre,arrayClientes[i].apellido);
                retorno = 0;
            }
        }
    }

    return retorno;
}

/**
 * \brief Imprime por pantalla los Prestamos
 * \param array de Prestamos
 * \param limite de array de Prestamos
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int prestamo_imprimirPrestamos(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes, int limiteClientes)
{
    int retorno = -1;

    if(limite > 0 && arrayPrestamos != NULL)
    {
        int i;
        retorno = 0;
        printf("\n\t**** Prestamos ****\n");
        printf("\n\tID Cliente\tNombre Cliente\t\tImporte\t\tCantidad Cuotas\tEstado");
        printf("\n\t-----------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {

            if(arrayPrestamos[i].isEmpty != LIBRE){

                printf("\n\t%d",arrayPrestamos[i].idCliente);

                prestamo_printCliente(arrayClientes,limiteClientes,arrayPrestamos[i].idCliente);

                printf("\t\t%2.f",arrayPrestamos[i].importe);

                printf("\t\t%d",arrayPrestamos[i].cantidadCuotas);

                if(arrayPrestamos[i].estado == ACTIVO) {
                    printf("\t\tActivo");
                } else {
                    printf("\t\tSaldado");
                }
            }
        }
        printf("\n");
    }

    return retorno;
}

int prestamo_imprimirDatosCliente(ePrestamo* arrayPrestamos,int limite, int indice)
{
    int retorno = -1;

    if(limite > 0 && arrayPrestamos != NULL)
    {
        int i;
        retorno = 0;
        printf("\n\t**** Datos del cliente ****\n");
        printf("\n\tID Cliente\tImporte\t\tCantidad Cuotas");
        printf("\n\t-----------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {

            if(arrayPrestamos[i].idCliente == indice){

                printf("\n\t%d",arrayPrestamos[i].idCliente);

                printf("\t\t%2.f",arrayPrestamos[i].importe);

                printf("\t\t%d",arrayPrestamos[i].cantidadCuotas);
            }
        }
        printf("\n");
    }

    return retorno;
}

int prestamo_saldarPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes){


    int retorno = -1;
    int idClienteAux;

    char confirmacion;
    int i;
    int flag=0;

    if(limite > 0 && arrayPrestamos != NULL){

        retorno = 0;

        cliente_mostrarClienteID(arrayClientes,limiteClientes);
        if(!getValidInt("\nIngrese ID de Cliente: ","\nError\n",&idClienteAux,0,limiteClientes,1) && (!prestamo_verificarCliente(arrayClientes,limiteClientes,idClienteAux))){

            prestamo_imprimirDatosCliente(arrayPrestamos,limite,idClienteAux);

            for(i=0;i<limite;i++){

                if(arrayPrestamos[i].idCliente == idClienteAux){

                    confirmacion = getChar("\n¿Desea cambiar su estado a SALDADO ? [s/n]: ");
                    if(confirmacion == 's' || confirmacion == 'S'){
                        arrayPrestamos[i].estado = SALDADO;
                        printf("\n\n\tEstado modificado a  SALDADO...");
                        retorno = 0;
                        flag=1;
                    }
                    else if(confirmacion == 'n' || confirmacion == 'N'){

                         printf("\n\n\tEstado NO modificado...");
                         flag=1;
                    }
                    else{
                        printf("\nError. Vuelva a Intentar");
                    }
                }
            }
            if(flag == 0){

                 printf("\nCliente no disponible\n\n");
            }
        }
    }

    return retorno;
}

int prestamo_reanudarPrestamo(ePrestamo* arrayPrestamos,int limite,eCliente* arrayClientes ,int limiteClientes){


    int retorno = -1;
    int idClienteAux;
    char confirmacion;
    int i;
    int flag=0;

    if(limite > 0 && arrayPrestamos != NULL){

        retorno = 0;

        cliente_mostrarClienteID(arrayClientes,limiteClientes);
        if(!getValidInt("\nIngrese ID de Cliente: ","\nError\n",&idClienteAux,0,limiteClientes,1) && (!prestamo_verificarCliente(arrayClientes,limiteClientes,idClienteAux))){

            prestamo_imprimirDatosCliente(arrayPrestamos,limite,idClienteAux);

            for(i=0;i<limite;i++){

                if(arrayPrestamos[i].idCliente == idClienteAux){

                    confirmacion = getChar("\n¿Desea cambiar su estado a ACTIVO ? [s/n]: ");
                    if(confirmacion == 's' || confirmacion == 'S'){
                        arrayPrestamos[i].estado = ACTIVO;
                        printf("\n\n\tEstado modificado a  ACTIVO...");
                        flag=1;
                    }
                    else if(confirmacion == 'n' || confirmacion == 'N'){

                         printf("\n\n\tEstado NO modificado...");
                         flag=1;
                    }
                    else{
                        printf("\nError. Vuelva a Intentar");
                    }
                }
            }
            if(flag == 0){

                 printf("\nCliente no disponible\n\n");
            }
        }
    }

    return retorno;
}

static int nextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}

