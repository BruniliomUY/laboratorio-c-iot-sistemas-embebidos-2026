#include "global.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>



size_t get_size(data_type_t type) {
    switch(type) {
        case TYPE_INT32: return sizeof(int32_t);
        case TYPE_UINT32: return sizeof(uint32_t);
        case TYPE_FLOAT: return sizeof(float);
        case TYPE_DOUBLE: return sizeof(double);
        case TYPE_CHAR: return sizeof(char);
        case TYPE_STRING: return sizeof(char *);
    }
    return 0;
}

void print_element(void *elem, data_type_t type) {
    switch(type) {
        case TYPE_INT32:
            printf("%d", *(int32_t *)elem);
            break;
        case TYPE_FLOAT:
            printf("%f", *(float *)elem);
            break;
        case TYPE_CHAR:
            printf("%c", *(char *)elem);
            break;
        case TYPE_STRING:
            printf("%s", *(char **)elem);
            break;
    }
}

/*
=========================
  init_lab:
   printea la informacion inicial del laboratorio
  parametros:
      ninguno
  retorno:
      no retorna nada
=========================
*/
void init_lab(void)
{
    printf("Laboratorio Lenguaje C""\n");
    printf("Integrantes del grupo:\n");
    printf("- Victoria Amor\n");
    printf("- Nicolas Meyer\n");
    printf("- Bruno Moreira\n");
}

/*
=========================
 root_t* eq_solver:
   resuelve la ecuacion de segundo grado dada por los coeficientes a, b y c usando el metodo de Bhaskara
   y devuelve un puntero a una estructura root_t con las soluciones reales o complejas segun corresponda
  parametros:
      coeficientes: puntero a una estructura coeff_t con los coeficientes a, b y c de la ecuacion
  retorno:
      puntero a una estructura root_t con las soluciones reales o complejas segun corresponda
=========================
*/
root_t* eq_solver(coeff_t *coeficientes) {
    root_t *solucion = malloc(sizeof(root_t));  // Asignamos var local para almacenar la solución

    if (solucion == NULL)
    {
        return NULL; // no hay memoria disponible,se aprendio de el video de lista enlazada que hace esta verificacion de si se reservo bien la memoria dinamica o no
    }
    
    double a = (double)coeficientes->a; // Convertimos a double para mayor precisión en el cálculo intermedio
    double b = (double)coeficientes->b;
    double c = (double)coeficientes->c;

	double discriminante = b*b - 4*a*c;// Calculamos el discriminante.

    //Segun el metodo de Bhaskara y el discriminante, asignamos los valores a la estructura de solución.
	if (discriminante > 0) {
        double x1 = (-b + sqrt(discriminante)) / (2.0 * a);          // Calculamos la primera raíz usando el método de Bhaskara.
	    double x2 = (-b - sqrt(discriminante)) / (2.0 * a);          // Calculamos la segunda raíz usando el método de Bhaskara.
        solucion->real1 = (int32_t)x1;                                 //  Se usa -> por que es a lo que apunta soulcion dentro de el espacio de está asignada la memoria para almacenar la solución.
        solucion->imag1 = 0;
        solucion->real2 = (int32_t)x2;
        solucion->imag2 = 0;
        solucion->complex = false;
	} else if (discriminante < 0) {
		solucion->real1 = (int32_t)(-b / (2.0 * a));
        solucion->imag1 = (int32_t)(sqrt(-discriminante) / (2.0 * a));
        solucion->real2 = (int32_t)(-b / (2.0 * a));
        solucion->imag2 = (int32_t)(-sqrt(-discriminante) / (2.0 * a));
        solucion->complex = true;
	} else {
		solucion->real1 = (int32_t)(-b / (2.0 * a));
        solucion->imag1 = 0;
        solucion->real2 = (int32_t)(-b / (2.0 * a));
        solucion->imag2 = 0;
        solucion->complex = false;
	}
    return solucion;  // Retornamos la solución calculada, hay que liberar la memoria asignada por el llamador de esta función para evitar fugas de memoria.
}
/*
=========================
  int32_t bin2dec:
   convierte un número binario a su equivalente en decimal
  parametros:
      binary: cadena de caracteres con el número binario
      sign: booleano que indica si el número es con signo o sin signo
  retorno:
      número decimal resultante
 =========================
*/
int32_t bin2dec(char *binary,bool sign) {
    int32_t num_dec = 0;                                   //Variable para almacenar el número decimal resultante.
    size_t len = strlen(binary);                        //Longitud del número binario para iterar sobre cada dígito.
    for (int i = 0; i < len; i++) {                        //Iteramos para calcular el valor de cada digito.
        if (binary[i] == '1') {              
            num_dec = num_dec + pow(2, len - 1 - i); //Desplazamos el puntero y sumamos la potencia de 2 correspondiente al encontrar un 1.
        }
    }
    if (sign && binary[0] == '1') {                       //Unsigned o Signed.
        num_dec = -num_dec + pow(2, len - 1); //Si es con signo y el primer dígito es 1, ajustamos el resultado para representar el número negativo
    }
    return num_dec;
}
/*
=========================
  void print_reverse_array:
   imprime los elementos de un array en orden inverso
  parametros:
        array: puntero al inicio del array a imprimir
        data_type: tamaño en bytes del tipo de dato de los elementos del array
        array_size: cantidad de elementos en el array
  retorno:      
        no retorna nada, pero imprime los elementos del array en orden inverso
=========================
*/
void print_reverse_array(void *array,data_type_t type,size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                 //Puntero generico que recorre el array por byte. 
    printf("Array en orden inverso:\n{");   //Marca el inicio de el array invertido.
    for (int i = array_size - 1; i >= 0; i--) {    //Iteramos el array restando 1 al indice.
        uint8_t *actual = pa + (i * get_size(type));    //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
         print_element(*(char **)actual,  type);  //Imprimimos el valor del elemento actual teniendo en cuenta que es un char si es otra cosa ocurrica un ERROR.
    }
    printf("}\n");
    }
/*
=========================
  max_index:
   encuentra el índice del valor máximo en un array
  parametros:
        array: puntero al inicio del array a analizar
        data_type: tamaño en bytes del tipo de dato de los elementos del array
        array_size: cantidad de elementos en el array
  retorno:      
        no retorna nada, pero imprime el índice y el valor máximo encontrado
=========================
*/
int max_index(void *array, data_type_t type, size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                            //Puntero generico que recorre el array por byte. 
    int  max_val = *(int *)pa;                          //Inicializamos el valor máximo con el primer elemento del array.
    int  max_indx = 0;                                     //Definimos variable para almacenar el indice.
    
    if (array_size == 0 || array == NULL){
        return -1;
    };

    for (size_t i = 1; i < array_size; i++){                   //Interamos para recorrer el array y comparar.       
        int *val_ptr = (int *)(pa + (i * get_size(type)));  //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
        int  valor_actual = *val_ptr;
        if (valor_actual > max_val) {                          //Almacenamos si el valor actual es mayor que el max anterior.
            max_val = valor_actual;
            max_indx = i;                                      //Almacenamos el indice del nuevo valor máximo.
        }
      }
        print_element(&max_indx,  type);                   //Imprimimos el indice del valor máximo encontrado.
        print_element(&max_val,  type);  
        return max_indx;                                        //Imprimimos el valor máximo encontrado %d para int32_t.
    }
/*
=========================
  min_index:
   encuentra el índice del valor máximo en un array
  parametros:
        array: puntero al inicio del array a analizar
        data_type: tamaño en bytes del tipo de dato de los elementos del array
        array_size: cantidad de elementos en el array
  retorno:      
        no retorna nada, pero imprime el índice y el valor mínimo encontrado
=========================
*/
int min_index(void *array, data_type_t type, size_t array_size) { //Analoga a max_index pero para encontrar el valor mínimo y su indice.
    uint8_t *pa = (uint8_t *)array;                            
    int  min_val = *(int *)pa;                          
    int  min_indx = 0;                                         

    if (array_size == 0 || array == NULL){
        return -1;
    };

    for (size_t i = 1; i < array_size; i++){                    
        int *val_ptr = (int *)(pa + (i * get_size(type)));  
        int  valor_actual = *val_ptr;                       
        if (valor_actual < min_val) {
            min_val = valor_actual;
            min_indx = i;
        }
      }
        print_element(&min_indx,  type);                   //Imprimimos el indice del valor máximo encontrado.
        print_element(&min_val,  type);                 //Imprimimos el valor máximo encontrado %d para int32_t.
        return min_indx;  
    }

/*
=========================
  matriz_t *matrix_sub:
   resta dos matrices
  parametros:
      A: matriz de entrada
      B: matriz de entrada
  retorno:
      puntero a la matriz resultado
=========================
*/
matriz_t *matrix_sub (matriz_t A,matriz_t B){
    size_t n_filas = A.rows;             //Definimos variables para almacenar el número de filas y columnas de las matrices A y B.
    size_t n_columna = A.cols;

    if (n_filas != B.rows || n_columna != B.cols) {
        return NULL;              // Retorna error por que la resta de matrices solo es posible si ambas tienen la misma cantidad de filas y columnas.
    }
 
	matriz_t *matriz_resultado = malloc(sizeof(matriz_t)); //Asignamos memoria para la matriz resultado.
   
    if (matriz_resultado == NULL)
    {
        return NULL; // no hay memoria disponible,se aprendio de el video de lista enlazada que hace esta verificacion de si se reservo bien la memoria dinamica o no
    }   

    matriz_resultado->rows = n_filas;
    matriz_resultado->cols = n_columna;

    matriz_resultado->data = malloc(A.rows * sizeof(int16_t *));//Asignamos memoria para las filas de la matriz resultado.
    if (matriz_resultado->data == NULL) {
        free(matriz_resultado);
        return NULL;
    }

    for (size_t i = 0; i < A.rows; i++) {
        matriz_resultado->data[i] = malloc(A.cols * sizeof(int16_t));
        if (matriz_resultado->data[i] == NULL) {
            // Si falla, liberar toda la memoria previa para evitar "leaks"
            for (size_t k = 0; k < i; k++) {
                free(matriz_resultado->data[k]);
            }
            free(matriz_resultado->data);
            free(matriz_resultado);
            return NULL;
        }
    }
    
	for (int i = 0; i < n_filas; i++) {  //Recorremos las 2 matrices y las restamos con 2 for anidados.
		for (int j = 0; j < n_columna; j++) {
			matriz_resultado->data[i][j] = A.data[i][j] - B.data[i][j];
		}
	}
	return matriz_resultado;            //Retornamos el resultado de la resta de las matrices
}                                       //Importante liberar la memoria asignada.
 

/*
 ========================= 
  swap:
  cambia dos elementos de cualquier tipo usando punteros genericos.
  parametros:
      elem_1: puntero al primer elemento
      elem_2: puntero al segundo elemento
      data_type: tamaño en bytes del tipo de dato
  retorno:
      0 si el swapeo se realizo correctamente, -1 si hubo algun error
=========================
*/
int swap(void *elem_1, void *elem_2, size_t data_type)//esto no esta hecho para que las variabels sean de distinto tama;o porque hay un solo parametro size_t data_type que guarda cuantos bytes ocupa el dato
//El pdf aclara:Las funciones que reciben void* deben usar el parámetro data_type
//(sizeof del tipo) para aritmética de punteros. Osea que no se sabe que tipo de dato es solo el tama;o que ocupa
{
    char *a;//porque ocupa un byte para cambiar los elementos byte a byte (la undiad mas chica para direccionar memoria no puedo ir de a medio byte digamos)
    char *b;
    char temp;

    if (elem_1 == NULL || elem_2 == NULL || data_type == 0)//si el puntero no apunta a nada o el dato tiene un tama;o de 0 que no puede ser ,el dato no ocuparia nada de espacio
    {
        return -1;
    }
    //void *elem_ es un puntero sin tipo no se de a cuantos bytes se mueve el puntero entonces no puedo hacer elem_1[i]
    a = (char *)elem_1;//esto es un casteo para que a apunte a la misma direccion que elem_1 pero movineo el puntero de a bytes,con vpid *elem_ anda a saber de a cuantos bytes es el puntero original elem_
    b = (char *)elem_2;

    for (int i = 0; i < data_type; i++)
    {
        temp = a[i];//como a es un puntero,a[i] accede al byte numero i del dato y lo cambia con el mismo numero de byte de b 
        a[i] = b[i];
        b[i] = temp;
    }

    return 0;
}

/*
========================= 
  consonantes:
  cuenta la cantidad de consonantes en una string
  parametros:
      string: cadena a analizar
  retorno:
      cantidad de consonantes o -1 si el puntero es NULL
=========================
*/
int consonantes(char *string)
{
    int contador = 0;
    char *consonantes = "bcdfghjklmnñpqrstvwxyzBCDFGHJKLMNÑPQRSTVWXYZ";

    if (string == NULL)
        return -1;//si el puntero no apunta a una direccion valida

    while (*string != '\0')//recorro la string
    {
        int es_consonante = 0;//flag

        for (int i = 0; consonantes[i] != '\0'; i++)//recorro la "lista" de consonantes
        {
            if (*string == consonantes[i])//si mi caracter actual es igual a una consonante de la "lista"
            {
                es_consonante = 1; // marco que es consonante activando la flag
            }
        }

        if (es_consonante == 1)
        {
            contador++; 
        }

        string++;
    }

    return contador;
}


/*
=========================
  vocales:
  cuenta la cantidad de vocales presentes en un string
  parametros:
      string: cadena a analizar
  retorno:
      cantidad de vocales o -1 si el puntero es NULL
=========================
*/
int vocales(char *string)
{
    int contador = 0;

    char *vocales = "aeiouAEIOU";

    if (string == NULL)
    {
        return -1;
    }

    while (*string != '\0')
    {
        int es_vocal = 0;

        for (int i = 0; vocales[i] != '\0'; i++)
        {
            if (*string == vocales[i])
            {
                es_vocal = 1;
            }
        }

        if (es_vocal == 1)
        {
            contador++;
        }

        string++;
    }

    return contador; //No se tiene en cuenta las vocales con tilde.
}

/*
=========================
  reverse_string:
  retorna una copia invertida del string recibido
  parametros:
      string: cadena a invertir
  retorno:
      puntero a memoria dinamica con la cadena invertida,
      o NULL si hubo error
=========================
*/
char * reverse_string(char *string)//la funcion pide reotrnar un puntero char a la string alreves
{
    int largo = 0;//daria problema ponerlo como int si la string tiene mas de 2millones de caracteres ,numero que no se puede guardar en 4 bytes
    int i = 0;
    char *alreves;//puntero donde guardar la string invertida

    if (string == NULL)//si la string esta vacia 
    {
        return NULL;
    }

    while (string[largo] != '\0')
    {
        largo++;
    }
    //distinto a mi funcion original que yo le decia el largo de la array aca se recibe un puntero que no se sabe cuantos caracteres tiene la array a la que apunta
    //entonces hay que recorrer la string hasta llegar al final 

    alreves = malloc((largo + 1) * sizeof(char));//segun diapositivas pagina 53
    //largo + 1 para incluir el \0
    // esto dice que alreves sea el puntero al que apunta la reserva de memoria dinamica para la nueva string invertida de tama;o largo + 1 para incluir el '\0' del final
    if (alreves == NULL)
    {
        return NULL; // no hay memoria disponible,se aprendio de el video de lista enlazada que hace esta verificacion de si se reservo bien la memoria dinamica o no
    }
    //string orden = 012345
    while (string[i] != '\0')
    {
        alreves[largo - 1 - i] = string[i];//empiezo en largo - 1 para que deje el ultimo caracter libre para cerrar la string con \0
        i++;
    }
    alreves[largo] = '\0';//agrego el final de la string a mano 

    return alreves;
    //La memoria reservada con malloc tiene que  liberarse con free() fuera de la funcion (cuando se la llame)
}

/*
=========================
  string_length:
  calcula la longitud de un string sin usar librerias estandar
  parametros:
      string: cadena a medir
  retorno:
      longitud de la cadena o -1 si el puntero es NULL
=========================
*/
int32_t string_length(char *string)
{
    int32_t contador = 0;

    if (string == NULL)
    {
        return -1;
    }

    while (*string != '\0')
    {
        string++;
        contador++;
    }

    return contador;
}

/*
=========================
  string_words:
  cuenta la cantidad de palabras de un string
  parametros:
      string: cadena a analizar
  retorno:
      cantidad de palabras o -1 si el puntero es NULL
=========================
*/
int32_t string_words(char *string)
{
    char *inicio = string;//pongo  un puntero que apunte al primer caracter de la string
    int32_t palabras = 0;

    if (string == NULL) // si el putnero no apunta a nada
    {
        return -1;
    }

    while (*string != '\0')
    {
        if (*string != ' ' && (string == inicio || *(string - 1) == ' '))
        // si el caracter es disitnto de un espacio y estamos en el primer caracter o el carcater anterior a ese es un espacio entonces se tiene una palabra
        {
            palabras++;//suma una palabra
        }
        string++;//puntero apunta al siguiente caracter
    }

    return palabras;
}

/*
========================
  string_copy:
  copia el contenido de source en destination sin usar librerias estandar
  parametros:
      source: cadena origen
      destination: cadena destino
  retorno:
      0 si la copia fue correcta, -1 si hubo error
========================
*/
int string_copy(char *source, char *destination)//ojo esto no te asegura que el destino tenga espacio para guardar los caracteres del source.Se supone que se reservo al memoria dinamica suficiente (para el /0 dle final y todo)
//Deberia haber un parametro del tama;o del destino 
{
    int i = 0;

    if (source == NULL || destination == NULL )//si alguno de los dos punteros no apunta a nada osea si hay un error con ellos devuelve -1
    {
        return -1;
    }
//sizeof punteros 
    while (source[i] != '\0')
    {
        destination[i] = source[i];//copia caracter por caracter
        i++;
    }

    destination[i] = '\0';//para finalizar la string

    return 0;
}
/*  
=========================
  print_coeff_t:
  imprime todos los atributos de una variable de tipo coeff_t
  parametros:
      coef: estructura con los coeficientes a, b y c
  retorno:
      no retorna nada
=========================
*/
void print_coeff_t(coeff_t coef)
{
    printf("a = %d, b = %d, c = %d\n", coef.a, coef.b, coef.c);
}

/*
  =========================
  print_root_t:
  imprime todos los atributos de una variable de tipo root_t
  parametros:
      root: estructura con las dos raices y si son complejas o no
  retorno:
      no retorna nada
=========================
*/
void print_root_t(root_t root)
{
    printf("real1 = %d, imag1 = %d, real2 = %d, imag2 = %d, complex = %d\n",
           root.real1, root.imag1, root.real2, root.imag2, root.complex);
}

/*
  =========================
  print_complex_t:
  imprime todos los atributos de una variable de tipo complex_t
  parametros:
      c: estructura con parte real e imaginaria
  retorno:
      no retorna nada
=========================
*/
void print_complex_t(complex_t c)
{
    printf("real = %d, imag = %d\n", c.real, c.imag);
}

/*
=========================
  print_date_t:
  imprime todos los atributos de una variable de tipo date_t
  parametros:
      date: estructura con dia, mes y anio
  retorno:
      no retorna nada
=========================
*/
void print_date_t(date_t date)
{
    printf("day = %d, month = %d, year = %d\n", date.day, date.month, date.year);
}

/*
  =========================
  print_matriz_t:
  imprime todos los atributos de una variable de tipo matriz_t
  parametros:
      matriz: estructura con los datos de la matriz, cantidad de filas y columnas
  retorno:
      no retorna nada
=========================
*/
void print_matriz_t(matriz_t matriz)
{
    if (matriz.data == NULL)
    {
        printf("Error: matriz.data es NULL\n");//si el puntero no apunta a un espacio de memoria valido osea si no hay matriz creada 
        return;
    }

    if (matriz.rows <= 0 || matriz.cols <= 0)
    {
        printf("Error: dimensiones invalidas\n");
        return;
    }

    printf("rows = %zu, cols = %zu\n", matriz.rows, matriz.cols);

    for (int i = 0; i < matriz.rows; i++)// recorre filas
    {
        if (matriz.data[i] == NULL)
        {
            printf("Error: fila %d es NULL\n", i);//chequea que la fila i exista 
            return;
        }

        for (int j = 0; j < matriz.cols; j++)// recorre columnas
        {
            printf("%d ", matriz.data[i][j]);// imprimo cada numero
        }

        printf("\n");
    }
}
/*
  =========================
  ind_in_string:
  busca la primera ocurrencia de needle en haystack
  parametros:
      haystack: cadena donde buscar
      needle: cadena a buscar
  retorno:
      índice de la primera ocurrencia o -1 si no se encuentra
=========================
*/
int find_in_string(char *haystack, char *needle){
    int largo_haystack = strlen(haystack); //Guardo la longitud de haystack
    int largo_needle = strlen(needle); //Guardo la longitud del needle
    int indice; //Defino el indice donde voy a guardar la direccion de needle
    int aux; // variable auxiliar


    for (indice=0; indice<=largo_haystack-largo_needle;indice++){
        int coincide=1;//valor para comprobar si coincide el needle con el haystack
        for (aux=0;aux < largo_needle; aux++){
            if (haystack[indice + aux] != needle[aux]){
                coincide=0;
                break;//revisar
            }
        }
        if (coincide == 1){
            return indice;
        }
    }
    return -1; 
}
/*
  =========================
  string_to_caps:
  convierte una cadena a mayúsculas
  parametros:
      string: cadena a convertir
  retorno:
        no retorna nada, pero modifica la cadena original a mayúsculas y la imprime.
=========================
*/
void string_to_caps(char *string){
    int indice;//defino un indice que va a representar la posicion en el string
    //inicio un bucle for que termina cuando se encuentra '\0'
    char mayus[]= "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
    char mins[]="abcdefghijklmnñopqrstuvwxyz";
    for (indice=0;string[indice] != '\0'; indice++){
        int aux1;//defino un indice auxiliar, que representa la pocicion en el listado de minusculas
        for(aux1=0; mins[aux1] != '\0'; aux1++){
            if (string[indice]==mins[aux1]){//comparo la letra [i] del string con todas las minusculas
                string[indice]=mayus[aux1];//si la letra es mayuscula, la reemplazo con la letra en minuscula
            }
        }    
    }
    printf("%s", string);
}
/*
  =========================
  string_to_mins:
  convierte una cadena a minúsculas
  parametros:
      string: cadena a convertir
  retorno:
        no retorna nada, pero modifica la cadena original a minúsculas y la imprime.
=========================
*/
void string_to_mins(char *string){
    int indice;//defino un indice que va a representar la posicion en el string
    //inicio un bucle for que termina cuando se encuentra '\0'
    char mayus[]= "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
    char mins[]="abcdefghijklmnñopqrstuvwxyz";
    for (indice=0;string[indice] != '\0'; indice++){
        int aux1; //defino un indice auxiliar, que representa la pocicion en el listado de mayusculas
        for(aux1=0; mayus[aux1] != '\0'; aux1++){
            if (string[indice]==mayus[aux1]){//comparo la letra [i] del string con todas las mayusculas 
                string[indice]=mins[aux1];//si la letra es mayuscula, la reemplazo con la letra en minuscula
            }
        }
    }
    printf("%s", string);
}
/*
  =========================
  complex_t *sum:
  suma dos números complejos
  parametros:
      a: primer número complejo
      b: segundo número complejo
  retorno:
        puntero a un número complejo con el resultado de la suma
=========================
*/
complex_t *sum(complex_t a, complex_t b){
    complex_t *resultado = malloc(sizeof(complex_t));
    resultado->real = a.real + b.real;//calculo y guardo la parte real del resultado
    resultado->imag = a.imag + b.imag;//calculo y guardo la parte imaginaria del resultado
    return resultado;
}
/*
  =========================
  complex_t *prod:
  multiplica dos números complejos
  parametros:
      a: primer número complejo
      b: segundo número complejo
  retorno:
        puntero a un número complejo con el resultado de la multiplicación
=========================
*/
complex_t *prod(complex_t a, complex_t b){
    // (a+bi)*(c+di)=a*c + a*di + bi*c + bi*di (como resolver 
    //una mutiplicacion de numeros complejos)
    complex_t *resultado = malloc(sizeof(complex_t));
    resultado->real= (a.real*b.real)-(a.imag*b.imag);//calculo y guardo la parte real del resultado
    resultado->imag=(a.real*b.imag)+(b.real*a.imag);//calculo y guardo la parte imaginaria del resultado
    return resultado;
}
/*
  =========================
  chequear_si_bisiesto(auxiliar de days_left):
  chequea si un año es bisiesto
  parametros:
      año: año a verificar
  retorno:
        1 si es bisiesto, 0 si no
=========================
*/
int chequear_si_bisiesto(int año){
    int bisiesto;//1 si es bisiesto, 0 si no;
    if (año % 4==0 && año %100 !=0 || año %400 == 0){
        bisiesto=1;
    }else{
        bisiesto=0;
    }
    return bisiesto;
}
/*
  =========================
  largo_del_mes(auxiliar de days_left):
  calcula el largo de un mes dado su número y el año
  parametros:
      month: número del mes (1-12)
      year: año
  (Segun el mes)
  retorno:
        cantidad de días en el mes
=========================
*/
int largo_del_mes(int month, int year){
    if (month==2){
        if(chequear_si_bisiesto(year)){
            return 29;
        }else{
            return 28;
        }
    }else if (month==4 || month==6 || month==9 || month==11){
        return 30;
    }else{
        return 31;
    }
}
/*
  =========================
  lo_que_va_del_año(auxiliar de days_left):
  calcula los días que han pasado desde el inicio del año hasta una fecha dada
  parametros:
      fecha: fecha a verificar
  retorno:
        cantidad de días que han pasado desde el inicio del año
=========================
*/
int lo_que_va_del_año(date_t fecha){
    int dias=0;
    int i;
    for (i=1;i<fecha.month;i++){
        dias+=largo_del_mes(i, fecha.year);
    }
    dias+=fecha.day;
    return dias;
}
/*
  =========================
  days_left:
  Uso de lo_que_va_del_año y chequear_si_bisiesto.
  calcula los días que faltan entre dos fechas
  parametros:
      start: fecha de inicio
      finish: fecha de finalización
  retorno:
        cantidad de días entre las dos fechas, o un número negativo si la fecha de inicio es mayor a la fecha de finalización
=========================
*/
int days_left(date_t start, date_t finish){
    int start_mayor_a_finish=0;
    if (start.year>finish.year || (start.year==finish.year && start.month>finish.month) || 
    (start.year==finish.year && start.month==finish.month && start.day>finish.day)){ 
        // Reviso que fecha es mayor que la otra, 
        //y si la de inicio es mayor a la final, las intercambio
        date_t aux=start;
        start=finish;
        finish=aux;
        start_mayor_a_finish=1;
    }
    // Calculo de diferencia y años bisiestos
    int i=0;
    int dias=0;
        if (start.year==finish.year){ //si ambos años son los mismos, calculo los dias que pasaron
        dias= lo_que_va_del_año(finish)-lo_que_va_del_año(start);
    }else{
    for(i=start.year;i<finish.year;i++){ //creo un indice que va desde el año menor
        //al año mayor, revisando si es bisiesto o no, y sumando los dias acordes 
        if(chequear_si_bisiesto(i)){
            dias+=366;
        }else{
            dias+=365;
        }
    }
    //resto los dias que ya pasaron del año de inicio, y sumo los dias que pasaron del año de finalización
    dias=dias-(lo_que_va_del_año(start))+(lo_que_va_del_año(finish));
    if (start_mayor_a_finish==1){ //si la fecha de inicio era mayor a la de finalización, el resultado es negativo
        dias=-dias;
    }
}
    return dias;
}

