#include <iostream>
using namespace std;

const int MAX_VERTICES = 100;

struct Grafo {
    int num_vertices; 
    int num_arestas; 
    int vertices[MAX_VERTICES]; 
    int matriz_adjacencia[MAX_VERTICES][MAX_VERTICES]; 
    bool direcionado; 
};

void ler_grafo(Grafo &g);
void imprimir_matriz(Grafo &g);
bool verificar_completo(Grafo &g);
bool verificar_multigrafo(Grafo &g);
int contar_lacos(Grafo &g);
int vertices_folhas(Grafo &g);
bool verificar_vertice_isolado(Grafo &g);


void ler_grafo(Grafo &g) {
    cout << "O grafo e direcionado? (0 para nao, 1 para sim): ";
    cin >> g.direcionado;

    cout << "Digite o numero de vertices: ";
    cin >> g.num_vertices;

    cout << "Digite o numero de arestas: ";
    cin >> g.num_arestas;

    for (int i = 0; i < g.num_vertices; ++i) {
        cout << "Digite o vertice " << i + 1 << ": ";
        cin >> g.vertices[i];
    }

    for (int i = 0; i < g.num_vertices; ++i) {
        for (int j = 0; j < g.num_vertices; ++j) {
            g.matriz_adjacencia[i][j] = 0;
        }
    }

    for (int i = 0; i < g.num_arestas; ++i) {
        int origem, destino;
        cout << "Digite a aresta " << i + 1 << " (origem e o destino): ";
        cin >> origem >> destino;

        if (origem >= 0 && origem < g.num_vertices && destino >= 0 && destino < g.num_vertices) {
            g.matriz_adjacencia[origem][destino] = 1; 
            if (!g.direcionado) {
                g.matriz_adjacencia[destino][origem] = 1; 
            }
        } else {
            cout << "Vertices invalidos. Tente novamente." << endl;
            i--;
        }
    }
}

void imprimir_matriz(Grafo &g) {
    cout << "Matriz de adjacencia:" << endl;
    for (int i = 0; i < g.num_vertices; ++i) {
        for (int j = 0; j < g.num_vertices; ++j) {
            cout << g.matriz_adjacencia[i][j] << " ";
        }
        cout << endl;
    }
}

bool verificar_completo(Grafo &g) {
    for (int i = 0; i < g.num_vertices; ++i) {
        for (int j = 0; j < g.num_vertices; ++j) {
            if (i != j && g.matriz_adjacencia[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

bool verificar_multigrafo(Grafo &g) {
    for (int i = 0; i < g.num_vertices; ++i) {
        for (int j = 0; j < g.num_vertices; ++j) {
            if (i != j && g.matriz_adjacencia[i][j] > 1) {
                return true; 
            }
        }
    }
    return false;
}

int contar_lacos(Grafo &g) {
    int count = 0;
    for (int i = 0; i < g.num_vertices; ++i) {
        if (g.matriz_adjacencia[i][i] > 0) {
            count += g.matriz_adjacencia[i][i];
        }
    }
    return count;
}

int vertices_folhas(Grafo &g) {
    int count2 = 0;

    for (int i = 0; i < g.num_vertices; ++i) {
        int grau = 0;

        for (int j = 0; j < g.num_vertices; ++j) {
            grau += g.matriz_adjacencia[i][j];
        }
        if (grau == 1) {
            count2++;
        }
    }
    return count2;
}

bool verificar_vertice_isolado(Grafo &g) {
    for (int i = 0; i < g.num_vertices; ++i) {
        bool verticeIsolado = true;

        for (int j = 0; j < g.num_vertices; ++j) {
            if (g.matriz_adjacencia[i][j] == 1 || g.matriz_adjacencia[j][i] == 1) {
                verticeIsolado = false;
                break;
            }
        }
        if (verticeIsolado) {
            return true;
        }
    }
    return false;
}

bool verificar_planar(Grafo&g){
    if(g.num_arestas <= (3*g.num_vertices) - 6)
        return true;
    else
        return false;
    
}


int main() {
    Grafo g;
    ler_grafo(g);
    imprimir_matriz(g); 
    int stop = 0;  

    while(stop == 0){
        cout << " 1. Verificar completo;\n 2. Verificar multigrafo;\n 3. Contar lacos;\n 4. Verificar vertices folhas;\n 5. Verificar vertices isolados;\n 6. Verificar planar;\n 7. Sair\n";
        cin>>stop;
        switch(stop){
            case 1:
                bool completo;
                completo = verificar_completo(g);
                if(completo == 1)
                    cout<<"O grafo eh completo"<<endl;
                else
                    cout<<"O grafo nao eh completo"<<endl;
                stop = 0;
                break;
            case 2:
                bool mult;
                mult = verificar_multigrafo(g);
                if(mult == false)
                    cout << "Eh multigrafo" << endl;
                else
                    cout<<"Nao eh multigrafo"<<endl;
                stop = 0;
                break;
            case 3:
                int l;
                l = contar_lacos(g);
                if(l != 0)
                    cout<<"O grafo tem "<<l<<" lacos"<<endl;
                else
                    cout<<"O grafo nao tem lacos."<<endl;
                stop = 0;
                break;
            case 4:
                int v;
                v = vertices_folhas(g);
                if(v != 0)
                    cout<<"O grafo tem "<<v<<" vertices folhas."<<endl;
                else
                    cout<<"O grafo nao tem vertices folhas."<<endl;
                stop = 0;
                break;
            case 5:
                bool vI;
                vI =verificar_vertice_isolado(g);
                if(vI == 1)
                    cout<<"O grafo tem vertices isolados"<<endl;
                else
                    cout<<"O grafo nao tem vertices isolados"<<endl;
                stop = 0;
                break;
            case 6:
                bool pl;
                pl = verificar_planar(g);
                if(pl == 1)
                    cout<<"Eh possivel ser planar"<<endl;
                else
                    cout<<"Nao eh possivel ser planar."<<endl;
                stop = 0;
                break;
            case 7:
                cout<<"Fim do Progaminha."<<endl;
                break;
            default:
                cout<<"INVALIDO";
                stop = 0;

        }
    }
    return 0;
}
