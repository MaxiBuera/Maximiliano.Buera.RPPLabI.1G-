#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "cliente.h"
#define OCUPADO 0
#define LIBRE 1

static int nextId();


/** \brief  Formatea la cadena pasada por parametro (primer letra mayuscula)
 *
 * \param   cadena a formatear
 * \return
 *
 */
void cliente_normalizarCadena(char cadena[]){

    int j,i;
    i = strlen(cadena);

    for(j=0;j<i;j++){

        if(j==0){

            cadena[j] = toupper(cadena[j]);
        }
        else{

            cadena[j] = tolower(cadena[j]);
        }
    }
}

/** \brief  Para indicar que todas las posiciones estan vacias,
 *          esta funcion coloca el flag (isEmpty) en True en
 *          todas las posiciones del array
 *
 * \param   array de Clientes
 * \param   limite del array de Clientes
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int cliente_inicializarArrayClientes(eCliente* arrayClientes, int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            arrayClientes[i].id = -1;
            strcpy(arrayClientes[i].nombre,"");
            strcpy(arrayClientes[i].apellido,"");
            arrayClientes[i].cuil = -1;
            arrayClientes[i].isEmpty = LIBRE;
        }
    }
    return retorno;
}

/** \brief  agrega una mascota  al array. Validando los tipos y colores
 *
 * \param   array de Mascotas
 * \param   limite del array de mascotas
 * \param   array de Tipos
 * \param   limite del array de tipos
 * \param   array de Colores
 * \param   limite del array de Colores
 * \param   indice de lugar libre en el array
 * \return  -1 si hay algun error, 0 si no
 *
 */
int cliente_agregarCliente(eCliente* arrayClientes,int limite, int indice){

    int retorno = -1;
    char nombreAux[20];
    char apellidoAux[20];
    int cuilAux;

    int id;


    if(limite > 0 && arrayClientes != NULL){

        retorno = -2;
        id = nextId();

        if(getStringLetras("\nIngrese nombre del cliente: ",nombreAux)){

            if(getStringLetras("\nIngrese apellido del cliente: ",apellidoAux)){

                if(!getValidInt("\nIngrese cuil (8 digitos): ","\ncuil Incorrecto\n",&cuilAux,10000000,99999999,2)){

                    cliente_normalizarCadena(nombreAux);
                    strcpy(arrayClientes[indice].nombre,nombreAux);
                    cliente_normalizarCadena(apellidoAux);
                    strcpy(arrayClientes[indice].apellido,apellidoAux);
                    arrayClientes[indice].cuil = cuilAux;
                    arrayClientes[indice].id = id;

                    arrayClientes[indice].isEmpty = OCUPADO;
                    arrayClientes[indice].id = id;
                    printf("\n\tCliente Agregado...");
                    retorno = 0;

                }
            }
        }
    }

    if(retorno != 0){

        printf("\nError. Dato invalido\n");
    }

    return retorno;
}

/** \brief  Busca un espacio libre en el array
 *
 * \param   array de Mascotas
 * \param   limite del array
 * \return  -1 o -2 si hay algun error, 0 si no
 *
 */
int cliente_buscarLugarLibre(eCliente* arrayClientes,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayClientes[i].isEmpty == LIBRE)
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
int cliente_altaForzada(eCliente* arrayClientes,int limite,char* nombre,char* apellido, int cuil)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayClientes != NULL)
    {
        i = cliente_buscarLugarLibre(arrayClientes,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(arrayClientes[i].nombre,nombre);
            strcpy(arrayClientes[i].apellido,apellido);
            arrayClientes[i].cuil = cuil;
            //------------------------------
            //------------------------------
            arrayClientes[i].id = nextId();
            arrayClientes[i].isEmpty = OCUPADO;
        }
        retorno = 0;
    }
    return retorno;
}

/**
 * \brief Busca un cliente por id dentro del array
 * \param array de clientes
 * \param limite de array de clientes
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int cliente_buscarClientePorId(eCliente* arrayClientes,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayClientes[i].isEmpty == OCUPADO && arrayClientes[i].id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Imprime por pantalla los clientes
 * \param array de clientes
 * \param limite de array de clientes
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int cliente_imprimirClientes(eCliente* arrayClientes,int limite)
{
    int retorno = -1;

    if(limite > 0 && arrayClientes != NULL)
    {
        int i;
        retorno = 0;
        printf("\n\t**** Clientes ****\n");
        printf("\n\tID Cliente\tNombre\t\tApellido\tcuil");
        printf("\n\t---------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {

            if(arrayClientes[i].isEmpty != LIBRE){

                printf("\n%12d%18s\t\t%s\t\t%d",arrayClientes[i].id,arrayClientes[i].nombre,arrayClientes[i].apellido,arrayClientes[i].cuil);
            }
        }
        printf("\n");
    }

    return retorno;
}

/** \brief  Muestra la lista de los Clientes ( Nombre,Apellido y id)
 *
 * \param   array de Clientes
 * \param   limite del array de Clientes
 * \return  -1 si hay un error, 0 si no
 *
 */
int cliente_mostrarClienteID(eCliente* arrayClientes,int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = 0;
        printf("\n\t**** Lista de Clientes ****\n");
        printf("\n\tNombre\t\tApellido\tID");
        printf("\n\t-------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayClientes[i].isEmpty)
            {

           		printf("\n\t%10s%12s%12d",arrayClientes[i].nombre,arrayClientes[i].apellido,arrayClientes[i].id);
        	}
        }
    }
    printf("\n\n");
    return retorno;
}

/** \brief  Menu al modificar un Cliente
 *
 * \param   array de clientes
 * \param   indice de mascota a modificar
 * \return  -
 *
 */
void cliente_menuModificacion(eCliente* arrayClientes, int indice){

    int opc;
    char nombreAux[20];
    char apellidoAux[20];
    int cuilAux;


    printf("\n\tCliente a Modificar: %s %s ",arrayClientes[indice].nombre,arrayClientes[indice].apellido);

    do{

        getValidInt("\n\n\t1.Modificar Nombre\n\t2.Modificar Apellido\n\t3.Modificar Cuil\n\t4.Listo\n","\nNo valida\n",&opc,1,4,1);
        switch(opc)
        {
            case 1:
                if(getStringLetras("\nIngrese nombre del cliente: ",nombreAux)){

                    cliente_normalizarCadena(nombreAux);
                    strcpy(arrayClientes[indice].nombre,nombreAux);
                    printf("\nNombre de Cliente Modificado...");
                }
                break;
            case 2:
                if(getStringLetras("\nIngrese apellido del cliente: ",apellidoAux)){

                    cliente_normalizarCadena(apellidoAux);
                    strcpy(arrayClientes[indice].apellido,apellidoAux);
                    printf("\nApellido de Cliente Modificado...");
                }
                break;
             case 3:
                if(!getValidInt("\nIngrese cuil: ","\ncuil Incorrecto\n",&cuilAux,10000000,99999999,2)){

                    arrayClientes[indice].cuil = cuilAux;
                    printf("\nCuil del Cliente Modificado...");
                }
                break;
        }
    }while(opc != 3);

}

int cliente_modificarCliente(eCliente* arrayClientes, int limite, int indice){

    int i;
    int retorno = -1;


    i = cliente_buscarClientePorId(arrayClientes,limite,indice);
    if(i >= 0)
    {
        cliente_menuModificacion(arrayClientes,i);
        arrayClientes[i].isEmpty = OCUPADO;
        retorno = 0;
    }
    else{
        printf("\nID No encotrado");
    }
    return retorno;
}

/** \brief  Baja logica de un cliente
 *
 * \param   array de clientes
 * \param   limite del array de clientes
 * \param   indice del cliente
 * \return  -1 si hay algun error, 0 si no
 *
 */
int cliente_eliminarCliente(eCliente* arrayClientes, int limite,int indice){

    int retorno = -1;
    int i;
    char confirmacion;
    i = cliente_buscarClientePorId(arrayClientes,limite,indice);
    if(i >= 0)
    {
        printf("\nCliente a eliminar: %s %s",arrayClientes[i].nombre,arrayClientes[i].apellido);
        confirmacion = getChar("\n¿Desea eliminar el cliente? [s/n]: ");
        if(confirmacion == 's' || confirmacion == 'S'){
            arrayClientes[i].isEmpty = LIBRE;
            printf("\n\n\tCliente Eliminado...");
            retorno = 0;
        }
        else if(confirmacion == 'n' || confirmacion == 'N'){

            printf("\n\tCliente No Eliminado...");
            return retorno;
        }
        else{
            printf("\nError. Vuelva a Intentar");
        }
    }
    else{

        printf("\nID no encontrado");
    }
    return retorno;
}

static int nextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}
