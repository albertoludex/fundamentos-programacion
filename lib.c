#include "lib.h"
#include <ctype.h>

// Saludo inicial
void hola(){ 

    printf("EJERCICIO 1: HECHO \n");
    printf("EJERCICIO 2: HECHO \n");
    printf("EJERCICIO 3: HECHO \n");
    printf("EJERCICIO 4:SIN HACER \n");


}



// Función para cambiar el color del texto en la consola
void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Presentación de comandos disponibles
/*void inicio() {  
    cambiarColor(11);  // Amarillo brillante
    cambiarColor(15);  // Blanco
    printf("Comandos Disponibles:\n");
    cambiarColor(14);  // Amarillo
    printf("  - save nombre_fichero: Guarda variables desde un fichero.\n");
    printf("  - load nombre_fichero: Carga variables desde un fichero.\n");
    printf("  - product n M1: Multiplica la matriz M1 por el número n.\n");
    printf("  - product M1 n: Multiplica la matriz M1 por el número n.\n");
    printf("  - view: Muestra todas las variables.\n");
    printf("  - det M1: Calcula el determinante de la matriz M1.\n");
    printf("  - quit: Cierra el Sistema Mini-Mat.\n");
    cambiarColor(15);  // Blanco
    printf("=============================================================\n");
    printf("Uso de comandos:\n");
    printf("  - Escribir matriz: ( 1 2 3 | 4 5 6 | 7 8 9 )\n");
    printf("  - Cargar un fichero: load nombre_fichero\n");
    printf("  - Multiplicar matriz por número: product n M1\n");
    printf("  - Visualizar las variables: view\n");
    printf("  - Sumar matrices: M1 + M2\n");
    printf("  - Restar matrices: M1 - M2\n");
    printf("  - Multiplicar matrices: M1 * M2\n");
    printf("  - Asignar matriz a variable: var1 = M1\n");
    printf("  - Calcular determinante de una matriz: det M1\n");
    printf("  - Salir del sistema: quit\n");
    cambiarColor(11);  // Amarillo brillante
    printf("=============================================================\n\n");
    cambiarColor(15);  // Blanco
    
}*/
void inicio(){
    printf(" ejemplo escribir matriz: ( 1 2 3 | 4 5 6 | 7 8 9 )\n");
}
// Tokenizador
char* MiStrTok(char *cad1, char *sep, int parentesis){

    static char *pt1 = NULL;
    static char *pt2 = NULL;
    static char *ptFinal;

    if(cad1 != NULL){
        pt1 = cad1;
        ptFinal = pt1+strlen(cad1);
    }
    else{
        pt1 = pt2+1;
    }
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    if(parentesis == 1){ // corchetes activados
        
        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL && pt1[0] != '('){
            pt1++;
        }

        if(pt1[0] == '('){
            pt1++;
            pt2 = pt1;
            while(pt2[0] != '\0' && pt2[0] != ')'){
                pt2++;
            }

            if(pt2[0] == '\0'){
                pt1 = pt2 = ptFinal = NULL;
                return NULL;
            }
            else{
                pt2[0] = '\0';
                return pt1; 
            }
        }

    }
    else{

        while(pt1[0]!='\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL){
            pt1++;
        }

    }
    
    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }
    pt2 = pt1+1;

    while(pt2[0] != '\0' && strchr(sep, pt2[0]) == NULL){
        pt2++;
    }

    pt2[0] = '\0';
    return pt1;

}

// Valida que los corchetes esten bn escritos. BN 1, MAL 0
int validate_parentesis(char * cadena){

    int i=0;
    int contador=0;
    int primeravez = 0;
    int corchetesApertura=0;
    int corchetesCierre=0;
    int orden = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '(' || cadena[i] == ')'){
            contador++;
        }
        i++;
    }

    if(contador == 0){
        return 1;
    }

    i = 0;
    contador = 0;

    while(cadena[i] != '\0'){
        if(cadena[i] == '(' && contador == 0){  
            contador++;
            primeravez=1;
        }
        else if(cadena[i] == ')' && contador == 1){
            contador--;
        }

        if(cadena[i] == '('){
            corchetesApertura++;
            if(orden == 1){ // si entra dentro MAL
                return 0;
            }
            orden = 1;
        }
        else if(cadena[i] == ')'){
            corchetesCierre++;
            if(orden == 0){ // si entra dentro MAL
                return 0;
            }
            orden = 0;
        }

        i++;
    }

    if(contador == 0 && primeravez == 1 && corchetesApertura == corchetesCierre){ // Si se mete aqui bn
        return 1;
    }
    else{ // si se mete aqui mal
        return 0;
    }

}

// Valida que la matriz tenga los elemtos correctos / 0 MAL 1 BIEN
int validate_matrix(char * cadena, int* filas ,int* elementosPorFila)
{
    // Detecta si la entrada parece ser una matriz entre paréntesis
    *filas = 1; // Contador de filas
    int elementosFila = 0; // Contador de elementos en la fila
    *elementosPorFila = -1; // Almacena el número de elementos en la primera fila
    char *caracter = cadena;

    // Variable para indicar si estamos dentro de un número
        
    int dentroNumero = 0;

    // Recorre la cadena y cuenta los elementos en cada fila
    while (*caracter) {
        if (*caracter == ' ' || *caracter == '(' || *caracter == ')') {
            // Si estamos dentro de un número, incrementa elementosFila
            if (dentroNumero) {
            elementosFila++;
            dentroNumero = 0;
            }
        } else if (*caracter == '|') {
            // Si estamos dentro de un número, incrementa elementosFila antes de cambiar de fila
            if (dentroNumero) {
                elementosFila++;
                dentroNumero = 0;
            }
                    
        if (*elementosPorFila == -1) {
           *elementosPorFila = elementosFila; // Establece el número de elementos en la primera fila
        } else if (elementosFila != *elementosPorFila) {

            return 0;

        }

        elementosFila = 0; // Reinicia el contador de elementos
        (*filas)++;

        } else {
            // Estamos dentro de un número
            dentroNumero = 1;

            // Verifica que el caracter sea un dígito
            
            if (!isdigit(*caracter) && *caracter != '+' && *caracter != '-' && *caracter != '.') {
                //printf("Error: La matriz contiene caracteres no numéricos en la fila %d.\n", *filas);
                //printf("caracter mal: %c\n", *caracter);
                return 0;
            }
            
            
        }
        caracter++;
    }

    // Contabiliza el último elemento en la última fila
    if (dentroNumero) {
        elementosFila++;
    }

    if (*filas == 1) {
        // Si hay solo una fila, el número de elementos en esa fila es igual al total de elementos
        *elementosPorFila = elementosFila;
    }

    if (*elementosPorFila != -1 && elementosFila != *elementosPorFila) {
        return 0;
        
    } else {
       
    }

    //printf("Número de filas de la matriz: %d\n", *filas);
    //printf("Número de elementos en cada fila: %d\n", *elementosPorFila);

    return 1;
}

// Función para crear una matriz con filas y columnas dadas e inicializarla a ceros
TMatriz *create_matrix(int filas, int columnas)
{
    TMatriz *matriz = (TMatriz *)malloc(sizeof(TMatriz));
    matriz->f = filas;
    matriz->c = columnas;
    matriz->m = (double **)malloc(filas * sizeof(double *));
    
    if (matriz->m == NULL) {
        perror("Error al asignar memoria para la matriz");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < filas; i++) {
        matriz->m[i] = (double *)malloc(columnas * sizeof(double));
        if (matriz->m[i] == NULL) {
            perror("Error al asignar memoria para las filas de la matriz");
            exit(EXIT_FAILURE);
        }
    }

    // Inicializar la matriz a ceros
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz->m[i][j] = 0.0;
        }
    }

    return matriz;
}

// Función para mostrar una matriz en la pantalla
void show_matrix(TMatriz* matriz)
{
    for (int i = 0; i < matriz->f; i++)
    {
        for (int j = 0; j < matriz->c; j++)
        {
            printf("%.2f ", matriz->m[i][j]);
        }
        printf("\n"); // Nueva línea al final de cada fila
    }

}

// Función para rellenar la matriz con los elementos de la cadena
void llena_matrix_from_cad(TMatriz* matriz, char *cadena){
    int fila = 0;
    int columna = 0;

    char *token = strtok(cadena, " "); // Divide la cadena usando espacios como delimitador

    while (token != NULL) {
        // Elimina cualquier espacio en blanco y paréntesis alrededor del token
        char *ptr = token;
        while (*ptr) {
            if (*ptr == '(' || *ptr == ')' || *ptr == '|') {
                memmove(ptr, ptr + 1, strlen(ptr));
            } else {
                ptr++;
            }
        }
        
        // Si el token resultante no está vacío, conviértelo en un número entero y almacénalo en la matriz
        if (strlen(token) > 0 ) {
            double numero = atof(token);
            matriz->m[fila][columna] = numero;
            columna++; // Incrementa la columna
        }
        
        token = strtok(NULL, " "); // Obtiene el siguiente token

        // Si encontramos el símbolo de tubería '|', pasamos a la siguiente fila de la matriz
        if (token != NULL && *token == '|') {
            fila++;
            columna = 0;
            token = strtok(NULL, " "); // Obtiene el siguiente token después del '|'
        }
    }
}


// Reservvamos memoria para una variable
TVar *create_var(char *var_name, TMatriz *matriz){

    TVar *nuevoNodo = (TVar *)malloc(sizeof(TVar));

    if(nuevoNodo != NULL){

        strcpy(nuevoNodo->nomVar, var_name);
        nuevoNodo->mat = matriz;

        nuevoNodo->sig = NULL;
        nuevoNodo->ant = NULL;
    }

    return nuevoNodo;
}

// Buscamos a partir de un nombre una variable
TVar *found_var(TVar *variable_gran, char *var_name){

    TVar *auxiliar = variable_gran;

    while(auxiliar != NULL){

        if(strcmp(auxiliar->nomVar, var_name) == 0){
            return auxiliar;
        }
        auxiliar = auxiliar->sig;
    }

    return NULL;
}

// Inserta la nueva variable en la ultima posicion de variable_gran
TVar *insert_last_var(TVar *variable, TVar *asignar_var){

    TVar *auxiliar = variable;

    if(auxiliar == NULL){

        // printf("Primer nodo\n");

        variable = asignar_var;

        variable->sig = NULL;
        variable->ant = NULL;
    }
    else{

        while(auxiliar->sig != NULL){
            auxiliar = auxiliar->sig;
        }

        auxiliar->sig = asignar_var;
        asignar_var->ant = auxiliar;
        asignar_var->sig = NULL;
    }

    return variable;

}

// Imprime todas las variables que cuelgan de variable_gran
void print_tvar(TVar *LaGranLista){
    TVar *aux = LaGranLista;
    while(aux != NULL){
        printf("%s\n", aux->nomVar);
        show_matrix(aux->mat);
        aux = aux->sig;
    }
}

// Implementación de la función de comparación
int compare_vars(const void *a, const void *b) {
    return strcmp(((TVar *)a)->nomVar, ((TVar *)b)->nomVar);
}

void great_view(TVar *variable_gran) {
    // Color Prompt
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (variable_gran == NULL) {
        SetConsoleTextAttribute(hConsole, 2);
        printf("No hay variables cargadas\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    // Contar el número de variables
    int numVars = count_vars(variable_gran);

    // Crear un arreglo de variables para ordenarlas
    TVar *varArray = malloc(numVars * sizeof(TVar));
    if (varArray == NULL) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error de memoria\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    // Copiar las variables a un arreglo
    int i = 0;
    TVar *auxiliar = variable_gran;
    while (auxiliar != NULL) {
        varArray[i] = *auxiliar;
        auxiliar = auxiliar->sig;
        i++;
    }

    // Ordenar el arreglo de variables alfabéticamente
    qsort(varArray, numVars, sizeof(TVar), compare_vars);

    // Mostrar las variables ordenadas
    SetConsoleTextAttribute(hConsole, 2);
    for (int j = 0; j < numVars; j++) {
        TMatriz *matrizaux = varArray[j].mat;
        if (matrizaux->m == 0) {
            printf("%s: [vacia!]\n", varArray[j].nomVar);
        } else {
            printf("%s ( %d x %d ) : ", varArray[j].nomVar, matrizaux->f, matrizaux->c);
            for (int k = 0; k < matrizaux->c; k++) {
                printf("%.2f ", matrizaux->m[0][k]);
            }
            printf("\n");
        }
    }

    SetConsoleTextAttribute(hConsole, 7);

    // Liberar la memoria del arreglo
    free(varArray);
}


//modifica grant_view para que muestre el listado de variables ordenadas alfabeticamente


// 0 si es variable, 1 si es error, 2 si es matriz
int matrix_or_var(char *cad){
    
    if(cad[0] >= 'a' && cad[0] <= 'z'){
        return 0;
    }
    else if(cad[0] >= 'A' && cad[0] <= 'Z'){
        return 0;
    }
    else if(cad[0] == '+' || cad[0] == '-'){ 

        if(cad[1] >= '0' || cad[1] <= '9'){
            return 2;
        }
        if(cad[1] == '.'){
            if(cad[2] >= '0' && cad[2] <= '9'){
                return 2;
            }
            return 1;
        }

    }
    else if(cad[0] == '.'){
        if(cad[1] >= '0' && cad[1] <= '9'){
            return 2;
        }
        return 1;
    }
    else if(cad[0] >= '0' || cad[0] <= '9'){
        return 2;
    }

    return 1;
}

// Validamos que este bn escrito todo,0 mal y 1 bien
int validate_name(char *nomVar){

    // Verifica la longitud del nombre de la variable
    if (strlen(nomVar) > 15) {
        return 0;
    }

    int i = 0;

    while(nomVar[i] != '\0'){
        if(nomVar[i] >= '0' && nomVar[i] <= '9'){
            i++;
            continue;
        }
        if(nomVar[i]>= 'a' && nomVar[i] <= 'z'){
            i++;
            continue;
        }
        if(nomVar[i] >= 'A' && nomVar[i] <= 'Z'){
            i++;
            continue;
        }
        return 0;
    }

    if(strcmp(nomVar, "quit") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "det") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "product") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "view") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "save") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "load") == 0){
        return 0;
    }
    // ej 3 ampliacion diciembre
    else if(strcmp(nomVar, "load over") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "$") == 0){
        return 0;
    }
    // EXTRAS
    else if(strcmp(nomVar, "rango") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "transp") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "triangular") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "diagonal") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "inversa") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "elevar") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "borrar") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "encontrar") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "obtener") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "adj") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "sumar") == 0){
        return 0;
    }
    else if(strcmp(nomVar, "restar") == 0){
        return 0;
    }
    
    
    return 1;

}

// nos devuelve el numero de veces que ha encontrado un caracter en concreto dentro de una cadena
int count_characters(char **cadena, char *caracter){

    int contador = 0;
    int i=0;

    while(cadena[i] != NULL){ //'\0'
        if(strcmp(cadena[i], caracter) == 0){
            contador++;
        }
        i++;
    }

    return contador;
}

// Función para realizar la suma de dos matrices y asignar el resultado a una tercera matriz
TMatriz* sum_matrix(TMatriz *matrizA, TMatriz *matrizB) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if ( matrizB != NULL && matrizA != NULL) {
        if (matrizB->f == matrizA->f && matrizB->c == matrizA->c ) {
            TMatriz *resultado = create_matrix(matrizB->f, matrizB->c);
            for (int i = 0; i < matrizA->f; i++) {
                for (int j = 0; j < matrizA->c; j++) {
                    
                    resultado->m[i][j] = matrizB->m[i][j] + matrizA->m[i][j];
                    //printf("Suma de matriz en (%d, %d) = %.2f\n", i, j, resultado->m[i][j]);
                }
            }
            return resultado;
        }
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: las matrices no son del mismo tamano.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
   
    return NULL;
}

// Función para realizar la suma de dos matrices y asignar el resultado a una tercera matriz
TMatriz* rest_matrix(TMatriz *matrizA, TMatriz *matrizB) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if ( matrizB != NULL && matrizA != NULL) {
        if (matrizB->f == matrizA->f && matrizB->c == matrizA->c ) {
            TMatriz *resultado = create_matrix(matrizB->f, matrizB->c);
            for (int i = 0; i < matrizA->f; i++) {
                for (int j = 0; j < matrizA->c; j++) {
                    
                    resultado->m[i][j] = matrizA->m[i][j] - matrizB->m[i][j];
                    //printf("Resta de matriz en (%d, %d) = %.2f\n", i, j, resultado->m[i][j]);
                }
            }
            return resultado;
        }
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: las matrices no son del mismo tamano.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
    return NULL;
}

// Función para multiplicar dos matrices
TMatriz* mult_matrix(TMatriz* matrizA, TMatriz* matrizB) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (matrizA == NULL || matrizB == NULL) {
        // Una o ambas matrices no son válidas
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: Una o ambas matrices no son válidas.\n");    
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    int filasA = matrizA->f;
    int columnasA = matrizA->c;
    int filasB = matrizB->f;
    int columnasB = matrizB->c;

    if (columnasA != filasB) {
        // Las matrices no tienen tamaños compatibles para la multiplicación
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: El número de columnas de la primera matriz no coincide con el número de filas de la segunda matriz.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    TMatriz* resultado = create_matrix(filasA, columnasB);

    if (resultado == NULL) {
        // Maneja errores de asignación de memoria
        return NULL;
    }

    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            resultado->m[i][j] = 0;
            for (int k = 0; k < columnasA; k++) {
                resultado->m[i][j] += matrizA->m[i][k] * matrizB->m[k][j];
            }
        }
    }

    return resultado;
}

// Vuelve todo matrices para ser tratado en otras funciones
TMatriz* create_auxiliar(char **cadena,TVar *var_gran)
{
    int filas, columnas;
    //printf("variable auxiliar: %s\n", cadena[0]);
    TVar *variableAux = found_var(var_gran, cadena[0]);
    
    if( variableAux != NULL){
        //printf("VARIABLE existe\n");
        return variableAux->mat;        
    }

    else
    {
        //printf("Es matriz\n");
        if (validate_matrix(cadena[0],&filas, &columnas) ==  1 && matrix_or_var(cadena[0]) == 2)
        {
            //printf("MATRIZ Valida\n");
            TMatriz *matrizAux = create_matrix(filas, columnas);
            llena_matrix_from_cad(matrizAux, cadena[0]);
            //printf("MATRIZ LLENA\n");
            return matrizAux;
        }
    }

    return NULL;
}

// Funcion para realizar todas las operations
TMatriz* operations(char **cadena,TVar *var_gran, int num_arg)
{
    int filas, columnas, filas2, columnas2;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



    if(count_characters(cadena, "+") == 1){
        TMatriz *matrizA = create_auxiliar(&cadena[0],var_gran);
        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoSuma = sum_matrix(matrizA, matrizB);
            return resultadoSuma;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            
            return NULL; 
        }          


    }else if(count_characters(cadena, "-") == 1){
        TMatriz *matrizA = create_auxiliar(&cadena[0],var_gran);
        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoResta = rest_matrix(matrizA, matrizB);
            return resultadoResta;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "*") == 1){
        TMatriz *matrizA = create_auxiliar(&cadena[0],var_gran);
        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);
        if (matrizA != NULL && matrizB != NULL) 
        {
            TMatriz *resultadoMulti = mult_matrix(matrizA, matrizB);
            return resultadoMulti;  
        } else {
            // Manejo de errores si las variables no se encuentran
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: una o ambas variables no existen.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "product") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        // ej 2 ampliacion diciembre
        if (matrix_or_var(cadena[1]) != 1  && validate_dec(cadena[2]) == 1) {
        
            TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

            if ( matrizA != NULL) 
            {
                TMatriz *resultadoproduct = produc_matrix_por_num(&cadena[2],matrizA);
                return resultadoproduct;  
            } else {
                // Manejo de errores si la variable no se encuentra
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: En el argumento 1.\n");
                SetConsoleTextAttribute(hConsole, 7);
                return NULL; 
            }  
        }

        // ORIGINAL

        if(validate_dec(cadena[1]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Numero no valido.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);

        if ( matrizB != NULL) 
        {
            TMatriz *resultadoproduct = produc_matrix_por_num(&cadena[1],matrizB);
            return resultadoproduct;  
        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento 2.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "sumar") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        // AMPLIACION EJECICIO 2 DICIEMBRE 
        //printf("matrix_or_var: %d y validate_dec: %d \n", matrix_or_var(cadena[1]),validate_dec(cadena[2]));

        if (matrix_or_var(cadena[1]) != 1  && validate_dec(cadena[2]) == 1) {
        
            TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

            if ( matrizA != NULL) 
            {
                TMatriz *resultadosumar = sum_matrix_por_number(&cadena[2],matrizA);
                return resultadosumar;  
            } else {
                // Manejo de errores si la variable no se encuentra
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: En el argumento 1.\n");
                SetConsoleTextAttribute(hConsole, 7);
                return NULL; 
            }  
        }

        // ORIGINAL

        if(validate_dec(cadena[1]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Numero no valido.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);

        if ( matrizB != NULL) 
        {
            TMatriz *resultadosuma = sum_matrix_por_number(&cadena[1],matrizB);
            return resultadosuma;  
        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento 2.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "restar") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        // AMPLIACION EJECICIO 2 DICIEMBRE 
        //printf("matrix_or_var: %d y validate_dec: %d \n", matrix_or_var(cadena[1]),validate_dec(cadena[2]));

        if (matrix_or_var(cadena[1]) != 1  && validate_dec(cadena[2]) == 1) {
        
            TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

            if ( matrizA != NULL) 
            {
                TMatriz *resultadoresta = rest_matrix_por_number(&cadena[2],matrizA);
                return resultadoresta;  
            } else {
                // Manejo de errores si la variable no se encuentra
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error: En el argumento 1.\n");
                SetConsoleTextAttribute(hConsole, 7);
                return NULL; 
            }  
        }

        // ORIGINAL

        if(validate_dec(cadena[1]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Numero no valido.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizB = create_auxiliar(&cadena[2],var_gran);

        if ( matrizB != NULL) 
        {
            TMatriz *resultadoresta = rest_matrix_por_number(&cadena[1],matrizB);
            return resultadoresta;  
        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento 2.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "triangular") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if ( matrizA != NULL) 
        {
            triang_matrix(matrizA);
            return matrizA;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "transp") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if ( matrizA != NULL) 
        {
            TMatriz *resultadotransp = matrix_transpuesta(matrizA);
            return resultadotransp;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "diagonal") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if ( matrizA != NULL) 
        {
            TMatriz *resultadodiagonal = matrix_diagonal(matrizA);
            return resultadodiagonal;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "inversa") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        // Calcular el determinante
        double det = det_gauss(matrizA);

        if( det == 0){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: El determinante de la matriz es cero, la matriz es no invertible.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if ( matrizA != NULL) 
        {
            TMatriz *resultadoinversa = matrix_inversa(matrizA);
            return resultadoinversa;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "elevar") == 1){

        if(num_arg != 3){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        if(validate_dec(cadena[2]) == 0){

            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Numero no valido.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if ( matrizA != NULL) 
        {
            TMatriz *resultadoelevar = matrix_potencia(matrizA, &cadena[2]);
            return resultadoelevar;  
        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento 2.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }
    }else if(count_characters(cadena, "ordenar") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if ( matrizA != NULL) 
        {
            TMatriz *resultadoordenada = ordenar_matrix_burbuja(matrizA);
            return resultadoordenada;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: En el argumento.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }else if(count_characters(cadena, "adj") == 1){

        if(num_arg != 2){
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Introduccion de argumentos.\n");
            SetConsoleTextAttribute(hConsole, 7);

            return NULL;
        }

        TMatriz *matrizA = create_auxiliar(&cadena[1],var_gran);

        if (matrizA->f != matrizA->c) {
            // Las matrices no son cuadradas
            SetConsoleTextAttribute(hConsole, 4);
            printf("ERROR: Las matrices no son cuadradas.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL;
        }

        if ( matrizA != NULL) 
        {
            TMatriz *resultadoadjunta = matrix_adjunta(matrizA);
            return resultadoadjunta;

        } else {
            // Manejo de errores si la variable no se encuentra
            SetConsoleTextAttribute(hConsole, 4);
            printf("Error: La variable no existe.\n");
            SetConsoleTextAttribute(hConsole, 7);
            return NULL; 
        }  
    }
    else{

        TMatriz *matrizA = create_auxiliar(&cadena[0],var_gran);
        if(matrizA != NULL)
        {
            return matrizA;
        }
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: COMANDO INVALIDO.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
        
    }
    
}

//Creacion del espacio de
TVars *crearWorkspace(TVars *workspace){

    workspace = (TVars *) malloc(sizeof(TVars));

    workspace->numVars = 0;
    workspace->primera = NULL;

    return workspace;
}

//Cuenta las variables guardadas en memoria
int count_vars(TVar *var_gran){

    TVar *aux = var_gran;
    int i = 0;

    while(aux != NULL){

        i++;
        aux = aux->sig;
    }

    return i;

}

//Guardamos en txt
void save(char *nombre, TVars *workspace){

    //Si al final acabamos poniendole filtros al nombre descomentar esto
    /*
    int i = validate_name(nombre);
    if(i == 0){
        printf("ERROR FATAL\n");
        return 0;
    }
    */

   char aux[50]="./";
   int numeroElementos = 0;

    strcat(aux, nombre);

    if(strchr(nombre, '.') == NULL){ //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    FILE *fichero;
    fichero = fopen(aux, "w");
    if(fichero != NULL){

        //fprintf(fichero, "LIST WORKSPACE\n"); // SI QUEREMOS PONER UN TITULO EN EL SAVE
        //fprintf(fichero, "---------------\n");   

        TVar *auxiliar = workspace->primera; 

        for(int i = 0; i<workspace->numVars; i++){
            
            //Imprimimos el nombre de la variable
            fprintf(fichero, "%s\n", auxiliar->nomVar);

            TMatriz *auxMatriz = auxiliar->mat;

            fprintf(fichero, "( ");
            for (int i = 0; i < auxMatriz->f; i++)
            {
                for (int j = 0; j < auxMatriz->c; j++)
                {
                    fprintf(fichero,"%.8f", auxMatriz->m[i][j]);
                    if (j < auxMatriz->c - 1) {
                        fprintf(fichero," ");
                    }
                }
                if (i < auxMatriz->f - 1) {
                    fprintf(fichero," | ");
                }
            }

            fprintf(fichero, " )\n");
            auxiliar = auxiliar->sig;
        }

        fclose(fichero);
    }
    else{
        printf("ERROR AL GUARDAR\n");
    }

}

//Quita los espacios en blanco de las cadenas por delante y por detras
void Trim(char *cad){
    int c, i=0, j, n = strlen(cad);

    if(cad == NULL || n < 1){
        return;
    }
    
    n--;

    while(n>0 && ((c=cad[n]) == ' ' || c=='\n')){ 
        n--;
    }

    cad[n+1] = '\0';

    while(i<=n && ((c=cad[i]) == ' ' || c == '\n')){ 
        i++;
    }

    for(j=0; j<=n-i+1; j++){
        cad[j] = cad[j+i];
    }
    
}

// AMPLIACION EJERCICIO 3 DICIEMBRE 1 para sobreescirbir 0 para solapar
//Cargar desde el fichero 
TVars *load(char *nombre, TVars *workspace, int reescribir) {
    

    FILE *fichero;
    char aux[50] = "./";
    char linea[1000]; // Caracteres en la linea
    int n = 0;

    strcat(aux, nombre);

    if (strchr(nombre, '.') == NULL) { //Entramos en el caso de que no tenga .txt
        strcat(aux, ".txt");
    }

    // printf("La ruta del load es: %s\n", aux);

    fichero = fopen(aux, "r");//abrimos fichero en modo lectura

    if (reescribir){
        workspace = crearWorkspace(NULL);
    }

    if (fichero == NULL) {
        // El archivo no existe o no puede ser abierto
        // perror("Error al abrir el archivo");
        fclose(fichero);
        return NULL; // Devolvemos el workspace actual sin cambios
    }

    // Contar las líneas del documento
    while (fgets(linea, sizeof(linea), fichero) != NULL) {
        n++;
    }

    // Validar que hay suficientes líneas para representar variables
    if (n % 2 != 0) {
        fclose(fichero);
        printf("Error: El número de líneas no es par.\n");
        return NULL;
    }

    fseek(fichero, 0, SEEK_SET); // Mover el cursor al principio del documento

    // Si el número de variables es 0, devolvemos un workspace vacío
    if (n == 0) {
        fclose(fichero);
        return workspace;
    }

    int num_vars = n / 2;
    workspace->numVars = num_vars;

    TVar *variable_gran = workspace->primera;

    for (int i = 0; i < num_vars; i++) {
        char var_name[16] = "";

        fgets(linea, 1000, fichero);
        strcpy(var_name, linea);
        Trim(var_name);
        // AMPLIACION EJER 3
        TVar *existingVariable = found_var(variable_gran, var_name);

        if (existingVariable != NULL) {
            fgets(linea, 1000, fichero);
            char separadores[8] = " \t\n";
            MiStrTok(linea, separadores, 1);
            int filas, columnas;
            if (validate_matrix(linea, &filas, &columnas) == 1) {
                //liberate_matrix(existingVariable->mat); // Libero la memoria de la matriz almacenada en la varibale existente 
                existingVariable->mat = create_matrix(filas, columnas); // Creo una nueva matriz en la variable con las filas y columnas nuevas
                llena_matrix_from_cad(existingVariable->mat, linea); // Lleno la nueva matriz con lo que hay en el fichero
            }
        } else {
        ////////////////////////
            fgets(linea, 1000, fichero);
            char separadores[8] = " \t\n";
            MiStrTok(linea, separadores, 1);
            int filas, columnas;
            if (validate_matrix(linea, &filas, &columnas) == 1) {
                TMatriz *matrizAux = create_matrix(filas, columnas);
                llena_matrix_from_cad(matrizAux, linea);
                TVar *auxiliarVariable = create_var(var_name, matrizAux);
                variable_gran = insert_last_var(variable_gran, auxiliarVariable);
            }
        }
    }

    workspace->primera = variable_gran;

    //imprimirTVAR(variable_gran);
    fclose(fichero);
    return workspace;
}

// Función para copiar una matriz (devuelve una nueva matriz copiada)
TMatriz* copy_matrix(TMatriz *matriz) {
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz
    TMatriz *matrizCopiada = create_matrix(filas, columnas);

    // Copiar los elementos de la matriz original a la matriz copiada
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizCopiada->m[i][j] = matriz->m[i][j];
        }
    }

    return matrizCopiada;
}

// Función para triangular una matriz mediante el método de Gauss (copia la matriz original y la devuelve modificada)
void triang_matrix(TMatriz *matriz) {
    int filas = matriz->f;
    int columnas = matriz->c;

    for (int k = 0; k < filas - 1; k++) {
        for (int i = k + 1; i < filas; i++) {
            double factor = matriz->m[i][k] / matriz->m[k][k];
            for (int j = k; j < columnas; j++) {
                matriz->m[i][j] -= factor * matriz->m[k][j];
            }
        }
    }
}

// Función para calcular el determinante de una matriz triangular (no altera la matriz original)
double det_triang(TMatriz *matriz) {
    int filas = matriz->f;
    double det = 1.0;

    for (int i = 0; i < filas; i++) {
        det *= matriz->m[i][i];
    }

    return det;
}

// Función para calcular el determinante de una matriz mediante el método de Gauss (copia la matriz original y la devuelve modificada)
double det_gauss(TMatriz *matriz) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Copiar la matriz original
    TMatriz *matrizCopiada = copy_matrix(matriz);

    // Triangular la matriz copiada
    triang_matrix(matrizCopiada);

    // Calcular el determinante de la matriz triangular copiada
    double det = det_triang(matrizCopiada);

    // Liberar la memoria de la matriz copiada
    liberate_matrix(matrizCopiada);

    return det;
}

// Función para multiplicar una matriz por un número
TMatriz* produc_matrix_por_num(char **cadena, TMatriz *matriz) {
    double numero = atof(*cadena);  // Convertir la cadena a un número
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz para almacenar el resultado
    TMatriz *resultado = create_matrix(filas, columnas);

    // Multiplicar cada elemento de la matriz por el número
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado->m[i][j] = numero * matriz->m[i][j];
        }
    }

    return resultado;
}

// Función para multiplicar una matriz por un número
TMatriz* sum_matrix_por_number(char **cadena, TMatriz *matriz) {
    double numero = atof(*cadena);  // Convertir la cadena a un número
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz para almacenar el resultado
    TMatriz *resultado = create_matrix(filas, columnas);

    // Multiplicar cada elemento de la matriz por el número
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado->m[i][j] = numero + matriz->m[i][j];
        }
    }

    return resultado;
}

// Función para multiplicar una matriz por un número
TMatriz* rest_matrix_por_number(char **cadena, TMatriz *matriz) {
    double numero = atof(*cadena);  // Convertir la cadena a un número
    int filas = matriz->f;
    int columnas = matriz->c;

    // Crear una nueva matriz para almacenar el resultado
    TMatriz *resultado = create_matrix(filas, columnas);

    // Multiplicar cada elemento de la matriz por el número
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado->m[i][j] =  matriz->m[i][j] - numero;
        }
    }

    return resultado;
}

//Valida que sea un numero real || 0 MAL, 1 BN
int validate_dec(char *cad){

    int i, ini, p=0, j;

    if(cad[0] == '+' || cad[0] == '-'){
        ini=1;
    }
    else{
        ini=0;
    }

    for(i=ini; i<strlen(cad); i++){
        if(cad[i]<'0' || cad[i]> '9'){
            if(cad[i] == '.'){
                p++;
            }
            else{
                return 0;
            }
        }
        if(p==2){
            return 0;
        }
    }

    if(ini==1 && strlen(cad) == 1){
        return 0;
    }
    if(strlen(cad) == 0){
        return 0;
    }

    if(ini==1 && strlen(cad) == 2 && cad[1] == '.'){ //+.
        return 0;
    }

    if(ini == 0 && strlen(cad) == 1 && cad[0] == '.'){ // .
        return 0;
    }

    return 1;
}

// Función para liberar la memoria de una matriz
TMatriz* liberate_matrix(TMatriz *matriz) {

    for (int i = 0; i < matriz->f; i++) {
        free(matriz->m[i]);
    }

    // Liberar el doble puntero a las filas
    free(matriz->m);

    // Liberar la estructura de la matriz
    free(matriz);
    
    //Devolver una matriz vacía
    TMatriz *matrizVacia = create_matrix(0, 0);
    show_matrix(matrizVacia);
    return matrizVacia;
    
}

//le pasamos la gran variable
TVar *liberarVariables(TVar *variable_gran){

    TVar *auxiliarVariable = NULL; //pq trabajar con la granVariable directamente es peligroso

    if(variable_gran == NULL){ //caso de que este vacio
        free(variable_gran);
        return NULL;
    }

    auxiliarVariable = variable_gran;


    while(auxiliarVariable != NULL){ 
        
        variable_gran = variable_gran->sig; //ahora la gran variable apunta a la segunda posicion

        // limpiamos la Tmatriz de la variable (TVar)
        auxiliarVariable->mat = liberate_matrix(auxiliarVariable->mat);

        //Recolocamos los punteros
        auxiliarVariable->ant = NULL;
        auxiliarVariable->sig = NULL;

       
        if(variable_gran != NULL){
            variable_gran->ant = NULL; //la que estaba en segunda posicion
        }

        free(auxiliarVariable);

        auxiliarVariable = variable_gran;

    }

    free(variable_gran);
    //great_view(variable_gran);
    return NULL;
}

//Eliminamos la variable y toda la informacion que tenga asociada
TVar *eliminarVariable(TVar *variable_gran, char *cad){

    TVar *var_delete = variable_gran;

    TVar *aux_var_next, *aux_var_anterior;

    while(var_delete != NULL){
        
        if(strcmp(cad, var_delete->nomVar) == 0){

            
            aux_var_next = var_delete->sig; 
            aux_var_anterior = var_delete->ant;


            if(aux_var_next == NULL && aux_var_anterior == NULL){ //UNICO ELEMENTO
                variable_gran = NULL;
            }
            else if(aux_var_next != NULL && aux_var_anterior == NULL){ //Es el PRIMERO
                variable_gran = aux_var_next;
                aux_var_next->ant = NULL;
            }
            else if(aux_var_next == NULL && aux_var_anterior != NULL){ //Es el ULTIMO
                aux_var_anterior->sig = NULL;
            }
            else{ //ESTA EN MEDIO
                aux_var_next->ant = aux_var_anterior;
                aux_var_anterior->sig = aux_var_next;
            }

            //Recolocamos los punteros
            var_delete->ant = NULL;
            var_delete->sig = NULL;

            liberate_matrix(var_delete->mat);

            free(var_delete);
            return variable_gran;

        }
        var_delete = var_delete->sig;
    }
    return variable_gran;
}

// validamos numeros enteros. 1 bien y el 0 para mal
int validate_int(char *cad){
    int i, ini;

    if(cad[0] == '+' || cad[0] == '-'){
        ini=1;
    }
    else{
        ini = 0;
    }

    for(int i=ini; i<strlen(cad); i++){
        if(cad[i]<'0' || cad[i]>'9'){
            return 0;
        }
    }

    if(ini==1 && strlen(cad) == 1){
        return 0;
    }
    
    return 1;

}

//Comprueba que exista en la carpeta un fichero con este nombre, 0 MAL, 1 BN.
int comprobate_file(char *cadena){

    DIR *d; 
    struct dirent *f;
    int j = 0;
    char aux[100];

    d = opendir(".");
    if(d == NULL){
        printf("error\n");
        return 0;
    }

    strcpy(aux, cadena);
    strcat(aux, ".txt");
    
    while((f = readdir(d)) != NULL){

        printf("%s\n", f->d_name);
        if(strcmp(f->d_name, aux) == 0){
            printf("el archivo ya existe.\n");
            return 0;
        }

    }
    closedir(d);
    return 1;
}

// AMPLIACION EJERCICIO 4 DICIEMBRE
// Función para realizar el producto escalar de dos matrices de 1xN
double produc_escalar(TMatriz *matriz1, TMatriz *matriz2)
{

    double resultado = 0.0;
    for (int i = 0; i < matriz1->c; i++) {
        resultado += matriz1->m[0][i] * matriz2->m[0][i];
    }

    return resultado;
}




// ESTO CREO Q NO SIRVE PA NAAA
// Función para imprimir el contenido del workspace
void imprimirWorkspace(TVars *workspace) {
    if (workspace == NULL) {
        printf("Error: Workspace no válido.\n");
        return;
    }

    printf("Número de variables en el workspace: %d\n", workspace->numVars);

    // Recorre la lista de variables e imprime sus nombres
    TVar *variableActual = workspace->primera;
    int contador = 1;

    while (variableActual != NULL) {
        printf("Variable %d: %s\n", contador, variableActual->nomVar);
        variableActual = variableActual->sig;
        contador++;
    }
}

int var_existe(TVars *workspace, const char *nombre) {
    TVar *variableActual = workspace->primera;

    while (variableActual != NULL) {
        if (strcmp(variableActual->nomVar, nombre) == 0) {
            // La variable ya existe en el workspace
            return 1;
        }
        variableActual = variableActual->sig;
    }

    // La variable no existe en el workspace
    return 0;
}

void add_var_final(TVars *workspace, TVar *nuevaVariable) {
    if (workspace->primera == NULL) {
        // El workspace está vacío
        workspace->primera = nuevaVariable;
    } else {
        // Encuentra la última variable en el workspace
        TVar *variableActual = workspace->primera;
        while (variableActual->sig != NULL) {
            variableActual = variableActual->sig;
        }

        // Agrega la nueva variable al final
        variableActual->sig = nuevaVariable;
        nuevaVariable->ant = variableActual;
    }

    // Incrementa el contador de variables en el workspace
    workspace->numVars++;
}

//ESTO SI QUE SIRVE PAPA

// Función para intercambiar dos filas de una matriz
void intercambiarFilas(TMatriz *matriz, int fila1, int fila2) {
    double *temp = matriz->m[fila1];
    matriz->m[fila1] = matriz->m[fila2];
    matriz->m[fila2] = temp;
}

// Función para hacer cero los elementos debajo del pivote en una columna
void hacerCeroDebajo(TMatriz *matriz, int filaPivote, int columnaPivote) {
    for (int i = filaPivote + 1; i < matriz->f; i++) {
        double factor = matriz->m[i][columnaPivote] / matriz->m[filaPivote][columnaPivote];
        for (int j = columnaPivote; j < matriz->c; j++) {
            matriz->m[i][j] -= factor * matriz->m[filaPivote][j];
        }
    }
}

// Función para llevar la matriz a su forma escalonada reducida
void forma_escalonada_reducida(TMatriz *matriz) {
    int filaPivote = 0;

    for (int columnaPivote = 0; columnaPivote < matriz->c; columnaPivote++) {
        // Buscar el pivote no nulo
        int filaNoNula = -1;
        for (int i = filaPivote; i < matriz->f; i++) {
            if (matriz->m[i][columnaPivote] != 0.0) {
                filaNoNula = i;
                break;
            }
        }

        // Si no hay fila no nula, pasar a la siguiente columna
        if (filaNoNula == -1) {
            continue;
        }

        // Intercambiar filas para poner el pivote en la fila pivote
        intercambiarFilas(matriz, filaPivote, filaNoNula);

        // Hacer cero los elementos debajo del pivote
        hacerCeroDebajo(matriz, filaPivote, columnaPivote);

        // Incrementar la fila del pivote
        filaPivote++;
    }
}

// Función para calcular el rango de una matriz
int matrix_rank(TMatriz *matriz) {
    // Copiar la matriz para no modificar la original
    TMatriz *copiaMatriz = create_matrix(matriz->f, matriz->c);
    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            copiaMatriz->m[i][j] = matriz->m[i][j];
        }
    }

    // Llevar la copia a su forma escalonada reducida
    forma_escalonada_reducida(copiaMatriz);

    // Contar el número de filas no nulas en la forma escalonada reducida
    int rango = 0;
    for (int i = 0; i < copiaMatriz->f; i++) {
        int filaNoNula = 0;
        for (int j = 0; j < copiaMatriz->c; j++) {
            if (copiaMatriz->m[i][j] != 0.0) {
                filaNoNula = 1;
                break;
            }
        }
        rango += filaNoNula;
    }

    liberate_matrix(copiaMatriz);
    return rango;
}

// Función para calcular la matriz transpuesta
TMatriz *matrix_transpuesta(TMatriz *matriz) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    TMatriz *transpuesta = create_matrix(matriz->c, matriz->f);

    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            transpuesta->m[j][i] = matriz->m[i][j];
        }
    }

    return transpuesta;
}

// Función para calcular la matriz diagonal de una matriz
TMatriz *matrix_diagonal(TMatriz *matriz) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (matriz->f != matriz->c) {
        // Las matrices no son cuadradas
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: Las matrices no son cuadradas.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    TMatriz *diagonal = create_matrix(matriz->f, matriz->c);

    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            diagonal->m[i][j] = (i == j) ? matriz->m[i][j] : 0.0;
        }
    }

    return diagonal;
}

// Función para crear la matriz identidad de tamaño n x n
TMatriz *matrix_identidad(int n) {
    TMatriz *identidad = create_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            identidad->m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    return identidad;
}

// Función para calcular la matriz inversa
TMatriz *matrix_inversa(TMatriz *matriz) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (matriz->f != matriz->c) {
        // Las matrices no son cuadradas
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: Las matrices no son cuadradas.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    int n = matriz->f;
    TMatriz *matrizExtendida = create_matrix(n, 2 * n);
    TMatriz *matrix_inversa = matrix_identidad(n);

    // Copiar la matriz original y la identidad en una matriz extendida
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrizExtendida->m[i][j] = matriz->m[i][j];
            matrizExtendida->m[i][j + n] = matrix_inversa->m[i][j];
        }
    }

    // Aplicar eliminación gaussiana para obtener una matriz triangular superior
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial
        int maxFila = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(matrizExtendida->m[k][i]) > abs(matrizExtendida->m[maxFila][i])) {
                maxFila = k;
            }
        }
        // Intercambiar filas
        for (int k = i; k < 2 * n; k++) {
            double temp = matrizExtendida->m[i][k];
            matrizExtendida->m[i][k] = matrizExtendida->m[maxFila][k];
            matrizExtendida->m[maxFila][k] = temp;
        }

        // Hacer ceros debajo del pivote
        for (int k = i + 1; k < n; k++) {
            double factor = matrizExtendida->m[k][i] / matrizExtendida->m[i][i];
            for (int j = i; j < 2 * n; j++) {
                matrizExtendida->m[k][j] -= factor * matrizExtendida->m[i][j];
            }
        }
    }

    // Hacer unos en la diagonal principal
    for (int i = 0; i < n; i++) {
        double factor = matrizExtendida->m[i][i];
        for (int j = 0; j < 2 * n; j++) {
            matrizExtendida->m[i][j] /= factor;
        }
    }

    // Hacer ceros encima y debajo de la diagonal principal
    for (int i = n - 1; i > 0; i--) {
        for (int k = i - 1; k >= 0; k--) {
            double factor = matrizExtendida->m[k][i] / matrizExtendida->m[i][i];
            for (int j = 0; j < 2 * n; j++) {
                matrizExtendida->m[k][j] -= factor * matrizExtendida->m[i][j];
            }
        }
    }

    // Extraer la matriz inversa de la matriz extendida
    TMatriz *resultado = create_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado->m[i][j] = matrizExtendida->m[i][j + n];
        }
    }

    // Liberar la memoria de la matriz extendida
    liberate_matrix(matrizExtendida);

    return resultado;
}

// Función para calcular la potencia de una matriz
TMatriz *matrix_potencia(TMatriz *matriz, char **exponente) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Convertir la cadena del exponente a un número entero
    double exp = atof(*exponente);

    if (matriz->f != matriz->c) {
        // Las matrices no son cuadradas
        SetConsoleTextAttribute(hConsole, 4);
        printf("ERROR: Las matrices no son cuadradas.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    if (exp < 0) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error: El exponente debe ser un número no negativo.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return NULL;
    }

    // Inicializar la matriz resultado como la matriz identidad
    TMatriz *resultado = create_matrix(matriz->f, matriz->c);
    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            resultado->m[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Calcular la potencia de la matriz mediante multiplicación repetida
    for (int i = 0; i < exp; i++) {
        TMatriz *temporal = create_matrix(matriz->f, matriz->c);

        // Multiplicar la matriz resultado por la matriz original
        for (int j = 0; j < matriz->f; j++) {
            for (int k = 0; k < matriz->c; k++) {
                for (int l = 0; l < matriz->c; l++) {
                    temporal->m[j][k] += resultado->m[j][l] * matriz->m[l][k];
                }
            }
        }

        // Copiar el resultado de la multiplicación a la matriz resultado
        for (int j = 0; j < matriz->f; j++) {
            for (int k = 0; k < matriz->c; k++) {
                resultado->m[j][k] = temporal->m[j][k];
            }
        }

        // Liberar la memoria de la matriz temporal
        liberate_matrix(temporal);
    }

    return resultado;
}

// Función para ordenar una matriz copiada usando el algoritmo burbuja
TMatriz* ordenar_matrix_burbuja(TMatriz *matriz) {
    // Copiar la matriz original para no afectarla
    TMatriz *matrizOrdenada = copy_matrix(matriz);

    // Algoritmo burbuja para ordenar la matriz copiada
    for (int i = 0; i < matrizOrdenada->f * matrizOrdenada->c - 1; i++) {
        for (int j = 0; j < matrizOrdenada->f * matrizOrdenada->c - i - 1; j++) {
            int fila1 = j / matrizOrdenada->c;
            int col1 = j % matrizOrdenada->c;

            int fila2 = (j + 1) / matrizOrdenada->c;
            int col2 = (j + 1) % matrizOrdenada->c;

            if (matrizOrdenada->m[fila1][col1] > matrizOrdenada->m[fila2][col2]) {
                // Intercambiar elementos si están en el orden incorrecto
                double temp = matrizOrdenada->m[fila1][col1];
                matrizOrdenada->m[fila1][col1] = matrizOrdenada->m[fila2][col2];
                matrizOrdenada->m[fila2][col2] = temp;
            }
        }
    }

    return matrizOrdenada;
}

// Función para buscar la posición de un número en la matriz
void found_position(TMatriz *matriz, char **num) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    double numero = atof(*num);

    int encontrado = 0;
    int fila = -1, columna = -1;

    // Buscar el número en la matriz
    for (int i = 0; i < matriz->f; i++) {
        for (int j = 0; j < matriz->c; j++) {
            if (matriz->m[i][j] == numero) {
                encontrado = 1;
                SetConsoleTextAttribute(hConsole, 2);
                printf("El numero %.2lf se encuentra en la posicion (%d, %d) de la matriz.\n", numero, i, j);
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
    }

    // Mostrar mensaje si no se encuentra
    if (!encontrado) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("El numero %.2lf no se encuentra en la matriz.\n", numero);
        SetConsoleTextAttribute(hConsole, 7);
    }
}

// Función para obtener el número en una posición de la matriz
void obten_num_en_posicion(TMatriz *matriz, char **fila, char **columna){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int numFila = atoi(*fila);
    int numColumna = atoi(*columna);

    if (numFila >= 0 && numFila < matriz->f && numColumna >= 0 && numColumna < matriz->c) {
        double numero = matriz->m[numFila][numColumna];
        SetConsoleTextAttribute(hConsole, 2);
        printf("El numero en la posicion (%s, %s) es: %.2lf\n", *fila, *columna, numero);
        SetConsoleTextAttribute(hConsole, 7);
    } else {
        // Si la posición está fuera de los límites de la matriz, devolvemos un valor especial
        SetConsoleTextAttribute(hConsole, 4);
        printf("Posicion fuera de los limites de la matriz.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
}

// Calcular la matriz de cofactores de una submatriz
TMatriz* matrizCofactores(TMatriz *matriz, int fila, int columna) {
    int n = matriz->f;
    TMatriz *cofactores = create_matrix(n - 1, n - 1);

    for (int i = 0, x = 0; i < n; i++) {
        if (i != fila) {
            for (int j = 0, y = 0; j < n; j++) {
                if (j != columna) {
                    cofactores->m[x][y] = matriz->m[i][j];
                    y++;
                }
            }
            x++;
        }
    }

    return cofactores;
}

// Calcular la matriz adjunta (adjugada) de una matriz cuadrada
TMatriz* matrix_adjunta(TMatriz *matriz) {
    int n = matriz->f;
    TMatriz *adjunta = create_matrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Calcular el cofactor
            TMatriz *cofactor = matrizCofactores(matriz, i, j);

            // Calcular el signo del cofactor
            int signo = ((i + j) % 2 == 0) ? 1 : -1;

            // Calcular el determinante del cofactor
            double determinanteCofactor = det_gauss(cofactor);

            // Asignar el cofactor transpuesto multiplicado por el signo al elemento de la matriz adjunta
            adjunta->m[j][i] = signo * determinanteCofactor;

            // Liberar la memoria utilizada para el cofactor
            liberate_matrix(cofactor);
        }
    }

    return adjunta;
}




