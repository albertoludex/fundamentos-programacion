#ifndef lib_H
#define lib_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

//---Definicion de estructuras del enunciado-------//
typedef struct
{
    int f, c; // filas y columnas
    double **m;// doble puntero a la memoria de la matriz
} TMatriz;


typedef struct variable
{
char nomVar[16];
TMatriz *mat;
struct variable *sig, *ant;
} TVar;


typedef struct
{
int numVars;
TVar *primera;
} TVars;

//-------------------------Funciones de la practica----------------------------------//

// Creadas por mi 
int validate_matrix(char * cadena, int* filas ,int* elementosPorFila);
TMatriz* create_matrix(int filas, int columnas);
void show_matrix(TMatriz* matriz);
void llena_matrix_from_cad(TMatriz* matriz, char *cadena);
TMatriz* sum_matrix(TMatriz *matrizA, TMatriz *matrizB);
TMatriz* rest_matrix(TMatriz *matrizA, TMatriz *matrizB);
TMatriz* mult_matrix(TMatriz* matrizA, TMatriz* matrizB);
TMatriz* create_auxiliar(char **cadena,TVar *var_gran);
TMatriz* operations(char **cadena,TVar *var_gran, int num_arg);
TMatriz* liberate_matrix(TMatriz *matriz);
// para determinante   
TMatriz* copy_matrix(TMatriz *matriz);
void triang_matrix(TMatriz *matriz);
double det_triang(TMatriz *matriz);
double det_gauss(TMatriz *matriz);
// Producto n x M 
TMatriz* produc_matrix_por_num(char **cadena, TMatriz *matriz); //ampliacion
//over o no
TVars *load(char *nombre, TVars *workspace, int reescribir);
//ampliacion ej4
double produc_escalar(TMatriz *matriz1, TMatriz *matriz2);

// Copiadas internet
void hola();
char* MiStrTok(char *cad1, char *sep, int parentesis);
int validate_parentesis(char * cadena);
TVar *create_var(char *var_name, TMatriz *lista);
TVar *found_var(TVar *variable_gran, char *var_name);
TVar *insert_last_var(TVar *variable, TVar *asignar_var);
void print_tvar(TVar *LaGranLista);
int matrix_or_var(char *cad);
void great_view(TVar *variable_gran);  // de la ampliacion
int validate_name(char *nombre);
int count_characters(char **cadena, char *caracter);
TVars *crearWorkspace(TVars *workspace);
int count_vars(TVar *var_gran);
void save(char *nombre, TVars *workspace);
void Trim(char *cad);
int validate_dec(char *cad);
TVar *liberarVariables(TVar *variable_gran);


//modificacion examen
int compare_vars(const void *a, const void *b);

void inicio(); 
void cambiarColor(int color);
TVar *eliminarVariable(TVar *variable_gran, char *cad);
int validate_int(char *cad);
// Necesario Rango
void intercambiarFilas(TMatriz *matriz, int fila1, int fila2);
void hacerCeroDebajo(TMatriz *matriz, int filaPivote, int columnaPivote);
void forma_escalonada_reducida(TMatriz *matriz);
int matrix_rank(TMatriz *matriz);
TMatriz *matrix_transpuesta(TMatriz *matriz);
TMatriz *matrix_diagonal(TMatriz *matriz); 
// Necesario Inversa
TMatriz *matrix_identidad(int n);
TMatriz *matrix_inversa(TMatriz *matriz);
TMatriz *matrix_potencia(TMatriz *matriz, char **exponente);
TMatriz* ordenar_matrix_burbuja(TMatriz *matriz);
void found_position(TMatriz *matriz, char **num);
void obten_num_en_posicion(TMatriz *matriz, char **fila, char **columna);
// Necesario adjunta
TMatriz* matrizCofactores(TMatriz *matriz, int fila, int columna);
TMatriz* matrix_adjunta(TMatriz *matriz);
// Similares al product pero sumando y restando
TMatriz* sum_matrix_por_number(char **cadena, TMatriz *matriz); 
TMatriz* rest_matrix_por_number(char **cadena, TMatriz *matriz);

int comprobate_file(char *cadena);
void imprimirWorkspace(TVars *workspace);
int var_existe(TVars *workspace, const char *nombre);
void add_var_final(TVars *workspace, TVar *nuevaVariable);





#endif