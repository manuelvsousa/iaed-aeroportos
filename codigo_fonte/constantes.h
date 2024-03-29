/*constantes*/
#define ADICIONA false
#define ENCERRA true
#define REABRE false
#define REMOVE true
#define IDA false
#define IDAEVOLTA true
#define MAXID 4
#define MAXAEROPORTOS 1001



/*structs utilizados pelo programa*/

//representacao dos aeroportos
typedef struct{
	char id[MAXID];
	int capacidade;
	bool estado;
	int crono;
	int conectados;
	int soma;
	int partem;
	int chegam;
} Aeroporto;

//representacao do histograma
typedef struct{
	int soma;
	int n;
} Histograma;

//representacao do voo mais popular
typedef struct{
	int voos;
	char partida[MAXID];
	int partida_crono;
	char chegada[MAXID];
	int chegada_crono;
} Voo;



/*funcoes_auxiliares.h*/
int OrdenaAeroportosNome(const void *a, const void *b);
int OrdenaAeroportosCronologicamente(const void *a, const void *b);
int OrdenaHistograma(const void *a, const void *b);
int PesquisaBinariaAeroportos (Aeroporto aeroportos[], char a_procurar[], int numero_aeroportos);
int PesquisaBinariaHistograma(Histograma hist[], int a_procurar, int n_hist);
void InsertionSortHistrograma(Histograma hist[], int n_hist);

/*funcoes_comandos.h*/
void CriaAeroporto(Aeroporto aeroportos[], int numero_aeroportos);
void AlteraCapacidadeAeroporto(Aeroporto aeroportos[], int numero_aeroportos);
void ImprimeAeroportos(Aeroporto aeroportos[],int numero_aeroportos);
void AdicionaRemoveVoo(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, bool ida_volta, bool remover, Voo popular[], long int total_voos[]);
void AdicionaRemove(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], bool remover, long int total_voos[], int index_1, int index_2);
void RemovePopular(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, Voo popular[], long int total_voos[]);
void RetornaVoo(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos);
void AeroportoPopular(Aeroporto aeroportos[], int numero_aeroportos);
void AeroportoConectado(Aeroporto aeroportos[], int numero_aeroportos);
void HistogramaImprime(Aeroporto aeroportos[], int numero_aeroportos);
void EncerraReabreAeroporto(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, long int total_voos[], bool encerra);