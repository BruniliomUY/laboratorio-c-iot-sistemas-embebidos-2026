#include "global.h"

#include <stdio.h>//para los printf
#include <stdlib.h>//para la memoria dinamica

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
    int vocales = 0;

    if (string == NULL)
    {
        return -1;
    }

    while (*string != '\0')
    {
        if (*string == 'a' || *string == 'e' || *string == 'i' || *string == 'o' || *string == 'u' || *string == 'A' || *string == 'E' || *string == 'I' || *string == 'O' || *string == 'U')//si el valor al que apunta el puntero e suna vocla en mayusucla o minuscula suma uno al contador
        {
            vocales++;
        }
        string++;//equivalente a string = string + 1 osea avanza al proximo caracter del array
    }

    return vocales;
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
