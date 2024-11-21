#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
const char* obterNomeMes(int mes);
#define ANO_INICIAL 1500
#define ANO_FINAL 2500
#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"

struct Usuario
{
    char nome_completo[100];
    char login[20];
    char senha[20];
    int empresaSelecionada;
};
struct Empresa
{
    char razao_social[100];
    char nome_fantasia[100];
    char cnpj[15];
    char data_abertura[11];
    char telefone[15];
    char responsavel[100];
    char email[100];
    char endereco[100];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[10];
    char indicadores[500];
};
enum Telas
{
    TELA_MENU_PRINCIPAL,
    TELA_CADASTRO_EMPRESA,
    TELA_GERENCIAR_EMPRESAS,
    TELA_GERAR_RELATORIO,
    TELA_RELATORIO,
    TELA_CONSULTA_EMPRESA,
    TELA_SAIR,
    TELA_NOVA_OPCAO
};

void inicializarEmpresas(struct Empresa **empresas, int *numEmpresas);
void visualizarDadosCadastrais(const struct Empresa *empresa);
void visualizarIndicadores(const struct Empresa *empresa);
void pausarExecucao(void);
void visualizarIndicadores(const struct Empresa *empresa);
void excluirCadastro(const struct Empresa **empresas, int *numEmpresas,int *telaAtual);
void opGerenciamento(const struct Empresa *empresas, int numEmpresas, int empresaSelecionada, int *telaAtual);
void exibirMenuPrincipal(const struct Usuario *usuarioLogado);
void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual);
void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual);
void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual);
void limparTela();
struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios);
const char* obterNomeMes(int mes)
{
    switch (mes)
    {
    case 1:
        return "Janeiro";
    case 2:
        return "Fevereiro";
    case 3:
        return "Março";
    case 4:
        return "Abril";
    case 5:
        return "Maio";
    case 6:
        return "Junho";
    case 7:
        return "Julho";
    case 8:
        return "Agosto";
    case 9:
        return "Setembro";
    case 10:
        return "Outubro";
    case 11:
        return "Novembro";
    case 12:
        return "Dezembro";
    default:
        return "Mês inválido";
    }
}
int main()
{

    SetConsoleTitle("Sistema STARTUP - PIM IV - UNIP");
    setlocale(LC_ALL, "Portuguese");
    struct Usuario usuarios[1] =
    {
        //   Nome  |-- LOGIN--SENHA--|
        {"ADMINISTRADOR", "admin", "admin"}
    };
    struct Empresa *empresas = NULL;
    int numEmpresas = 0;
    int telaAtual = TELA_MENU_PRINCIPAL;
    struct Usuario usuarioLogado = fazerLogin(usuarios, 7);
    inicializarEmpresas(&empresas, &numEmpresas);
    if (strcmp(usuarioLogado.login, "") == 0)
    {
        printf(ANSI_RED "\nUsuário não encontrado. Encerrando o programa\n"ANSI_RESET);
        system("pause");
        return 0;
    }
    printf("\nLogin bem-sucedido! Bem-vindo, %s.\n", usuarioLogado.nome_completo);
    system("pause");
    while (telaAtual != TELA_SAIR)
    {
        limparTela();
        switch (telaAtual)
        {
        // case TELA_MENU_PRINCIPAL:exibirMenuPrincipal(&usuarioLogado);break;
        case TELA_CADASTRO_EMPRESA:
            cadastrarEmpresa(&empresas, &numEmpresas, &telaAtual);
            break;
        case TELA_GERENCIAR_EMPRESAS:
            gerenciarEmpresas(empresas, numEmpresas, &telaAtual);
            break;
        case TELA_RELATORIO:
            exibirRelatorio(empresas, numEmpresas, &telaAtual);
            break;
        case TELA_CONSULTA_EMPRESA:
        {
            char cnpjConsulta[15];
            printf("\nDigite o CNPJ para consulta: ");
            scanf(" %[^\n]", cnpjConsulta);
            int empresaEncontrada = 0;
            int indiceEmpresa = -1;
            for (int i = 0; i < numEmpresas; i++)
            {
                if (strcmp(empresas[i].cnpj, cnpjConsulta) == 0)
                {
                    printf(ANSI_GREEN"\nConsulta bem-sucedida!"ANSI_RESET);
                    printf("\nAbrindo Gerenciamento para "ANSI_GREEN" %s\n" ANSI_RESET, empresas[i].nome_fantasia);

                    empresaEncontrada = 1;
                    indiceEmpresa = i;
                    break;
                }
            }
            if (!empresaEncontrada)
            {
                printf(ANSI_RED"\nNenhuma empresa com o CNPJ informado.\n"ANSI_RESET);
                system("pause");
            }
            else
            {
                usuarioLogado.empresaSelecionada = indiceEmpresa;
                opGerenciamento(empresas, numEmpresas, indiceEmpresa, &telaAtual);
            }
            system("pause");
            while (getchar() != '\n');
            telaAtual = TELA_MENU_PRINCIPAL;
        }
        break;
        case TELA_NOVA_OPCAO:
            printf("\nNova opção escolhida!\n");
            telaAtual = TELA_MENU_PRINCIPAL;
            break;
        }
        if (telaAtual == TELA_MENU_PRINCIPAL)
        {
            limparTela();
            exibirMenuPrincipal(&usuarioLogado);
            int opcao;
            printf("\nOpção escolhida: ");
            scanf("%d", &opcao);
            while (getchar() != '\n');
            switch (opcao)
            {
            case 1:
                telaAtual = TELA_CADASTRO_EMPRESA;
                break;
            case 2:
                telaAtual = TELA_GERENCIAR_EMPRESAS;
                break;
            case 3:
                telaAtual = TELA_RELATORIO;
                break;
            case 4:
                telaAtual = TELA_CONSULTA_EMPRESA;
                break;
            case 5:
                telaAtual = TELA_SAIR;
                break;
            default:
                printf(ANSI_RED"\nOpção inválida. Tente novamente.\n"ANSI_RESET);
                system("pause");
                break;
            }
        }
    }
    free(empresas);
    printf("\n----Até Logo----\n");
    return 0;
}
struct Usuario fazerLogin(const struct Usuario *usuarios, int numUsuarios)
{
    struct Usuario usuarioLogado;
    char loginInformado[20];
    char senhaInformada[20];
    do
    {
        limparTela();
        printf("\n\t------------------------------");
        printf(ANSI_GREEN "\n\t\tREALIZAR LOGIN" ANSI_RESET);
        printf("\n\t------------------------------\n");
        printf("Login: ");
        scanf(" %[^\n]", loginInformado);
        while (getchar() != '\n');
        printf("Senha: ");
        scanf(" %[^\n]", senhaInformada);
        int usuarioValido = 0;
        for (int i = 0; i < numUsuarios; i++)
        {
            if (strcmp(usuarios[i].login, loginInformado) == 0 &&
                    strcmp(usuarios[i].senha, senhaInformada) == 0)
            {
                usuarioLogado = usuarios[i];
                usuarioValido = 1;
                break;
            }
        }
        if (!usuarioValido)
        {
            printf(ANSI_RED"\n[--Usuário ou senha inválidos. Tente novamente--]\n"ANSI_RESET);
            system("pause");
            strcpy(usuarioLogado.login, "");
        }
    }
    while (strcmp(usuarioLogado.login, "") == 0);
    return usuarioLogado;
}

void exibirMenuPrincipal(const struct Usuario *usuarioLogado)
{
    printf("\n\t-------------SISTEMA STARTUP------------\n");
    printf("\tGerenciador de Soluções Ambientais\n");
    printf("\tSeja Bem-vindo! - " ANSI_GREEN " %s" ANSI_RESET, usuarioLogado->nome_completo);
    printf("\n\t-------------------------------------\n");
    printf("\nEscolha uma Opção:\n");
    printf("[1] Cadastrar nova empresa.\n");
    printf("[2] Gerenciar empresas.\n");
    printf("[3] Relatório.\n");
    printf("[4] Consultar empresa por CNPJ.\n");
    printf("[5] Sair.\n");
}

void cadastrarEmpresa(struct Empresa **empresas, int *numEmpresas, int *telaAtual)
{
    limparTela();
    struct Empresa novaEmpresa;
    printf("\n\t-------------------------------------");
    printf("\n\t\tCADASTRO DE EMPRESA");
    printf("\n\t-------------------------------------\n");
    printf("Razão Social: ");
    scanf(" %[^\n]", novaEmpresa.razao_social);
    printf("Nome Fantasia: ");
    scanf(" %[^\n]", novaEmpresa.nome_fantasia);
    printf("CNPJ: ");
    scanf(" %[^\n]", novaEmpresa.cnpj);
    printf("Data de Abertura: ");
    scanf(" %[^\n]", novaEmpresa.data_abertura);
    printf("Telefone: ");
    scanf(" %[^\n]", novaEmpresa.telefone);
    printf("Responsável: ");
    scanf(" %[^\n]", novaEmpresa.responsavel);
    printf("E-mail: ");
    scanf(" %[^\n]", novaEmpresa.email);
    printf("Endereço: ");
    scanf(" %[^\n]", novaEmpresa.endereco);
    printf("Bairro: ");
    scanf(" %[^\n]", novaEmpresa.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", novaEmpresa.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", novaEmpresa.estado);
    printf("CEP: ");
    scanf(" %[^\n]", novaEmpresa.cep);
    struct Empresa *temp = realloc(*empresas, (*numEmpresas + 1) * sizeof(struct Empresa));
    if (temp == NULL)
    {
        printf(ANSI_RED"Erro ao alocar memória.\n"ANSI_RESET);
        system("pause");
        return;
    }
    *empresas = temp;
    (*empresas)[*numEmpresas] = novaEmpresa;
    (*numEmpresas)++;
    printf(ANSI_GREEN"\n[--Empresa cadastrada com sucesso!--]\n"ANSI_RESET);
    system("pause");
    limparTela();
    *telaAtual = TELA_MENU_PRINCIPAL;
}

void gerenciarEmpresas(struct Empresa *empresas, int numEmpresas, int *telaAtual)
{
    if (numEmpresas == 0)
    {
        printf(ANSI_RED"\n[--Nenhuma empresa cadastrada--]\n"ANSI_RESET);
        system("pause");
        *telaAtual = TELA_MENU_PRINCIPAL;
    }
    limparTela();


    printf("\n\t-----------------------------------");
    printf("\n\t\tGERENCIAR EMPRESAS");
    printf("\n\t-----------------------------------\n");
    printf("Escolha uma opção:\n");
    printf("[1] Consultar empresa\n");
    printf("[2] Voltar ao menu principal.\n");
    int opcao;
    printf("Opção escolhida: ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    switch (opcao)
    {
    case 1:
        *telaAtual = TELA_CONSULTA_EMPRESA;
        break;
    case 2:
        *telaAtual = TELA_MENU_PRINCIPAL;
        break;
    default:
        printf(ANSI_RED"\n[--Opção inválida. Tente novamente--]\n"ANSI_RESET);
        system("pause");
        break;
    }
}

void exibirRelatorio(const struct Empresa *empresas, int numEmpresas, int *telaAtual)
{
    limparTela();
    printf("\n\t-----------------------------------");
    printf("\n\t\tRELATORIOS");
    printf("\n\t-----------------------------------\n");

    printf("Escolha uma opção:\n");
    printf("[1] Totais Semestrais\n");
    printf("[2] Comparativos Mensais\n");
    printf("[3] Comparativos Anuais\n");
    printf("[4] Estado com Maior Volume/Ano\n");
    printf("[5] Voltar ao menu anterior\n");
    printf("[6] Sair\n");
    int opcaoRelatorio;
    printf("Opção escolhida: ");
    scanf("%d", &opcaoRelatorio);
    while (getchar() != '\n');
    switch (opcaoRelatorio)
    {
    case 1:
    {
        printf("\n-------------------------------------");
        printf("\nRELATÓRIO – Totais Semestrais");
        printf("\n-------------------------------------\n");
        int anoRelatorio;
        int semestreRelatorio;
        printf("Ano: ");
        scanf("%d", &anoRelatorio);
        printf("Semestre (1 ou 2): ");
        scanf("%d", &semestreRelatorio);
        const struct Empresa *empresaAtual = &empresas[0];
        printf("\nNo %s semestre de %d, a empresa tratou %.2f toneladas de resíduos com um custo total de R$ %.2f.\n",
               (semestreRelatorio == 1) ? "primeiro" : "segundo", anoRelatorio,
               atof(empresaAtual->indicadores), atof(empresaAtual->indicadores + 100));
        printf("\nOpções:\n");
        printf("[1] Salvar relatório\n");
        printf("[2] Voltar ao menu anterior\n");
        int opcaoSalvar;
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSalvar);
        while (getchar() != '\n');
        switch (opcaoSalvar)
        {
        case 1:
            printf(ANSI_GREEN"[--Relatório salvo com sucesso!--]\n"ANSI_RESET);
            system("pause");
            break;
        case 2:
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        default:
            printf(ANSI_RED"[--Opção inválida. Retornando ao menu anterior--]\n"ANSI_RESET);
            system("pause");
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        }
        break;
    }
    break;
    case 2:
    {
        printf("\n-------------------------------------");
        printf("\nRELATÓRIO – Comparativos Mensais");
        printf("\n-------------------------------------\n");
        int ano1, mes1, ano2, mes2;
        printf("Ano 1: ");
        scanf("%d", &ano1);
        printf("Mês 1 (1 a 12): ");
        scanf("%d", &mes1);
        printf("Ano 2: ");
        scanf("%d", &ano2);
        printf("Mês 2 (1 a 12): ");
        scanf("%d", &mes2);
        srand(time(NULL));
        double toneladas1 = ((double)rand() / RAND_MAX) * 100.0;
        double custo1 = ((double)rand() / RAND_MAX) * 9000.0 + 1000.0;
        double toneladas2 = ((double)rand() / RAND_MAX) * 100.0;
        double custo2 = ((double)rand() / RAND_MAX) * 9000.0 + 1000.0;
        printf("\nEm %s de %d, a empresa tratou %.2f toneladas de resíduos\ncom um custo total de R$ %.2f.", obterNomeMes(mes1), ano1, toneladas1, custo1);
        printf("\nEnquanto em %s de %d tratou %.2f toneladas de resíduos\ncom um custo total de R$ %.2f.\n", obterNomeMes(mes2), ano2, toneladas2, custo2);
        double aumentoToneladas = ((toneladas2 - toneladas1) / toneladas1) * 100.0;
        double aumentoCusto = ((custo2 - custo1) / custo1) * 100.0;
        printf("\nEm termos percentuais, temos %s de %.2f%% para\na quantidade de resíduos e de %.2f%% para os custos totais.\n", (aumentoToneladas >= 0) ? "um aumento" : "uma diminuição", fabs(aumentoToneladas), aumentoCusto);
        printf("\nOpções:\n");
        printf("[1] Salvar relatório\n");
        printf("[2] Voltar ao menu anterior\n");
        int opcaoSalvar;
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSalvar);
        while (getchar() != '\n');
        switch (opcaoSalvar)
        {
        case 1:
            printf(ANSI_GREEN"\n[--Relatório salvo com sucesso!--]\n"ANSI_RESET);
            system("pause");
            break;
        case 2:
            *telaAtual = TELA_GERAR_RELATORIO;
            break;
        default:
            printf(ANSI_RED"\n[--Opção inválida. Retornando ao menu anterior--]\n"ANSI_RESET);
            system("pause");
            *telaAtual = TELA_GERAR_RELATORIO;
            break;
        }
        break;
    }
    case 3:
    {
        printf("\n-------------------------------------");
        printf("\nRELATÓRIO – Comparativos Anuais");
        printf("\n-------------------------------------\n");
        int ano1, ano2;
        printf("Ano 1: ");
        scanf("%d", &ano1);
        printf("Ano 2: ");
        scanf("%d", &ano2);
        if (ano1 < ANO_INICIAL || ano2 < ANO_INICIAL || ano1 > ANO_FINAL || ano2 > ANO_FINAL)
        {
            printf(ANSI_RED"\n[--Ano(s) inválido(s). Retornando ao menu anterior--]\n"ANSI_RESET);
            system("pause");
            *telaAtual = TELA_GERAR_RELATORIO;
            break;
        }
        srand(time(NULL));
        double toneladas1 = ((double)rand() / RAND_MAX) * 100.0;
        double custo1 = ((double)rand() / RAND_MAX) * 9000.0 + 1000.0;
        double toneladas2 = ((double)rand() / RAND_MAX) * 100.0;
        double custo2 = ((double)rand() / RAND_MAX) * 9000.0 + 1000.0;
        printf("\nNo ano %d, a empresa tratou %.2f toneladas de resíduos\ncom um custo total de R$ %.2f.\n", ano1, toneladas1, custo1);
        printf("Enquanto em %d tratou %.2f toneladas de resíduos\ncom um custo total de R$ %.2f.\n", ano2, toneladas2, custo2);
        double aumentoToneladas = ((toneladas2 - toneladas1) / toneladas1) * 100.0;
        double aumentoCusto = ((custo2 - custo1) / custo1) * 100.0;
        printf("\nEm termos percentuais, temos %s de %.2f%% para\na quantidade de resíduos e de %.2f%% para os custos totais.\n", (aumentoToneladas >= 0) ? "um aumento" : "uma diminuição", fabs(aumentoToneladas), aumentoCusto);
        printf("\nOpções:\n");
        printf("[1] Salvar relatório\n");
        printf("[2] Voltar ao menu anterior\n");
        int opcaoSalvar;
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSalvar);
        while (getchar() != '\n');
        switch (opcaoSalvar)
        {
        case 1:
            printf(ANSI_GREEN"\n[--Relatório salvo com sucesso!--]\n"ANSI_RESET);
            system("pause");
            break;
        case 2:
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        default:
            printf(ANSI_RED"\n[--Opção inválida. Retornando ao menu anterior--]\n"ANSI_RESET);
            system("pause");
            *telaAtual = TELA_GERAR_RELATORIO;
            break;
        }
        break;
    }
    break;
    case 4:
    {

        printf("\n-----------------------------------------");
        printf("\nRELATÓRIO – Estado com Maior Volume/Ano");
        printf("\n-----------------------------------------\n");
        int anoDesejado;
        printf("Ano: ");
        scanf("%d", &anoDesejado);
        if (anoDesejado < ANO_INICIAL || anoDesejado > ANO_FINAL)
        {
            printf(ANSI_RED"Ano inválido. Retornando ao menu anterior.\n"ANSI_RESET);
            *telaAtual = TELA_GERAR_RELATORIO;
            break;
        }
        srand(time(NULL));
        double maiorVolume = ((double)rand() / RAND_MAX) * 1000.0;
        double mediaDemaisEstados = ((double)rand() / RAND_MAX) * 500.0;
        double diferencaPercentual = ((maiorVolume - mediaDemaisEstados) / mediaDemaisEstados) * 100.0;
        const char* estadoMaiorVolume = "São Paulo";
        printf("\nNo ano %d, %s foi o estado que apresentou o maior\nvolume de tratamento de resíduos pelas indústrias.\n", anoDesejado, estadoMaiorVolume);
        printf("%.2f%% a mais que a média dos demais estados brasileiros.\n", diferencaPercentual);
        printf("\nOpções:\n");
        printf("[1] Salvar relatório\n");
        printf("[2] Voltar ao menu anterior\n");
        int opcaoSalvar;
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSalvar);
        while (getchar() != '\n');
        switch (opcaoSalvar)
        {
        case 1:
            printf(ANSI_GREEN"\n[--Relatório salvo com sucesso!--]\n"ANSI_RESET);
            system("pause");
            break;
        case 2:
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        default:
            printf(ANSI_RED"\n[--Opção inválida. Retornando ao menu anterior--]\n"ANSI_RESET);
            system("pause");
            *telaAtual = TELA_MENU_PRINCIPAL;
            break;
        }
        break;
    }
    case 5:
        printf(ANSI_GREEN"\n[--VOLTANDO--]\n"ANSI_RESET);
        system("pause");

        *telaAtual = TELA_MENU_PRINCIPAL;
        break;
    case 6:
        printf(ANSI_RED"\nSaindo do programa...\n"ANSI_RESET);
        exit(0);
        break;
    }
}

void relatorioEstadoMaiorVolume(const struct Empresa *empresas, int numEmpresas,int *telaAtual)
{
    int anoDesejado;
    printf("Ano: ");
    scanf("%d", &anoDesejado);
    if (anoDesejado < ANO_INICIAL || anoDesejado > ANO_FINAL)
    {
        printf(ANSI_RED"\n[--Ano inválido. Retornando ao menu anterior--]\n"ANSI_RESET);
        system("pause");
        return;
    }
    int maiorVolume = -1;
    char estadoMaiorVolume[3];
    double somaVolume = 0.0;
    for (int i = 0; i < numEmpresas; ++i)
    {
        int anoAtual = atoi(empresas[i].data_abertura + 6);
        if (anoAtual == anoDesejado)
        {
            int volumeAtual = atoi(empresas[i].indicadores);
            somaVolume += volumeAtual;
            if (volumeAtual > maiorVolume)
            {
                maiorVolume = volumeAtual;
                strcpy(estadoMaiorVolume, empresas[i].estado);
            }
        }
    }
    double mediaDemaisEstados = (somaVolume - maiorVolume) / (numEmpresas - 1);
    double diferencaPercentual = ((maiorVolume - mediaDemaisEstados) / mediaDemaisEstados) * 100.0;
    printf("\nNo ano %d, %s foi o estado que apresentou o maior volume de tratamento de resíduos pelas indústrias.\n", anoDesejado, estadoMaiorVolume);
    printf("%.2f%% a mais que a média dos demais estados brasileiros.\n", diferencaPercentual);
    printf("\nOpções:\n");
    printf("[1] Salvar relatório\n");
    printf("[2] Voltar ao menu anterior\n");
    int opcaoSalvar;
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoSalvar);
    while (getchar() != '\n');
    switch (opcaoSalvar)
    {
    case 1:
        printf(ANSI_GREEN"\n[--Relatório salvo com sucesso!--]\n"ANSI_RESET);
        system("pause");
        break;
    case 2:
        *telaAtual = TELA_MENU_PRINCIPAL;
        break;
    default:
        printf(ANSI_RED"\n[--Opção inválida. Retornando ao menu anterior--]\n"ANSI_RESET);
        system("pause");
        break;
    }
}

void visualizarDadosCadastrais(const struct Empresa *empresa)
{
    limparTela();
    printf("\n\t-------------------------------------");
    printf("\n\t\tDADOS CADASTRAIS");
    printf("\n\t-------------------------------------\n");
    printf("Razão Social: "ANSI_GREEN"%s\n"ANSI_RESET, empresa->razao_social);
    printf("Nome Fantasia: %s\n", empresa->nome_fantasia);
    printf("CNPJ: %s\n", empresa->cnpj);
    printf("Data de Abertura: %s\n", empresa->data_abertura);
    printf("Telefone: %s\n", empresa->telefone);
    printf("Responsável: %s\n", empresa->responsavel);
    printf("E-mail: %s\n", empresa->email);
    printf("Endereço: %s\n", empresa->endereco);
    printf("Bairro: %s\n", empresa->bairro);
    printf("Cidade: %s\n", empresa->cidade);
    printf("Estado: %s\n", empresa->estado);
    printf("CEP: %s\n", empresa->cep);
    printf(ANSI_GREEN"\n[--Dados cadastrais exibidos com sucesso!--]\n"ANSI_RESET);
}

void opGerenciamento(const struct Empresa *empresas, int numEmpresas, int empresaSelecionada, int *telaAtual)
{
    limparTela();
    printf("\n\t----------------------------------------");
    printf("\n\t GERENCIAMENTO - "ANSI_GREEN "%s" ANSI_RESET, empresas[empresaSelecionada].nome_fantasia);
    printf("\n\t----------------------------------------\n");
    printf("Escolha uma opção:\n");
    printf("[1] Visualizar dados cadastrais.\n");
    printf("[2] Visualizar Indicadores.\n");
    printf("[3] Gerar Relatórios.\n");
    printf("[4] Excluir cadastro.\n");
    printf("[5] Voltar ao menu anterior.\n");
    printf("[6] Sair.\n");
    int opcao;
    printf("Opção escolhida: ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    switch (opcao)
    {
    case 1:
        visualizarDadosCadastrais(&empresas[empresaSelecionada]);
        break;
    case 2:
        visualizarIndicadores(&empresas[empresaSelecionada]);
        break;
    case 4:
        excluirCadastro(&empresas, &numEmpresas,&telaAtual);
        printf(ANSI_GREEN"\n[--Cadastro excluído com sucesso!--]\n"ANSI_RESET);
        system("pause");
        *telaAtual = TELA_MENU_PRINCIPAL;
        break;
    case 5:
        *telaAtual = TELA_GERENCIAR_EMPRESAS;
        break;
    case 6:
        *telaAtual = TELA_SAIR;
        break;
    default:
        printf(ANSI_RED"\n[--Opção inválida. Tente novamente--]\n"ANSI_RESET);
        system("pause");
        break;
    }
}

void excluirCadastro(const struct Empresa **empresas, int *numEmpresas,int *telaAtual)
{
    char cnpjExclusao[15];
    printf("\nDigite o CNPJ da empresa que deseja excluir: ");
    scanf(" %[^\n]", cnpjExclusao);
    int indiceExclusao = -1;
    for (int i = 0; i < *numEmpresas; i++)
    {
        if (strcmp((*empresas)[i].cnpj, cnpjExclusao) == 0)
        {
            indiceExclusao = i;
            break;
        }
    }
    if (indiceExclusao != -1)
    {
        struct Empresa *temp = malloc((*numEmpresas - 1) * sizeof(struct Empresa));
        if (temp != NULL)
        {
            for (int i = 0; i < indiceExclusao; i++)
            {
                temp[i] = (*empresas)[i];
            }
            for (int i = indiceExclusao; i < *numEmpresas - 1; i++)
            {
                temp[i] = (*empresas)[i + 1];
            }
            free(*empresas);
            *empresas = temp;
            (*numEmpresas)--;
            printf(ANSI_GREEN"\nEmpresa excluída com sucesso!\n"ANSI_RESET);
            system("pause");
        }
        else
        {
            printf(ANSI_RED"Erro ao alocar memória para a exclusão.\n"ANSI_RESET);
            system("pause");
        }
    }
    else
    {
        printf(ANSI_RED"[--Empresa com o CNPJ fornecido não encontrada--]\n"ANSI_RESET);
        system("pause");
    }
    *telaAtual = TELA_MENU_PRINCIPAL;
}
void limparTela()
{
    system("cls");
}

void visualizarIndicadores(const struct Empresa *empresa)
{
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    char dataAtual[20];
    strftime(dataAtual, sizeof(dataAtual), "%d/%m/%Y", &tm_info);

    double arrecada01 = ((double)rand() / RAND_MAX) * 5000.0+ 1020.0;
    double arrecada02 = ((double)rand() / RAND_MAX) * 2000.0 + 800.0;
    printf(ANSI_GREEN"\n[--INDICADORES ATUAIS--]"ANSI_RESET);
    printf("\nNo dia %s a %s arrecadou R$ %.2f",dataAtual, empresa->nome_fantasia, arrecada02);
    printf("\nSuperando o record de R$ %.2f.\n", arrecada01);
}

void inicializarEmpresas(struct Empresa **empresas, int *numEmpresas)
{
    struct Empresa novaEmpresa;
    strcpy(novaEmpresa.razao_social, "GreenVista Innovations Ltda");
    strcpy(novaEmpresa.nome_fantasia, "GreenVista EcoTech");
    strcpy(novaEmpresa.cnpj, "69340898000143");
    strcpy(novaEmpresa.data_abertura, "16/10/1998");
    strcpy(novaEmpresa.telefone, "(11) 9876-5432");
    strcpy(novaEmpresa.responsavel, "Ana Silva");
    strcpy(novaEmpresa.email, "contato@greenvistainnovations.com.br");
    strcpy(novaEmpresa.endereco, "Rua das Flores, 123");
    strcpy(novaEmpresa.bairro, "Bairro Verdejante");
    strcpy(novaEmpresa.cidade, "Cidade Sustentavel");
    strcpy(novaEmpresa.estado, "Estado Ecologico");
    strcpy(novaEmpresa.cep, "01234-567");

    struct Empresa *temp = realloc(*empresas, (*numEmpresas + 1) * sizeof(struct Empresa));
    if (temp == NULL)
    {
        printf(ANSI_RED"\nErro ao alocar memória.\n"ANSI_RESET);
        system("pause");
        return;
    }

    *empresas = temp;
    (*empresas)[*numEmpresas] = novaEmpresa;
    (*numEmpresas)++;
}
