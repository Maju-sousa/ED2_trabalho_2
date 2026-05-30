#include "arv.2-3.h"

int main()
{
    Arvore23 *raizCursos = NULL;
    Arvore23 *raizAlunos = NULL;

    int opcao = -1;
    int flag  = 0;

    while (opcao != 0) {

      
        printf("\n  MENU PRINCIPAL");
    

        printf("\n1  - Cadastrar Curso");
        printf("\n2  - Cadastrar Disciplina");
        printf("\n3  - Cadastrar Aluno");
        printf("\n4  - Listar Alunos por Curso");
        printf("\n5  - Listar Alunos por Curso e Ano de Ingresso");
        printf("\n6  - Contar Alunos de um Curso");
        printf("\n7  - Listar Cursos em Ordem Crescente");
        printf("\n8  - Exibir Dados de um Curso");
        printf("\n9  - Listar Cursos por Quantidade de Blocos");
        printf("\n10 - Listar Disciplinas de um Curso em Ordem");
        printf("\n11 - Exibir Dados de uma Disciplina");
        printf("\n12 - Listar Disciplinas de um Bloco");
        printf("\n13 - Listar Disciplinas por Carga Horaria");
        printf("\n14 - Excluir Disciplina de um Curso");
        printf("\n15 - Excluir Curso");
        printf("\n0  - Sair");

        printf("\n\nOpcao: ");
        scanf("%d", &opcao);

        system("cls");

        switch(opcao) {

        case 1:
        {
            Curso curso;

            printf("\n CADASTRAR CURSO \n");

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

            cadastrarCurso(&raizCursos, curso, &flag);

            if (flag)
                printf("\nCurso cadastrado com sucesso!\n");
            else
                printf("\nErro ao cadastrar curso.\n");

            break;
        }

    case 2:{
       Disciplina disciplina;
       int codigoCurso;

      printf("\n CADASTRAR DISCIPLINA \n");

      printf("Codigo do curso: ");
      scanf("%d", &codigoCurso);

      Arvore23 *cursoExiste= buscar23(
            raizCursos,
            codigoCurso
        );

      if (cursoExiste == NULL) {

        printf("\nCurso nao encontrado.\n");

     } else {

        Curso *curso;

        if (cursoExiste->info1.chave == codigoCurso)
            curso = &(cursoExiste->info1.dado.curso);
        else
            curso = &(cursoExiste->info2.dado.curso);

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

        do {

            printf(
                "Bloco (0 ate %d): ",
                curso->qtdBlocos - 1
            );

            scanf("%d", &disciplina.bloco);

            if (
                disciplina.bloco < 0 ||
                disciplina.bloco >= curso->qtdBlocos
            ) {
                printf("Bloco invalido.\n");
            }

        } while (
            disciplina.bloco < 0 ||
            disciplina.bloco >= curso->qtdBlocos
        );

        do {

            printf(
                "Carga horaria (multiplo de %d): ",
                curso->semanas
            );

            scanf("%d", &disciplina.cargahr);

            if (
                disciplina.cargahr <= 0 ||
                disciplina.cargahr % curso->semanas != 0
            ) {
                printf("Carga horaria invalida.\n");
            }

        } while (
            disciplina.cargahr <= 0 ||
            disciplina.cargahr % curso->semanas != 0
        );

        cadastrarDisciplina(
            raizCursos,
            codigoCurso,
            disciplina,
            &flag
        );

        if (flag)
            printf(
                "\nDisciplina cadastrada com sucesso!\n"
            );
        else
            printf(
                "\nErro ao cadastrar disciplina.\n"
            );
          }

           break;
        }

       
         case 3:{
          Aluno aluno;

          printf("\n CADASTRAR ALUNO \n");

          printf("Matricula: ");
          scanf("%d", &aluno.matricula);

          getchar();

          printf("Nome: ");
          fgets(aluno.nome, 50, stdin);

          aluno.nome[strcspn( aluno.nome, "\n" )] = '\0';

          printf("Codigo do curso: ");
          scanf("%d", &aluno.codigo_curso);

          Arvore23 *cursoExiste = buscar23( raizCursos,aluno.codigo_curso);

           if (cursoExiste == NULL) {

           printf("\nCurso nao encontrado.\n");

           } else {

          do {

            printf("Ano de ingresso: ");
            scanf("%d", &aluno.anoingresso);

            if (aluno.anoingresso <= 0)
                printf("Ano invalido.\n");

        } while (
            aluno.anoingresso <= 0
        );

        do {

            printf(
                "Semestre de ingresso (1 ou 2): "
            );

            scanf("%d", &aluno.semestre);

            if (
                aluno.semestre != 1 &&
                aluno.semestre != 2
            ) {
                printf("Semestre invalido.\n");
            }

        } while (
            aluno.semestre != 1 &&
            aluno.semestre != 2
        );

        cadastrarAluno(
            &raizAlunos,
            raizCursos,
            aluno,
            &flag
        );

        if (flag)
            printf(
                "\nAluno cadastrado com sucesso!\n"
            );
        else
            printf(
                "\nErro ao cadastrar aluno.\n"
            );
        }

         break;
        }

    case 4:{
      int codigoCurso;
      int quantidade = 0;
      Aluno resultado[1000];

      printf("\n===== LISTAR ALUNOS POR CURSO =====\n");

      printf("Codigo do curso: ");
      scanf("%d", &codigoCurso);

     Arvore23 *cursoExiste = buscar23(
        raizCursos,
        codigoCurso);

     if (cursoExiste == NULL) {

        printf("\nCurso nao encontrado.\n");

     } else {

        listarAlunosPorCurso(
            raizAlunos,
            codigoCurso,
            resultado,
            &quantidade
        );

        if (quantidade == 0) {

            printf(
                "\nNenhum aluno encontrado para este curso.\n"
            );

        } else {

            printf(
                "\n%-15s %-50s\n",
                "Matricula",
                "Nome"
            );

            int i;

            for (i = 0; i < quantidade; i++) {

                printf(
                    "%-15d %-50s\n",
                    resultado[i].matricula,
                    resultado[i].nome
                );
            }

            printf("\nTotal: %d aluno(s).\n",   quantidade);
           }
        }

        break;
       }

        case 5:{
        int codigoCurso;
        int anoIngresso;
        int quantidade = 0;
        Aluno resultado[1000];

       printf("\n===== LISTAR ALUNOS POR CURSO E ANO DE INGRESSO =====\n" );

       printf("Codigo do curso: ");
       scanf("%d", &codigoCurso);

       printf("Ano de ingresso: ");
       scanf("%d", &anoIngresso);

       Arvore23 *cursoExiste = buscar23(
        raizCursos,
        codigoCurso);

       if (cursoExiste == NULL) {

        printf("\nCurso nao encontrado.\n");

       } else {

        listarAlunosPorCursoEAno(
            raizAlunos,
            codigoCurso,
            anoIngresso,
            resultado,
            &quantidade
        );

        if (quantidade == 0) {

            printf(
                "\nNenhum aluno encontrado para este curso e ano.\n"
            );

        } else {

            printf(
                "\n%-15s %-50s\n",
                "Matricula",
                "Nome"
            );

            int i;

            for (i = 0; i < quantidade; i++) {

                printf(
                    "%-15d %-50s\n",
                    resultado[i].matricula,
                    resultado[i].nome
                );
            }

             printf("\nTotal: %d aluno(s).\n", quantidade);
           }
         }

          break;
        }
        case 6:
        {
            int codigoCurso;
            int quantidade = 0;

            printf("\n===== CONTAR ALUNOS DE UM CURSO =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            contarAlunosPorCurso(raizAlunos, codigoCurso, &quantidade);

            printf("\nO curso de codigo %d possui %d aluno(s).\n",
                codigoCurso, quantidade);
            }
            break;
        }

        case 7:
        {
            int quantidade = 0;
            Curso resultado[1000];

            printf("\n===== CURSOS EM ORDEM CRESCENTE =====\n");

            listarCursosEmOrdem(raizCursos, resultado, &quantidade);

            if (quantidade == 0) {
                printf("\nNenhum curso cadastrado.\n");
            } else {
                printf("\n%-10s %-50s %-10s %-10s\n",
                    "Codigo", "Nome", "Blocos", "Semanas");
                printf("---------------------------------------------------------------\n");

                int i;
                for (i = 0; i < quantidade; i++) {
                    printf("%-10d %-50s %-10d %-10d\n",
                        resultado[i].codigo,
                        resultado[i].nome,
                        resultado[i].qtdBlocos,
                        resultado[i].semanas);
                }

                printf("\nTotal: %d curso(s).\n", quantidade);
            }

            break;
        }

        case 8:
        {
            int codigoCurso;
            int encontrado = 0;
            Curso resultado;

            printf("\n===== EXIBIR DADOS DE UM CURSO =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            buscarDadosCurso(raizCursos, codigoCurso, &resultado, &encontrado);

            if (!encontrado) {
                printf("\nCurso nao encontrado.\n");
            } else {
                printf("\n---------------------------------------------------------------\n");
                printf("Codigo  : %d\n", resultado.codigo);
                printf("Nome    : %s\n", resultado.nome);
                printf("Blocos  : %d\n", resultado.qtdBlocos);
                printf("Semanas : %d\n", resultado.semanas);
                printf("---------------------------------------------------------------\n");
            }

            break;
        }

        case 9:
        {
            int qtdBlocos;

            printf("\n===== LISTAR CURSOS POR QUANTIDADE DE BLOCOS =====\n");

            printf("Quantidade de blocos: ");
            scanf("%d", &qtdBlocos);

            if (raizCursos == NULL) {
                printf("\nNenhum curso cadastrado.\n");
                
            }else{

            printf("\n---------------------------------------------------------------\n");
            printf("Cursos com %d bloco(s):\n", qtdBlocos);
            printf("---------------------------------------------------------------\n");

            listarCursosqtdblocos(raizCursos, qtdBlocos);

            printf("\n---------------------------------------------------------------\n");
            }
            break;
        }

        case 10:
        {
            int codigoCurso;

            printf("\n===== LISTAR DISCIPLINAS DE UM CURSO EM ORDEM =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            printf("\n---------------------------------------------------------------\n");
            printf("Disciplinas do curso %d em ordem crescente:\n", codigoCurso);
            printf("---------------------------------------------------------------\n");

            listarDisciplinasCurso(raizCursos, codigoCurso);

            printf("\n---------------------------------------------------------------\n");
            }
            break;
        }

        case 11:
        {
            int codigoCurso;
            int codigoDisciplina;
            int encontrado = 0;
            Disciplina resultado;

            printf("\n===== EXIBIR DADOS DE UMA DISCIPLINA =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            printf("Codigo da disciplina: ");
            scanf("%d", &codigoDisciplina);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            buscarDadosDisciplina(
                raizCursos,
                codigoCurso,
                codigoDisciplina,
                &resultado,
                &encontrado
            );

            if (!encontrado) {
                printf("\nDisciplina nao encontrada.\n");
            } else {
                
                printf("Codigo        : %d\n", resultado.codigo);
                printf("Nome          : %s\n", resultado.nome);
                printf("Bloco         : %d\n", resultado.bloco);
                printf("Carga Horaria : %d\n", resultado.cargahr);
            }
            }
            break;
        }

        case 12:
        {
            int codigoCurso;
            int bloco;
            int quantidade = 0;
            Disciplina resultado[1000];

            printf("\nLISTAR DISCIPLINAS DE UM BLOCO\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            printf("Bloco: ");
            scanf("%d", &bloco);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            listarDisciplinasPorBloco(
                raizCursos,
                codigoCurso,
                bloco,
                resultado,
                &quantidade
            );

            if (quantidade == 0) {
                printf("\nNenhuma disciplina encontrada para este bloco.\n");
            } else {
                printf("\n%-10s %-50s %-10s %-15s\n",
                    "Codigo", "Nome", "Bloco", "Carga Horaria");
            

                int i;
                for (i = 0; i < quantidade; i++) {
                    printf("%-10d %-50s %-10d %-15d\n",
                        resultado[i].codigo,
                        resultado[i].nome,
                        resultado[i].bloco,
                        resultado[i].cargahr);
                }

                printf("\nTotal: %d disciplina(s).\n", quantidade);
            }
            }
            break;
        }

        case 13:
        {
            int codigoCurso;
            int cargahr;

            printf("\n===== LISTAR DISCIPLINAS POR CARGA HORARIA =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            printf("Carga horaria: ");
            scanf("%d", &cargahr);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            printf("\n---------------------------------------------------------------\n");
            printf("Disciplinas do curso %d com carga horaria %d:\n",
                codigoCurso, cargahr);
            printf("---------------------------------------------------------------\n");

            listarDisciplinasMesmoCH(raizCursos, codigoCurso, cargahr);

            printf("\n---------------------------------------------------------------\n");
            }
            break;
        }

        case 14:
        {
            int codigoCurso;
            int codigoDisciplina;
            int removeu = 0;

            printf("\n===== EXCLUIR DISCIPLINA DE UM CURSO =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            printf("Codigo da disciplina: ");
            scanf("%d", &codigoDisciplina);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
               
            }else{

            removeu = excluirDisciplinaCurso(
                raizCursos,
                codigoCurso,
                codigoDisciplina
            );

            if (removeu)
                printf("\nDisciplina removida com sucesso!\n");
            else
                printf("\nDisciplina nao encontrada.\n");
            }
            break;
        }

        case 15:
        {
            int codigoCurso;
            int removeu = 0;

            printf("\n===== EXCLUIR CURSO =====\n");

            printf("Codigo do curso: ");
            scanf("%d", &codigoCurso);

            Arvore23 *cursoExiste = buscar23(raizCursos, codigoCurso);

            if (cursoExiste == NULL) {
                printf("\nCurso nao encontrado.\n");
                
            }else{

            removeu = excluirCurso(&raizCursos, codigoCurso);

            if (removeu)
                printf("\nCurso removido com sucesso!\n");
            else
                printf("\nNao e possivel remover: o curso ainda possui disciplinas cadastradas.\n");
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
