#define MAXAEROPORTOID 4
#define MAXAEROPORTOS 1001
#define COMANDOS "AIFGRSNPQVCOLX"


typedef struct{
	char id[4];
	long int capacidade;
	bool estado;
	short int crono;
} Aeroporto;

