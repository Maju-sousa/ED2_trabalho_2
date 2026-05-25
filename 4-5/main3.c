#include "4-5.h"


static void lerStatus(int *st)
{
    char opc;
    do
    {
        printf("O bloco e livre ou ocupado? (L - Livre / O - Ocupado): ");
        scanf(" %c", &opc);

        if      (opc == 'L' || opc == 'l') *st = LIVRE;
        else if (opc == 'O' || opc == 'o') *st = OCUPADO;
        else
        {
            printf("Opcao invalida! Escolha 'L' (Livre) ou 'O' (Ocupado).\n");
            *st = -1;   
        }
    } while (*st != LIVRE && *st != OCUPADO);
}


static void lerEndFinal(long *endFinal, long endInicialAtual, long endMaximo)
{
    do
    {
        printf("Informe o endereco final do no (entre %ld e %ld): ",
               endInicialAtual, endMaximo);
        scanf("%ld", endFinal);

        if (*endFinal < endInicialAtual || *endFinal > endMaximo)
            printf("Valor invalido. O endereco deve estar entre %ld e %ld.\n",
                   endInicialAtual, endMaximo);
    } while (*endFinal < endInicialAtual || *endFinal > endMaximo);
}


static void cadastrarNos(Memoria **raiz, int totalBlocos)
{
    long endMaximo    = (long)totalBlocos * MB - 1;
    long endAtual     = 0;   
    long endFinal     = 0;
    int  blocoAtual   = 0;   
    int  blocoFinal   = 0;
    int  status       = -1;
    Info novaInfo;

    printf("\n--- Cadastro do primeiro no ---\n");
    printf("Endereco inicial = %ld (bloco 0)\n", endAtual);
    lerStatus(&status);

    lerEndFinal(&endFinal, endAtual, endMaximo);


    blocoFinal = (int)((endFinal + 1) / MB) - 1;

    criarInfo(&novaInfo, blocoAtual, blocoFinal, status);
    insereMemoria(raiz, novaInfo);

    endAtual   = endFinal + 1;
    blocoAtual = blocoFinal + 1;

    
    while (endFinal != endMaximo)
    {

        status = (status == LIVRE) ? OCUPADO : LIVRE;

        printf("\n--- Cadastro do proximo no (status: %s) ---\n",
               (status == LIVRE) ? "LIVRE" : "OCUPADO");
        printf("Endereco inicial = %ld (bloco %d)\n", endAtual, blocoAtual);

        lerEndFinal(&endFinal, endAtual, endMaximo);

        blocoFinal = (int)((endFinal + 1) / MB) - 1;

        criarInfo(&novaInfo, blocoAtual, blocoFinal, status);
        insereMemoria(raiz, novaInfo);

        endAtual   = endFinal + 1;
        blocoAtual = blocoFinal + 1;
    }
}

static void exibirMenu(int *op)
{
    printf("\n========================================\n");
    printf("  GERENCIADOR DE MEMORIA DINAMICA\n");
    printf("========================================\n");
    printf("1. Ver alocacoes de memoria\n");
    printf("2. Sair\n");
    printf("Escolha uma opcao (1-2): ");
    scanf("%d", op);
}

int main(void)
{
    Memoria *arvore     = NULL;
    int      totalBlocos = 0;
    int      op          = -1;

    printf("============================================\n");
    printf("   GERENCIADOR DE MEMORIA DINAMICA (4-5)   \n");
    printf("============================================\n");
    printf("Cada bloco logico possui 1 MByte.\n");

    printf("Informe o total de blocos da memoria: ");
    scanf("%d", &totalBlocos);

    while (totalBlocos <= 0)
    {
        printf("Valor invalido. Informe um numero de blocos positivo: ");
        scanf("%d", &totalBlocos);
    }

    cadastrarNos(&arvore, totalBlocos);

    while (op != 2)
    {
        exibirMenu(&op);

        switch (op)
        {
        case 1:
            printf("\n--- Alocacao de memoria ---\n");
            exibirInfos(arvore);
            break;

        case 2:
            liberaArv45(&arvore);
            printf("\nSaindo da aplicacao...\n");
            break;

        default:
            printf("\nOpcao invalida! Escolha 1 ou 2.\n");
            break;
        }
    }

    return 0;
}
