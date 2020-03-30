#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



//Número de neuronas por capa

#define cantidadEntrada 8
#define cantidadSalida 5
#define cantidadOculta 6       //Se utilizara la regla piramidal con 3 capas, es decir, una sola capa oculta sqrt(7*4)=5.2 
                                //se decide aproximar al entero superior


void inicializarPesosEntradaOculta(double[][cantidadOculta],int);
void inicializarPesosOcultaSalida(double[][cantidadSalida],int);
/*
void mostrarPesosEntradaOculta(double[][cantidadOculta],int);
void mostrarPesosOcultaSalida(double[][cantidadSalida],int);
*/
double sigmoideOculta(double[],int,double[][cantidadOculta]);
double sigmoideSalida(double[],int,double[][cantidadSalida]);
double calcularValorCapaOculta(double[],int,double[][cantidadOculta],int);
double calcularValorCapaSalida(double[],int,double[][cantidadSalida],int);


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
    double capaEntrada[cantidadEntrada];
    double capaOculta1[cantidadOculta];
    double capaSalida[cantidadSalida];
    //Se inicializa el X0 y el H0 en 1
    capaEntrada[0] = 1;
    capaOculta1[0] = 1;
    
    //Los pesos de cada capa arreglados en matrices bidimensionales
    double pesosEntradaOculta[cantidadEntrada][cantidadOculta];
    double pesosOcultaSalida[cantidadOculta][cantidadSalida];

    srand(time(NULL));
    inicializarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    inicializarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    /*
    mostrarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    mostrarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    */
    return 0;

}


void inicializarPesosEntradaOculta(double pesos[][cantidadOculta], int cantidadNeuronasEntrada){
    int numero = 0;
    double resultado = 0;

    for(int i=0;i<cantidadNeuronasEntrada;i++){
        for(int j=0;j<cantidadOculta;j++){
            numero = 0 + rand() %2000;
            numero = numero - 1000;
            resultado = (double) numero/10000;
            pesos[i][j] = resultado;
        }
    }
}

void inicializarPesosOcultaSalida(double pesos[][cantidadSalida], int cantidadNeuronasEntrada){
    int numero = 0;
    double resultado = 0;

    for(int i=0;i<cantidadNeuronasEntrada;i++){
        for(int j=0;j<cantidadSalida;j++){
            numero = 0 + rand() %2000;
            numero = numero - 1000;
            resultado = (double) numero/10000;
            pesos[i][j] = resultado;
        }
    }
}

/*
void mostrarPesosEntradaOculta(double pesos[][cantidadOculta], int cantidaNeuronasEntrada){
    for(int i=0;i<cantidaNeuronasEntrada;i++){
        for(int j=0;j<cantidadOculta;j++){
            printf("%f\n",pesos[i][j]);
        }
    }
}


void mostrarPesosOcultaSalida(double pesos[][cantidadSalida], int cantidaNeuronasEntrada){
    for(int i=0;i<cantidaNeuronasEntrada;i++){
        for(int j=0;j<cantidadSalida;j++){
            printf("%f\n",pesos[i][j]);
        }
    }
}
*/

//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoideOculta(double  entradas[], int tamanoEntradas, double  pesos[][cantidadOculta]){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0;i<tamanoEntradas;i++){
        exponente = exponente + (entradas[i]*pesos[i][cantidadOculta-1]);
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

//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoideSalida(double  entradas[], int tamanoEntradas, double  pesos[][cantidadSalida]){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0;i<tamanoEntradas;i++){
        exponente = exponente + (entradas[i]*pesos[i][cantidadSalida-1]);
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
void calcularValorCapaOculta(double  entradas[], int tamanoEntrada, double  pesos[][cantidadOculta]){
    //Realiza el calculo para cada neurona de la capa
    for(int i=0;i<cantidadOculta;i++)
        sigmoideOculta(entradas,tamanoEntrada,pesos);
}


//Función para efectuar los calcuos de una capa
void calcularValorCapaSalida(double  entradas[], int tamanoEntrada, double  pesos[][cantidadSalida]){
    //Realiza el calculo para cada neurona de la capa
    for(int i=0;i<cantidadSalida;i++)
        sigmoideSalida(entradas,tamanoEntrada,pesos);
}


double error(){

}


void calcularErrorCapa(){

}




//consultar valores intermedios de la función sigmoide
