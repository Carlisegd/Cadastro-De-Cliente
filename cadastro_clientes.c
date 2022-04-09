#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define QTD_CARACTERES 30
#define QTD_CLIENTES 10
#define TAM_REALOC 10


struct cliente{
    char nome[QTD_CARACTERES];
    int ano_nasc;
    float gasto;
};

void menu(){
	
    printf("--->ESCOLHA UMA DAS OPÇÕES\n\n");
    printf("1. Listar clientes \n");
    printf("2. Inserir cliente \n");
    printf("3. Remover cliente \n");
    printf("4. Atualizar montante de cliente \n");
    printf("5. Zerar montantes \n");
    printf("6. Encontrar melhor comprador \n");
    printf("7. Exibir montante de um cliente \n");
    printf("8. Finalizar programa \n\n");
    printf("--->Digite a opção desejada: \n");
}


int cadastrar_cliente(struct cliente **clientes, int qtd_cadastros){

    if (qtd_cadastros != 0 && qtd_cadastros % QTD_CLIENTES == 0){
        *clientes = (struct cliente *) realloc(*clientes, (qtd_cadastros + TAM_REALOC) * sizeof(struct cliente));
    }

    char nome[QTD_CARACTERES];
    int ano_nasc;
    float gasto;

    printf("Informe o nome: \n");
    scanf("%s", &nome);
    printf("Informe o ano de nascimento: \n");
    scanf("%d", &ano_nasc);
    printf("Informe o montante gasto: \n");
    scanf("%f", &gasto);

    memcpy((*clientes)[qtd_cadastros].nome, nome, sizeof(nome));
    (*clientes)[qtd_cadastros].ano_nasc = ano_nasc;
    (*clientes)[qtd_cadastros].gasto = gasto;
}

void listar_clientes(struct cliente *clientes, int qtd_cadastros){

	int i;
    	for (i = 0; i < qtd_cadastros; i++ ){
		printf("Cliente %d \n", i);
		printf("Nome: %s \n", clientes[i].nome);
		printf("Ano nascimento: %d \n", clientes[i].ano_nasc);
		printf("Montante gasto: %f \n\n\n", clientes[i].gasto);
    }
}

int busca_por_nome(struct cliente *clientes, int qtd_cadastros){

    char nome[QTD_CARACTERES];

    printf("Informe o nome do cliente: \n");
    scanf("%s", &nome);

		int i;
    for (i = 0; i < qtd_cadastros; i++ ){
        if  (strcmp(clientes[i].nome, nome) == 0){
            return i;
        }
    }

    return -1;
}

int excluir_cliente(struct cliente *clientes, int qtd_cadastros){

    int pos_exclusao = busca_por_nome(clientes, qtd_cadastros);

    if (pos_exclusao == -1){
        return -1;
    }

	int i;
    	for (i = pos_exclusao; i < qtd_cadastros - 1; i++){
        memcpy(clientes[i].nome, clientes[i + 1].nome, sizeof(clientes[i + 1].nome));
        clientes[i].ano_nasc =  clientes[i + 1].ano_nasc;
        clientes[i].gasto =  clientes[i + 1].gasto;
    }

    return 1;
}


int atualizar_gasto(struct cliente *clientes, int qtd_cadastros){

    int pos_atualizacao = busca_por_nome(clientes, qtd_cadastros);
    float novo_gasto;

    if (pos_atualizacao == -1){
        return -1;
    }

    printf("Informe o novo montante gasto: \n");
    scanf("%f", &novo_gasto);

    clientes[pos_atualizacao].gasto =  novo_gasto;

    return 1;
}

void zerar_gastos(struct cliente *clientes, int qtd_cadastros){

	int i;
    	for (i = 0; i < qtd_cadastros; i++){
        clientes[i].gasto =  0.0;
    }
}

int encontrar_melhor_cliente(struct cliente *clientes, int qtd_cadastros){

    float maior_gasto = clientes[0].gasto;
    int pos_melhor_cliente = 0;

		int i;
    for (i = 1; i < qtd_cadastros; i++){
        if (clientes[i].gasto > maior_gasto){
            maior_gasto = clientes[i].gasto;
            pos_melhor_cliente = i;
        }
    }

    return pos_melhor_cliente;
}


int exibir_montante_cliente(struct cliente *clientes, int qtd_cadastros){

    int pos_gasto = busca_por_nome(clientes, qtd_cadastros);

    if (pos_gasto == -1){
        return -1;
    }

    printf("O montante gasto pelo cliente %s foi %f \n", clientes[pos_gasto].nome, clientes[pos_gasto].gasto);

    return 1;
}

int main(){
	setlocale(LC_ALL, "Portuguese");

    int opcao;
    int qtd_cadastros = 0;
    int verif_op;
    struct cliente *clientes;
    int pos_melhor_cliente;

    clientes = (struct cliente *) malloc(QTD_CLIENTES * sizeof(struct cliente));

    while (1){
        menu();
        scanf("%d", &opcao);

        if (opcao == 8){
            break;
        }else if (opcao > 8 || opcao < 1){
            printf("Opção não existente!");
        }else{
            if (opcao == 2){
                cadastrar_cliente(&clientes, qtd_cadastros);
                qtd_cadastros++;
            }else if (opcao == 1){
                listar_clientes(clientes, qtd_cadastros);
            }else if (opcao == 3){
                verif_op = excluir_cliente(clientes, qtd_cadastros);
                if (verif_op == -1){
                    printf("Erro na exclusão!");
                }else{
                    qtd_cadastros--;
                }
            }else if (opcao == 4){
                verif_op = atualizar_gasto(clientes, qtd_cadastros);
                if (verif_op == -1){
                    printf("Erro na atualização!");
                }
            }else if (opcao == 5){
                zerar_gastos(clientes, qtd_cadastros);
            }else if (opcao == 6){
                pos_melhor_cliente = encontrar_melhor_cliente(clientes, qtd_cadastros);
                printf("O melhor cliente é %s", clientes[pos_melhor_cliente].nome);
            }else if (opcao == 7){
                verif_op = exibir_montante_cliente(clientes, qtd_cadastros);
                if (verif_op == -1){
                    printf("Erro ao buscar cliente!");
                }
            }
        }
    }
}
