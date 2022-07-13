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

void verifica_var(char linha[])//fun��o para verificar o comando var
{
  if(linha[4]=='i' && linha[5]=='n' && linha[6]=='t' && linha[7]==' ')//Vari�vel como tipo inteiro
    {
        printf("V�riavel de tipo int\n");
        for(int i = 8; i<strlen(linha)-2; i++)
        {
            if(linha[i]=='>' && linha[i+1]=='=' || linha[i]=='<' && linha[i+1]=='=' || linha[i]=='=' && linha[i+1]=='=' || linha[i]=='!' && linha[i+1]=='=')
            {
                printf("Uso de operadores l�gicos indevido, somente � permitido usar = para atribuir valores!\n");
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
                exit(0);
            }
        }
        if(linha[strlen(linha)-2]!=';')
        {
            printf("O comando var est� faltando o ';' no final da linha %d!!\n", linhas_lidas);
            printf("Conserte o erro e tente novamente!\n");
            printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
            exit(0);
        }
    }
    else if(linha[4]=='f' && linha[5]=='l' && linha[6]=='o' && linha[7]=='a' && linha[8]=='t' && linha[9]==' ')//Vari�vel como tipo float
    {
        printf("V�riavel de tipo float\n");
        for(int i = 10; i<strlen(linha)-2; i++)
        {
            if(linha[i]=='>' && linha[i+1]=='=' || linha[i]=='<' && linha[i+1]=='=' || linha[i]=='=' && linha[i+1]=='=' || linha[i]=='!' && linha[i+1]=='=')
            {
                printf("Uso de operadores l�gicos indevido, somente � permitido usar = para atribuir valores!\n");
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
                exit(0);
            }
        }
        if(linha[strlen(linha)-2]!=';')
        {
            printf("O comando var est� faltando o ';' no final da linha %d!!\n", linhas_lidas);
            printf("Conserte o erro e tente novamente!\n");
            printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
            exit(0);
        }
    }
    else if(linha[4]=='c' && linha[5]=='h' && linha[6]=='a' && linha[7]=='r' && linha[8]==' ')//Vari�vel de tipo char
    {
        printf("V�riavel de tipo string\n");
        int chave_char=0;
        for(int i = 9; i<strlen(linha)-2; i++)//Esse for vai verificar a presen�a de [] e a garantia dos operadores l�gicos
        {
            if(linha[i]=='[')
            {
                chave_char+=1;
            }
            if(linha[i]==']')
            {
                chave_char-=1;
            }
            if(linha[i]=='>' && linha[i+1]=='=' || linha[i]=='<' && linha[i+1]=='=' || linha[i]=='=' && linha[i+1]=='=' || linha[i]=='!' && linha[i+1]=='=')
            {
                printf("Uso de operadores l�gicos indevido, somente � permitido usar = para atribuir valores!\n");
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
                exit(0);
            }
            if(chave_char>=1 || chave_char<0)
            {
                printf("Erro nos colchetes do tamanho do char na linha %d, foi colocado um colchete de abertura a mais ou um de fechamento!!\n", linhas_lidas);
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
                exit(0);
            }
        }
        if(chave_char!=0)
        {
            printf("Erro nos colchetes do tamanho do char na linha %d, n�o foi fechado o colchete!!\n", linhas_lidas);
            printf("Conserte o erro e tente novamente!\n");
            printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
            exit(0);
        }  
        if(linha[strlen(linha)-2]!=';' )
        {
            printf("O comando var est� faltando o ';' no final da linha %d!!\n", linhas_lidas);
            printf("Conserte o erro e tente novamente!\n");
            printf("Foram lidas %d linhas do arquivo!", linhas_lidas);
            exit(0);
        }
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
    int verificador_start = 0;
    int verificador_stop = 0;
    int verificador_main = 0;
    int verificador_chaves = 0;

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

    while(!feof(fp))
    {
        leitura = fgets(linha, 100, fp);
        linhas_lidas++;
        transformar_minusculo(linha);
        preparar_linha(linha);

        if((strncmp(linha, "!start", 5)==0))//Vai inicializar o verificador para travar o funcionamento do restante do c�digo se n�o tiver o Start
        {
            verificador_start+=1;
            if(verificador_start>1)//Tratamento de exce��o para duplica��o do comando start
            {
                printf("Um comando de Start a mais foi inserido no c�digo, remova o excedente, lembre-se que o c�digo s� ir� contar apartir de quando o !start for iniciado!\n", linhas_lidas);
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!\n", linhas_lidas);
                exit(0);
            }
        }
        if(verificador_start==1 && verificador_stop==0)
        {
            if((strncmp(linha, "var", 3)==0))
            {
                verifica_var(linha);
            }
        }
        if(strncmp(linha, "func void main()", 16)==0 && verificador_start==1 && verificador_stop==0 || strncmp(linha, "func void main ()", 17)==0 && verificador_start==1 && verificador_stop==0)//Mesmo principio do Start, mas para fun��o Main
        {
            if(verificador_main>1)//Tratamento de exce��o para duplica��o da cria��o da main
            {
                printf("Houve uma tentativa de abertura de outra main na linha %d, apague-a e deixe seu c�digo dentro de apenas uma fun��o main!\n", linhas_lidas);
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!\n", linhas_lidas);
                exit(0);
            }
            if(linha[strlen(linha)-2]!='{')//Verificar a presen�a da chave de abertura na main
            {
                printf("A abertura da main faltou a chave de abertura no final da linha %d!\n", linhas_lidas);
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!\n", linhas_lidas);
                exit(0);
            }
            else//A main ir� operar sempre com um o valor 1 no verificador_chaves at� reconhecer sua chave de fechamento devidamente
            {
                verificador_main+=1;
                verificador_chaves+=1;
            }
        }
        /*if(verificador_chaves==1 && verificador_main==1 && verificador_start==1)
        {
            if(strncmp(linha, ))
        }*/

        if(strncmp(linha, "}", 1)==0)//Ajustar o contador de acordo com as chaves de fechamento
        {
            verificador_chaves-=1;
        }
        if(strncmp(linha, "!stop", 5) == 0)//Verificador para checar se o c�digo teve o Stop colocado devidamente
        {   
            verificador_stop+=1;
            if(verificador_stop>1)//Tratamento de exce��o para duplica��o do comando stop
            {
                printf("Um comando de Stop a mais foi inserido no c�digo, remova o excedente, lembre-se que o c�digo ir� deixar de verificar depois do !stop\n", linhas_lidas);
                printf("Conserte o erro e tente novamente!\n");
                printf("Foram lidas %d linhas do arquivo!\n", linhas_lidas);
                exit(0);
            }
        }
        i++;
    }
    fclose(fp);

    if(verificador_chaves>0)
    {
        if(verificador_main==1 && verificador_chaves==1)
        {
            printf("O arquivo terminou de ser lido, por�m, a main n�o foi fechada e assim ficou incorreto!\n");
        }
        else
        {
            printf("O arquivo terminou de ser lido, por�m, o c�digo ficou com uma chave a mais e assim, incorreto!\n");
        }
    }
    else if(verificador_chaves<0)
    {
        printf("O arquivo terminou de ser lido, por�m, o c�digo ficou com uma chave a menos e assim ficou incorreto!\n");
    }

    if(verificador_stop<1)
    {
        printf("O arquivo terminou de ser lido, por�m, o c�digo ficou sem o !stop para parar a leitura do c�digo e assim ficou incorreto!\n"); 
    }
    if(verificador_stop==1 && verificador_chaves==0)
    {
        printf("O c�digo estava totalmente correto!\n");
    }
    printf("Foram lidas %d linhas do arquivo!\n", linhas_lidas);
    free(fp);
    free(leitura);
    return 0;
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