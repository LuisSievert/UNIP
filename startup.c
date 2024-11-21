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

// Estrutura para armazenar informações do usuário
struct Usuario {
  char nome[100];
  char cpf[12];
  char senha[100];
};

// Função para verificar a validade do usuário e senha
int verificar_credenciais(const char *usuario, const char *senha, const struct Usuario *usuarios, int num_usuarios) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuario, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
      return 1;  // Credenciais válidas
    }
  }
  return 0;  // Credenciais inválidas
}

//Funções
void exibir_cabecalho();
int exibir_menu_inicial();
void exibir_tela_cadastro(struct Usuario *usuarios, int *num_usuarios);
void exibir_tela_login(const struct Usuario *usuarios, int num_usuarios);
void exibir_menu_principal();
void set_color(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
  setlocale(LC_ALL, "");  // Configura a localização para suportar acentos
  exibir_cabecalho();

  // Inicialize alguns usuários fictícios
  struct Usuario usuarios[] = {
    {"xxxx", "xxxxxx"},
    // Adicione mais usuários conforme necessário
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
      printf("Essa opção ainda não está disponível.\n");
      break;
    }
  } while (opcao != OPCAO_LOGIN);

  exibir_menu_principal();

  return 0;
}

void exibir_cabecalho() {
  printf("\t\t------------------------------------\n\n");
  printf("\t\t========== SISTEMA STARTUP ============\n\n" );
  printf("\t\tGerenciador de Soluções Ambientais\n\n");
  printf("\t\t========= Seja Bem-vindo! ==========\n\n");
  printf("\t\t------------------------------------\n\n\n");
 }

int exibir_menu_inicial() {
  int opcao;

  printf("Escolha uma Opção:\n");
  printf("[1] Realizar Login.\n");
  printf("[2] Ainda não tenho cadastro.\n");
  printf("[3] Esqueci minha senha.\n");

  printf("Opção escolhida: ");
  scanf("%d", &opcao);

  return opcao;
}

void exibir_tela_cadastro(struct Usuario *usuarios, int *num_usuarios) {
  printf("------------------------------------\n");
  set_color(FOREGROUND_GREEN);
  printf("CADASTRO DE FUNCIONÁRIO\n");
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
  printf("Seu usuário é: %s\n", novoUsuario.nome);
  printf("Seu CPF é: %s\n", novoUsuario.cpf);
  printf("Sua senha é: %s\n", novoUsuario.senha);

  // Adicione o novo usuário à lista de usuários
  usuarios[*num_usuarios] = novoUsuario;
  (*num_usuarios)++;

  printf("Retorne à tela inicial pressionando 'espaço + enter' no teclado.\n");
  while (getchar() != ' ');
}

void exibir_tela_login(const struct Usuario *usuarios, int num_usuarios) {
  int tentativas_maximas = 3;
  int tentativas = 0;
  int credenciais_validas = 0;

  do {
    printf("------------------------------------\n");
    set_color(FOREGROUND_GREEN);
    printf("FAÇA LOGIN\n");
    set_color(FOREGROUND_RESET);
    printf("------------------------------------\n");

    char usuario[100];
    char senha[100];

    printf("Informe o Usuário: ");
    scanf(" %[^\n]s", usuario);

    printf("Informe a senha: ");
    scanf(" %[^\n]s", senha);

    // Verifica a validade do usuário e senha
    if (verificar_credenciais(usuario, senha, usuarios, num_usuarios)) {
      printf("Usuário válido!\n");
      printf("Senha correta!\n");
      credenciais_validas = 1;
    } else {
      set_color(FOREGROUND_RED);
      printf("Usuário ou senha inválidos! Tente novamente.\n");
      set_color(FOREGROUND_RESET);
      tentativas++;

      if (tentativas >= tentativas_maximas) {
        printf("Número máximo de tentativas atingido. Saindo do sistema.\n");
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
    printf("Por favor, escolha uma opção:\n");
    printf("[1] Cadastrar nova empresa\n");
    printf("[2] Gerenciar empresas\n");
    printf("[3] Relatórios Globais\n");
    printf("[4] Sair\n");

    printf("Opção Escolhida: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case OPCAO_CADASTRAR_EMPRESA:
      printf("Lógica para cadastrar nova empresa.\n");
      break;
    case OPCAO_GERENCIAR_EMPRESAS:
      printf("Lógica para gerenciar empresas.\n");
      break;
    case OPCAO_RELATORIOS_GLOBAIS:
      printf("Lógica para relatórios globais.\n");
      break;
    case OPCAO_SAIR:
      printf("Saindo do sistema.\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  } while (opcao != OPCAO_SAIR);
}
