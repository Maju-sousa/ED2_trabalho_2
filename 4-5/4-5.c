#include "4-5.h"


void criarInfo(Info *info, int blocoInicial, int blocoFinal, int status)
{
    info->blocoInicial = blocoInicial;
    info->blocoFinal   = blocoFinal;
    info->endInicial   = (long)blocoInicial * MB;
    info->endFinal     = (long)(blocoFinal + 1) * MB - 1;
    info->status       = status;
}


void criarNo(Memoria **no, Info info, Memoria *filho1, Memoria *filho2)
{
    *no = (Memoria *)malloc(sizeof(Memoria));
    if (*no == NULL)
        return;

    (*no)->info1  = info;
    (*no)->info2  = (*no)->info3 = (*no)->info4 = (Info){0, 0, 0, 0, 0};
    (*no)->nInfos = 1;

    (*no)->filho1 = filho1;
    (*no)->filho2 = filho2;
    (*no)->filho3 = (*no)->filho4 = (*no)->filho5 = NULL;
}


static int ehFolha(const Memoria *no)
{
    return (no != NULL && no->filho1 == NULL);
}


void adicionaInfo(Memoria **no, Info info, Memoria *filho)
{
    if ((*no)->nInfos == 1)
    {
        (*no)->info2  = info;
        (*no)->filho3 = filho;
    }
    else if ((*no)->nInfos == 2)
    {
        (*no)->info3  = info;
        (*no)->filho4 = filho;
    }
    else if ((*no)->nInfos == 3)
    {
        (*no)->info4  = info;
        (*no)->filho5 = filho;
    }
    (*no)->nInfos++;
}


void quebraNo(Memoria **no, Info novaInfo, Memoria *filho,
              Info *sobe, Memoria **maior)
{
    *sobe = (*no)->info3;

    criarNo(maior, (*no)->info4, (*no)->filho4, (*no)->filho5);
    adicionaInfo(maior, novaInfo, filho);

    (*no)->info3  = (*no)->info4  = (Info){0, 0, 0, 0, 0};
    (*no)->nInfos = 2;
    (*no)->filho4 = (*no)->filho5 = NULL;
}


void insereArv45(Memoria **raiz, Info info, Memoria *pai,
                 Info *sobe, Memoria **retorno)
{
    Memoria *maior = NULL;

    if (*raiz == NULL)
    {
        criarNo(raiz, info, NULL, NULL);
        *retorno = NULL;
        return;
    }

    if (ehFolha(*raiz))
    {
        if ((*raiz)->nInfos < 4)
        {
            adicionaInfo(raiz, info, NULL);
            *retorno = NULL;
        }
        else
        {
            quebraNo(raiz, info, NULL, sobe, &maior);
            if (pai == NULL)
            {
                Memoria *novaRaiz = NULL;
                criarNo(&novaRaiz, *sobe, *raiz, maior);
                *raiz    = novaRaiz;
                *retorno = NULL;
            }
            else
            {
                *retorno = maior;
            }
        }
    }
    else
    {
        if ((*raiz)->nInfos == 1)
            insereArv45(&((*raiz)->filho2), info, *raiz, sobe, &maior);
        else if ((*raiz)->nInfos == 2)
            insereArv45(&((*raiz)->filho3), info, *raiz, sobe, &maior);
        else if ((*raiz)->nInfos == 3)
            insereArv45(&((*raiz)->filho4), info, *raiz, sobe, &maior);
        else
            insereArv45(&((*raiz)->filho5), info, *raiz, sobe, &maior);

        if (maior != NULL)
        {
            if ((*raiz)->nInfos < 4)
            {
                adicionaInfo(raiz, *sobe, maior);
                *retorno = NULL;
            }
            else
            {
                quebraNo(raiz, *sobe, maior, sobe, &maior);
                if (pai == NULL)
                {
                    Memoria *novaRaiz = NULL;
                    criarNo(&novaRaiz, *sobe, *raiz, maior);
                    *raiz    = novaRaiz;
                    *retorno = NULL;
                }
                else
                {
                    *retorno = maior;
                }
            }
        }
        else
        {
            *retorno = NULL;
        }
    }
}


void insereMemoria(Memoria **raiz, Info info)
{
    Info    sobe    = {0, 0, 0, 0, 0};
    Memoria *retorno = NULL;
    insereArv45(raiz, info, NULL, &sobe, &retorno);
}


static const char *statusStr(int status)
{
    return (status == LIVRE) ? "LIVRE" : "OCUPADO";
}

void exibirInfos(Memoria *raiz)
{
    if (raiz == NULL)
        return;

    exibirInfos(raiz->filho1);
    printf("Status: %-8s | Blocos: %4d - %4d | End. inicial: %12ld bytes | End. final: %12ld bytes\n",
           statusStr(raiz->info1.status),
           raiz->info1.blocoInicial, raiz->info1.blocoFinal,
           raiz->info1.endInicial,   raiz->info1.endFinal);

    exibirInfos(raiz->filho2);

    if (raiz->nInfos >= 2)
    {
        printf("Status: %-8s | Blocos: %4d - %4d | End. inicial: %12ld bytes | End. final: %12ld bytes\n",
               statusStr(raiz->info2.status),
               raiz->info2.blocoInicial, raiz->info2.blocoFinal,
               raiz->info2.endInicial,   raiz->info2.endFinal);
        exibirInfos(raiz->filho3);
    }
    if (raiz->nInfos >= 3)
    {
        printf("Status: %-8s | Blocos: %4d - %4d | End. inicial: %12ld bytes | End. final: %12ld bytes\n",
               statusStr(raiz->info3.status),
               raiz->info3.blocoInicial, raiz->info3.blocoFinal,
               raiz->info3.endInicial,   raiz->info3.endFinal);
        exibirInfos(raiz->filho4);
    }
    if (raiz->nInfos >= 4)
    {
        printf("Status: %-8s | Blocos: %4d - %4d | End. inicial: %12ld bytes | End. final: %12ld bytes\n",
               statusStr(raiz->info4.status),
               raiz->info4.blocoInicial, raiz->info4.blocoFinal,
               raiz->info4.endInicial,   raiz->info4.endFinal);
        exibirInfos(raiz->filho5);
    }
}


void liberaArv45(Memoria **raiz)
{
    if (*raiz == NULL)
        return;

    liberaArv45(&((*raiz)->filho1));
    liberaArv45(&((*raiz)->filho2));
    liberaArv45(&((*raiz)->filho3));
    liberaArv45(&((*raiz)->filho4));
    liberaArv45(&((*raiz)->filho5));

    free(*raiz);
    *raiz = NULL;
}
