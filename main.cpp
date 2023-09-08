/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <cmath>

using namespace std;

// Blinking rate in milliseconds
#define BLINKING_RATE     200ms
UnbufferedSerial serial(USBTX, USBRX, 9600);

const int ROW = 4;
const int COLS = 3;
char matriz [ROW][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'},
    };

DigitalIn rows[ROW] = {D2, D3, D4, D5};
DigitalOut col[COLS] = {D6, D7, D8};

char recorrerMatriz(bool isEnter, int x){
    while(isEnter == false){
        for (int i = 0; i < COLS; i++){
            col[i] = 0;
            for (int j  = 0; j < ROW; j++){
                if(rows[j] == 0){
                    if (matriz[j][i] == '#')
                        isEnter = true;
                    else
                        x += matriz[j][i];
                    ThisThread::sleep_for(BLINKING_RATE);
                }    
            }
            col[i] = 1;
        }
    }
    return x;
}

int main()
{   
    cout << "Inicia, por favor ingrese el número correspondiente al caso deseado" << endl;
    int caso;
    bool salir = false;

    while (salir == false){
        caso = recorrerMatriz(false, caso) - '0';
        salir = true;
        cout << caso << endl; 
    }
    if (caso == 1){
        int x1, y1, x2, y2 = 0;
        while(true){
            ThisThread::sleep_for(BLINKING_RATE);
            cout << "Ingrese el valor de x del primer punto" << endl;
            x1 = recorrerMatriz(false, x1) - '0';
            cout << x1 << endl;
            ThisThread::sleep_for(BLINKING_RATE);
            cout << "Ingrese el valor de y del primer punto" << endl;
            y1 = recorrerMatriz(false, y1) - '0';
            cout << y1 << endl;
            ThisThread::sleep_for(BLINKING_RATE);
            cout << "Ingrese el valor de x del segundo punto" << endl;
            x2 = recorrerMatriz(false, x2) - '0';
            cout << x2 << endl;
            ThisThread::sleep_for(BLINKING_RATE);
            cout << "Ingrese el valor de y del segundo punto" << endl;
            y2 = recorrerMatriz(false, y2) - '0';
            cout << y2 << endl;
            ThisThread::sleep_for(BLINKING_RATE);
            if (x1 != x2){
                float pendiente = (y2-y1)/(x2-x1);
                cout << "La pendiente de los puntos es: " << pendiente << endl;
                float intercepto = -y1/pendiente + x1;
                cout << "El intercepto con el eje y es: " << intercepto << endl;
            }else {
                cout << "Por favor ingrese puntos válidos" << endl;
            }
        } 
        
                
    } else if (caso == 2){
        while (true){
            int N;
            cout << "Ingrese el número de temperaturas" << endl;
            N = recorrerMatriz(false, N) - '0';
            cout << N << endl;
            int temperaturas[N];
            for (int k = 0; k < N; k++){
                ThisThread::sleep_for(BLINKING_RATE);
                cout << "Ingrese la temperatura que quiera para el elemento " << k+1 << endl;
                temperaturas[k] = recorrerMatriz(false, temperaturas[k]) - '0';
                cout << temperaturas[k] << endl;
            }
            float suma = 0;
            for (int i = 0; i < N; i++){
                suma = suma + temperaturas[i];
            }
            suma = suma/N;
            cout << "El promedio de las temperaturas es: " << suma << endl;
            float desviacion = 0;
            for (int i = 0; i < N; i++){
                desviacion = desviacion + pow(temperaturas[i]-suma, 2);
            }
            desviacion = sqrt(desviacion/N);
            cout << "La desviación estándar es: " << desviacion << endl;
        }
    } else if (caso == 3){
        int r, g ,b;
        PwmOut ledR(LED1);
        PwmOut ledG(LED2);
        PwmOut ledB(LED3);

        ledR.period(0.01);
        ledG.period(0.01);
        ledB.period(0.01);

        while(true){
            cout << "Introduzca un valor entre 0 y 255 para el Led R: " << endl;
            r = recorrerMatriz(false, r) - '0';
            cout << r << endl;

            cout << "Introduzca un valor entre 0 y 255 para el Led G: " << endl;
            g = recorrerMatriz(false, g) - '0';
            cout << g << endl;

            cout << "Introduzca un valor entre 0 y 255 para el Led B: " << endl;
            b = recorrerMatriz(false, b) - '0';
            cout << b << endl;

            ledR.write(1.0f - (float)r / 255.0f);
            ledG.write(1.0f - (float)g / 255.0f);
            ledB.write(1.0f - (float)b / 255.0f);

            ThisThread::sleep_for(BLINKING_RATE);
        }

    }
    
}
