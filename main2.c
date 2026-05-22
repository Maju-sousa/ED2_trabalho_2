#include "arv.2-3.h"

int main()
{
    Arvore23 *raizCursos = NULL;
    Arvore23 *raizAlunos = NULL;

    int opcao = -1;
    int flag  = 0;

    while (opcao != 0) {

        printf("\n==============================");
        printf("\n        MENU PRINCIPAL");
        printf("\n==============================");

        printf("\n1 - Cadastrar Curso");
        printf("\n2 - Cadastrar Disciplina");
        printf("\n3 - Cadastrar Aluno");
        
        // Essas funções são só pra testar curso, disciplina e aluno(vou remover amanhã)
        printf("\n4 - Exibir Cursos");
        printf("\n5 - Exibir Alunos");
        printf("\n6 - Exibir Disciplinas de um Curso");

        printf("\n0 - Sair");

        printf("\n\nOpcao: ");
        scanf("%d", &opcao);

        system("cls");

        switch(opcao) {

      
        case 1:
        {
            Curso curso; 

            printf("\n===== CADASTRAR CURSO =====\n");

            printf("Codigo: ");
            scanf("%d", &curso.codigo);

            getchar();

            printf("Nome: ");
            fgets(curso.nome, 50, stdin);

            curso.nome[strcspn(curso.nome, "\n")] = '\0';

            printf("Quantidade de blocos: ");
            scanf("%d", &curso.qtdBlocos);

            printf("Numero de semanas: ");
            scanf("%d", &curso.semanas);

            cadastrarCurso(
                &raizCursos,
                curso,
                &flag
            );

            if (flag) {
                printf("\nCurso cadastrado com sucesso!\n");
            }
            else {
                printf("\nErro ao cadastrar curso.\n");
            }

            break;
        }

        
        case 2:
        {
            Disciplina disciplina;

            int codigoCurso;

            printf("\n===== CADASTRAR DISCIPLINA =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            printf("Codigo da disciplina: ");
            scanf("%d", &disciplina.codigo);

            getchar();

            printf("Nome da disciplina: ");
            fgets(disciplina.nome, 50, stdin);

            disciplina.nome[
                strcspn(
                    disciplina.nome,
                    "\n"
                )
            ] = '\0';

            printf("Bloco da disciplina: ");
            scanf("%d", &disciplina.bloco);

            printf("Carga horaria: ");
            scanf("%d", &disciplina.cargahr);

            cadastrarDisciplina(
                raizCursos,
                codigoCurso,
                disciplina,
                &flag
            );

            if (flag) {
                printf(
                    "\nDisciplina cadastrada com sucesso!\n"
                );
            }
            else {
                printf(
                    "\nErro ao cadastrar disciplina.\n"
                );
            }

            break;
        }

       
        case 3:
        {
            Aluno aluno;

            printf("\n===== CADASTRAR ALUNO =====\n");

            printf("Matricula: ");
            scanf("%d", &aluno.matricula);

            getchar();

            printf("Nome: ");
            fgets(aluno.nome, 50, stdin);

            aluno.nome[
                strcspn(
                    aluno.nome,
                    "\n"
                )
            ] = '\0';

            printf("Codigo do curso: ");
            scanf("%d", &aluno.codigo_curso);

            printf("Ano de ingresso: ");
            scanf("%d", &aluno.anoingresso);

            printf("Semestre de ingresso (1 ou 2): ");
            scanf("%d", &aluno.semestre);

            cadastrarAluno(
                &raizAlunos,
                raizCursos,
                aluno,
                &flag
            );

            if (flag) {
                printf(
                    "\nAluno cadastrado com sucesso!\n"
                );
            }
            else {
                printf(
                    "\nErro ao cadastrar aluno.\n"
                );
            }

            break;
        }

        
        case 4:
        {
            printf("\n===== CURSOS =====\n");

            if (raizCursos != NULL) {

                exibir_Arvore23(
                    raizCursos,
                    exibirCurso
                );
            }
            else {
                printf("\nNenhum curso cadastrado.\n");
            }

            break;
        }

        
        case 5:
        {
            printf("\n===== ALUNOS =====\n");

            if (raizAlunos != NULL) {

                exibir_Arvore23(
                    raizAlunos,
                    exibirAluno
                );
            }
            else {
                printf("\nNenhum aluno cadastrado.\n");
            }

            break;
        }

       
        case 6:
        {
            int codigoCurso;

            Arvore23 *noCurso = NULL;

            Curso *curso = NULL;

            printf(
                "\n===== DISCIPLINAS DO CURSO =====\n"
            );

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            noCurso = buscar23(
                raizCursos,
                codigoCurso
            );

            if (noCurso != NULL) {

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
                    curso->raizdisciplinas != NULL
                ) {

                    exibir_Arvore23(
                        curso->raizdisciplinas,
                        exibirDisciplina
                    );
                }
                else {

                    printf(
                        "\nNenhuma disciplina cadastrada.\n"
                    );
                }
            }
            else {

                printf(
                    "\nCurso nao encontrado.\n"
                );
            }

            break;
        }

       

        case 0:
        {
            printf("\nEncerrando...\n");
            break;
        }

        
        default:
        {
            printf("\nOpcao invalida.\n");
        }

        }

        printf("\n");
        system("pause");
        system("cls");
    }

    freeTree(&raizCursos);

    freeTree(&raizAlunos);

    return 0;
}