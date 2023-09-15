#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>
#include "Portal_AUTO.h"

// Função referente ao aplicativo
void portal()
{

    // Colocando em portugues
    setlocale(LC_ALL, "Portuguese");

    /*-----------------------QUESTIONARIO DO CLIENTE-------------------------------------------*/

    while (mudardados != 0)
    {

        /*EXPLICANDO OS IF DE MUDARDADOS
        Se mudardados == x quer dizer que o cliente escolheu para mudar esse dado e essa parte da leitura do codigo se repitarada
        || (OU) se mudardados == -1 essa parte acontecera, como o mudardados = -1 na priemira vez que inicia o codigo então ele fara
        todas as leituras, pois no OU so um precisa ser verdadeiro para a condição ser verdadeira*/

        printar_Autoinfo();

        // Lendo valor a pagar no carro
        if (mudardados == 1 || mudardados == -1)
        {
            valor_maximo_cliente();
        }

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        // Lendo qual tipo de combustivel que o cliente prefere
        if (mudardados == 2 || mudardados == -1)
        {
            escolha_combustivel();
        }

        escolha_combustivel_2();

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        // Lendo quantas portas o cliente prefere
        if (mudardados == 3 || mudardados == -1)
        {
            printf("\n-------------Preferencia pela quantidade de portas-------------\n");

            quantidade_portas();
        }

        quantidade_portas_2();

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        // Lendo se o cliente ira fazer viagens com o carro o q implica que ele precisa de um carro grande
        if (mudardados == 4 || mudardados == -1)
        {
            viagem_ou_nao();
        }

        // Armazenando frase na varivel escolha
        viagem_ou_nao_2();

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        // Lendo o tipo de cambio que o cliente prefere
        if (mudardados == 5 || mudardados == -1)
        {
            transmissao();
        }

        // Armazenando frase na variavel escolha
        transmissao_2();

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        // Escolhendo preferencia de marca
        if (mudardados == 6 || mudardados == -1)
        {

            marca();

            // Se o cliente tem preferencia vai entrar aqui
            marca_2();
        }

        //--------------------------------------------Limpar a tela--------------------------------------------
        system("cls");

        /*Aqui o programa mostra os dados do cliente, aqui é usado as variaveis escolha tipo string
        pois assim eu armazeno e sei qual é a escolha do cliente em uma string*/
        dados_do_cliente();
        // Mostrando marcas preferidas.

        // Se o cliente inseriu 0 na primeira posição é pq ele nao escolheu nenhuma marca
        marca_escolhida();

        // Perguntando para o cliente se ele quer alterar algum dado?
        deseja_alterar_algum_dado();

        // Se o cliente quer alterar algum dado a resposta é 1 e ira entrar nessa condição
        alterar_algum_dado();
        // Limpa a tela
        system("cls");

    } // volta e verifica a condição se o mudardados for != de 0 o codigo se repete

    aux_switch();

    melhores_opcoes();
    printf(" \n Aperte qualquer tecla para continuar !\n");
    getch();
}
// Função para cadastrar um novo usuário
void cadastrar()
{
    struct Usuario usuario;
    // Pede para o usuario digitar o Nome completo e faz a leitura do mesmo
    printf("Digite o nome completo: ");
    fgets(usuario.nome, MAX_NOME, stdin);
    usuario.nome[strcspn(usuario.nome, "\n")] = '\0'; // remove o caractere de nova linha do final da string

    // Pede para o usuario digitar o email e faz a leitura do mesmo
    printf("Digite o email: ");
    fgets(usuario.email, MAX_EMAIL, stdin);
    usuario.email[strcspn(usuario.email, "\n")] = '\0';

    // loop para validação do CPF
    char cpf_valido = 0;
    while (!cpf_valido)
    {
        // Pede para o usuario digitar o CPF e faz a leitura do mesmo
        printf("Digite o CPF (somente números): ");
        fgets(usuario.cpf, MAX_CPF, stdin);
        usuario.cpf[strcspn(usuario.cpf, "\n")] = '\0';

        cpf_valido = 1;
        for (i = 0; usuario.cpf[i] != '\0'; i++)
        {
            if (!isdigit(usuario.cpf[i]))
            {
                // Caso o CPF não for valido (conter outra coisa alem de numeros) da erro e pede novamente para digitar o CPF
                cpf_valido = 0;
                printf("Erro: o CPF deve conter apenas números.\n");
                break;
            }
        }
    }

    // Pede para o usuario digitar a senha e faz a leitura da mesma
    printf("Digite a senha (até %d caracteres): ", MAX_SENHA - 1);
    fgets(usuario.senha, MAX_SENHA, stdin);
    usuario.senha[strcspn(usuario.senha, "\n")] = '\0';

    // Abre o arquivo de usuários para adicionar o novo usuário
    FILE *arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuários.\n");
        exit(1);
    }

    fprintf(arquivo, "%s;%s;%s;%s\n", usuario.nome, usuario.email, usuario.cpf, usuario.senha);
    fclose(arquivo);

    system("cls");
    printf("Usuário cadastrado com sucesso!\n\n");
}
// Função para mudar alguma informação anterior
void mudar_info()
{
    int info;
    do
    {
        printf("\nQual informação deseja mudar?\n");
        printf("1-Nome\n");
        printf("2-Email\n");
        printf("3-CPF\n");
        printf("4-Senha\n");
        printf("5-Nenhuma(voltar ao menu anterior)\n");
        scanf("%d", &info);
        switch (info)
        {
        case 1:
            system("cls");
            printf("Troca de nome efetuada com sucesso\n");

            printf("Aperte qualquer tecla para proseguir.");
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            printf("mudar email\n");
            printf("Aperte qualquer tecla para proseguir.");
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            printf("mudar CPF\n");
            printf("Aperte qualquer tecla para proseguir.");
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            printf("Mudar senha\n");
            printf("Aperte qualquer tecla para proseguir.");
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            printf("Voltando...\n");
            break;
        default:
            system("cls");
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf("x  Opção invalida, Digite uma das apresentadas anteriormente  x\n");
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf("Aperte qualquer tecla para proseguir.");
            getch();
            system("cls");
            break;
        }

    } while (info != 5);
}
// Função para fazer login
void login()
{
    // loop para caso ocorra erro na digitação dos dados (email e senha)
    int sn = 0;
    do
    {
        char email[MAX_EMAIL];
        char senha[MAX_SENHA];

        // pede para inserir email e senha e faz a leitura de ambos
        fflush(stdin);
        printf("Digite o email: ");
        fgets(email, MAX_EMAIL, stdin);
        email[strcspn(email, "\n")] = '\0';

        fflush(stdin);
        printf("Digite a senha: ");
        fgets(senha, MAX_SENHA, stdin);
        senha[strcspn(senha, "\n")] = '\0';

        // Abre o arquivo de usuários para verificar se as credenciais estão corretas
        FILE *arquivo = fopen("usuarios.txt", "r");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo de usuários.\n");
            exit(1);
        }

        char linha[200];
        int encontrado = 0;

        while (fgets(linha, 200, arquivo))
        {
            linha[strcspn(linha, "\n")] = '\0';
            char *nome, *email_arq, *cpf, *senha_arq;
            nome = strtok(linha, ";");
            email_arq = strtok(NULL, ";");
            cpf = strtok(NULL, ";");
            senha_arq = strtok(NULL, ";");

            if (strcmp(email, email_arq) == 0 && strcmp(senha, senha_arq) == 0)
            {
                printf("Login efetuado com sucesso, Bem-vindo, %s!\n\n", nome);
                encontrado = 1;
                // Menu após o login bem-sucedido
                int opcao;
                do
                {
                    printf("Escolha uma opção:\n");
                    printf("1. Ver perfil\n");
                    printf("2. Utilizar o aplicativo\n");
                    printf("3. Sair da conta e voltar\n");
                    printf("> ");
                    scanf("%d", &opcao);
                    getchar(); // consome o caractere de nova linha deixado pelo scanf

                    switch (opcao)
                    {
                    case 1:
                        system("cls");
                        verPerfil(email);
                        printf("Aperte qualquer tecla para proseguir.");
                        getch();
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        portal();
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        printf("Voltando ao menu anterior...\n");
                        printf("\n");
                        sn = 2;
                        break;
                    default:
                        system("cls");
                        printf("Opção inválida.\n\n");
                        break;
                    }
                } while (opcao != 3);
                sn = 2;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Email ou senha incorretos.\n\n");
            do
            {
                printf("Deseja tentar novamente?\n");
                printf("1-SIM\n");
                printf("2-NÃO\n");
                scanf("%d", &sn);
                fflush(stdin);
                system("cls");
                if ((sn != 1) && (sn != 2))
                    printf("Opção invalida, por favor digite uma das apresentadas");
            } while ((sn != 1) && (sn != 2));
        }
    } while (sn != 2);
}
// Função para ver o perfil do usuário logado
void verPerfil(char *email)
{
    // Abre o arquivo de usuários para verificar as informações do usuário logado
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuários.\n");
        exit(1);
    }

    char linha[200];
    int encontrado = 0;

    while (fgets(linha, 200, arquivo))
    {
        linha[strcspn(linha, "\n")] = '\0';
        char *nome, *email_arq, *cpf, *senha_arq;
        nome = strtok(linha, ";");
        email_arq = strtok(NULL, ";");
        cpf = strtok(NULL, ";");
        senha_arq = strtok(NULL, ";");

        if (strcmp(email, email_arq) == 0)
        {
            printf("Nome: %s\n", nome);
            printf("Email: %s\n", email_arq);
            printf("CPF: %s\n", cpf);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Usuário não encontrado.\n\n");
    }

    fclose(arquivo);
}
// Função principal que exibe o menu e lê a opção escolhida pelo usuário
int main()
{
    setlocale(LC_ALL, "Portuguese");

    // Função que atribui os dados do banco de dados para a struct Carros
    ler_dados_carros();

    // Função que atribui os nomes dos carros a matrix nomecarros
    ler_nomes_carros();

    do
    {
        printf("Escolha uma opção:\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");
        printf("> ");
        scanf("%d", &opcao);
        getchar(); // consome o caractere de nova linha deixado pelo scanf
        int x = opcao;
        escolha_opcao(x);
    } while (opcao != 3);

    return 0;
}
