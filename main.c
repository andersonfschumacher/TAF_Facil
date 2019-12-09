#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~elo/IntroducaoComputacao/Manipulacao%20de%20arquivo.htm

/*** VERSãO 1.0 DO PROGRAMA PARA FACILITAR CONFECçõES DE ETIQUETAS PARA OS PAINéIS -- * -- * -- *

 Com esta versão é possível:
 1. criar etiquetas para um único componente ou
 2. criar etiquetas para um grupo de componentes.
 Um exemplo de utilização para a opção de grupo de componentes é  quando há um mesmo tipo de partida que
 se repete por várias páginas. Assim, é possível  colocar os componentes de apenas uma página que o programa
 replica para as demais!!!

 As etiquetas são gravadas em um arquivo de nome "aqui_suas_tags_fresquinhas.txt", neste arquivo cada tag
 está em uma linha, facilitando assim a importação para o software das etiquetas.
 Para cada componente adicionado é criada a tag do próprio componente e a tag dos fios.

 Os fios somente são nomeados com números de 1 a n, ou seja, ainda não é possível colocar letras nas etiquetas.


 O que esperar das próximas versões:
 i.   possibilidade de nomear o arquivo de saída;
 ii.  possibilidade de dividir as tags dos componentes das tags dos fios;
 iii. possibilidade de continuar um trabalho previamente iniciado;
 iv.  colocar opção de salvar os dados dos componentes em vetores para organizá-los por página no arquivo de saída;
 v.   colocar opção AGRUPAR POR CÓDIGO e a opção AGRUPAR POR PÁGINA;
 vi.  colocar o código do componente sempre em maiúsculo independente de como seja escrito;


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


    // limpa o conteúdo da variável codigo
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

    // limpa o conteúdo da variável codigo
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


    // criando a variável ponteiro para o arquivo
    FILE *pont_arq;

    // *** - *** - *** - *** - abrindo o arquivo *** - *** - *** - *** - *** - ***

    pont_arq = fopen("aqui_suas_tags_fresquinhas.txt", "w");
    if (pont_arq == NULL)
    {
        printf("Um erro ocorreu ao tentar criar o arquivo `aqui_suas_tags_fresquinhas.txt'.\n");
        system("pause");
        exit(-1);
    }
    //mensagem para o usuário
    printf("O arquivo .txt foi criado com sucesso!\n");
    printf("\n\n\n\n");

    // *** - *** - *** - *** - abrindo o arquivo *** - *** - *** - *** - *** - ***

    //chama a função menu e abre a opção escolhida
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
