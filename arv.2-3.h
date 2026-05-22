#ifndef ARVORE23_H
#define ARVORE23_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arvore23 Arvore23;



typedef struct {
    int  codigo;        
    char nome[50];      
    int  bloco;         
    int  cargahr;       
} Disciplina;

typedef struct {
    int       codigo;           
    char      nome[50];        
    int       qtdBlocos;        
    int       semanas;          
    Arvore23 *raizdisciplinas; 
} Curso;

typedef struct {
    int  matricula;     
    char nome[50];      
    int  codigo_curso;  
    int  anoingresso;   
    int  semestre;      
} Aluno;


typedef struct {
    int chave; 
    int tipo;  
    union {
        Aluno      aluno;
        Curso      curso;
        Disciplina disciplina;
    } dado;
} Info;


struct Arvore23 {
    Info           info1;   
    Info           info2;   
    int            nInfos;  
    struct Arvore23 *esq;   
    struct Arvore23 *cent;  
    struct Arvore23 *dir;   
};


int      inserirArvore23(Arvore23 **arvore, Info info);

Arvore23 *inserirArv23(Arvore23 **no, Info informacao, Info *promove, Arvore23 **Pai);

void exibir_Arvore23(Arvore23 *raiz, void (*exibir_dado)(Info));

int      arvore_2_3_remover(Arvore23 **raiz, int chave);

void     freeTree(Arvore23 **no);

void     freeNo(Arvore23 **no);




#endif 
