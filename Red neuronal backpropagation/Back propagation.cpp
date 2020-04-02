#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



//Numero de neuronas por capa

#define cantidadEntrada 8
#define cantidadSalida 4
#define cantidadOculta 7      //Se utilizara la regla piramidal con 3 capas, es decir, una sola capa oculta sqrt(8*4)=5.2 
                                //se decide aproximar al entero superior y se suma una neurona que sera h0
#define factor 0.16            //factor de aprendizaje arbitrario

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
double calcularErrorSalidaTotal(double[]);
void calcularErrorOcultaSalida(double[],double[][cantidadSalida],double[],double[][cantidadSalida],double[]);
void mostrarErrorOcultaSalida(double[][cantidadSalida]);
double calcularAporteErrorOculta(double[],double[],double[][cantidadSalida],int);
void calcularErrorEntradaOculta(double[],double[][cantidadSalida],double[][cantidadOculta],double[],double[][cantidadOculta],double[],double[],
double[][cantidadSalida]);
void mostrarErrorEntradaOculta(double[][cantidadOculta]);
double sumaErrorOcultaSalida(double[][cantidadSalida],int);
void actualizarPesosEntradaOculta(double[][cantidadOculta],double[],double[][cantidadOculta]);
void actualizarPesosOcultaSalida(double[][cantidadSalida],double[],double[][cantidadSalida]);
void entrenar(double[][7],int,int,double[],double[],double[][cantidadOculta],double[],double[][cantidadSalida],double[],double[][4],double[],
double[][cantidadSalida],double[][cantidadOculta]);





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

    int cantidadDatos = 10;
    int bitsEntrada = 7;
    
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

    //Arreglos que conteneran los errores en las capas
    double errorSalida[cantidadSalida];
    double errorOcultaSalida[cantidadOculta][cantidadSalida];
    double errorEntradaOculta[cantidadEntrada][cantidadOculta];
    //double errorEntradaOculta[cantidadEntrada][cantidadOculta];
    
    srand(time(NULL));  //inicia el seed del random con la hora del pc

    //se inicializan los pesos
    inicializarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    inicializarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    
    //Se muestran los pesos
    mostrarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);
    mostrarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
    
    entrenar(patrones_entrada,cantidadDatos,bitsEntrada,capaEntrada,pesosEntrada,pesosEntradaOculta,capaOculta,pesosOcultaSalida,capaSalida,
    patrones_salida,errorSalida,errorOcultaSalida,errorEntradaOculta);
    /*
    calcularErrorEntradaOculta(capaEntrada,errorOcultaSalida,pesosEntradaOculta,capaOculta,errorEntradaOculta);
    mostrarErrorEntradaOculta(errorEntradaOculta);
    */
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
    for(int i=1;i<=bits;i++){
        capaEntrada[i] = patrones_entrada[numeroDato][i-1] * pesosEntrada[i-1];
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




void calcularErrorSalida(double capaSalida[], double patrones_salida[][cantidadSalida], int numeroDato, double errorSalida[]){
    for(int i=0;i<cantidadSalida;i++){
        errorSalida[i] = (capaSalida[i]-patrones_salida[numeroDato][i]);
    }
}


void mostrarErrorSalida(double errorSalida[]){
    printf("Error capa salida: \n");
    for(int i=0;i<cantidadSalida;i++){
        printf("e%d : %f\n",i,errorSalida[i]);
    }
}

double calcularErrorSalidaTotal(double errorSalida[]){
    double error = 0;
    for(int i=0;i<cantidadSalida;i++){
        error = error + errorSalida[i];
    }
    return error;
}

void calcularErrorOcultaSalida(double errorSalida[], double pesos[][cantidadSalida], double capaSalida[], double errorOcultaSalida[][cantidadSalida], double capaOculta[]){
    for(int i=0;i<cantidadOculta;i++){
        for(int j=0;j<cantidadSalida;j++){
            errorOcultaSalida[i][j] = errorSalida[j] * capaSalida[j] * (1-capaSalida[j]) * capaOculta[i];
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

double calcularAporteErrorOculta(double errorSalida[], double capaSalida[], double pesosOcultaSalida[][cantidadSalida], int dato){
    double resultado = 0;
    for(int i=0;i<cantidadSalida;i++){
        resultado = resultado + (errorSalida[i] * capaSalida[i] * (1-capaSalida[i]) * pesosOcultaSalida[dato][i]);
    }
    return resultado;
}

void calcularErrorEntradaOculta(double capaEntrada[], double errorOcultaSalida[][cantidadSalida], double pesos[][cantidadOculta], double capaOculta[],
double errorEntradaOculta[][cantidadOculta], double errorSalida[], double capaSalida[], double pesosOcultaSalida[][cantidadSalida]){
    double aporte = 0;
    for(int i=0;i<cantidadEntrada;i++){
        errorEntradaOculta[i][0] = 0;       //se inicializan espacios sin usar para evitar bugs
    }

    for(int i=0;i<cantidadEntrada;i++){
        double aporte = 0;
        for(int j=1;j<cantidadOculta;j++){
            
            aporte = calcularAporteErrorOculta(errorSalida,capaSalida,pesosOcultaSalida,j);
            //printf("suma error %d : %f\n",j,sumaErrores);
            errorEntradaOculta[i][j] = capaEntrada[i] * capaOculta[j] * (1-capaOculta[j]) * aporte;
            aporte = 0;
        }
    }
}

void mostrarErrorEntradaOculta(double errorEntradaOculta[][cantidadOculta]){
    printf("Error entrada oculta: \n");
    for(int i=0;i<cantidadEntrada;i++){
        for(int j=0;j<cantidadOculta;j++){
            printf("e%d%d : %f\n",i,j,errorEntradaOculta[i][j]);
        }
    }
}


double sumaErrorOcultaSalida(double errorOcultaSalida[][cantidadSalida],int dato){
    double resultado = 0;
    for(int i=0;i<cantidadSalida;i++){
        resultado = resultado + errorOcultaSalida[dato][i];
    }

    return resultado;
}

void actualizarPesosEntradaOculta(double pesosEntradaOculta[][cantidadOculta], double capaEntrada[], double errorEntradaOculta[][cantidadOculta]){
    for(int i=1;i<cantidadEntrada;i++){
        for(int j=1;j<cantidadOculta;j++){      
            pesosEntradaOculta[i][j] = pesosEntradaOculta[i][j] - (factor * errorEntradaOculta[i][j]);
        }
    }
}

void actualizarPesosOcultaSalida(double pesosOcultaSalida[][cantidadSalida], double capaOculta[], double errorOcultaSalida[][cantidadSalida]){
    for(int i=1;i<cantidadOculta;i++){
        for(int j=0;j<cantidadSalida;j++){
            pesosOcultaSalida[i][j] = pesosOcultaSalida[i][j] - (factor * errorOcultaSalida[i][j]);
        }
    }
}

void entrenar(double patrones_entrada[][7], int cantidadDatos, int bitsEntrada, double capaEntrada[], double pesosEntrada[], 
double pesosEntradaOculta[][cantidadOculta], double capaOculta[], double pesosOcultaSalida[][cantidadSalida], double capaSalida[], 
double patrones_salida[][4], double errorSalida[], double errorOcultaSalida[][cantidadSalida], double errorEntradaOculta[][cantidadOculta]){
    int epocas = 0;
    double errorTotal=1;
    while(errorTotal!=0){
    
        errorTotal = 0;
        for(int j=0;j<cantidadDatos;j++){
            transferirAEntrada(patrones_entrada,j,bitsEntrada,capaEntrada,pesosEntrada);
            mostrarEntrada(capaEntrada);

            calcularValorCapaOculta(capaEntrada,cantidadEntrada,pesosEntradaOculta,capaOculta);
            mostrarCapaOculta(capaOculta);

            calcularValorCapaSalida(capaOculta,cantidadOculta,pesosOcultaSalida,capaSalida);
            mostrarCapaSalida(capaSalida);

            calcularErrorSalida(capaSalida,patrones_salida,j,errorSalida);
            mostrarErrorSalida(errorSalida);
            errorTotal = errorTotal + calcularErrorSalidaTotal(errorSalida);
            calcularErrorOcultaSalida(errorSalida,pesosOcultaSalida,capaSalida,errorOcultaSalida,capaOculta);
            mostrarErrorOcultaSalida(errorOcultaSalida);
            
            calcularErrorEntradaOculta(capaEntrada,errorOcultaSalida,pesosEntradaOculta,capaOculta,errorEntradaOculta,errorSalida,capaSalida,
            pesosOcultaSalida);
            mostrarErrorEntradaOculta(errorEntradaOculta);

            actualizarPesosEntradaOculta(pesosEntradaOculta,capaEntrada,errorEntradaOculta);
            mostrarPesosEntradaOculta(pesosEntradaOculta,cantidadEntrada);

            actualizarPesosOcultaSalida(pesosOcultaSalida,capaOculta,errorOcultaSalida);
            mostrarPesosOcultaSalida(pesosOcultaSalida,cantidadOculta);
        }
        epocas++;
    
    }
    printf("Epocas: %d\n",epocas);
}