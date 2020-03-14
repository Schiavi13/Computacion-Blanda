#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Número de neuronas por capa

#define cantidadEntrada 7
#define cantidadSalida 4
#define cantidadOculta1 6       //Se utilizara la regla piramidal con 3 capas, es decir, una sola capa oculta sqrt(7*4)=5.2 
                                //se decide aproximar al entero superior



double sigmoide(double[],int,double[][1],int);
double calcularCapa(double[],int,double[][1],int);


int main(){
    /*Patrones de entrada de un 7 segmentos digital
               a
            //////              
         /          /
         /          /
      f  /          /  b
         /          /
         /     g    / 
            //////
         /          /
         /          /
      e  /          /  c
         /          /
         /          /
            //////
               d
    */
    double patrones_entrada[10][7] = {{1,1,1,1,1,1,0},  //0     //dispuestos en este orden a,b,c,d,e,f,g
                                      {0,1,1,0,0,0,0},  //1
                                      {1,1,0,1,1,0,1},  //2
                                      {1,1,1,1,0,0,1},  //3
                                      {0,1,1,0,0,1,1},  //4
                                      {1,0,1,1,0,1,1},  //5
                                      {1,0,1,1,1,1,1},  //6
                                      {1,1,1,0,0,0,1},  //7
                                      {1,1,1,1,1,1,1},  //8
                                      {1,1,1,1,0,1,1},  //9
                                      };
    
    //Las respuestas del problema seran en binario
    double patrones_salida[10][4] = {{0,0,0,0}, // cero en binario
                                     {0,0,0,1}, // uno en binario
                                     {0,0,1,0}, // dos en binario
                                     {0,0,1,1}, // tres en binario
                                     {0,1,0,0}, // cuatro en binario
                                     {0,1,0,1}, // cinco en binario
                                     {0,1,1,0}, // seis en binario
                                     {0,1,1,1}, // siete en binario
                                     {1,0,0,0}, // ocho en binario
                                     {1,0,0,1}, // nueve en binario
                                     };
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
double sigmoide(double  entradas[], int tamanoEntradas, double  pesos[][1], int numeroNeurona){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0,i<tamanoEntradas,i++){
        exponente = exponente + (entradas[i]*pesos[i][numeroNeurona-1]);
    }

    neto=exp(exponente*(-1));
    result = (1/(1+neto));


    //Aproximacion del resultado
    if(result>=0.9)         //A uno si es mayor que 0.9
        result = 1;
    else if(result<=0.1)    //A cero si es menor que 0.1 
        result = 0;
    return result;          //de lo contrario no se aproxima
    
}



//Función para efectuar los calcuos de una capa
void calcularValorCapa(double  entradas[], int tamanoEntrada, double  pesos[][1], int cantidadNeuronas){
    //Realiza el calculo para cada neurona de la capa
    for(int i=0;i<cantidadNeuronas,i++)
        sigmoide(entradas,tamanoEntrada,pesos,i);
}


double error(){

}


void calcularErrorCapa(){

}




//consultar valores intermedios de la función sigmoide