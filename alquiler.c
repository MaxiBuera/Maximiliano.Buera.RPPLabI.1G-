#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "cliente.h"
#include "alquiler.h"
#define OCUPADO 0
#define LIBRE 1
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
 * \param   array de Alquileres
 * \param   limite del array de Alquileres
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int alquiler_inicializarArrayAlquileres(eAlquiler* arrayAlquileres, int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayAlquileres != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            arrayAlquileres[i].idCliente = -1;
            arrayAlquileres[i].equipo = -1;
            arrayAlquileres[i].estado = -1;
            arrayAlquileres[i].tiempoEstimado = -1;
            arrayAlquileres[i].tiempoReal = -1;
            arrayAlquileres[i].isEmpty = LIBRE;
        }
    }
    return retorno;
}

/** \brief  Busca un espacio libre en el array
 *
 * \param   array de Alquileres
 * \param   limite del array
 * \return  -1 o -2 si hay algun error, 0 si no
 *
 */
int alquiler_buscarLugarLibre(eAlquiler* arrayAlquileres,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayAlquileres != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayAlquileres[i].isEmpty == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief  Alta de un cliente, usando datos de los parametros
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
int alquiler_altaForzada(eAlquiler* arrayAlquileres,int limite,int idCliente, int equipo, int estado,int tiempoEstimado,int tiempoReal)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayAlquileres != NULL)
    {
        i = alquiler_buscarLugarLibre(arrayAlquileres,limite);
        if(i >= 0)
        {
            retorno = 0;
            arrayAlquileres[i].idCliente = idCliente;
            arrayAlquileres[i].equipo = equipo;
            arrayAlquileres[i].estado = estado;
            arrayAlquileres[i].tiempoEstimado = tiempoEstimado;
            arrayAlquileres[i].tiempoReal = tiempoReal;

            //------------------------------
            //------------------------------
            arrayAlquileres[i].id = nextId();
            arrayAlquileres[i].isEmpty = OCUPADO;
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
int verificarCliente(eCliente* arrayClientes, int limiteClientes, int idCliente){

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

void mostrarEquipos(){

    printf("\n\t**** Lista de Equipos ****\n");
    printf("\t-------------------------------------");
    printf("\n\tAmoladora\t1\n\tMezcladora\t2\n\tTaladro\t\t3\n");

}

int alquiler_nuevoAlquiler(eAlquiler* arrayAlquiler,int limite,eCliente* arrayClientes ,int limiteClientes, int indice){

    int retorno = -1;
    int idClienteAux;
    int equipoAux;
    int tiempoEstimadoAux;
    int id;

    if(limite > 0 && arrayAlquiler != NULL){

        retorno = -2;
        id = nextId();

        cliente_mostrarClienteID(arrayClientes,limiteClientes);
        if(!getValidInt("\nIngrese ID de Cliente: ","\nError\n",&idClienteAux,0,limiteClientes,1) && (!verificarCliente(arrayClientes,limiteClientes,idClienteAux))){

            mostrarEquipos();
            if(!getValidInt("\nIngrese equipo a alquilar: ","\nError\n",&equipoAux,1,EQUIPOS,1)){

                if(!getValidInt("\nIngrese tiempo estimado (en horas): ","\nError\n",&tiempoEstimadoAux,1,672,1)){ // 2 semanas

                    arrayAlquiler[indice].idCliente = idClienteAux;
                    arrayAlquiler[indice].isEmpty = OCUPADO;
                    arrayAlquiler[indice].equipo = equipoAux;
                    arrayAlquiler[indice].estado = ALQUILADO;
                    arrayAlquiler[indice].tiempoEstimado = tiempoEstimadoAux;
                    arrayAlquiler[indice].id = id;
                    printf("\nAlquiler Agregado ...\n\n");
                    retorno = 0;
                }
            }
        }
    }

    return retorno;
}

/**
 * \brief Imprime por pantalla los alquileres
 * \param array de alquileres
 * \param limite de array de alquileres
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int alquiler_imprimirAlquileres(eAlquiler* arrayAlquileres,int limite)
{
    int retorno = -1;

    if(limite > 0 && arrayAlquileres != NULL)
    {
        int i;
        retorno = 0;
        printf("\n\t**** Alquileres ****\n");
        printf("\n\tID Cliente\tEquipo Alquilado\tEstado\t\tTiempo Estimado\t\tTiempo Real");
        printf("\n\t-----------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {

            if(arrayAlquileres[i].isEmpty != LIBRE){

                printf("\n\t%d",arrayAlquileres[i].idCliente);

                if(arrayAlquileres[i].equipo == AMOLADORA){
                   printf("\t\tAmoladora");
                }
                else if(arrayAlquileres[i].equipo == MEZCLADORA){
                    printf("\t\tMezcladora");
                }
                else{
                    printf("\t\tTaladro");
                }

                if(arrayAlquileres[i].estado == ALQUILADO){
                    printf("\t\tAlquilado");
                }
                else{
                    printf("\t\tFinalizado");
                }

                printf("\t\t%d hs",arrayAlquileres[i].tiempoEstimado);

                if(arrayAlquileres[i].tiempoReal == -1){
                    printf("\t\tNo definido");
                }
                else{
                     printf("\t\t%d hs",arrayAlquileres[i].tiempoReal);
                }

            }
        }
        printf("\n");
    }

    return retorno;
}

int alquiler_finAlquiler(eAlquiler* arrayAlquileres,int limite,eCliente* arrayClientes ,int limiteClientes){


    int retorno = -1;
    int idClienteAux;
    int tiempoRealAux;
    int i;
    int flag=0;

    if(limite > 0 && arrayAlquileres != NULL){

        retorno = -2;

        cliente_mostrarClienteID(arrayClientes,limiteClientes);
        if(!getValidInt("\nIngrese ID de Cliente: ","\nError\n",&idClienteAux,0,limiteClientes,1) && (!verificarCliente(arrayClientes,limiteClientes,idClienteAux))){

            for(i=0;i<limite;i++){

                if(arrayAlquileres[i].idCliente == idClienteAux){

                    if(!getValidInt("\nIngrese tiempo real del alquiler (en horas): ","\nError\n",&tiempoRealAux,1,672,1)){ // 2 semanas
                        arrayAlquileres[i].tiempoReal = tiempoRealAux;
                        arrayAlquileres[i].estado = FINALIZADO;

                        printf("\nAlquiler Finalizado ...\n\n");
                        flag=1;
                        retorno = 0;
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

