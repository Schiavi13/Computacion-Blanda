#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Número de neuronas por capa

#define cantidadEntrada 10
#define cantidadOculta1 20
#define cantidadSalida 5


double sigmoide(int,int);
double neto(double,double);
double calcularCapa(double*,int,double*,int);

int main(){
    //Cada capa arreglada en matrices
    double capaEntrada[cantidadEntrada + 1];
    double capaOculta1[cantidadOculta1 + 1];
    double capaSalida[cantidadSalida];
    //Se inicializa el X0 y el H0 en 1
    capaEntrada[0] = 1;
    capaOculta1[0] = 1;
    
    //Los pesos de cada capa arreglados en matrices bidimensionales
    double pesosEntradaOculta1[cantidadEntrada][cantidadOculta1];
    double pesosOculta1Salida[cantidadOculta1][cantidadSalida];
    //Se inicializan los pesos en 1 para que pasen el X0 y el H0
    pesosEntradaOculta1[0] = 1;
    pesosOculta1Salida[0] = 1;

    return 0;

}


//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoide(double * entradas, int tamanoEntradas, double * pesos, int numeroNeurona){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0,i<tamanoEntradas,i++){
        exponente = exponente + (entradas[i]*pesos[i][numeroNeurona]);
    }

    neto=exp(exponente*(-1));
    result = (1/(1+neto));

    return result;
}



//Función para efectuar los calcuos de una capa
void calcularCapa(double * entradas, int tamanoEntrada, double * pesos, int cantidadNeuronas){
    //Realiza el calculo para cada neurona de la capa
    for(int i=0;i<cantidadNeuronas,i++)
        sigmoide(entradas,tamanoEntrada,pesos,i);
}




//consultar valores intermedios de la función sigmoide