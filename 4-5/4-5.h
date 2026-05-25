#ifndef Q3_H
#define Q3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIVRE   1
#define OCUPADO 0


typedef struct Info
{
    int  blocoInicial;
    int  blocoFinal;
    long endInicial;   
    long endFinal;     
    int  status;
} Info;

typedef struct ArvMemoria
{
    Info info1, info2, info3, info4;
    int  nInfos;
    struct ArvMemoria *filho1;
    struct ArvMemoria *filho2;
    struct ArvMemoria *filho3;
    struct ArvMemoria *filho4;
    struct ArvMemoria *filho5;
} Memoria;

#define MB (1024L * 1024L)   

void criarInfo      (Info *info, int blocoInicial, int blocoFinal, int status);
void criarNo        (Memoria **no, Info info, Memoria *filho1, Memoria *filho2);
void adicionaInfo   (Memoria **no, Info info, Memoria *filho);
void quebraNo       (Memoria **no, Info novaInfo, Memoria *filho,
                     Info *sobe, Memoria **maior);

void insereArv45    (Memoria **raiz, Info info, Memoria *pai, Info *sobe,
                     Memoria **retorno);
void insereMemoria  (Memoria **raiz, Info info);
void exibirInfos    (Memoria *raiz);
void liberaArv45    (Memoria **raiz);

#endif 
