#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    int id;
    int cuil;
    char nombre[20];
    char apellido[20];
    int isEmpty;
}eCliente;

#endif // CLIENTE_H_INCLUDED


void cliente_normalizarCadena(char cadena[]);

int cliente_inicializarArrayClientes(eCliente* arrayClientes, int limite);

int cliente_agregarCliente(eCliente* arrayClientes,int limite, int indice);

int cliente_buscarLugarLibre(eCliente* arrayClientes,int limite);

int cliente_altaForzada(eCliente* arrayClientes,int limite,char* nombre,char* apellido, int cuil);

int cliente_buscarClientePorId(eCliente* arrayClientes,int limite, int id);

int cliente_imprimirClientes(eCliente* arrayClientes,int limite);

int cliente_mostrarClienteID(eCliente* arrayClientes,int limite);

void cliente_menuModificacion(eCliente* arrayClientes, int indice);

int cliente_modificarCliente(eCliente* arrayClientes, int limite, int indice);

int cliente_eliminarCliente(eCliente* arrayClientes, int limite,int indice);
