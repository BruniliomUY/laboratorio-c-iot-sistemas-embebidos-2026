#include "global.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


root_t* eq_solver(coeff_t *coeficientes) {
    root_t *solucion = malloc(sizeof(root_t));  // Asignamos var local para almacenar la solución
    
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

int32_t bin2dec(char *binary,bool sign) {
    int32_t num_dec = 0;                                   //Variable para almacenar el número decimal resultante.
    size_t len = strlen(binary);                        //Longitud del número binario para iterar sobre cada dígito.

    for (int i = 0; i < len; i++) {                        //Iteramos para calcular el valor de cada digito.
        if (binary[i] == '1') {              
            num_dec = num_dec + pow(2, len - 1 - i); //Desplazamos el puntero y sumamos la potencia de 2 correspondiente al encontrar un 1.
        }
    }
    if (sign && binary[0] == '1') {                       //Unsigned o Signed.
        num_dec = -num_dec;
    }
    return num_dec;
}

void print_reverse_array(void *array,size_t data_type,size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                 //Puntero generico que recorre el array por byte. 
    printf("Array en orden inverso:\n{");   //Marca el inicio de el array invertido.
    for (int i = array_size - 1; i >= 0; i--) {    //Iteramos el array restando 1 al indice.
        uint8_t *actual = pa + (i * data_type);    //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
        printf("%s", *(char **)actual);    //Imprimimos el valor del elemento actual.
    }
    printf("}\n");
    }

void max_index(void *array, size_t data_type, size_t array_size) {
    uint8_t *pa = (uint8_t *)array;                            //Puntero generico que recorre el array por byte. 
    int32_t max_val = *(int32_t *)pa;                          //Inicializamos el valor máximo con el primer elemento del array.
    int  max_indx = 0;   $//VER                                    //Definimos variable para almacenar el indice.
             
    for (size_t i = 1; i < array_size; i++){                   //Interamos para recorrer el array y comparar.       
        int32_t *val_ptr = (int32_t *)(pa + (i * data_type));  //Calculamos la dirección del elemento actual teniendo en cuenta el tamaño del tipo de dato.
        int32_t  valor_actual = *val_ptr;
        if (valor_actual > max_val) {                          //Almacenamos si el valor actual es mayor que el max anterior.
            max_val = valor_actual;
            max_indx = i;                                      //Almacenamos el indice del nuevo valor máximo.
        }
      }
        printf("Indice max: %d\n", max_indx);           //Imprimimos el indice del valor máximo encontrado.
        printf("Valor max: %d\n", max_val);            //Imprimimos el valor máximo encontrado %d para int32_t.
    }

void min_index(void *array, size_t data_type, size_t array_size) { //Analoga a max_index pero para encontrar el valor mínimo y su indice.
    uint8_t *pa = (uint8_t *)array;                            
    int32_t min_val = *(int32_t *)pa;                          
    int  min_indx = 0;        $//VER                                  

    for (size_t i = 1; i < array_size; i++){                    
        int32_t *val_ptr = (int32_t *)(pa + (i * data_type));  
        int32_t  valor_actual = *val_ptr;                       
        if (valor_actual < min_val) {
            min_val = valor_actual;
            min_indx = i;
        }
      }
        printf("Indice min: %d\n", min_indx);
        printf("Valor min: %d\n", min_val);
    }

matriz_t *matrix_sub (matriz_t A,matriz_t B){
    size_t n_filas = A.rows;             //Definimos variables para almacenar el número de filas y columnas de las matrices A y B.
    size_t n_columna = A.cols;

    if (n_filas != B.rows || n_columna != B.cols) {
        return NULL;              // Retorna error por que la resta de matrices solo es posible si ambas tienen la misma cantidad de filas y columnas.
    }
 
	matriz_t *matriz_resultado = malloc(sizeof(matriz_t)); //Asignamos memoria para la matriz resultado.
    matriz_resultado->rows = n_filas;
    matriz_resultado->cols = n_columna;
    
	for (int i = 0; i < n_filas; i++) {  //Recorremos las 2 matrices y las restamos con 2 for anidados.
		for (int j = 0; j < n_columna; j++) {
			matriz_resultado->data[i][j] = A.data[i][j] - B.data[i][j];
		}
	}
	return matriz_resultado;            //Retornamos el resultado de la resta de las matrices
}                                       //Importante liberar la memoria asignada.
 

