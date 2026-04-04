#include "global.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

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

complex_t *sum(complex_t a, complex_t b){
    complex_t *resultado = malloc(sizeof(complex_t));
    resultado->real = a.real + b.real;//calculo y guardo la parte real del resultado
    resultado->imag = a.imag + b.imag;//calculo y guardo la parte imaginaria del resultado
    return resultado;
}

complex_t *prod(complex_t a, complex_t b){
    // (a+bi)*(c+di)=a*c + a*di + bi*c + bi*di (como resolver 
    //una mutiplicacion de numeros complejos)
    complex_t *resultado = malloc(sizeof(complex_t));
    resultado->real= (a.real*b.real)-(a.imag*b.imag);//calculo y guardo la parte real del resultado
    resultado->imag=(a.real*b.imag)+(b.real*a.imag);//calculo y guardo la parte imaginaria del resultado
    return resultado;
}

int chequear_si_bisiesto(int año){
    int bisiesto;//1 si es bisiesto, 0 si no;
    if (año % 4==0 && año %100 !=0 || año %400 == 0){
        bisiesto=1;
    }else{
        bisiesto=0;
    }
    return bisiesto;
}

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

int lo_que_va_del_año(date_t fecha){
    int dias=0;
    int i;
    for (i=1;i<fecha.month;i++){
        dias+=largo_del_mes(i, fecha.year);
    }
    dias+=fecha.day;
    return dias;
}

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

