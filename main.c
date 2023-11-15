#include <stdlib.h>
#include <stdio.h>
#include "color.h"
#include <string.h>


typedef struct indicator{
    int indicatorY;
    int indicatorX;

}indicator;

const int fil = 28;
const int col = 96;
char archivoMapas[20] = "mapas.dat";


int main(){

    char mapa[28][96];
    indicator cursor;
    cursor.indicatorY = fil/2;
    cursor.indicatorX = col/2;

    memset(mapa, 219, sizeof(mapa));

    char eleccion;

    printf("Ingrese c para cargar un mapa o v para ver el archivo\n");

    scanf("%c", &eleccion);

    if(eleccion == 'c'){

    while(1){
    printf("\x1b[H");
    system("");
    estrucuraBasica(mapa);
    indicador(mapa, &cursor);
    mostrarMapa(mapa, &cursor);
    Sleep(10);
    }
    }

    else if(eleccion == 'v'){
    leerArchivo();

    }

    return 0;
}


void fixMapa(char mapa[fil][col]){
    int i, j;
    for(i = 0; i<fil;i++){
        for(j = 0; j<col; j++){
            if(mapa[i][j] == -37){
                mapa[i][j] = ' ';
            }
        }
    }
}

void estrucuraBasica(char mapa[fil][col]){

        int i,j;
 //PAREDES BORDER NO BORRAR BAJO NINGUNA SIRCUNSTANCIA :3
    for(i = 0; i < fil; i++){
        for(j = 0; j<2; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = 0; i < fil; i++){
        for(j = col - 2; j<col; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = fil - 2; i < fil; i++){
        for(j = 0; j<col; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = 0; i < 2; i++){
        for(j = 0; j<col; j++){
            mapa[i][j] = '#';
        }
    }

}

void mostrarMapa(char mapa[fil][col], indicator * cursor){
    int i, j;

    printf("%c------------------------------------------------------------------------------------------------%c\n",218, 191);

    for(i = 0; i<fil; i++){
        printf("|");

        for(j = 0; j<col; j++){
        if(i == cursor->indicatorY && j == cursor->indicatorX){
            printf(RED"%c", mapa[i][j]);
        }else{
            printf(BWHT"%c", mapa[i][j]);
        }
        }
        printf("|\n");

    }
    printf("%c------------------------------------------------------------------------------------------------%c\n", 192, 217);

    printf("C para escribir\n");
    printf("X para borrar\n");
    printf("R para borrar TODO\n");
    printf("G para guardar en el archivo");

}

void indicador(char mapa[fil][col], indicator * cursor){


    if(GetKeyState('W') & 0x8000){
     cursor->indicatorY = cursor->indicatorY - 1;
    }
    if(GetKeyState('S') & 0x8000){
     cursor->indicatorY = cursor->indicatorY + 1;

    }
    if(GetKeyState('A') & 0x8000){
     cursor->indicatorX = cursor->indicatorX - 1;
    }
    if(GetKeyState('D') & 0x8000){
     cursor->indicatorX = cursor->indicatorX + 1;
    }
    mapa[cursor->indicatorY][cursor->indicatorX] = mapa[cursor->indicatorY][cursor->indicatorX];

    if(GetKeyState('C') & 0x8000){

        mapa[cursor->indicatorY][cursor->indicatorX] = '#';

    }
    if(GetKeyState('X') & 0x8000){

        mapa[cursor->indicatorY][cursor->indicatorX] = 219;

    }if(GetKeyState('R') & 0x8000){
        memset(mapa, 219, fil*col);
    }
    if(GetKeyState('G') & 0x8000){
        infoArchivo(mapa);
        exit(0);
    }


}

void infoArchivo(char mapa[fil][col]){
    FILE * archi = fopen(archivoMapas, "a");
    char nivel;
    system("cls");
    system("pause");
    if(archi){

        printf("A que nivel pertenece el mapa?\n");
        fflush(stdin);
        scanf("%c", &nivel);

        mapa[0][0] = nivel;
        fixMapa(mapa);

        fwrite(mapa, fil*col, 1, archi);

        fclose(archi);
    }

}

void leerArchivo(){
    FILE * archi = fopen(archivoMapas, "r");

    char mapaAux[fil][col];

    if(archi){
        while(!feof(archi)){
        fread(&mapaAux, fil*col, 1, archi);
            if(!feof(archi)){
                printearMapa(mapaAux);
            }
        }
        fclose(archi);
    }
}

void printearMapa(char mapaAux[fil][col]){
     int i, j;
    printf("%c------------------------------------------------------------------------------------------------%c\n",218, 191);
    for(i = 0; i<fil; i++){
        printf("|");
        for(j = 0; j<col; j++){
          printf("%c", mapaAux[i][j]);
        }
    printf("|\n");
}
    printf("%c------------------------------------------------------------------------------------------------%c\n", 192, 217);

}
