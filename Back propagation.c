#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Número de neuronas por capa

#define cantidadEntrada 10
#define cantidadOculta1 20
#define cantidadSalida 5


double sigmoide(double,double);

int main(){
    //Cada capa arreglada en matrices
    double capaEntrada[cantidadEntrada];
    double capaOculta1[cantidadOculta1];
    double capaSalida[cantidadSalida];
    capaEntrada[0] = 1;
    capaOculta1[0] = 1;
    
    //Los pesos de cada capa arreglados en matrices bidimensionales
    double pesosEntrada[cantidadEntrada];
    double pesosEntradaOculta1[cantidadEntrada][cantidadOculta1];
    double pesosOculta1Salida[cantidadOculta1][cantidadSalida];

    return 0;

}


//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoide(double * X, double * W){

    double neto = 0;
    double exponente = 0;
    double result;
    


    result = (1/(1+neto));

    return result;

}