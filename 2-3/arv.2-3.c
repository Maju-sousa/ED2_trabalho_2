

#include "arv.2-3.h"


 typedef int (*FuncaoRemover)(
    Arvore23 **,
    int,
    Arvore23 *,
    Arvore23 **,
    Arvore23 **
);

int arvore23_remover1(
    Arvore23 **raiz,
    int chave,
    Arvore23 *pai,
    Arvore23 **origem,
    Arvore23 **maior
);

int arvore23_remover2(
    Arvore23 **raiz,
    int chave,
    Arvore23 *pai,
    Arvore23 **origem,
    Arvore23 **maior
);

// Funções Básicas

Arvore23 *criaNo(Info informacao, Arvore23 *filhoesq, Arvore23 *filhocen)
{
    Arvore23 *no = (Arvore23 *)malloc(sizeof(Arvore23));

    no->info1  = informacao; 
    no->esq    = filhoesq;
    no->cent   = filhocen;
    no->nInfos = 1;
    no->dir    = NULL;

    return no;
}
void adicionaChave(Arvore23 *no, Info informacao, Arvore23 *filho)
{
    if (informacao.chave > no->info1.chave) {
        no->info2 = informacao;
        no->dir   = filho;
    } else {
        no->info2 = no->info1;
        no->info1 = informacao;
        no->dir   = no->cent;
        no->cent  = filho;
    }
    no->nInfos = 2;
}

Arvore23 *quebraNo(Arvore23 *no, Info informacao, Info *promove, Arvore23 *filho)
{
    Arvore23 *maior;

    if (informacao.chave < no->info1.chave) {
        *promove = no->info1;
        maior    = criaNo(no->info2, no->cent, no->dir);
        no->info1 = informacao;
        no->cent  = filho;

    } else if (informacao.chave < no->info2.chave) {
        *promove = informacao;
        maior    = criaNo(no->info2, filho, no->dir);

    } else {
        *promove = no->info2;
        maior    = criaNo(informacao, no->dir, filho);
    }

    no->nInfos = 1;  
    no->dir    = NULL;

    return maior;
}

 int ehFolha(const Arvore23 *no)
{
    return (no->esq == NULL) ? 1 : 0;
}

int eh_info1(Arvore23 no, int chave)
{
    return (chave == no.info1.chave);
}

int eh_info2(Arvore23 no, int chave)
{
    return (no.nInfos == 2 && chave == no.info2.chave);
}

void freeNo(Arvore23 **no)
{
    free(*no);
    *no = NULL;
}





// Funções Auxiliares de Busca

Info *no23_maior_info(Arvore23 *raiz)
{
    Info *maior = &(raiz->info1);

    if (raiz->nInfos == 2)
        maior = &(raiz->info2);

    return maior;
}

Arvore23 *arvore23_buscar_maior_filho(Arvore23 *raiz, Arvore23 **pai, Info **maior_valor)
{
    Arvore23 *filho = raiz;

    while (!ehFolha(filho)) {
        *pai = filho;
        if (filho->nInfos == 1)
            filho = filho->cent;
        else
            filho = filho->dir;
    }

    if (filho != NULL)
        *maior_valor = no23_maior_info(filho);

    return filho;
}

Arvore23 *arvore23_buscar_menor_filho(Arvore23 *raiz, Arvore23 **pai)
{
    Arvore23 *filho = raiz;

    while (!ehFolha(filho)) {
        *pai  = filho;
        filho = filho->esq;
    }

    return filho;
}

int calcular_altura(Arvore23 *no)
{
    int altura = -1;

    if (no != NULL)
        altura = 1 + calcular_altura(no->esq);

    return altura;
}

Arvore23 *arvore23_buscar_pai(Arvore23 *raiz, int chave)
{
    Arvore23 *pai = NULL;

    if (raiz != NULL) {
        if (!eh_info1(*raiz, chave) && !eh_info2(*raiz, chave)) {
            if (chave < raiz->info1.chave)
                pai = arvore23_buscar_pai(raiz->esq, chave);
            else if (raiz->nInfos == 1 || chave < raiz->info2.chave)
                pai = arvore23_buscar_pai(raiz->cent, chave);
            else
                pai = arvore23_buscar_pai(raiz->dir, chave);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

Arvore23 *arvore23_buscar_maior_pai(Arvore23 *raiz, int chave)
{
    Arvore23 *pai = NULL;

    if (raiz != NULL) {
        if (!eh_info1(*raiz, chave) && !eh_info2(*raiz, chave)) {
            if (chave < raiz->info1.chave)
                pai = arvore23_buscar_maior_pai(raiz->esq, chave);
            else if (raiz->nInfos == 1 || chave < raiz->info2.chave)
                pai = arvore23_buscar_maior_pai(raiz->cent, chave);
            else
                pai = arvore23_buscar_maior_pai(raiz->dir, chave);

            if (pai == NULL &&
                ((raiz->nInfos == 1 && raiz->info1.chave > chave) ||
                 (raiz->nInfos == 2 && raiz->info2.chave > chave)))
                pai = raiz;
        }
    }

    return pai;
}

Arvore23 *arvore23_buscar_menor_pai_2_infos(Arvore23 *raiz, int chave)
{
    Arvore23 *pai = NULL;

    if (raiz != NULL) {
        if (!eh_info1(*raiz, chave) && !eh_info2(*raiz, chave)) {
            if (chave < raiz->info1.chave)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->esq, chave);
            else if (raiz->nInfos == 1 || chave < raiz->info2.chave)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->cent, chave);
            else
                pai = arvore23_buscar_menor_pai_2_infos(raiz->dir, chave);

            if (pai == NULL && raiz->nInfos == 2 && chave < raiz->info2.chave)
                pai = raiz;
        }
    }

    return pai;
}

 Arvore23 *arvore23_buscar_menor_pai(Arvore23 *raiz, int chave)
{
    Arvore23 *pai = NULL;

    if (raiz != NULL) {
        if (!eh_info1(*raiz, chave) && !eh_info2(*raiz, chave)) {
            if (chave < raiz->info1.chave)
                pai = arvore23_buscar_menor_pai(raiz->esq, chave);
            else if (raiz->nInfos == 1 || chave < raiz->info2.chave)
                pai = arvore23_buscar_menor_pai(raiz->cent, chave);
            else
                pai = arvore23_buscar_menor_pai(raiz->dir, chave);

            if (pai == NULL && raiz->info1.chave < chave)
                pai = raiz;
        }
    }

    return pai;
}




// Funções de Innserir

Arvore23 *inserirArv23(Arvore23 **no, Info informacao, Info *promove, Arvore23 **Pai)
{
    Info  promove1;
    Arvore23 *maiorNo = NULL;

    if (*no == NULL) {
        *no = criaNo(informacao, NULL, NULL);

    } else if (ehFolha(*no)) {
        if ((*no)->nInfos == 1) {
            adicionaChave(*no, informacao, NULL);
        } else {
            maiorNo = quebraNo(*no, informacao, promove, NULL);

            if (*Pai == NULL) {
                *no     = criaNo(*promove, *no, maiorNo);
                maiorNo = NULL;
            }
        }
    } else {
        if (informacao.chave < (*no)->info1.chave)
            maiorNo = inserirArv23(&((*no)->esq),  informacao, promove, no);
        else if ((*no)->nInfos == 1 || informacao.chave < (*no)->info2.chave)
            maiorNo = inserirArv23(&((*no)->cent), informacao, promove, no);
        else
            maiorNo = inserirArv23(&((*no)->dir),  informacao, promove, no);

        if (maiorNo != NULL) {
            if ((*no)->nInfos == 1) {
                adicionaChave(*no, *promove, maiorNo);
                maiorNo = NULL;
            } else {
                Arvore23 *novo = NULL;
                novo = quebraNo(*no, *promove, &promove1, maiorNo);

                if (*Pai == NULL) {
                    Arvore23 *novaRaiz = criaNo(promove1, *no, novo);
                    *no     = novaRaiz;
                    maiorNo = NULL;
                } else {
                    maiorNo  = novo;
                    *promove = promove1;
                }
            }
        }
    }

    return maiorNo;
}

int inserirArvore23(Arvore23 **arvore, Info info)
{
    Info promove;
    Arvore23 *Pai = NULL;
    int inseriu = 0;

    if (inserirArv23(arvore, info, &promove, &Pai))
        inseriu = 1;

    return inseriu;
}



// Funções de Mostrar

void exibir_Arvore23(Arvore23 *raiz, void (*exibir_dado)(Info))
{
    if (raiz != NULL) {
        exibir_Arvore23(raiz->esq, exibir_dado); 

        exibir_dado(raiz->info1); 

        exibir_Arvore23(raiz->cent, exibir_dado); 

        if (raiz->nInfos == 2) {
            exibir_dado(raiz->info2);
            exibir_Arvore23(raiz->dir, exibir_dado); 
        }
    }
}




 //AUXILIARES DE REMOÇÃO

int movimento_onda(Info saindo, Info *entrada, Arvore23 *pai,   Arvore23 **origem, Arvore23 **raiz, Arvore23 **maior,  FuncaoRemover funcao_remover)
{
    int removeu = funcao_remover(raiz, saindo.chave, pai, origem, maior);
    *entrada = saindo; 
    return removeu;
}

 int arvore23_remover_nao_folha1(Arvore23 **origem, Arvore23 *raiz, Info *info,    Arvore23 *filho1, Arvore23 *filho2, Arvore23 **maior)
{
    int  removeu;
    Arvore23 *filho, *pai;
    Info *info_filho;

    pai = raiz;
    filho = arvore23_buscar_maior_filho(filho1, &pai, &info_filho);

    if (filho->nInfos == 2) {
        *info = *info_filho;   
        filho->nInfos = 1;
        removeu = 1;
    } else {
        filho = arvore23_buscar_menor_filho(filho2, &pai);
        removeu = movimento_onda(filho->info1, info, pai, origem, &filho, maior, arvore23_remover1);
    }

    return removeu;
}

int arvore23_remover_nao_folha2(Arvore23 **origem, Arvore23 *raiz, Info *info,  Arvore23 *filho1, Arvore23 *filho2, Arvore23 **maior)
{
    int  removeu = 0;
    Arvore23 *filho, *pai;
    Info *info_filho;

    pai   = raiz;
    filho = arvore23_buscar_menor_filho(filho1, &pai);

    if (filho->nInfos == 2) {
        *info        = filho->info1;
        filho->info1 = filho->info2;
        filho->nInfos = 1;
        removeu      = 1;
    } else {
        filho  = arvore23_buscar_maior_filho(filho2, &pai, &info_filho);
        removeu = movimento_onda(*info_filho, info, pai, origem, &filho, maior, arvore23_remover2);
    }

    return removeu;
}



// REBALANCEAMENTO


 int possivel_remover(Arvore23 *raiz)
{
    int possivel = 0;

    if (raiz != NULL) {
        possivel = (raiz->nInfos == 2);

        if (!possivel) {
            possivel = possivel_remover(raiz->cent);
            if (!possivel)
                possivel = possivel_remover(raiz->esq);
        }
    }

    return possivel;
}

 Arvore23 *no23_juntar(Arvore23 *filho1, Info info, Arvore23 *maior, Arvore23 **raiz)
{
    adicionaChave(filho1, info, maior);

    (*raiz)->nInfos--;

    if ((*raiz)->nInfos == 0)
        freeNo(raiz);

    return filho1;
}

 void balanceamento(Arvore23 **raiz, Arvore23 *filho1, Arvore23 **filho2,
                           Info info, Arvore23 **maior)
{
    if (*filho2 == NULL || (*filho2)->nInfos == 0) {
        if (*filho2 != NULL)
            freeNo(filho2);
        *maior = no23_juntar(filho1, info, *maior, raiz);
    }
}

int arvore23_rebalancear(Arvore23 **raiz, int chave, Arvore23 **maior)
{
    int balanceou = 0;

    if (*raiz == NULL)
        return 0;

    if (!ehFolha(*raiz)) {
        if (chave < (*raiz)->info1.chave) {
            balanceou = arvore23_rebalancear(&((*raiz)->esq), chave, maior);

        } else if ((*raiz)->nInfos == 1 || chave < (*raiz)->info2.chave) {
            if ((*raiz)->esq->nInfos == 2 && !possivel_remover((*raiz)->cent))
                balanceou = -1;
            else
                balanceou = arvore23_rebalancear(&((*raiz)->cent), chave, maior);

        } else {
            if ((*raiz)->cent->nInfos == 2 && !possivel_remover((*raiz)->dir))
                balanceou = -1;
            else
                balanceou = arvore23_rebalancear(&((*raiz)->dir), chave, maior);
        }

        if (balanceou != -1) {
            if ((*raiz)->nInfos == 1)
                balanceamento(raiz, (*raiz)->esq, &((*raiz)->cent), (*raiz)->info1, maior);
            else if ((*raiz)->nInfos == 2)
                balanceamento(raiz, (*raiz)->cent, &((*raiz)->dir), (*raiz)->info2, maior);
            balanceou = 1;
        }
    }

    return balanceou;
}





// Funções de Remover

int arvore23_remover1(Arvore23 **raiz, int chave, Arvore23 *pai,
                              Arvore23 **origem, Arvore23 **maior)
{
    int removeu = 0;

    if (*raiz == NULL)
        return 0;

    int info1 = eh_info1(**raiz, chave);
    int info2 = eh_info2(**raiz, chave);

    if (info1 || info2) {
        removeu = 1;

        if (ehFolha(*raiz)) {
            if ((*raiz)->nInfos == 2) {
                if (info1)
                    (*raiz)->info1 = (*raiz)->info2;
                (*raiz)->nInfos = 1;

            } else {
                if (pai == NULL) {
                    freeNo(raiz);
                } else {
                    Arvore23 *pai_aux;
                    Info      info_pai;

                    if (*raiz == pai->esq ||
                        (pai->nInfos == 2 && *raiz == pai->cent))
                    {
                        pai_aux = arvore23_buscar_pai(*origem, pai->info1.chave);

                        if (*raiz == pai->esq)
                            info_pai = pai->info1;
                        else
                            info_pai = pai->info2;

                        removeu = movimento_onda(info_pai, &((*raiz)->info1),
                                                  pai_aux, origem, &pai, maior,
                                                  arvore23_remover1);
                    } else {
                        pai_aux = arvore23_buscar_maior_pai(*origem, (*raiz)->info1.chave);

                        Arvore23 *menor_pai;
                        menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.chave);

                        if (pai_aux != NULL) {
                            if (pai_aux->info1.chave > (*raiz)->info1.chave)
                                info_pai = pai_aux->info1;
                            else
                                info_pai = pai_aux->info2;
                        }

                        int altura_menor_pai = calcular_altura(menor_pai);
                        int altura_pai_aux   = calcular_altura(pai_aux);

                        if (pai_aux == NULL ||
                            (pai_aux != pai && menor_pai != NULL &&
                             altura_menor_pai <= altura_pai_aux &&
                             info_pai.chave > menor_pai->info2.chave))
                        {
                            *maior          = pai;
                            (*raiz)->nInfos = 0;
                            removeu         = -1;
                        } else {
                            Arvore23 *avo = arvore23_buscar_pai(*origem, info_pai.chave);
                            removeu = movimento_onda(info_pai, &((*raiz)->info1),
                                                      avo, origem, &pai_aux, maior,
                                                      arvore23_remover1);
                        }
                    }
                }
            }
        } else {
            if (info2)
                removeu = arvore23_remover_nao_folha1(origem, *raiz, &((*raiz)->info2),
                                                       (*raiz)->cent, (*raiz)->dir, maior);
            else 
                removeu = arvore23_remover_nao_folha1(origem, *raiz, &((*raiz)->info1),
                                                       (*raiz)->esq,  (*raiz)->cent, maior);
        }
    } else {
        if (chave < (*raiz)->info1.chave)
            removeu = arvore23_remover1(&(*raiz)->esq,  chave, *raiz, origem, maior);
        else if ((*raiz)->nInfos == 1 || chave < (*raiz)->info2.chave)
            removeu = arvore23_remover1(&(*raiz)->cent, chave, *raiz, origem, maior);
        else
            removeu = arvore23_remover1(&(*raiz)->dir,  chave, *raiz, origem, maior);
    }

    return removeu;
}

 int arvore23_remover2(Arvore23 **raiz, int chave, Arvore23 *pai,
                              Arvore23 **origem, Arvore23 **maior)
{
    int removeu = 0;

    if (*raiz == NULL)
        return 0;

    int info1 = eh_info1(**raiz, chave);
    int info2 = eh_info2(**raiz, chave);

    if (info1 || info2) {
        removeu = 1;

        if (ehFolha(*raiz)) {
            if ((*raiz)->nInfos == 2) {
                if (info1)
                    (*raiz)->info1 = (*raiz)->info2;
                (*raiz)->nInfos = 1;

            } else {
                if (pai == NULL) {
                    freeNo(raiz);
                } else {
                    Arvore23 *pai_aux;
                    Info      info_pai;

                    if (*raiz == pai->cent ||
                        (pai->nInfos == 2 && *raiz == pai->dir))
                    {
                        pai_aux = arvore23_buscar_pai(*origem, pai->info1.chave);

                        if (*raiz == pai->cent)
                            info_pai = pai->info1;
                        else
                            info_pai = pai->info2;

                        removeu = movimento_onda(info_pai, &((*raiz)->info1),
                                                  pai_aux, origem, &pai, maior,
                                                  arvore23_remover2);
                    } else {
                        pai_aux = arvore23_buscar_menor_pai(*origem, (*raiz)->info1.chave);

                        Arvore23 *menor_pai;
                        menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.chave);

                        if (pai_aux == NULL ||
                            (pai_aux != pai && menor_pai != NULL))
                        {
                            removeu         = -1;
                            *maior          = pai;
                        } else {
                            if (pai_aux->nInfos == 2 &&
                                pai_aux->info2.chave < (*raiz)->info1.chave)
                                info_pai = pai_aux->info2;
                            else
                                info_pai = pai_aux->info1;

                            Arvore23 *avo = arvore23_buscar_pai(*origem, info_pai.chave);
                            removeu = movimento_onda(info_pai, &((*raiz)->info1),
                                                      avo, origem, &pai_aux, maior,
                                                      arvore23_remover2);
                        }
                    }
                }
            }
        } else {
            if (info2)
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info2),
                                                       (*raiz)->dir,  (*raiz)->cent, maior);
            else 
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info1),
                                                       (*raiz)->cent, (*raiz)->esq,  maior);
        }
    } else {
        if (chave < (*raiz)->info1.chave)
            removeu = arvore23_remover2(&(*raiz)->esq,  chave, *raiz, origem, maior);
        else if ((*raiz)->nInfos == 1 || chave < (*raiz)->info2.chave)
            removeu = arvore23_remover2(&(*raiz)->cent, chave, *raiz, origem, maior);
        else
            removeu = arvore23_remover2(&(*raiz)->dir,  chave, *raiz, origem, maior);
    }

    return removeu;
}

int arvore_2_3_remover(Arvore23 **raiz, int chave)
{
    Arvore23 *maior = NULL;
    Arvore23 *posicao_juncao = NULL;

    int removeu = arvore23_remover1(raiz, chave, NULL, raiz, &posicao_juncao);

    if (removeu == -1) {
        Info *valor_juncao = no23_maior_info(posicao_juncao);
        maior   = NULL;
        removeu = arvore23_rebalancear(raiz, valor_juncao->chave, &maior);

        if (removeu == -1) {
            Arvore23 *pai, *posicao_juncao2;
            Info     *entrada;

            pai = arvore23_buscar_pai(*raiz, valor_juncao->chave);

            if (eh_info1(*posicao_juncao, valor_juncao->chave))
                entrada = &(posicao_juncao->cent->info1);
            else
                entrada = &(posicao_juncao->dir->info1);

            removeu = movimento_onda(*valor_juncao, entrada, pai,
                                      raiz, &posicao_juncao, &posicao_juncao2,
                                      arvore23_remover2);

            if (removeu == -1) {
                *valor_juncao = posicao_juncao2->info1;
                pai = arvore23_buscar_pai(*raiz, valor_juncao->chave);

                removeu = movimento_onda(*valor_juncao,
                                          &(posicao_juncao2->esq->info1),
                                          pai, raiz, &posicao_juncao2,
                                          &posicao_juncao, arvore23_remover1);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior   = NULL;
                removeu = arvore23_rebalancear(raiz, valor_juncao->chave, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}



void freeTree(Arvore23 **no)

{
    if (*no != NULL) {
        freeTree(&((*no)->esq));
        freeTree(&((*no)->cent));
        if ((*no)->nInfos == 2)
            freeTree(&((*no)->dir));
        freeNo(no);
    }
}

// CURSOS


Arvore23 *buscar23(Arvore23 *raiz, int chave)
{
    Arvore23 *resultado = NULL;

    if (raiz != NULL) {

        if (raiz->info1.chave == chave) {
            resultado = raiz;
        }
        else if (
            raiz->nInfos == 2 &&
            raiz->info2.chave == chave
        ) {
            resultado = raiz;
        }
        else {

            if (chave < raiz->info1.chave) {
                resultado = buscar23(raiz->esq, chave);
            }
            else if (
                raiz->nInfos == 1 ||
                chave < raiz->info2.chave
            ) {
                resultado = buscar23(raiz->cent, chave);
            }
            else {
                resultado = buscar23(raiz->dir, chave);
            }
        }
    }

    return resultado;
}


void cadastrarCurso(
    Arvore23 **raizCursos,
    Curso curso,
    int *flag
)
{
    Arvore23 *existe = NULL;

    *flag = 0;

    existe = buscar23(*raizCursos, curso.codigo);

    if (existe == NULL) {

        Info info;

        curso.raizdisciplinas = NULL;

        info.chave = curso.codigo;
        info.tipo = 2;
        info.dado.curso = curso;

        inserirArvore23(raizCursos, info);

        *flag = 1;
    }
}

void cadastrarAluno(
    Arvore23 **raizAlunos,
    Arvore23 *raizCursos,
    Aluno aluno,
    int *flag
)
{
    Arvore23 *existeAluno = NULL;
    Arvore23 *existeCurso = NULL;

    *flag = 0;

    existeAluno = buscar23(*raizAlunos, aluno.matricula);

    existeCurso = buscar23(
        raizCursos,
        aluno.codigo_curso
    );

    if (
        existeAluno == NULL &&
        existeCurso != NULL &&
        (
            aluno.semestre == 1 ||
            aluno.semestre == 2
        )
    ) {

        Info info;

        info.chave = aluno.matricula;
        info.tipo = 1;
        info.dado.aluno = aluno;

        inserirArvore23(raizAlunos, info);

        *flag = 1;
    }
}

void cadastrarDisciplina(
    Arvore23 *raizCursos,
    int codigoCurso,
    Disciplina disciplina,
    int *flag
)
{
    Arvore23 *noCurso = NULL;

    *flag = 0;

    noCurso = buscar23(
        raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        Curso *curso = NULL;

        if (
            noCurso->info1.chave ==
            codigoCurso
        ) {
            curso =
            &(noCurso->info1.dado.curso);
        }
        else {
            curso =
            &(noCurso->info2.dado.curso);
        }

        if (
            disciplina.bloco <
            curso->qtdBlocos
        ) {

            if (
                disciplina.cargahr %
                curso->semanas == 0
            ) {

                Arvore23 *existeDisciplina;

                existeDisciplina =
                buscar23(
                    curso->raizdisciplinas,
                    disciplina.codigo
                );

                if (
                    existeDisciplina == NULL
                ) {

                    Info info;

                    info.chave =
                    disciplina.codigo;

                    info.tipo = 3;

                    info.dado.disciplina =
                    disciplina;

                    inserirArvore23(
                        &(curso->raizdisciplinas),
                        info
                    );

                    *flag = 1;
                }
            }
        }
    }
}


// aux função 1

void coletarAlunos(
    Arvore23 *raiz,
    int codigoCurso,
    int anoIngresso,
    int filtrarAno,
    Aluno *resultado,
    int *quantidade
)
{
    if (raiz != NULL) {

        coletarAlunos(raiz->esq, codigoCurso, anoIngresso, filtrarAno, resultado, quantidade);

        if (raiz->info1.tipo == 1 &&
            raiz->info1.dado.aluno.codigo_curso == codigoCurso)
        {
            if (!filtrarAno || raiz->info1.dado.aluno.anoingresso == anoIngresso) {
                resultado[*quantidade] = raiz->info1.dado.aluno;
                (*quantidade)++;
            }
        }

        coletarAlunos(raiz->cent, codigoCurso, anoIngresso, filtrarAno, resultado, quantidade);

        if (raiz->nInfos == 2) {

            if (raiz->info2.tipo == 1 &&
                raiz->info2.dado.aluno.codigo_curso == codigoCurso)
            {
                if (!filtrarAno || raiz->info2.dado.aluno.anoingresso == anoIngresso) {
                    resultado[*quantidade] = raiz->info2.dado.aluno;
                    (*quantidade)++;
                }
            }

            coletarAlunos(raiz->dir, codigoCurso, anoIngresso, filtrarAno, resultado, quantidade);
        }
    }
}


// função 1
void listarAlunosPorCurso(
    Arvore23 *raizAlunos,
    int codigoCurso,
    Aluno *resultado,
    int *quantidade
)
{
    *quantidade = 0;
    coletarAlunos(raizAlunos, codigoCurso, 0, 0, resultado, quantidade);
}

// função 2
void listarAlunosPorCursoEAno(
    Arvore23 *raizAlunos,
    int codigoCurso,
    int anoIngresso,
    Aluno *resultado,
    int *quantidade
)
{
    *quantidade = 0;
    coletarAlunos(raizAlunos, codigoCurso, anoIngresso, 1, resultado, quantidade);
}

// Função 3
void contarAlunosPorCurso(
    Arvore23 *raizAlunos,
    int codigoCurso,
    int *quantidade
)
{
    if (raizAlunos != NULL) {

        contarAlunosPorCurso(raizAlunos->esq, codigoCurso, quantidade);

        if (raizAlunos->info1.tipo == 1 &&
            raizAlunos->info1.dado.aluno.codigo_curso == codigoCurso)
        {
            (*quantidade)++;
        }

        contarAlunosPorCurso(raizAlunos->cent, codigoCurso, quantidade);

        if (raizAlunos->nInfos == 2) {

            if (raizAlunos->info2.tipo == 1 &&
                raizAlunos->info2.dado.aluno.codigo_curso == codigoCurso)
            {
                (*quantidade)++;
            }

            contarAlunosPorCurso(raizAlunos->dir, codigoCurso, quantidade);
        }
    }
}

// Função 4
void listarCursosEmOrdem(
    Arvore23 *raizCursos,
    Curso *resultado,
    int *quantidade
)
{
    if (raizCursos != NULL) {

        listarCursosEmOrdem(raizCursos->esq, resultado, quantidade);

        if (raizCursos->info1.tipo == 2) {
            resultado[*quantidade] = raizCursos->info1.dado.curso;
            (*quantidade)++;
        }

        listarCursosEmOrdem(raizCursos->cent, resultado, quantidade);

        if (raizCursos->nInfos == 2) {

            if (raizCursos->info2.tipo == 2) {
                resultado[*quantidade] = raizCursos->info2.dado.curso;
                (*quantidade)++;
            }

            listarCursosEmOrdem(raizCursos->dir, resultado, quantidade);
        }
    }
}

// Função 5
void buscarDadosCurso(
    Arvore23 *raizCursos,
    int codigoCurso,
    Curso *resultado,
    int *encontrado
)
{
    Arvore23 *no = NULL;

    *encontrado = 0;

    no = buscar23(raizCursos, codigoCurso);

    if (no != NULL) {

        if (no->info1.chave == codigoCurso) {
            *resultado  = no->info1.dado.curso;
            *encontrado = 1;
        }
        else if (no->nInfos == 2 && no->info2.chave == codigoCurso) {
            *resultado  = no->info2.dado.curso;
            *encontrado = 1;
        }
    }
}
//função 6
void listarCursosqtdblocos(Arvore23 *raiz, int qtdBlocos
)
{
    if (raiz != NULL) {

        listarCursosqtdblocos(
            raiz->esq,
            qtdBlocos
        );

        if (
            raiz->info1.tipo == 2 &&
            raiz->info1.dado.curso.qtdBlocos == qtdBlocos
        ) {

            printf(
                "\nCodigo: %d",
                raiz->info1.dado.curso.codigo
            );

            printf(
                "\nNome: %s",
                raiz->info1.dado.curso.nome
            );

            printf(
                "\nQuantidade de blocos: %d\n",
                raiz->info1.dado.curso.qtdBlocos
            );
        }

        listarCursosqtdblocos(
            raiz->cent,
            qtdBlocos
        );

        if (raiz->nInfos == 2) {

            if (
                raiz->info2.tipo == 2 &&
                raiz->info2.dado.curso.qtdBlocos == qtdBlocos
            ) {

                printf(
                    "\nCodigo: %d",
                    raiz->info2.dado.curso.codigo
                );

                printf(
                    "\nNome: %s",
                    raiz->info2.dado.curso.nome
                );

                printf(
                    "\nQuantidade de blocos: %d\n",
                    raiz->info2.dado.curso.qtdBlocos
                );
            }
            listarCursosqtdblocos(
                raiz->dir,
                qtdBlocos
            );
        }
    }
}

//7
void imprimirDisciplinasEmOrdem(
    Arvore23 *raizDisciplinas
)
{
    if (raizDisciplinas != NULL) {

        imprimirDisciplinasEmOrdem(
            raizDisciplinas->esq
        );

        if (raizDisciplinas->info1.tipo == 3) {

            printf(
                "\nCodigo: %d",
                raizDisciplinas->info1.dado.disciplina.codigo
            );

            printf(
                "\nNome: %s",
                raizDisciplinas->info1.dado.disciplina.nome
            );

            printf(
                "\nBloco: %d",
                raizDisciplinas->info1.dado.disciplina.bloco
            );

            printf(
                "\nCarga Horaria: %d\n",
                raizDisciplinas->info1.dado.disciplina.cargahr
            );
        }

        imprimirDisciplinasEmOrdem(
            raizDisciplinas->cent
        );

        if (raizDisciplinas->nInfos == 2) {

            if (raizDisciplinas->info2.tipo == 3) {

                printf(
                    "\nCodigo: %d",
                    raizDisciplinas->info2.dado.disciplina.codigo
                );

                printf(
                    "\nNome: %s",
                    raizDisciplinas->info2.dado.disciplina.nome
                );

                printf(
                    "\nBloco: %d",
                    raizDisciplinas->info2.dado.disciplina.bloco
                );

                printf(
                    "\nCarga Horaria: %d\n",
                    raizDisciplinas->info2.dado.disciplina.cargahr
                );
            }

            imprimirDisciplinasEmOrdem(
                raizDisciplinas->dir
            );
        }
    }
}
// principal

void listarDisciplinasCurso(
    Arvore23 *raizCursos,
    int codigoCurso
)
{
    Arvore23 *noCurso = NULL;

    Curso *curso = NULL;

    noCurso = buscar23(
        raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        if (curso->raizdisciplinas != NULL) {

            imprimirDisciplinasEmOrdem(
                curso->raizdisciplinas
            );
        }
    }
}


//8
void DadosDisciplina(
    Arvore23 *noCurso,
    int codigoCurso,
    int codigoDisciplina
)
{
    Curso *curso = NULL;

    Arvore23 *disc = NULL;

    Disciplina d;

    if (noCurso != NULL) {

        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        disc = buscar23(
            curso->raizdisciplinas,
            codigoDisciplina
        );

        if (disc != NULL) {

            if (disc->info1.chave == codigoDisciplina)
                d = disc->info1.dado.disciplina;
            else
                d = disc->info2.dado.disciplina;

            printf("\nCodigo: %d", d.codigo);

            printf("\nNome: %s", d.nome);

            printf("\nBloco: %d", d.bloco);

            printf("\nCarga Horaria: %d\n", d.cargahr);
        }
    }
}
//9

// aux

void imprimirDisciplinasBloco(
    Arvore23 *raizDisciplinas,
    int bloco
)
{
    if (raizDisciplinas != NULL) {

        imprimirDisciplinasBloco(
            raizDisciplinas->esq,
            bloco
        );

        if (
            raizDisciplinas->info1.tipo == 3 &&
            raizDisciplinas->info1.dado.disciplina.bloco == bloco
        ) {

            printf(
                "\nCodigo: %d",
                raizDisciplinas->info1.dado.disciplina.codigo
            );

            printf(
                "\nNome: %s",
                raizDisciplinas->info1.dado.disciplina.nome
            );

            printf(
                "\nBloco: %d",
                raizDisciplinas->info1.dado.disciplina.bloco
            );

            printf(
                "\nCarga Horaria: %d\n",
                raizDisciplinas->info1.dado.disciplina.cargahr
            );
        }

        imprimirDisciplinasBloco(
            raizDisciplinas->cent,
            bloco
        );

        if (raizDisciplinas->nInfos == 2) {

            if (
                raizDisciplinas->info2.tipo == 3 &&
                raizDisciplinas->info2.dado.disciplina.bloco == bloco
            ) {

                printf(
                    "\nCodigo: %d",
                    raizDisciplinas->info2.dado.disciplina.codigo
                );

                printf(
                    "\nNome: %s",
                    raizDisciplinas->info2.dado.disciplina.nome
                );

                printf(
                    "\nBloco: %d",
                    raizDisciplinas->info2.dado.disciplina.bloco
                );

                printf(
                    "\nCarga Horaria: %d\n",
                    raizDisciplinas->info2.dado.disciplina.cargahr
                );
            }

            imprimirDisciplinasBloco(
                raizDisciplinas->dir,
                bloco
            );
        }
    }
}
///principal
// PRINCIPAL

void listarDisciplinasPorBlocoCurso(
    Arvore23 *raizCursos,
    int codigoCurso,
    int bloco
)
{
    Arvore23 *noCurso;

    Curso *curso;

    noCurso = buscar23(
        raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        imprimirDisciplinasBloco(
            curso->raizdisciplinas,
            bloco
        );
    }
}

//10
//aux:
void imprimirDisciplinasCargaHoraria(
    Arvore23 *raizDisciplinas,
    int cargahr
)
{
    if (raizDisciplinas != NULL) {

        imprimirDisciplinasCargaHoraria(
            raizDisciplinas->esq,
            cargahr
        );

        if (
            raizDisciplinas->info1.tipo == 3 &&
            raizDisciplinas->info1.dado.disciplina.cargahr == cargahr
        ) {

            printf(
                "\nCodigo: %d",
                raizDisciplinas->info1.dado.disciplina.codigo
            );

            printf(
                "\nNome: %s",
                raizDisciplinas->info1.dado.disciplina.nome
            );

            printf(
                "\nBloco: %d",
                raizDisciplinas->info1.dado.disciplina.bloco
            );

            printf(
                "\nCarga Horaria: %d\n",
                raizDisciplinas->info1.dado.disciplina.cargahr
            );
        }

        imprimirDisciplinasCargaHoraria(
            raizDisciplinas->cent,
            cargahr
        );

        if (raizDisciplinas->nInfos == 2) {

            if (
                raizDisciplinas->info2.tipo == 3 &&
                raizDisciplinas->info2.dado.disciplina.cargahr == cargahr
            ) {

                printf(
                    "\nCodigo: %d",
                    raizDisciplinas->info2.dado.disciplina.codigo
                );

                printf(
                    "\nNome: %s",
                    raizDisciplinas->info2.dado.disciplina.nome
                );

                printf(
                    "\nBloco: %d",
                    raizDisciplinas->info2.dado.disciplina.bloco
                );

                printf(
                    "\nCarga Horaria: %d\n",
                    raizDisciplinas->info2.dado.disciplina.cargahr
                );
            }

            imprimirDisciplinasCargaHoraria(
                raizDisciplinas->dir,
                cargahr
            );
        }
    }
}
//principal
void listarDisciplinasMesmoCH(
    Arvore23 *raizCursos,
    int codigoCurso,
    int cargahr
)
{
    Arvore23 *noCurso = NULL;

    Curso *curso = NULL;

    noCurso = buscar23(
        raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        if (curso->raizdisciplinas != NULL) {

            imprimirDisciplinasCargaHoraria(
                curso->raizdisciplinas,
                cargahr
            );
        }
    }
}



//11

// e o código do curso

int excluirDisciplinaCurso(Arvore23 *raizCursos,int codigoCurso,int codigoDisciplina
)
{
    int removeu = 0;

    Arvore23 *noCurso = NULL;

    Curso *curso = NULL;

    noCurso = buscar23(
        raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        
        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        
        if (
            buscar23(
                curso->raizdisciplinas,
                codigoDisciplina
            ) != NULL
        ) {

           
            removeu = arvore_2_3_remover(
                &(curso->raizdisciplinas),
                codigoDisciplina
            );
        }
    }

    return removeu;
}

//12



int excluirCurso(
    Arvore23 **raizCursos,
    int codigoCurso
)
{
    int removeu = 0;

    Arvore23 *noCurso = NULL;

    Curso *curso = NULL;

    noCurso = buscar23(
        *raizCursos,
        codigoCurso
    );

    if (noCurso != NULL) {

        
        if (noCurso->info1.chave == codigoCurso)
            curso = &(noCurso->info1.dado.curso);
        else
            curso = &(noCurso->info2.dado.curso);

        
        if (curso->raizdisciplinas == NULL) {

            removeu = arvore_2_3_remover(
                raizCursos,
                codigoCurso
            );
        }
    }

    return removeu;
}
