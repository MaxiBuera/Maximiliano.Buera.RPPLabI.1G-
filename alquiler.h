#ifndef ALQUILER_H_INCLUDED
#define ALQUILER_H_INCLUDED

typedef struct{
    int idCliente;
    int equipo;
    int estado;
    int tiempoEstimado;
    int tiempoReal;
    int isEmpty;
    int id;
}eAlquiler;

#endif // ALQUILER_H_INCLUDED

int alquiler_inicializarArrayAlquileres(eAlquiler* arrayAlquileres, int limite);

int alquiler_buscarLugarLibre(eAlquiler* arrayAlquileres,int limite);

int verificarCliente(eCliente* arrayClientes, int limiteClientes, int idCliente);

int alquiler_altaForzada(eAlquiler* arrayAlquileres,int limite,int idCliente, int equipo, int estado,int tiempoEstimado,int tiempoReal);

int alquiler_nuevoAlquiler(eAlquiler* arrayAlquiler,int limite,eCliente* arrayClientes ,int limiteClientes, int indice);

int alquiler_imprimirAlquileres(eAlquiler* arrayAlquileres,int limite);

int alquiler_finAlquiler(eAlquiler* arrayAlquiler,int limite,eCliente* arrayClientes ,int limiteClientes);
