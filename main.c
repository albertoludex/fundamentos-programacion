#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "lib.h"

//gcc lib.c main.c -o main.exe
//para compilarlo hacemos gcc lib.c main.c -o main.exe

int main(int argc, char *argv[]) {


    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char comando[1000]; // Tu cadena de números con paréntesis
    double matriz[10][10]; // Suponemos un tamaño máximo para la matriz
    int fila = 0; // Variable para rastrear la fila actual en la matriz
    int columna = 0; // Variable para rastrear la columna actual en la matriz
    char separadores[8] = " \t\n";
    char *comtok[1000];

    int num_arg;

    TVars *workspace = NULL;
    TVar *variable_gran = NULL;

    hola();
    inicio();

    workspace = crearWorkspace(workspace);
    

    while (1) {
        //printf("Ingrese un comando: ");
        //imprimirWorkspace(workspace);
    printf(":[%d]> ", count_vars(variable_gran));
        gets(comando);

        //validar que lo que nos han escrito sea correcto
        if(validate_parentesis(comando) == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR\n");
            SetConsoleTextAttribute(hConsole, 7);
            continue;
        }

        //printf("comando: %s\n", comando);
        //tokenizar (trocear command) segun los separadores
        //Esta parte mete en comtok las palabras sueltas
        num_arg = 0;
        comtok[num_arg] = MiStrTok(comando, separadores, 1);

        //printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);
        //printf("comando: %s\n", comando);

        num_arg++;
        while((comtok[num_arg] = MiStrTok(NULL, separadores, 1)) != NULL){
            //printf("comtok[%d]: %s\n", num_arg, comtok[num_arg]);
            num_arg++;
        }
        if(comtok[0] == NULL){
            continue;
        }

        if (strcmp(comtok[0], "quit") == 0 && num_arg == 1) {

            //Realiza tareas de limpieza antes de salir
            //Liberamos la memoria de laGranVariable
            //las variables globales que estamos usando aqui son el workspace (que contiene a la granvariable) y laGranVariable, asi que hay que borrar esas dos cosas
            variable_gran = liberarVariables(variable_gran);

            if(workspace->numVars == 0){
                workspace->primera = liberarVariables(workspace->primera);
            }
            
            //Liberamos la memoria del workspace
            free(workspace);
            workspace = NULL;
           
            SetConsoleTextAttribute(hConsole, 2);
            printf("Exit ok\n");
            SetConsoleTextAttribute(hConsole, 7);
            return 0;

        }else if (strcmp(comtok[0], "borrar") == 0 && num_arg == 1) {

            if(count_vars(variable_gran) <= 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: No hay nada que borrar\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            //Liberamos la memoria de laGranVariable
            //las variables globales que estamos usando aqui son el workspace (que contiene a la granvariable) y laGranVariable, asi que hay que borrar esas dos cosas
            variable_gran = liberarVariables(variable_gran);

            if(workspace->numVars == 0){
                workspace->primera = liberarVariables(workspace->primera);
            }
            
            //Liberamos la memoria del workspace
            //free(workspace);
            //workspace = NULL;
           
            SetConsoleTextAttribute(hConsole, 2);
            printf("Borrado completado\n");
            SetConsoleTextAttribute(hConsole, 7);

        }else if(strcmp(comtok[0], "view") == 0){

            if(num_arg != 1){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            great_view(variable_gran);

        

        }else if (strcmp(comtok[0], "det") == 0) {

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[1],variable_gran);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: La variable no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            if (matrizA->f != matrizA->c) {
                // Las matrices no son cuadradas
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Las matrices no son cuadradas.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            // Calcular el determinante
            double det = det_gauss(matrizA);

            // Imprimir el resultado
            SetConsoleTextAttribute(hConsole, 2);
            printf("Determinante: %.2lf\n", det);
            SetConsoleTextAttribute(hConsole, 7);

            
        }else if (strcmp(comtok[0], "rango") == 0) {

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[1],variable_gran);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: La variable no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            int rango = matrix_rank(matrizA);

            // Imprimir el resultado
            SetConsoleTextAttribute(hConsole, 2);
            printf("El rango de la matriz es: %d\n", rango);
            SetConsoleTextAttribute(hConsole, 7);

            
        }else if (strcmp(comtok[0], "save") == 0) {

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            if(count_vars(variable_gran) <= 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: No hay nada que guardar\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            workspace->numVars = count_vars(variable_gran);
            //printf("Numero de variables en el workspace: %d\n", workspace->numVars);
            workspace->primera = variable_gran;
            //imprimirTVAR(workspace->primera);

            save(comtok[1], workspace);

            //printf("Guardao\n");

        }else if (strcmp(comtok[0], "load") == 0) {

            // if(validate_name(comtok[1]) == 0){
            //     SetConsoleTextAttribute(hConsole, 4);
            //     printf("ERROR\n");
            //     SetConsoleTextAttribute(hConsole, 7);
            //     continue;
            // }

            //workspace->primera = variable_gran;
            TVars *nuevoWorkspace;
            // AMPLIACION EJERCICIO 3 DICIEMBRE
            if (num_arg == 1) {
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Falta el nombre del archivo.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(strcmp(comtok[1], "over") == 0){
                
                if(num_arg != 3){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Argumentos\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    
                    continue;
                }


                nuevoWorkspace = load(comtok[2],workspace,0);
                
                if(nuevoWorkspace == NULL){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Al cargar el fichero\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    
                    continue;
                }
                else
                {
                    workspace = load(comtok[2],workspace,0);
                }

                variable_gran = workspace->primera;
            
            }else{
            ///////////////////////////////////
                
                //printf("LOAD NORMAL\n"); 

                if(num_arg != 2){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Argumentos\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    
                    continue;
                }

                nuevoWorkspace = load(comtok[1],workspace,1);
                
                if(nuevoWorkspace == NULL){
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("ERROR: Al cargar el fichero\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    
                    continue;
                }
                else
                {
                    workspace = load(comtok[1],workspace,1);
                }

                variable_gran = workspace->primera;
            }
        
        }else if (strcmp(comtok[0], "eliminar") == 0){

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVar *variableAsignar = found_var(variable_gran,comtok[1]);
            if(variableAsignar == NULL){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            variable_gran = eliminarVariable(variable_gran, variableAsignar->nomVar);

        }else if(num_arg>1 && strcmp(comtok[1], "=") == 0){ // a = (1 2 3)    a = b     a = (1) + (2)

            if(matrix_or_var(comtok[0]) != 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
           
            if(validate_name(comtok[0]) == 0){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            TVar *variableDestino = found_var(variable_gran, comtok[0]);

            int cortafuegos = 0;

            if(variableDestino == NULL){
                variableDestino = create_var(comtok[0], NULL);
                // Agrega la nueva variable al final del workspace
                //add_var_final(workspace, variableDestino);
                cortafuegos = 2;
            }    

            int filas, columnas, filas2, columnas2;

            TMatriz *matrizValor = operations(&comtok[2],variable_gran, num_arg-2);

            if(matrizValor == NULL){
                continue;
            }

            variableDestino->mat = matrizValor;

            if(cortafuegos == 2){
                variable_gran = insert_last_var(variable_gran, variableDestino);
            }

        }else if(num_arg>=2 && strcmp(comtok[1], "$") == 0){

            //printf("Escalar\n");

            if(num_arg != 3){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[0],variable_gran);
            TMatriz *matrizB = create_auxiliar(&comtok[2],variable_gran);

            if (matrizA == NULL || matrizB == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: Una o ambas variables no existen.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            // Verificar que ambas matrices sean de 1xN
            if (matrizA->f != 1 || matrizB->f != 1 || matrizA->c != matrizB->c) {
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: Las matrices deben ser de 1xN y tener el mismo número de columnas.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue; // Manejo de error, puedes ajustarlo según tus necesidades
            }

            // Calcular el determinante
            double escalar = produc_escalar(matrizA, matrizB);

            // Imprimir el resultado
            SetConsoleTextAttribute(hConsole, 2);
            printf("Producto escalar: %.2lf\n", escalar);
            SetConsoleTextAttribute(hConsole, 7);

        }else if(num_arg>=2 && strcmp(comtok[1], "encontrar") == 0){

            //printf("Escalar\n");

            if(num_arg != 3){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[0],variable_gran);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error:  La matriz no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(validate_dec(comtok[2]) == 0){

                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Numero no valido.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            found_position(matrizA,&comtok[2]);

        }else if(num_arg>=2 && strcmp(comtok[1], "obtener") == 0){

            //printf("Escalar\n");

            if(num_arg != 4){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[0],variable_gran);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: La matriz no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            if(validate_int(comtok[2]) == 0 || validate_int(comtok[3]) == 0){

                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Algun numero no es valido, tienen que ser enteros.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }

            obten_num_en_posicion(matrizA,&comtok[2],&comtok[3]);

        }
        else 
        {  
            //TVar *variableDestino = found_var(variable_gran, comtok[0]);
            
            TMatriz *verMatriz =  operations(comtok,variable_gran, num_arg);    
            if(verMatriz != NULL){
                SetConsoleTextAttribute(hConsole, 2);
                show_matrix(verMatriz);
                SetConsoleTextAttribute(hConsole, 7);
                //liberate_matrix(verMatriz);
            }
            
        }

        //implementar mi funcion matrix_transpuesta
        if (strcmp(comtok[0], "transp") == 0) {

            if(num_arg != 2){
                SetConsoleTextAttribute(hConsole, 4);
                printf("ERROR: Argumentos\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            }
            
            TMatriz *matrizA = create_auxiliar(&comtok[1],variable_gran);

            if (matrizA == NULL) 
            {
                // Manejo de errores si las variables no se encuentran
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: La variable no existe.\n");
                SetConsoleTextAttribute(hConsole, 7);
                continue;
            } 

            TMatriz *matrizTranspuesta = matrix_transpuesta(matrizA);

            // Imprimir el resultado
            SetConsoleTextAttribute(hConsole, 2);

            SetConsoleTextAttribute(hConsole, 7);

            liberate_matrix(matrizTranspuesta);
            
        }

        
        workspace->numVars = count_vars(variable_gran);
        //printf("Numero de variables en el workspace: %d\n", workspace->numVars);
        //se actualiza el workspace con la nueva variable agregada
        workspace->primera = variable_gran;
        //imprimirTVAR(workspace->primera);
    }
    
    return 0;
}

