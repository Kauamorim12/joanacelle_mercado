#include <stdio.h>

#define MAX_PRODUTOS 10


void cadastrarProduto(char nomes[][50], float precos[], int quantidades[], int *total);
void consultarEstoque(char nomes[][50], float precos[], int quantidades[], int total);
void registrarVenda(char nomes[][50], float precos[], int quantidades[], int total);
void alertaReposicao(char nomes[][50], int quantidades[], int total);
void entradaMercadorias(char nomes[][50], int quantidades[], int total);
float calcularFaturamento(float preco, int quantidade);
float calcularValorTotalEstoque(float precos[], int quantidades[], int total);

int main() {

   
    char nomes[MAX_PRODUTOS][50];
    float precos[MAX_PRODUTOS];
    int quantidades[MAX_PRODUTOS];

    int totalProdutos = 0;
    int opcao;

  
    do {

        printf("\n========== CONTROLE DE ESTOQUE ==========\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Consultar estoque\n");
        printf("3 - Registrar venda\n");
        printf("4 - Consultar produtos para reposicao\n");
        printf("5 - Registrar entrada de mercadorias\n");
        printf("6 - Calcular valor do estoque\n");
        printf("7 - Encerrar programa\n");
        printf("=========================================\n");

        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            break;
        }

        switch (opcao) {

            case 1:
                cadastrarProduto(nomes, precos, quantidades, &totalProdutos);
                break;

            case 2:
                consultarEstoque(nomes, precos, quantidades, totalProdutos);
                break;

            case 3:
                registrarVenda(nomes, precos, quantidades, totalProdutos);
                break;

            case 4:
                alertaReposicao(nomes, quantidades, totalProdutos);
                break;

            case 5:
                entradaMercadorias(nomes, quantidades, totalProdutos);
                break;

            case 6: {
                float valorTotal;

                valorTotal = calcularValorTotalEstoque(precos, quantidades, totalProdutos);

                printf("\nValor total do estoque: R$ %.2f\n", valorTotal);
                break;
            }

            case 7:
                printf("\nPrograma encerrado!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 7);

    return 0;
}



void cadastrarProduto(char nomes[][50], float precos[], int quantidades[], int *total) {

    if (*total >= MAX_PRODUTOS) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    printf("\n========== CADASTRO DE PRODUTO ==========\n");

    printf("Nome do produto: ");
    scanf(" %49[^\n]", nomes[*total]);

    printf("Preco unitario: R$ ");
    scanf("%f", &precos[*total]);

    printf("Quantidade em estoque: ");
    scanf("%d", &quantidades[*total]);

    if (precos[*total] < 0 || quantidades[*total] < 0) {
        printf("\nPreco ou quantidade invalida! Cadastro cancelado.\n");
        return;
    }

    printf("\nProduto cadastrado com sucesso!\n");
    printf("Codigo do produto: %d\n", *total + 1);

    (*total)++;
}



void consultarEstoque(char nomes[][50], float precos[], int quantidades[], int total) {

    if (total == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n========== ESTOQUE ATUAL ==========\n");

    for (int i = 0; i < total; i++) {

        printf("\nCodigo: %d\n", i + 1);
        printf("Nome: %s\n", nomes[i]);
        printf("Preco: R$ %.2f\n", precos[i]);
        printf("Quantidade: %d unidades\n", quantidades[i]);

    }
}



void registrarVenda(char nomes[][50], float precos[], int quantidades[], int total) {

    int codigo;
    int quantidadeVendida;
    float valorVenda;

    if (total == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n========== REGISTRAR VENDA ==========\n");

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    if (codigo < 1 || codigo > total) {
        printf("\nCodigo de produto invalido!\n");
        return;
    }

    printf("Produto: %s\n", nomes[codigo - 1]);

    printf("Quantidade que deseja vender: ");
    scanf("%d", &quantidadeVendida);

    if (quantidadeVendida <= 0) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    if (quantidades[codigo - 1] >= quantidadeVendida) {

      
        quantidades[codigo - 1] -= quantidadeVendida;

       
        valorVenda = calcularFaturamento(precos[codigo - 1], quantidadeVendida);

        printf("\nVenda realizada com sucesso!\n");
        printf("Valor total da venda: R$ %.2f\n", valorVenda);

    } else {

        printf("\nEstoque insuficiente!\n");
        printf("Quantidade disponivel: %d\n", quantidades[codigo - 1]);

    }
}



void alertaReposicao(char nomes[][50], int quantidades[], int total) {

    int encontrou = 0;

    printf("\n========== PRODUTOS PARA REPOSICAO ==========\n");

    for (int i = 0; i < total; i++) {

        if (quantidades[i] < 5) {

            printf("\nProduto: %s\n", nomes[i]);
            printf("Quantidade atual: %d unidades\n", quantidades[i]);

            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("\nNenhum produto precisa de reposicao.\n");
    }
}



void entradaMercadorias(char nomes[][50], int quantidades[], int total) {

    int codigo;
    int quantidadeRecebida;

    if (total == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n========== ENTRADA DE MERCADORIAS ==========\n");

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    if (codigo < 1 || codigo > total) {
        printf("\nCodigo de produto invalido!\n");
        return;
    }

    printf("Produto: %s\n", nomes[codigo - 1]);

    printf("Quantidade recebida: ");
    scanf("%d", &quantidadeRecebida);

    if (quantidadeRecebida <= 0) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    
    quantidades[codigo - 1] += quantidadeRecebida;

    printf("\nEntrada registrada com sucesso!\n");
    printf("Nova quantidade em estoque: %d\n", quantidades[codigo - 1]);
}



float calcularFaturamento(float preco, int quantidade) {

    return preco * quantidade;

}


float calcularValorTotalEstoque(float precos[], int quantidades[], int total) {

    float valorTotal = 0;

    for (int i = 0; i < total; i++) {

        valorTotal += precos[i] * quantidades[i];

    }

    return valorTotal;
}