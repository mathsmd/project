#include<iostream>
using namespace std;


struct Card {

    string nome;
    int nivel;
    string tipo;
    int ATK;
    int DEF;

};

struct NoPilha{

    Card * carta;
    NoPilha * abaixo;

};

struct NoFila {

    int quant_cartas;
    NoPilha * pilha_cartas;
    NoFila * prox;
    NoFila * ant;

};

struct Descritor{

    int tam;
    NoFila * ini;
    NoFila * fim;

};


Descritor * criar_descritor();
NoFila * add_deck(Descritor * Des);
void remove_deck(Descritor * Des, NoFila * &deck_atual);
NoFila * escolher_deck(Descritor * Des);
void add_carta(Descritor * Des, NoFila * deck_atual);
void remove_carta(Descritor * Des, NoFila * deck_atual);
void imprimir_cartas(Descritor * Des, NoFila * deck_atual);
void filtrar_cartas(Descritor * Des, NoFila * deck_atual);
void contador_de_vida_recursivo(int PV, int TURNO);



int main(){

    Descritor * Des = criar_descritor();

    NoFila * deck_atual = add_deck(Des);

    int tarefa;
    
    do{
        cout << " 1. Adicionar deck (ao fim da fila);\n 2. Remover deck (primeiro da fila);\n 3. Escolher um deck;\n 4. Adicionar carta (ao topo da pilha);\n 5. Remover carta (do topo da pilha);\n 6. Imprimir cartas do deck atual;\n 7. Filtrar cartas do deck atual;\n 8. Contador de Pontos de Vida\n 9. Encerrar programa;\n";
        cout << endl << "COMANDO:  ";
        cin >> tarefa;
        
        switch (tarefa){
            case 1:
                system("cls");
                deck_atual = add_deck(Des);
                break;
            case 2:
                system("cls");
                remove_deck(Des, deck_atual);
                break;
            case 3:
                system("cls");
                deck_atual = escolher_deck(Des);
                break;
            case 4:
                system("cls");
                add_carta(Des, deck_atual);
                break;
            case 5:
                system("cls");
                remove_carta(Des, deck_atual);
                break;
            case 6:
                system("cls");
                imprimir_cartas(Des, deck_atual);
                break;
            case 7:
                system("cls");
                filtrar_cartas(Des, deck_atual);
                break;
            case 8:
                system("cls");
                cout << "Pontos de vida Positivos representam Cura e Negativos Dano" << endl;
                cout << "O jogo acaba quando seus Pontos de vida chegarem a 0 ou menos." << endl << endl;
                contador_de_vida_recursivo(8000, 1);
                cout << "\nFIM DE JOGO\n" << endl;
                system("pause");
                system("cls");
                break;
            case 9:
                cout << "\nFIM DO PROGRAMA\n" << endl;
                break;
            default:
                cout << "\nCOMANDO INAVALIDO!\n" << endl;
                break;
        }
    }while(tarefa != 9);
    
    system("pause");
    return 0;
}



Descritor * criar_descritor(){

    Descritor * Des = new Descritor;
    Des->tam = 0;
    Des->ini = NULL;
    Des->fim = NULL;

    return Des;

}



NoFila * add_deck(Descritor * Des){

    NoFila * novo_deck = new NoFila;
    novo_deck->quant_cartas = 0;
    novo_deck->pilha_cartas = NULL;
    novo_deck->prox = NULL;
    novo_deck->ant = NULL;

    Des->tam++;

    if (Des->ini == NULL){
        Des->ini = novo_deck;
        Des->fim = novo_deck;
    }
    else{
        Des->fim->prox = novo_deck;
        novo_deck->ant = Des->fim;
        Des->fim = novo_deck;
    }

    cout << "DECK " << Des->tam << " CRIADO COM SUCESSO." << endl << endl;
    cout << "VOCE ESTA EDITANDO O DECK " << Des->tam << endl << endl;

    return novo_deck;

}



void remove_deck(Descritor * Des, NoFila * &deck_atual){

    if (Des->ini == NULL){
        cout << "NAO HA DECKS PARA REMOVER!!" << endl << endl;
    }
    else{
        Des->tam--;
        cout << "DECK EXCLUIDO COM SUCESSO." << endl << endl;

        if (Des->ini == Des->fim){
            Des->ini = NULL;
            Des->fim = NULL;
        }
        else{
            if (deck_atual = Des->ini){
                deck_atual = deck_atual->prox;
                cout << "VOCE EXCLUIU O DECK QUE ESTAVA EDITANDO E FOI JOGADO PARA O PROXIMO" << endl << endl;
            }
            Des->ini->prox->ant = NULL;
            Des->ini = Des->ini->prox;
            Des->ini->ant = NULL;
        }
        cout << "Numero de decks restantes: " << Des->tam << endl << endl;
    }
}



NoFila * escolher_deck(Descritor * Des){

    if (Des->tam <= 0){
        cout << "NAO HA DECKS PARA ESCOLHER!!" << endl << endl;
        return NULL;
    }
    else{
        NoFila * deck_escolhido = Des->ini;
        int num;

        do{
            cout << "Escolha um deck de 1 a " << Des->tam << ": ";
            cin >> num;
        }while(num < 1 or num > Des->tam);

        for (int i = 1; i < num; i++){
            deck_escolhido = deck_escolhido->prox;
        }

        cout << "VOCE ESTA EDITANDO O DECK " << num << endl << endl;

        return deck_escolhido;
    }
}



void add_carta(Descritor * Des, NoFila * deck_atual){

    if (Des->ini == NULL){
        cout << "ADICIONE UM DECK PRIMEIRO!!" << endl << endl;
    }
    else{
        if(deck_atual->quant_cartas < 60){
            char continuar;

            do{
                NoPilha * nova_pilha = new NoPilha;
                nova_pilha->abaixo = deck_atual->pilha_cartas;
                deck_atual->pilha_cartas = nova_pilha;

                Card * nova_carta = new Card;
                deck_atual->pilha_cartas->carta = nova_carta;
                deck_atual->quant_cartas++;


                cout << "Carta N. " << deck_atual->quant_cartas << ": \n" << endl;
                cout << "Nome da carta: ";
                cin >> nova_carta->nome;
                cout << "Nivel da carta: ";
                cin >> nova_carta->nivel;
                cout << "Tipo da carta: ";
                cin >> nova_carta->tipo;
                cout << "Ataque da carta: ";
                cin >> nova_carta->ATK;
                cout << "Defesa da carta: ";
                cin >> nova_carta->DEF;

                cout << endl << "-------------------------" << endl << endl;
                cout << "Adicionar outro Card? (y/n): ";
                cin >> continuar;
                cout << endl << "-------------------------" << endl << endl;

            }while(continuar == 'y' && deck_atual->quant_cartas < 60);

        }
        if(deck_atual->quant_cartas >= 60){
            cout << "O DECK ATUAL JA CHEGOU AO SEU LIMITE" << endl;
        }
    }
    
}



void remove_carta(Descritor * Des, NoFila * deck_atual){

    if (Des->ini == NULL){
        cout << "ADICIONE UM DECK PRIMEIRO!!" << endl << endl;
    }
    else{

        if(deck_atual->quant_cartas > 0){
            char continuar;

            do{
                cout << deck_atual->pilha_cartas->carta->nome << " FOI REMOVIDO(A)." << endl;

                deck_atual->pilha_cartas = deck_atual->pilha_cartas->abaixo;
                deck_atual->quant_cartas--;

                cout << endl << "Numero de cartas restantes nesse deck: " << deck_atual->quant_cartas << endl;

                cout << endl << "-------------------------" << endl << endl;
                cout << "Remover outra Card? (y/n): ";
                cin >> continuar;
                cout << endl << "-------------------------" << endl << endl;

            }while(continuar == 'y' && deck_atual->quant_cartas > 0);

        }
        if(deck_atual->quant_cartas <= 0){
            cout << "O DECK ATUAL NAO TEM MAIS CARTAS" << endl;
        }
    }
}



void imprimir_cartas(Descritor * Des, NoFila * deck_atual){

    if (Des->ini == NULL){
        cout << "ADICIONE UM DECK PRIMEIRO!!" << endl << endl;
    }
    else if(deck_atual->quant_cartas <= 0){
        cout << "ADICIONE UM CARD PRIMEIRO!!" << endl << endl;
    }
    else{
        NoPilha * P = deck_atual->pilha_cartas;
        int QC = deck_atual->quant_cartas;

        for (int i=0; i<QC; i++){
            cout << "Nome da carta " << QC-i << ": " << P->carta->nome << endl;
            cout << "Nivel da carta " << QC-i << ": " << P->carta->nivel << endl;
            cout << "Tipo da carta " << QC-i << ": " << P->carta->tipo << endl;
            cout << "Ataque da carta " << QC-i << ": " << P->carta->ATK << endl;
            cout << "Defesa da carta " << QC-i << ": " << P->carta->DEF << endl;
            cout << endl << "-------------------------" << endl << endl;

            P = P->abaixo;
        }
    }
}



void filtrar_cartas(Descritor * Des, NoFila * deck_atual){

    string tipo_de_monstro;
    char continuar;
    int status, X, Y;

    if (Des->ini == NULL){
        cout << "ADICIONE UM DECK PRIMEIRO!!" << endl << endl;
    }
    else if (deck_atual->quant_cartas <= 0){
        cout << "ADICIONE UM CARD PRIMEIRO!!" << endl << endl;
    }
    else{
        do{
            NoPilha * P = deck_atual->pilha_cartas;

            cout << "Selecione um STATUS para filtrar:" << endl;
            cout << endl << " 1. NIVEL do card.\n 2. TIPO do card.\n 3. ATK do card.\n 4. DEF do card.\n" << endl;
            cout << "  COMANDO: ";
            cin >> status;

        switch (status){
            case 1:
                cout << endl << "Insira nivel de X a Y para a busca: "  << endl;
                cout << "X = ";
                cin >> X;
                cout << "Y = ";
                cin >> Y;

                for (int i=0; i<deck_atual->quant_cartas; i++){
                    if (P->carta->nivel >= X && P->carta->nivel <= Y){
                        cout << endl << P->carta->nome << ": LVL " << P->carta->nivel << endl;
                    }
                    P = P->abaixo;
                }
                break;
        
            case 2:
                cout << endl << "Insira um tipo de monstro para a busca: "  << endl;
                cout << "TIPO = ";
                cin >> tipo_de_monstro;

                for (int i=0; i<deck_atual->quant_cartas; i++){
                    if (P->carta->tipo == tipo_de_monstro){
                        cout << endl << P->carta->nome << ": TIPO " << P->carta->tipo << endl;
                    }
                    P = P->abaixo;
                }
                break;
            
            case 3:
                cout << endl << "Insira ATK de X a Y para a busca: "  << endl;
                cout << "X = ";
                cin >> X;
                cout << "Y = ";
                cin >> Y;

                for (int i=0; i<deck_atual->quant_cartas; i++){
                    if (P->carta->ATK >= X && P->carta->ATK <= Y){
                        cout << endl << P->carta->nome << ": ATK " << P->carta->ATK << endl;
                    }
                    P = P->abaixo;
                }
                break;
            
            case 4:
                cout << endl << "Insira DEF de X a Y para a busca: "  << endl;
                cout << "X = ";
                cin >> X;
                cout << "Y = ";
                cin >> Y;

                for (int i=0; i<deck_atual->quant_cartas; i++){
                    if (P->carta->DEF >= X && P->carta->DEF <= Y){
                        cout << endl << P->carta->nome << ": DEF " << P->carta->DEF << endl;
                    }
                    P = P->abaixo;
                }
                break;
            
            default:
                cout << endl << "INVALIDO!" << endl;
                break;
            }

        cout << endl << "-------------------------" << endl << endl;
        cout << "Continuar filtrando Cards? (y/n): ";
        cin >> continuar;
        cout << endl << "-------------------------" << endl << endl;
        system("cls");

        }while(continuar == 'y');
    }
}


void contador_de_vida_recursivo(int PV, int TURNO){

    cout << "TURNO " << TURNO << endl;
    cout << "Seus Pontos de Vida atuais sao: " << PV << endl << endl;
    if (PV > 0){
        TURNO++;
        int aux;
        cout << "Insira os Pontos de Vida ganhos ou perdidos neste turno: ";
        cin >> aux;
        system("cls");
        contador_de_vida_recursivo(PV+aux, TURNO);
    }
}
