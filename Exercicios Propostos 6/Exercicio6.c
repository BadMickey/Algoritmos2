#include <stdio.h>
#include <string.h>
#include <locale.h>

#define SAL_MINIM0 1200

char dados_pessoais(char nomes[]);
float salario(float *sal_liquido, float *sal_recebido, float *refeicoes, float *idesc_eventuais, float *vales);
void imprime(char inome[], float isal_liquido, float isalario, float iref, float idesc_event, float idesc_vale);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char nome[50];
    dados_pessoais(nome);

    float sal_final;
    float sal;
    float ref;
    float de;
    float val;

    salario(&sal_final, &sal, &ref, &de, &val);

    imprime(nome, sal_final, sal, ref, de, val);
    
    return 0;
}

char dados_pessoais(char nomes[])
{
    //l� o nome do funcion�rio
    printf("Digite o nome do funcion�rio: ");
    fgets(nomes, 50, stdin);
}

float salario(float *sal_liquido, float *sal_recebido, float *refeicoes, float *idesc_eventuais, float *vales)
{
    float valor_hed;
    float valor_hen;
    float hed;
    float hen;
    int nd;
    int fal;

//l� o sal�rio do empregado
    printf("Sal�rio do empregado: R$");
    scanf("%f", &*sal_recebido);
    
    //l� o valor-hora-diurna
    printf("Valor hora extra diurna: R$");
    scanf("%f", &valor_hed);
    
    //l� o valor-hora-noturna
    printf("Valor hora extra noturna: R$");
    scanf("%f", &valor_hen);
    
    //quantidade de horas extras diurnas trabalhadas
    printf("Quantas horas extras diurnas o funcion�rio trabalhou esse m�s? ");
    scanf("%f", &hed);
    
    //quantidade de horas extras noturnas trabalhadas
    printf("Quantas horas extras diurnas o funcion�rio trabalhou esse m�s? ");
    scanf("%f", &hen);
    
    //quantidade de dependentes
    printf("Quantos dependentes o funcion�rio tem? ");
    scanf("%d", &nd);
    
    //quantidade de faltas do funcion�rio
    printf("Quantas faltas o funcion�rio tem esse m�s? ");
    scanf("%d", &fal);
    
    //descontos eventuais  
    printf("Descontos evetuais no sal�rio: R$");
    scanf("%f", &*idesc_eventuais);
    
    //gastos com refei��es feitas na empresa
    printf("Quanto o funcion�rio gastou com refei��o esse m�s? R$");
    scanf("%f", &*refeicoes);
    
    //vales retirados durante o m�s
    printf("Quanto de vale dever� ser descontado no sal�rio do funcion�rio? R$");
    scanf("%f", &*vales);

    //calcula e aplica valores a vari�veis necess�rias para c�lculos
    float hora_extra = hed * *sal_recebido/160 + hen * 1.2 * *sal_recebido/160;
    float sal_familia = nd * 0.05 * SAL_MINIM0;
    float total_horas_extras = (hen * valor_hen) + (hed * valor_hed);
    float sal_bruto = *sal_recebido + total_horas_extras + sal_familia;
    float inamps = 0.08 * (*sal_recebido);
    float faltas = fal * (*sal_recebido / 160);
    float imposto_renda = 0.08 * sal_bruto;

    //calcula o desconto total
    float desc_total;
    desc_total = sal_bruto - faltas - *refeicoes - *idesc_eventuais - *vales - inamps - imposto_renda;

    //calcula o sal�rio l�quido
    *sal_liquido = sal_bruto - desc_total;
}

void imprime(char inome[], float isal_liquido, float isalario, float iref, float idesc_event, float idesc_vale)
{
    //imprime os valores
    printf("\n\n\nDados do colaborador:\n");
    printf("\n\nNome do colaborador: %s", inome);
    printf("Sal�rio do colaborador: R$%.2f", isalario);
    printf("\nDescontos em refei��es: R$%.2f", iref);
    printf("\nDescontos em vales: R$%.2f", idesc_vale);
    printf("\nDescontos eventuais: R$%.2f", idesc_event);
    printf("\nSalario l�quido: R$%.2f", isal_liquido);
}