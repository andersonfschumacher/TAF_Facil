#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~elo/IntroducaoComputacao/Manipulacao%20de%20arquivo.htm

/*** VERS�O 1.0 DO PROGRAMA PARA FACILITAR CONFEC��ES DE ETIQUETAS PARA OS PAIN�IS -- * -- * -- *

 Com esta vers�o � poss�vel:
 1. criar etiquetas para um �nico componente ou
 2. criar etiquetas para um grupo de componentes.
 Um exemplo de utiliza��o para a op��o de grupo de componentes �  quando h� um mesmo tipo de partida que
 se repete por v�rias p�ginas. Assim, � poss�vel  colocar os componentes de apenas uma p�gina que o programa
 replica para as demais!!!

 As etiquetas s�o gravadas em um arquivo de nome "aqui_suas_tags_fresquinhas.txt", neste arquivo cada tag
 est� em uma linha, facilitando assim a importa��o para o software das etiquetas.
 Para cada componente adicionado � criada a tag do pr�prio componente e a tag dos fios.

 Os fios somente s�o nomeados com n�meros de 1 a n, ou seja, ainda n�o � poss�vel colocar letras nas etiquetas.


 O que esperar das pr�ximas vers�es:
 i.   possibilidade de nomear o arquivo de sa�da;
 ii.  possibilidade de dividir as tags dos componentes das tags dos fios;
 iii. possibilidade de continuar um trabalho previamente iniciado;
 iv.  colocar op��o de salvar os dados dos componentes em vetores para organiz�-los por p�gina no arquivo de sa�da;
 v.   colocar op��o AGRUPAR POR C�DIGO e a op��o AGRUPAR POR P�GINA;
 vi.  colocar o c�digo do componente sempre em mai�sculo independente de como seja escrito;


 by Anderson Schumacher
  -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- * -- *     ***/

unsigned menu();
void componenteUnico(pont_arq);
void grupoComponentes(pont_arq);

unsigned menu(){

    system("cls");
    unsigned opcao;
    // menu
    do{
        printf("Etiquetas para quantos componentes?\n");
        printf("1 - Apenas um!\n");
        printf("2 - Para um grupo de componentes;\n");
        printf("3 - Sair.\n");
        printf("(Coloque abaixo o numero correspondente a opcao desejada)\n")/
        printf("Opcao: ");
        fscanf(stdin, "%d", &opcao);
        fflush(stdin);
    }while((opcao != 1) && (opcao != 2) && (opcao != 3));

    return opcao;
}

void componenteUnico(FILE* pont_arq){

    char *codigo = (char *) malloc(4*sizeof(char));
    unsigned i;
    int pag,col, fios, pagFinal;


    // limpa o conte�do da vari�vel codigo
    for(i=0;i<3*sizeof(char);i++){
        *codigo = NULL;
    }

    printf("Insira o cod. do componente: ");
    scanf("%s", codigo);
    fflush(stdin);

    printf("Insira o numero da pagina da TAG: ");
    scanf("%d", &pag);

    printf("Insira o numero da coluna do componente: ");
    scanf("%d", &col);

    printf("Insira o numero de fios do componente: ");
    scanf("%d", &fios);

    printf("Ate qual pagina este componente se repete?\n");
    scanf("%d", &pagFinal);

    do{
        for(i=0;i<fios;i++){

            fprintf(pont_arq,"%s", codigo);
            fprintf(pont_arq,"%d", pag);
            fprintf(pont_arq,".");
            fprintf(pont_arq,"%d", col);
            fprintf(pont_arq,"-");
            fprintf(pont_arq,"%d", i+1);
            fprintf(pont_arq,"\n");
        }
        pag++;
    }while(pag<=pagFinal);

    codigo = NULL;
}

void grupoComponentes(pont_arq){

    char *codigo = (char *) malloc(4*sizeof(char));
    unsigned i;
    int pag,col, fios, pagFinal, numComp=0, aux;

    // limpa o conte�do da vari�vel codigo
    for(i=0;i<3*sizeof(char);i++){
        *codigo = NULL;
    }

    printf("Insira o numero da pagina em que o grupo de componentes se inicia: ");
    scanf("%d", &pag);

    printf("Insira o numero da pagina em que este grupo termina: ");
    scanf("%d", &pagFinal);
    do{
        aux = pag;
        numComp++;
        printf("Insira o cod. do %do componente: ", numComp);
        scanf("%s", codigo);
        fflush(stdin);

        printf("Insira o numero da coluna do %do componente: ", numComp);
        scanf("%d", &col);

        printf("Insira o numero de fios do %do componente: ", numComp);
        scanf("%d", &fios);

        printf("\n");

        do{
            for(i=0;i<fios;i++){

                fprintf(pont_arq,"%s", codigo);
                fprintf(pont_arq,"%d", aux);
                fprintf(pont_arq,".");
                fprintf(pont_arq,"%d", col);
                fprintf(pont_arq,"-");
                fprintf(pont_arq,"%d", i+1);
                fprintf(pont_arq,"\n");
            }
            aux++;
        }while(aux<=pagFinal);
    }while(fios != 0);

    codigo = NULL;
}


int main(void)
{
    unsigned sair=0;


    // criando a vari�vel ponteiro para o arquivo
    FILE *pont_arq;

    // *** - *** - *** - *** - abrindo o arquivo *** - *** - *** - *** - *** - ***

    pont_arq = fopen("aqui_suas_tags_fresquinhas.txt", "w");
    if (pont_arq == NULL)
    {
        printf("Um erro ocorreu ao tentar criar o arquivo `aqui_suas_tags_fresquinhas.txt'.\n");
        system("pause");
        exit(-1);
    }
    //mensagem para o usu�rio
    printf("O arquivo .txt foi criado com sucesso!\n");
    printf("\n\n\n\n");

    // *** - *** - *** - *** - abrindo o arquivo *** - *** - *** - *** - *** - ***

    //chama a fun��o menu e abre a op��o escolhida
    do{
        switch (menu()){
            case 1:
                componenteUnico(pont_arq);
            break;

            case 2:
                grupoComponentes(pont_arq);
            break;

            case 3:// opcao sair
                sair = 1;
            break;

            default:

            break;
        }
    }while(sair != 1);

    // fechando arquivo
    fclose(pont_arq);
    printf("\n\n\nArquivo fechado");
    return(0);
}
