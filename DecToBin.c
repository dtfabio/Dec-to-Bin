/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DecToBin.c
 * Author: dtfabio96
 *
 * Created on 27 novembre 2015, 17.14
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 32
void conversione (int bin[], int dec){
    int i;
    for(i=0;i<32;i++){
        if(dec%2==0)
            bin[i]=0;
        else
            bin[i]=1;
       dec=dec/2;
    }
    }

void stampa(int bin[]){
    int i;
        int presenza_uno=0;
    for(i=32; i>=0; i--){
        if(bin[i]==1) // se trova uno assegna 1
            presenza_uno=1;
        if(presenza_uno==1){
        printf("%d", bin[i]);
        }
    }
                       }

int binario[MAX], decimale;
int main() {
    printf("Inserisci il numero decimale da convertire in binario: ");
        scanf("%d", &decimale);
        conversione(binario,decimale);
        stampa(binario);
}
