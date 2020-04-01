#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



//Numero de neuronas por capa

#define cantidadEntrada 8
#define cantidadSalida 4
#define cantidadOculta 7      //Se utilizara la regla piramidal con 3 capas, es decir, una sola capa oculta sqrt(8*4)=5.2 
                                //se decide aproximar al entero superior y se suma una neurona que sera h0
#define factor 0.1            //factor de aprendizaje arbitrario

void inicializarPesosEntradaOculta(double[][cantidadOculta],int);
void inicializarPesosOcultaSalida(double[][cantidadSalida],int);
void mostrarPesosEntradaOculta(double[][cantidadOculta],int);
void mostrarPesosOcultaSalida(double[][cantidadSalida],int);
void transferirAEntrada(double[][7],int,int,double[],double[]);
void mostrarEntrada(double[]);
double sigmoideOculta(double[],int,double[][cantidadOculta]);
void calcularValorCapaOculta(double[],int,double[][cantidadOculta],double[]);
void mostrarCapaOculta(double[]);
double sigmoideSalida(double[],int,double[][cantidadSalida]);
void calcularValorCapaSalida(double[],int,double[][cantidadSalida],double[]);
void mostrarCapaSalida(double[]);
void calcularErrorSalida(double[], double[][cantidadSalida], int, double[]);
void mostrarErrorSalida(double[]);
void calcularErrorOcultaSalida(double[],double[][cantidadSalida],double[],double[][cantidadSalida]);
void mostrarErrorOcultaSalida(double[][cantidadSalida]);

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
    double capaOculta[cantidadOculta];
    double capaSalida[cantidadSalida];
    //Se inicializa el X0 y el H0 en 1
    capaEntrada[0] = 1;
    capaOculta[0] = 1;
    
    //Se inicializan pesos en la capa de entrada, todos en 1, solo para asegurarse de que no haya acceso directo al resto de capas
    double pesosEntrada[cantidadEntrada-1] = {1,1,1,1,1,1,1};

    //Los pesos de cada capa arreglados en matrices bidimensionales 
    double pesosEntradaOculta[cantidadEntrada][cantidadOculta];
    double pesosOcultaSalida[cantidadOculta][cantidadSalida];

    //Arreglo que contenera los errores en la capa de salida
    double errorSalida[cantidadSalida];
    double errorOcultaSalida[cantidadOculta][cantidadSalida];
    
    srand(time(NULL));  //inicia el seed del random con la hora del pc

    //se inicializan los pesos
    inicializarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    inicializarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    

    //Se muestran los pesos
    mostrarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    mostrarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    
    transferirAEntrada(patrones_entrada,0,7,capaEntrada,pesosEntrada);
    mostrarEntrada(capaEntrada);

    calcularValorCapaOculta(capaEntrada,cantidadEntrada,pesosEntradaOculta,capaOculta);
    mostrarCapaOculta(capaOculta);

    calcularValorCapaSalida(capaOculta,cantidadOculta,pesosOcultaSalida,capaSalida);
    mostrarCapaSalida(capaSalida);

    calcularErrorSalida(capaSalida,patrones_salida,0,errorSalida);
    mostrarErrorSalida(errorSalida);

    calcularErrorOcultaSalida(errorSalida,pesosOcultaSalida,capaSalida,errorOcultaSalida);
    mostrarErrorOcultaSalida(errorOcultaSalida);
    return 0;

}

//Funcion que inicializa los pesos entre la capa de entrada y la capa oculta
void inicializarPesosEntradaOculta(double pesos[][cantidadOculta], int cantidadNeuronasEntrada){
    int numero = 0;
    double resultado = 0;

    //Inicializar pesos que no se usaran, para evitar bugs, basura del buffer
    for(int i=0;i<cantidadNeuronasEntrada;i++){
        pesos[i][0] = 0;
    }
    //printf("Pesos entrada oculta calculo: \n");
    //se incializan los pesos en orden w00,w01,w02,...,w11,w12
    for(int i=0;i<cantidadNeuronasEntrada;i++){
        for(int j=1;j<cantidadOculta;j++){
            numero = 0 + rand() %2000;
            numero = numero - 1000;
            resultado = (double) numero/10000;
            //printf("w%d%d : %f\n",i,j,resultado);
            pesos[i][j] = resultado;
            
        }
    }
}

//Funcion que inicializa los pesos entre la capa oculta y la capa de salida
void inicializarPesosOcultaSalida(double pesos[][cantidadSalida], int cantidadNeuronasEntrada){
    int numero = 0;
    double resultado = 0;

    //printf("Pesos oculta salida calculo: \n");
    for(int i=0;i<cantidadNeuronasEntrada;i++){
        for(int j=0;j<cantidadSalida;j++){
            numero = 0 + rand() %2000;
            numero = numero - 1000;
            resultado = (double) numero/10000;
            //printf("w%d%d : %f\n",i,j,resultado);
            pesos[i][j] = resultado;
        }
    }
}


void mostrarPesosEntradaOculta(double pesos[][cantidadOculta], int cantidaNeuronasEntrada){

    printf("Pesos entrada oculta asignados: \n");
    for(int i=0;i<cantidaNeuronasEntrada;i++){
        for(int j=0;j<cantidadOculta;j++){
            printf("w%d%d : %f\n",i,j,pesos[i][j]);
        }
    }
}


void mostrarPesosOcultaSalida(double pesos[][cantidadSalida], int cantidaNeuronasEntrada){

    printf("Pesos oculta salida asignados: \n");
    for(int i=0;i<cantidaNeuronasEntrada;i++){
        for(int j=0;j<cantidadSalida;j++){
            printf("w%d%d : %f\n",i,j,pesos[i][j]);
        }
    }
}


void transferirAEntrada(double patrones_entrada[][7],int numeroDato, int bits, double capaEntrada[], double pesosEntrada[] ){
    for(int i=1;i<bits;i++){
        capaEntrada[i] = patrones_entrada[numeroDato][i-1] * pesosEntrada[i];
    }
}


void mostrarEntrada(double capaEntrada[]){
    printf("Valores Capa Entrada: \n");

    for(int i=0;i<cantidadEntrada;i++){
        printf("N%d : %f\n",i,capaEntrada[i]);
    }
}


//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoideOculta(double  entradas[], int tamanoEntradas, double  pesos[][cantidadOculta], int numeroNeurona){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0;i<tamanoEntradas;i++){
        exponente = exponente + (entradas[i]*pesos[i][numeroNeurona]);
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
void calcularValorCapaOculta(double  entradas[], int tamanoEntrada, double  pesos[][cantidadOculta], double capaOculta[]){
    //Realiza el calculo para cada neurona de la capa
    for(int i=1;i<cantidadOculta;i++){
        capaOculta[i] = sigmoideOculta(entradas,tamanoEntrada,pesos,i);
    }
}




void mostrarCapaOculta(double oculta[]){
    printf("Valores capa oculta: \n");
    for(int i=0;i<cantidadOculta;i++){
        printf("N%d : %f\n",i,oculta[i]);
    }
}

//Funcion de transferencia, se usa la sigmoide en este caso
double sigmoideSalida(double  entradas[], int tamanoEntradas, double  pesos[][cantidadSalida], int numeroNeurona){

    double neto = 0;
    double exponente = 0;
    double result = 0;
    
    /*
    Se hace el calculo de la suma correspondiente al exponente de la funcion sigmoide
    En este caso X0*W00+X1*W10+...+Xi*Wi0  siendo el segundo subindice de los pesos el parametro numeroNeurona que indica la neurona a la que
    se le esta haciendo el calculo
    */
    for(int i=0;i<tamanoEntradas;i++){
        exponente = exponente + (entradas[i]*pesos[i][numeroNeurona]);
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
void calcularValorCapaSalida(double  entradas[], int tamanoEntrada, double  pesos[][cantidadSalida], double capaSalida[]){
    //Realiza el calculo para cada neurona de la capa
    for(int i=0;i<cantidadSalida;i++){
        capaSalida[i] = sigmoideSalida(entradas,tamanoEntrada,pesos,i);
    }
}

void mostrarCapaSalida(double salida[]){
    printf("Valores capa salida: \n");
    for(int i=0;i<cantidadSalida;i++){
        printf("N%d : %f\n",i,salida[i]);
    }
}

double error(){

}


void calcularErrorSalida(double capaSalida[], double patrones_salida[][cantidadSalida], int numeroDato, double errorSalida[]){
    for(int i=0;i<cantidadSalida;i++){
        errorSalida[i] = patrones_salida[0][i] - capaSalida[i];
    }
}

void mostrarErrorSalida(double errorSalida[]){
    printf("Error capa salida: \n");
    for(int i=0;i<cantidadSalida;i++){
        printf("e%d : %f\n",i,errorSalida[i]);
    }
}

void calcularErrorOcultaSalida(double errorSalida[], double pesos[][cantidadSalida], double capaSalida[], double errorOcultaSalida[][cantidadSalida]){
    for(int i=0;i<cantidadOculta;i++){
        for(int j=0;j<cantidadSalida;j++){
            errorOcultaSalida[i][j] = errorSalida[j] * capaSalida[j] * (1-capaSalida[j]) * pesos[i][j];
        }
    }
}

void mostrarErrorOcultaSalida(double errorOcultaSalida[][cantidadSalida]){
    printf("Error oculta salida: \n");
    for(int i=0;i<cantidadOculta;i++){
        for(int j=0;j<cantidadSalida;j++){
            printf("e%d%d : %f\n",i,j,errorOcultaSalida[i][j]);
        }
    }
}

//consultar valores intermedios de la función sigmoide