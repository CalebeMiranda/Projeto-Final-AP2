#ifndef Portal_Auto
#define Portal_Auto

//--- Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

//---Define Constantes

#define MAX_NOME 50
#define MAX_EMAIL 50
#define MAX_CPF 14
#define MAX_SENHA 20

#define C1 7 // Carros abaixo de 35 mil = media 15 mil
#define C2 5 // Carros abaixo de 45 mil = media 30 mil
#define C3 5 // Carros abaixo de 75 mil = media 50 mil
#define C4 5 // Carros abaixo de 100 mil = media 80 mil

// Define para manipular os arquivos do banco de dados
#define QUANT_CARROS 22
#define TAM_NOME_CARRO 70

//---Structs

// Estrutura para armazenar os dados do usuário
struct Usuario
{
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];
};

struct carros // Carros é o tipo de dado
{
    int tipo_valor;
    int numero_carro;
    int carrocerto;
    int combustivel;
    int portas;
    int viagem;
    int cambio;
    int marca;
};

// criei uma variavel que chama carros do tipo de dado carros
typedef struct carros Carro;

Carro carros[QUANT_CARROS];

/*
    Variavel carrocerto = todos os carros começam com ela valendo 10, dependendo das respostas do cliente essa variavel
    vai diminuir de valor e assim o programa sabe qual o melhor carro pra ela
    Variavel combustivel =  1 para gasolina e 2 para flex
    Variavel portas = 1 para 2 portas e 2 para 4 portas
    Variavel viagem = 0 pequeno 1 para carro espaçoso
    Variavel cambio = 1 manual e 2 automatico
    Variavel marca = Saber a marca do carro
*/

//---Comentarios

/* Esta em ordem alfabetica marcas
            Chevrolet   = 1
            Fiat        = 2
            Ford        = 3
            Honda       = 4
            Hyundai     = 5
            Nissan      = 6
            Renault     = 7
            Toyota      = 8
            Volkswagen  = 9
            */

//===============VARIAVEIS GERAL===================
/*Variavel mudardados é usada para ser a condição do laço de repetição while, e as condições para saber qual é o tipo
de dado que o cliente quer mudar caso ele escolha algum para ser mudado*/
/*Ela começa valendo -1 pois assim ela é != 0, e no if de cada tipo de leitura de dado ela vale -1 então da primeira
vez que o while roda faz todo tipo de leitura, assim quando o cliente inserir 0 (para nao mudar dados) o codigo para*/
int mudardados = -1;

// Valormaximo é o valor inserido pelo cliente do que ele ira gastar com o carro
float valormaximo;

// Variavel valida é usada para fazer o tratamento de erro
int valida;

// Usado para manipular as estruturas for
int i, j;

// As variaveis com o inicio de "cliente" são os valores inseridos pelo cliente
/* As variaveis char com escolha é para eu atribuir uma palavra com base no valor que o cliente escolheu para a
    ela e conseguir mostrar as escolhas do cliente */

int clientecombustivel;
char escolhacombustivel[20];

int clienteporta;
char escolhaporta[20];

int clienteviagem;
char escolhaviagem[20];

int clientecambio;
char escolhacambio[20];

// Variavel que cria uma matriz para os nomes dos carros
char nome_carros[QUANT_CARROS][TAM_NOME_CARRO];

/*Cliente marca é um vetor pq o cliente pode inserir varias marcas que ele tem prefencia, ele é de 10 posiçoes pois
a primeira posição é para saber se ele quer escolhar marca ou se ele nao tem preferencia pela marca*/
int clientemarca[10];

/*Escolha marca é uma string de ate 20 caracteres com 9 linhas, sendo elas a possibilidade maxima de
marcas preferidas do cliente*/
char escolhamarca[9][20];

/*Criei uma variavel int e ela vai receber valor de 1 a 5, sendo isso a media de preço que o cliente quer
isso foi usado para entrar no swith case*/
int valor, comeco, fina;

/*A variavel maiorpontos serve para ser armazenada nela qual é o maior numero que um carro tem na variavel
carrocerto, depois de ser passado por todos os testes, assim o programa mostrara o melhor carro ou carros se tiver
mais de um carro com esta mesma pontuação */
int maiorpontos = 0;

int opcao;

void ler_dados_carros()
{
    FILE *arquivo;
    arquivo = fopen("infocarros.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    i = 0;
    while (i < QUANT_CARROS && fscanf(arquivo, "%d,%d,%d,%d,%d,%d,%d,%d",
                                      &carros[i].tipo_valor, &carros[i].numero_carro,
                                      &carros[i].carrocerto, &carros[i].combustivel,
                                      &carros[i].portas, &carros[i].viagem,
                                      &carros[i].cambio, &carros[i].marca) == 8)
    {
        i++;
    }

    fclose(arquivo);
}
//***************************************************************************************************************

void ler_nomes_carros()
{
    FILE *arquivo;
    arquivo = fopen("nomecarros.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    i = 0;
    char linha[TAM_NOME_CARRO];
    while (fgets(linha, TAM_NOME_CARRO, arquivo) != NULL && i < QUANT_CARROS)
    {
        // Remove o caractere de nova linha (\n) da string lida do arquivo
        linha[strcspn(linha, "\n")] = '\0';
        strncpy(nome_carros[i], linha, TAM_NOME_CARRO);
        i++;
    }

    fclose(arquivo);
}

//***************************************************************************************************************
void valor_maximo_cliente()
{
    printf("\n-------------Valor maximo a pagar no carro-------------\n");
    do
    {
        // Valida volta a valer 0 sempre que se reinicia a leitura
        valida = 0;
        printf("\n...Qual o valor maximo que deseja pagar em um carro?\n\n...Insira o valor R$");
        scanf("%f", &valormaximo);

        // Se o valor for abaixo de 10000
        if (valormaximo >= 0 && valormaximo < 10000)
        {
            printf("\n***Não temos carros abaixo do valor de R$10.000,00\n\n");
            /*Valida = 1, pois a condição do codigo se repetir é se valida == 1, assim eu sei que o usuario
            inseriu um numero invalido e o codigo pede para inserir outro valor*/
            valida = 1;
        }
        else if (valormaximo < 0)
        {
            printf("\n***Voce deve inserir numeros positivos\n\n");
            valida = 1;
        }

    } while (valida == 1);
}

//***************************************************************************************************************
void escolha_combustivel()
{

    do
    {
        valida = 0;
        printf("\n...Voce tem preferencia pelo tipo de combustivel do carro?\n");
        printf("   0 - (NÃO)\n   1 - (GASOLINA)\n   2 - (Flex)\n\n...Insira o numero:");
        scanf("%d", &clientecombustivel);

        // Se o cliente inserir um numero diferente de (0,1,2)
        if (clientecombustivel != 0 && clientecombustivel != 1 && clientecombustivel != 2)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            // valida passa a valer 1 e o codigo vai se repetir
            valida = 1;
        }

    } while (valida == 1);
}

void escolha_combustivel_2()
{
    /*Armazenando uma frase na variavel string escolha com base no valor que o cliente escolheu*/
    if (clientecombustivel == 0)
    {
        strcpy(escolhacombustivel, "Sem preferencia.");
    }
    else if (clientecombustivel == 1)
    {
        strcpy(escolhacombustivel, "Gasolina");
    }
    else
    {
        strcpy(escolhacombustivel, "Flex");
    }
}
//***************************************************************************************************************
void quantidade_portas()
{

    do
    {
        valida = 0;

        printf("\n...Voce tem preferencia pela quantidade portas?\n");
        printf("   0 - (NÃO)\n   1 - (2 PORTAS)\n   2 - (4 PORTAS)\n\n...Insira o numero:");
        scanf("%d", &clienteporta);
        if (clienteporta != 0 && clienteporta != 1 && clienteporta != 2)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            valida = 1;
        }
    } while (valida == 1);
}

void quantidade_portas_2()
{
    // Armazenando frase na variavel escolha
    if (clienteporta == 0)
    {

        strcpy(escolhaporta, "Sem preferencia.");
    }
    else if (clienteporta == 1)
    {

        strcpy(escolhaporta, "2 Portas");
    }
    else
    {

        strcpy(escolhaporta, "4 Portas");
    }
}
//***************************************************************************************************************
void viagem_ou_nao()
{
    printf("\n-------------Carro sera usado para viagem?-------------\n");
    do
    {

        valida = 0;
        printf("\n...Voce ira fazer muitas viagens com seu carro?\n");
        printf("   0 - (NÃO)\n   1 - (SIM)\n\n...Insira o numero:");
        scanf("%d", &clienteviagem);

        if (clienteviagem != 0 && clienteviagem != 1)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            valida = 1;
        }

    } while (valida == 1);
}

void viagem_ou_nao_2()
{
    if (clienteviagem == 0)
    {

        strcpy(escolhaviagem, "Sem preferencia.");
    }
    else
    {

        strcpy(escolhaviagem, "Carros para viagem");
    }
}
//***************************************************************************************************************
void transmissao()
{

    printf("\n-------------Carro automatico ou manual-------------\n");

    do
    {

        valida = 0;
        printf("\n...Voce tem preferencia pelo tipo de cambio?\n");
        printf("   0 - (NÃO)\n   1 - (MANUAL)\n   2 - (AUTOMATICO)\n\n...Insira o numero:");
        scanf("%d", &clientecambio);

        if (clientecambio != 0 && clientecambio != 1 && clientecambio != 2)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            valida = 1;
        }

    } while (valida == 1);
}

void transmissao_2()
{
    if (clientecambio == 0)
    {

        strcpy(escolhacambio, "Sem preferencia.");
    }
    else if (clientecambio == 1)
    {

        strcpy(escolhacambio, "Manual");
    }
    else
    {

        strcpy(escolhacambio, "Automatico");
    }
}
//***************************************************************************************************************
void marca()
{
    printf("\n-------------Marcas preferidas-------------\n");

    do
    {

        valida = 0;
        printf("...Você deseja inserir suas marcas preferidas?\n");
        printf("   0 - (NÃO)\n   1 - (SIM)\n\n...Insira o numero:");
        scanf("%d", &clientemarca[0]);

        if (clientemarca[0] != 0 && clientemarca[0] != 1)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            valida = 1;
        }

    } while (valida == 1);
}

void marca_2()
{

    if (clientemarca[0] == 1)
    {

        printf("\n...Quais marcas você tem preferencia?(Insira quantas desejar)\n");
        printf("   1 - (CHEVROLET)\n   2 - (FIAT)\n   3 - (FORD)\n   4 - (HONDA)\n   5 - (HYUNDAI)\n");
        printf("   6 - (NISSAN)\n   7 - (RENAULT)\n   8 - (TOYOTA)\n   9 - (VOLKSWAGEN)\n   0 - (PARAR DE INSERIR)\n");
        printf("OBS(INSIRA UMA MARCA POR VEZ)\n");

        // Essa parte vai se repetir para ler quantas marcas ele tem como preferida
        // O laço começa no 1 pois a posição 0 do vetor clientemarca é destinada se ele tem marca preferida ou se não
        for (i = 1; i < 10; i++)
        {
            do
            {
                valida = 0;

                printf("\n...%d- Marca:", i);
                scanf("%d", &clientemarca[i]);

                // Tratamento de erro
                if (clientemarca[i] < 0 || clientemarca[i] > 9)
                {
                    printf("\n***Insira apenas os valores indicados.\n");
                    valida = 1;
                }

            } while (valida == 1);

            // se o usuario digitou 0 nessa possição quer dizer que ele não quer inserir mais marcas
            if (clientemarca[i] == 0)
            {
                // Para o laço de repetição
                break;
            }
            else
            {
                /*Aqui eu armazeno o tipo da marca que o cliente escolheu na string matriz escolhamarca
                na posição([i - 1], pois como o laço começa no 1) aqui eu quero armazenar desde o 0*/
                switch (clientemarca[i])
                {
                case 1:
                    strcpy(escolhamarca[i - 1], "CHEVROLET");
                    break;
                case 2:
                    strcpy(escolhamarca[i - 1], "FIAT");
                    break;
                case 3:
                    strcpy(escolhamarca[i - 1], "FORD");
                    break;
                case 4:
                    strcpy(escolhamarca[i - 1], "HONDA");
                    break;
                case 5:
                    strcpy(escolhamarca[i - 1], "HYUNDAI");
                    break;
                case 6:
                    strcpy(escolhamarca[i - 1], "NISSAN");
                    break;
                case 7:
                    strcpy(escolhamarca[i - 1], "RENAULT");
                    break;
                case 8:
                    strcpy(escolhamarca[i - 1], "TOYOTA");
                    break;
                case 9:
                    strcpy(escolhamarca[i - 1], "VOLKSWAGEN");
                    break;
                }
            }
        }
    }
}
//***************************************************************************************************************
void dados_do_cliente()
{
    printf("\n-------------Dados do cliente-------------\n\n");
    printf("Valor maximo...............: R$%.2f\n", valormaximo);
    printf("Combustivel................: %s\n", escolhacombustivel);
    printf("Portas.....................: %s\n", escolhaporta);
    printf("Viagem.....................: %s\n", escolhaviagem);
    printf("Cambio.....................: %s\n", escolhacambio);
}
//***************************************************************************************************************
void marca_escolhida()
{
    if (clientemarca[0] == 0)
    {
        printf("Sem preferencia de marca...:");
    }
    else
    {
        printf("Marcas(s) preferida(s).....:\n");

        /*Aqui o codigo se repete ate a escolha do cliente em alguma posição for 0, o que quer dizer
        que o cliente inseriu 0 pois nao foi colocado mais marcas preferidas*/
        for (i = 0; clientemarca[i + 1] != 0; i++)
        {

            printf("%d - %s\n", i + 1, escolhamarca[i]);
        }
    }
}
//***************************************************************************************************************
void deseja_alterar_algum_dado()
{
    do
    {
        valida = 0;
        printf("\n...Deseja alterar algum dado?\n");
        printf("   0 - (NÃO)\n   1 - (SIM)\n\n...Insira o numero:");
        scanf("%d", &mudardados);
        if (mudardados != 0 && mudardados != 1)
        {
            printf("\n***Insira apenas os valores indicados.\n");
            valida = 1;
        }
    } while (valida == 1);
}
//***************************************************************************************************************
void alterar_algum_dado()
{
    if (mudardados == 1)
    {
        do
        {
            valida = 0;

            printf("\n...Qual dado deseja mudar?\n");
            printf("   1 - Valor maximo\n   2 - Combustivel\n   3 - Portas\n   4 - Viagem\n");
            printf("   5 - Cambio\n   6 - Marcas\n\n...Insira o numero:");
            scanf("%d", &mudardados);

            if (mudardados < 0 || mudardados > 6)
            {
                printf("\n***Insira apenas os valores indicados.\n");
                valida = 1;
            }

        } while (valida == 1);
    }
}
//***************************************************************************************************************
void aux_switch()
{

    if (valormaximo <= 20000)
    {
        valor = 1;
        comeco = 0;
        fina = 6;
    }
    else if (valormaximo <= 40000)
    {
        valor = 2;
        comeco = 7;
        fina = 11;
    }
    else if (valormaximo <= 60000)
    {
        valor = 3;
        comeco = 12;
        fina = 16;
    }
    else
    {
        valor = 4;
        comeco = 17;
        fina = 21;
    }
}
//***************************************************************************************************************
void melhores_opcoes()
{
    printf("\n\n-------------Melhores opções de carros-------------\n");
    /*Testando as preferencias do cliente em um laço de repetição e transformando
        a variavel carro certo = 0 nos carros que a preferencia nao bater*/
    for (i = comeco; i <= fina; i++)
    {

        // testando a preferencia do cliente no combustivel
        if (clientecombustivel != carros[i].combustivel)
        {
            if (clientecombustivel != 0)
            {
                carros[i].carrocerto--;
            }
        }

        // Testando a opção de porta
        if (clienteporta != 0)
        {
            if (clienteporta != carros[i].portas)
            {
                carros[i].carrocerto--;
            }
        }

        // comparando se o cliente escolheu que quer um carro pra viagem
        if (clienteviagem != 0)
        {
            if (clienteviagem != carros[i].viagem)
            {
                carros[i].carrocerto--;
            }
        }

        // Apenas cambios manuais para este valor
        //"0-Não 1-Manual 2-Automatico
        if (clientecambio != 0)
        {
            if (clientecambio != carros[i].cambio)
            {
                carros[i].carrocerto--;
            }
        }

        // Comparando marcas preferidas
        if (clientemarca[0] == 1)
        {
            for (j = 1; clientemarca[j] != 0; j++)
            {
                if (clientemarca[j] != carros[i].marca)
                {
                    carros[i].carrocerto--;
                }
            }
        }

        // Sabendo qual foi a maior pontuação
        if (carros[i].carrocerto > maiorpontos)
        {
            maiorpontos = carros[i].carrocerto;
        }
    }

    // Mostrando o(s) carro(s) com maior pontuação
    for (i = comeco; i <= fina; i++)
    {
        if (carros[i].carrocerto == maiorpontos)
        {
            printf("Melhor opcao:%s \n", nome_carros[i]);
            printf("\n");
        }
    }
    if (valor == 1)
    {
        printarcarro1();
        printf("\n");
    }
    else if (valor == 2)
    {
        printarcarro2();
        printf("\n");
    }
    else if (valor == 3)
    {
        printarcarro3();
        printf("\n");
    }
    else if (valor == 4)
    {
        printarcarro4();
        printf("\n");
    }
}
//***************************************************************************************************************
void escolha_opcao()
{
    switch (opcao)
    {
    case 1:
        system("cls");
        cadastrar();
        break;
    case 2:
        system("cls");
        login();
        break;
    case 3:
        system("cls");
        printf("Saindo...\n");
        printf("Agradecemos a preferencia :D\n");
        printf("Criadores: Calebe, Fernando Carvalho e Fernando Leão.\n");
        obrigado();
        getch();
        break;
    default:
        system("cls");
        printf("Opção inválida.\n\n");
        break;
    }
}
//***************************************************************************************************************
void printarcarro4()
{
    printf("\n");
    printf("\n");
    printf("\n                       ___................._");
    printf("\n              __.. ' _' ......\\\\..........- .`-._");
    printf("\n  ______.-'         (_) |      \\\\           ` \\\\`-. _");
    printf("\n /_       --------------'-------\\\\---....______\\\\__`.`  -..___");
    printf("\n | T      _.----._           Xxx|x...           |          _.._`--. _");
    printf("\n | |    .' ..--.. `.         XXX|XXXXXXXXXxx==  |       .'.---..`.     -._");
    printf("\n \\_j   /  /  __  \\  \\        XXX|XXXXXXXXXXX==  |      / /  __  \\ \\        `-.");
    printf("\n  _|  |  |  /  \\  |  |       XXX|"
           "'              |     / |  /  \\  | |          |");
    printf("\n |__\\_j  |  \\__/  |  L__________|_______________|_____j |  \\__/  | L__________J");
    printf("\n      `\\ \\       / ./__________________________________\\ \\      / /___________\\ ");
    printf("\n         `.`----'.'                                     `.`----'.'  ");
    printf("\n           `----'                                         `-----");
}
//***************************************************************************************************************
void printarcarro1()
{
    printf("\n          ######################                  ");
    printf("\n        ##########################                ");
    printf("\n        ############################              ");
    printf("\n      ######      ####        ########            ");
    printf("\n      ######      ####          ########          ");
    printf("\n    ########      ####            ######          ");
    printf("\n    ##########################################    ");
    printf("\n  ################################################");
    printf("\n##################################################");
    printf("\n##################################################");
    printf("\n##################################################");
    printf("\n##################################################");
    printf("\n############  ######################    ##########");
    printf("\n##########      ##################        ########");
    printf("\n      ####      ####          ####        ####    ");
    printf("\n      ######  ######            ######  ######    ");
    printf("\n        ############            ############      ");
    printf("\n          ######                  ########        ");
}
//***************************************************************************************************************
void printarcarro2()
{
    printf("\n         _______      ");
    printf("\n        //  ||\\ \\     ");
    printf("\n  _____//___||_\\ \\___ ");
    printf("\n ))  _          _    \\");
    printf("\n  |_/ \\________/ \\___|");
    printf("\n ___\\_/________\\_/____");
}
//***************************************************************************************************************
void printarcarro3()
{
    printf("\n                       ____________________                              ");
    printf("\n                    //|           |        \\                            ");
    printf("\n                  //  |           |          \\                          ");
    printf("\n     ___________//____|___________|__________()\\__________________      ");
    printf("\n    /__________________|_=_________|_=___________|_________________{}    ");
    printf("\n    [           ______ |           | .           | ==  ______      { }   ");
    printf("\n__[__        /##  ##\\|           |             |    /##  ##\\    _{# }_ ");
    printf("\n{_____)______|##    ##|___________|_____________|___|##    ##|__(______}");
    printf("\n            /  ##__##                              /  ##__##        \\   ");
}
//***************************************************************************************************************
void obrigado()
{
    printf("\n");
    printf("\n");
    printf("\n");

    printf("\n  ______   __                  __                            __                  __ ");
    printf("\n /      \\ |  \\                |  \\                          |  \\                |  \\ ");
    printf("\n|  $$$$$$\\| $$____    ______   \\$$  ______    ______    ____| $$  ______        | $$");
    printf("\n| $$  | $$| $$    \\  /      \\ |  \\ /      \\  |      \\  /      $$ /      \\       | $$");
    printf("\n| $$  | $$| $$$$$$$\\|  $$$$$$\\| $$|  $$$$$$\\  \\$$$$$$\\|  $$$$$$$|  $$$$$$\\      | $$");
    printf("\n| $$  | $$| $$  | $$| $$  \\$$ | $$| $$  | $$ /      $$| $$  | $$| $$  | $$       \\$$");
    printf("\n| $$__/ $$| $$__/ $$| $$      | $$| $$__| $$|  $$$$$$$| $$__| $$| $$__/ $$       __ ");
    printf("\n \\$$    $$| $$    $$| $$      | $$ \\$$    $$ \\$$    $$ \\$$    $$ \\$$    $$      |  \\ ");
    printf("\n  \\$$$$$$  \\$$$$$$$  \\$$       \\$$ _\\$$$$$$$  \\$$$$$$$  \\$$$$$$$  \\$$$$$$        \\$$");
    printf("\n                                  |  \\__| $$                                        ");
    printf("\n                                   \\$$    $$                                        ");
    printf("\n                                    \\$$$$$$                                         ");
}
//***************************************************************************************************************
void printar_Autoinfo()
{
    printf("\n  _______                        __                __         ______               __                      ______             ______           ");
    printf("\n |       \\                      |  \\              |  \\       /      \\             |  \\                    |      \\           /      \\          ");
    printf("\n | $$$$$$$\\  ______    ______  _| $$_     ______  | $$      |  $$$$$$\\ __    __  _| $$_     ______         \\$$$$$$ _______  |  $$$$$$\\ ______  ");
    printf("\n | $$__/ $$ /      \\  /      \\|   $$ \\   |      \\ | $$      | $$__| $$|  \\  |  \\|   $$ \\   /      \\  ______ | $$  |       \\ | $$_  \\$$/      \\ ");
    printf("\n | $$    $$|  $$$$$$\\|  $$$$$$\\$$$$$$    \\$$$$$$\\ | $$      | $$    $$| $$  | $$ \\$$$$$$  |  $$$$$$\\|      \\| $$  | $$$$$$$\\| $$ \\   |  $$$$$$\\ ");
    printf("\n | $$$$$$$ | $$  | $$| $$   \\$$ | $$ __  /      $$| $$      | $$$$$$$$| $$  | $$  | $$ __ | $$  | $$ \\$$$$$$| $$  | $$  | $$| $$$$   | $$  | $$ ");
    printf("\n | $$      | $$__/ $$| $$       | $$|  \\|  $$$$$$$| $$      | $$  | $$| $$__/ $$  | $$|  \\| $$__/ $$       _| $$_ | $$  | $$| $$     | $$__/ $$ ");
    printf("\n | $$       \\$$    $$| $$        \\$$  $$ \\$$    $$| $$      | $$  | $$ \\$$    $$   \\$$  $$ \\$$    $$      |   $$ \\| $$  | $$| $$      \\$$    $$ ");
    printf("\n  \\$$        \\$$$$$$  \\$$         \\$$$$   \\$$$$$$$ \\$$       \\$$   \\$$  \\$$$$$$     \\$$$$   \\$$$$$$        \\$$$$$$ \\$$   \\$$ \\$$       \\$$$$$$  ");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("\n BEM VINDO(A) !");
    printf("\n Para obter sua análise personalizada, favor responda todas as perguntas do questionário!");
    printf("\n QUESTIONÁRIO DE PESQUISA PERSONALIZADA: ");

    printf("\n");
    printf("\n");
}
//***************************************************************************************************************

#endif