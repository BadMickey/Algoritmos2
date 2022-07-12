/*
Esse c�digo � de um compilador sint�tico, em que ele ir� pegar um arquivo.txt e ir� verificar se o c�digo presente nele est� de acordo com o padr�o exigido. 
Apenas ir� verificar comandos b�sicos como os de declara��o de vari�vel, abertura de blocos como os if's, else's e fun��es.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int linhas_lidas = 0;

void transformar_minusculo(char linha[])//Essa fun��o ir� transformar tudo em min�sculo.
{
    int i = 0;
    while(linha[i]!='\0')
    {
        linha[i] = tolower(linha[i]);
        i++;
    }
    linha[i]='\0';
}

void preparar_linha(char linha[])//Essa fun��o ir� remover a identa��o para facilitar a leitura, depois chamar� outra fun��o para espa�os.
{
    int i = 0;
    int ident = -1;
    while(linha[i]==' ')
    {
        ident++;
        i++;
    }
    if(ident>=0)
    {
        for(i=0; i<strlen(linha); i++)
        {
            ident++;
            linha[i]=linha[ident];
        }
    }
    tirar_espacos(linha);
}

void tirar_espacos(char linha[])//Essa fun��o remover� espa�os duplos no c�digo, acima disso o c�digo ir� parar.
{
    for(int i=0; i<strlen(linha); i++){
        if(linha[i]==' ' && linha[i+1]==' ')
        {
            if(linha[i+2]==' ')
            {
                printf("O c�digo do arquivo est� contendo espa�os triplos, conserte-os antes de tentar executar o compilador novamente!\n");
                printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
                exit(0);  
            }
            linha[i]=linha[i+1];
            int j = i+1;
            for(j = j; j<strlen(linha); j++){
                linha[j]=linha[j+1];
            }
        }  
    }
}

void verifica_var(char linha[])
{
    if((strncmp(linha[4], "int", 3)==0))
    {
        printf("V�riavel de tipo inteiro");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *fp;
    char arquivo[20];
    char linha[100];
    char result[100];
    char *leitura;
    int i;

    //Digitar o nome do arquivo para leitura
    printf("Digite o nome do arquivo a ser lido pelo compilador: ");
    scanf("%s", &arquivo);
    fp = fopen(arquivo, "rt");
    //

    if(fp == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }

    i = 1;
    while(!feof(fp))
    {
        leitura = fgets(linha, 100, fp);
        linhas_lidas++;
        transformar_minusculo(linha);
        preparar_linha(linha);
        
        //printf("Linha sem espa�os %d: %s", i, linha);

        if((strncmp(linha, "var", 3)==0))
        {
            printf("Comando Var reconhecido!\n");
            verifica_var(linha);
        }

        //if((strncmp(leitura, "if(", 3)==0) || (strncmp(leitura, "if (", 4)==0))


        /*if(strcmp(leitura, "!Start\n") == 0)
        {
            printf("Programa iniciado!\n");
            //fflush(leitura);
            //printf("Linha %d: %s", i, linha);
        }
        if(strcmp(leitura, "!Stop") == 0)
        {
            printf("Programa finalizado!\n");
        }
        else if(strcmp(leitura, "\n") == 0)
        {
            printf("linha v�zia\n");
        }*/
        if(strncmp(linha, "!stop", 5) == 0)
        {   
          free(fp);
          free(leitura);  
        }
        i++;
    }
    fclose(fp);

    return 0;
}