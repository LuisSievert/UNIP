//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Constantes
#define OPCAO_LOGIN 1
#define OPCAO_CADASTRO 2
#define OPCAO_ESQUECI_SENHA 3
#define OPCAO_CADASTRAR_EMPRESA 1
#define OPCAO_GERENCIAR_EMPRESAS 2
#define OPCAO_RELATORIOS_GLOBAIS 3
#define OPCAO_SAIR 4
#define FOREGROUND   "\x1b[32m" //GREEN
#define FOREGROUND   "\x1b[31m" //RED
#define FOREGROUND_RESET   "\x1b[0m"

// Estrutura para armazenar informa��es do usu�rio
struct Usuario {
  char nome[100];
  char cpf[12];
  char senha[100];
};

// Fun��o para verificar a validade do usu�rio e senha
int verificar_credenciais(const char *usuario, const char *senha, const struct Usuario *usuarios, int num_usuarios) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuario, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
      return 1;  // Credenciais v�lidas
    }
  }
  return 0;  // Credenciais inv�lidas
}

//Fun��es
void exibir_cabecalho();
int exibir_menu_inicial();
void exibir_tela_cadastro(struct Usuario *usuarios, int *num_usuarios);
void exibir_tela_login(const struct Usuario *usuarios, int num_usuarios);
void exibir_menu_principal();
void set_color(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
  setlocale(LC_ALL, "");  // Configura a localiza��o para suportar acentos
  exibir_cabecalho();

  // Inicialize alguns usu�rios fict�cios
  struct Usuario usuarios[] = {
    {"xxxx", "xxxxxx"},
    // Adicione mais usu�rios conforme necess�rio
  };

  int num_usuarios = sizeof(usuarios) / sizeof(usuarios[0]);

  int opcao;

  do {
    opcao = exibir_menu_inicial();

    switch (opcao) {
    case OPCAO_LOGIN:
      exibir_tela_login(usuarios, num_usuarios);
      break;
    case OPCAO_CADASTRO:
      exibir_tela_cadastro(usuarios, &num_usuarios);
      break;
    case OPCAO_ESQUECI_SENHA:
      printf("Essa op��o ainda n�o est� dispon�vel.\n");
      break;
    }
  } while (opcao != OPCAO_LOGIN);

  exibir_menu_principal();

  return 0;
}

void exibir_cabecalho() {
  printf("\t\t------------------------------------\n\n");
  printf("\t\t========== SISTEMA STARTUP ============\n\n" );
  printf("\t\tGerenciador de Solu��es Ambientais\n\n");
  printf("\t\t========= Seja Bem-vindo! ==========\n\n");
  printf("\t\t------------------------------------\n\n\n");
 }

int exibir_menu_inicial() {
  int opcao;

  printf("Escolha uma Op��o:\n");
  printf("[1] Realizar Login.\n");
  printf("[2] Ainda n�o tenho cadastro.\n");
  printf("[3] Esqueci minha senha.\n");

  printf("Op��o escolhida: ");
  scanf("%d", &opcao);

  return opcao;
}

void exibir_tela_cadastro(struct Usuario *usuarios, int *num_usuarios) {
  printf("------------------------------------\n");
  set_color(FOREGROUND_GREEN);
  printf("CADASTRO DE FUNCION�RIO\n");
  set_color(FOREGROUND_RESET);
  printf("------------------------------------\n");

  printf("Por favor, preencha os seguintes dados:\n");

  struct Usuario novoUsuario;

  printf("Nome Completo: ");
  scanf(" %[^\n]s", novoUsuario.nome);
  printf("Digite seu CPF: ");
  scanf(" %[^\n]s", novoUsuario.cpf);
  printf("Digite sua senha: ");
  scanf(" %[^\n]s", novoUsuario.senha);

  set_color(FOREGROUND_GREEN);
  printf("Seu cadastro foi realizado com sucesso!\n");
  set_color(FOREGROUND_RESET);
  printf("Seu usu�rio �: %s\n", novoUsuario.nome);
  printf("Seu CPF �: %s\n", novoUsuario.cpf);
  printf("Sua senha �: %s\n", novoUsuario.senha);

  // Adicione o novo usu�rio � lista de usu�rios
  usuarios[*num_usuarios] = novoUsuario;
  (*num_usuarios)++;

  printf("Retorne � tela inicial pressionando 'espa�o + enter' no teclado.\n");
  while (getchar() != ' ');
}

void exibir_tela_login(const struct Usuario *usuarios, int num_usuarios) {
  int tentativas_maximas = 3;
  int tentativas = 0;
  int credenciais_validas = 0;

  do {
    printf("------------------------------------\n");
    set_color(FOREGROUND_GREEN);
    printf("FA�A LOGIN\n");
    set_color(FOREGROUND_RESET);
    printf("------------------------------------\n");

    char usuario[100];
    char senha[100];

    printf("Informe o Usu�rio: ");
    scanf(" %[^\n]s", usuario);

    printf("Informe a senha: ");
    scanf(" %[^\n]s", senha);

    // Verifica a validade do usu�rio e senha
    if (verificar_credenciais(usuario, senha, usuarios, num_usuarios)) {
      printf("Usu�rio v�lido!\n");
      printf("Senha correta!\n");
      credenciais_validas = 1;
    } else {
      set_color(FOREGROUND_RED);
      printf("Usu�rio ou senha inv�lidos! Tente novamente.\n");
      set_color(FOREGROUND_RESET);
      tentativas++;

      if (tentativas >= tentativas_maximas) {
        printf("N�mero m�ximo de tentativas atingido. Saindo do sistema.\n");
        exit(1);
      }
    }
  } while (!credenciais_validas);
}

void exibir_menu_principal() {
  int opcao;

  do {
    printf("------------------------------------\n");
    set_color(FOREGROUND_GREEN);
    printf("MENU INICIAL\n");
    set_color(FOREGROUND_RESET);
    printf("------------------------------------\n");
    printf("Por favor, escolha uma op��o:\n");
    printf("[1] Cadastrar nova empresa\n");
    printf("[2] Gerenciar empresas\n");
    printf("[3] Relat�rios Globais\n");
    printf("[4] Sair\n");

    printf("Op��o Escolhida: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case OPCAO_CADASTRAR_EMPRESA:
      printf("L�gica para cadastrar nova empresa.\n");
      break;
    case OPCAO_GERENCIAR_EMPRESAS:
      printf("L�gica para gerenciar empresas.\n");
      break;
    case OPCAO_RELATORIOS_GLOBAIS:
      printf("L�gica para relat�rios globais.\n");
      break;
    case OPCAO_SAIR:
      printf("Saindo do sistema.\n");
      break;
    default:
      printf("Op��o inv�lida. Tente novamente.\n");
      break;
    }
  } while (opcao != OPCAO_SAIR);
}
