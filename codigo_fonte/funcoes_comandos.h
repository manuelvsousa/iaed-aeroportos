/******************************************************************************
* CriaAeroporto()
*
* Arguments:   	aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: 	void
* Description:  cria um novo aeroporto baseado numa string fornecida pelo utilizador e inicializa as variaveis do mesmo
*****************************************************************************/
void CriaAeroporto(Aeroporto aeroportos[], int numero_aeroportos){
	int cap;
	char str1_input[MAXID];
	Aeroporto aeroporto;
	
	scanf("%s %d", str1_input, &cap);
	
	aeroporto.capacidade = cap;
	aeroporto.estado = true;
	aeroporto.conectados = 0;
	aeroporto.soma = 0;
	aeroporto.partem = 0;
	aeroporto.chegam = 0;
	aeroporto.crono = numero_aeroportos;
	strcpy(aeroporto.id, str1_input);
	aeroportos[numero_aeroportos] = aeroporto;
}

/************************************************************************************************
* AlteraCapacidadeAeroporto()
*
* Arguments:   	aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: void
* Description:  altera a capacidade do aeroporto para um numero fornecido pelo utilizador
***********************************************************************************************/
void AlteraCapacidadeAeroporto(Aeroporto aeroportos[], int numero_aeroportos){
	int cap, index_1;
	char str1_input[MAXID];
	scanf("%s %d", str1_input, &cap);
	index_1 = PesquisaBinariaAeroportos(aeroportos, str1_input, numero_aeroportos);

	if(index_1 != -1 && aeroportos[index_1].soma <= (aeroportos[index_1].capacidade + cap) && aeroportos[index_1].estado)
		aeroportos[index_1].capacidade += cap;
	else
		printf("*Capacidade de %s inalterada\n",str1_input);
}

/**********************************************************************
* ImprimeAeroportos()
*
* Arguments:	aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: void
* Description:  imprime todos os aeroportos
**********************************************************************/
void ImprimeAeroportos(Aeroporto aeroportos[],int numero_aeroportos){
	int i;
	for (i = 0 ; i < numero_aeroportos; i++){
	  printf("%s:%d:%d:%d\n",aeroportos[i].id,aeroportos[i].capacidade,aeroportos[i].partem,aeroportos[i].chegam);
    }
}

/*****************************************************************************************************************
* AdicionaRemoveVoo()
*
* Arguments:   	grafo:   		matrix 2D que representa o grafo dos voos entre os diferentes aeroportos
*		aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*		ida_volta:		boolean (true se a operacao for de ida e volta, false se for so de ida)
*		remover:		boolean (true se o voo for removido, false se for adicionado)
*		popular:		variavel que guarda o aeroporto mais popular
*		total_voos:		variavel que guarda o numero total de voos
*
* Returns: void
* Description:  adiciona ou remove voos de ida e volta ou so de ida
*****************************************************************************************************************/
void AdicionaRemoveVoo(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, bool ida_volta, bool remover, Voo popular[], long int total_voos[])
{

	int index_1, index_2;
	char str1_input[MAXID], str2_input[MAXID];

	scanf("%s %s", str1_input, str2_input);
	index_1 = PesquisaBinariaAeroportos(aeroportos, str1_input, numero_aeroportos);
	index_2 = PesquisaBinariaAeroportos(aeroportos, str2_input, numero_aeroportos);

	//condicoes iniciais para aceitar um voo
	if (index_1 != -1 && index_2 != -1 && aeroportos[index_1].estado && aeroportos[index_2].estado){

		//se o voo for de ida
		if (!(ida_volta)){

			//se o voo for removido
			if (remover){

				//se o numero de voos for maior que 0
				if (grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] > 0){

					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_1, index_2);

					//Se os aeroportos deixarem de estar conectados
					if (grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] == 0 &&
					grafo[aeroportos[index_1].crono][aeroportos[index_2].crono] == 0){
						aeroportos[index_1].conectados -= 1;
						aeroportos[index_2].conectados -= 1;
					}
				} else {
					printf("*Impossivel remover voo %s %s\n", str1_input, str2_input);
				}

			//se o voo for adicionado
			} else {

				//se os aeroportos nao excederem a capacidade
				if (aeroportos[index_1].soma + 1 <= aeroportos[index_1].capacidade &&
				aeroportos[index_2].soma + 1 <= aeroportos[index_2].capacidade){

					//Se os aeroportos ainda nao estavam conectados
					if (grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] == 0 &&
					grafo[aeroportos[index_1].crono][aeroportos[index_2].crono] == 0){
						aeroportos[index_1].conectados += 1;
						aeroportos[index_2].conectados += 1;
					}

					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_1, index_2);

				} else {
					printf("*Impossivel adicionar voo %s %s\n", str1_input, str2_input);
				}
			}

		//se o voo for de ida e volta
		} else  {

			//se o voo for removido
			if (remover){

				//se houver pelo menos um voo de ida e volta no grafo
				if (grafo[aeroportos[index_1].crono][aeroportos[index_2].crono] > 0 &&
				grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] > 0){

					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_1, index_2);
					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_2, index_1);

					//Se os aeroportos deixarem de estar conectados
					if (grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] == 0 &&
					grafo[aeroportos[index_1].crono][aeroportos[index_2].crono] == 0){
						aeroportos[index_1].conectados -= 1;
						aeroportos[index_2].conectados -= 1;
					}
				} else {
					printf("*Impossivel remover voo RT %s %s\n", str1_input, str2_input);
				}

			//se o voo for adicionado
			} else {

				//se os aeroportos nao excederem a capacidade
				if (aeroportos[index_2].soma + 2 <= aeroportos[index_2].capacidade &&
				aeroportos[index_1].soma + 2 <= aeroportos[index_1].capacidade){

					//Se os aeroportos ainda nao estavam conectados
					if (grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] == 0 &&
					grafo[aeroportos[index_1].crono][aeroportos[index_2].crono] == 0){
						aeroportos[index_1].conectados += 1;
						aeroportos[index_2].conectados += 1;
					}

					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_1, index_2);
					AdicionaRemove(grafo, aeroportos, remover, total_voos, index_2, index_1);

				} else {
					printf("*Impossivel adicionar voo RT %s %s\n", str1_input, str2_input);
				}
			}
		}

	//se as condicoes iniciais nao se verificarem
	} else {
		if (remover){
			if (ida_volta)
				printf("*Impossivel remover voo RT %s %s\n", str1_input, str2_input);
			else
				printf("*Impossivel remover voo %s %s\n", str1_input, str2_input);
		} else {
			if (ida_volta)
				printf("*Impossivel adicionar voo RT %s %s\n", str1_input, str2_input);
			else
				printf("*Impossivel adicionar voo %s %s\n", str1_input, str2_input);
		}
	}
}

/******************************************************************************************
* AdicionaRemove()
*
* Arguments:	grafo:   		matrix 2D que representa o grafo dos voos entre os diferentes aeroportos
*		aeroportos:   		vetor que contem todos os aeroportos
*		remover:		boolean (true se o voo for removido, false se for adicionado)
*		total_voos:		variavel que guarda o numero total de voos
*		index_1:		indice do aeroporto de partida
*		index_2:		indice do aeroporto de chegada
*
* Returns: void
* Description:  adiciona ou remove um voo de ida (funcao auxiliar de AdicionaRemoveVoo())
******************************************************************************************/
void AdicionaRemove(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], bool remover, long int total_voos[], int index_1, int index_2){
	int num;

	if (remover)
		num = -1;
	else
		num = 1;

	grafo[aeroportos[index_2].crono][aeroportos[index_1].crono] += num;
	aeroportos[index_1].partem += num;
	aeroportos[index_1].soma += num;
	aeroportos[index_2].chegam += num;
	aeroportos[index_2].soma += num;
	total_voos[0] += num;
}

/**************************************************************************************************************
* VerificaPopular()
*
* Arguments:   	grafo:   			matrix 2D que representa o grafo dos voos entre os diferentes aeroportos
*		aeroportos:   			vetor que contem todos os aeroportos87450ab
*              	numero_aeroportos:  		numero de aeroportos atuais
*		popular:			variavel que guarda o aeroporto mais popular
*		total_voos:			variavel que guarda o numero total de voos
*
* Returns: void
* Description:  procura e imprime o voo mais popular
**************************************************************************************************************/
void VerificaPopular(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, Voo popular[], long int total_voos[]){
	int i, j, maior = -1, maior_i = -1, maior_j = -1, maior_partida_crono = 1000, maior_chegada_crono = 1000;

	//ciclo que procura o voo mais popular
	for (i = 0; i < numero_aeroportos; i++){
		for (j = 0; j < numero_aeroportos; j++){
			if (grafo[j][i] > maior){
				maior_i = i;
				maior_j = j;
				maior = grafo[j][i];
				maior_partida_crono = aeroportos[maior_i].crono;
				maior_chegada_crono = aeroportos[maior_j].crono;
			}
		}
	}

	int t, indice_1 = 0, indice_2 = 0;

	//procura o aeroporto certo a partir do indice obtido
	for (t = 0; t < numero_aeroportos; t++){
		if (aeroportos[t].crono == maior_i)
			indice_1 = t;
		else if (aeroportos[t].crono == maior_j)
			indice_2 = t;
	}

	popular[0].voos = maior;
	strcpy(popular[0].partida, aeroportos[indice_1].id);
	popular[0].partida_crono = maior_partida_crono;
	strcpy(popular[0].chegada, aeroportos[indice_2].id);
	popular[0].chegada_crono = maior_chegada_crono;

	printf("Voo mais popular %s:%s:%d\n", popular[0].partida, popular[0].chegada, popular[0].voos);
}

/******************************************************************************************
* RetornaVoo()
*
* Arguments:   	grafo:   		matrix 2D que representa o grafo dos voos entre os diferentes aeroportos
*		aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: void
* Description:  imprime o numero de voos entre dois aeroportos indicados pelo utilizador
*****************************************************************************************/
void RetornaVoo(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos){
	int index_1, index_2;
	char str1_input[MAXID], str2_input[MAXID];

	scanf("%s %s", str1_input, str2_input);
	index_1 = PesquisaBinariaAeroportos(aeroportos, str1_input, numero_aeroportos);
	index_2 = PesquisaBinariaAeroportos(aeroportos, str2_input, numero_aeroportos);

	if (index_1 == -1)
		printf("*Aeroporto %s inexistente", str1_input);

	if (index_2 == -1)
		printf("*Aeroporto %s inexistente", str2_input);

	if (index_1 != -1 && index_2 != -1)
		printf("Voos entre cidades %s:%s:%d:%d\n", str1_input, str2_input, grafo[aeroportos[index_2].crono][aeroportos[index_1].crono], grafo[aeroportos[index_1].crono][aeroportos[index_2].crono]);
}

/******************************************************************************************
* AeroportoPopular()
*
* Arguments:	aeroportos:   		vetor que contem todos os aeroportos
*              	numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: void
* Description:  imprime o aeroporto com mais voos a sair e a entrar
*****************************************************************************************/
void AeroportoPopular(Aeroporto aeroportos[], int numero_aeroportos){
	int i, maior = (aeroportos[0].soma), indice = 0;

	for (i = 1; i < numero_aeroportos; i++){
		if (maior < (aeroportos[i].soma)){
			maior = (aeroportos[i].soma);
			indice = i;
		}
		else if (maior == aeroportos[i].soma && aeroportos[i].crono < aeroportos[indice].crono){
			maior = (aeroportos[i].soma);
			indice = i;
		}
	}

	printf("Aeroporto com mais rotas %s:%d:%d\n", aeroportos[indice].id, aeroportos[indice].partem, aeroportos[indice].chegam);
}

/****************************************************************************
* AeroportoConectado()
*
* Arguments:	aeroportos:   		vetor que contem todos os aeroportos
* 		numero_aeroportos:	numero de aeroportos atuais
*
* Returns: void
* Description:  imprime o aeroporto com mais conexoes entre ele e outros aeroportos
****************************************************************************/
void AeroportoConectado(Aeroporto aeroportos[], int numero_aeroportos){
	int i, maior = 0, indice = 0;

	for (i = 0; i < numero_aeroportos; i++){
		if (maior < (aeroportos[i].conectados)){
			maior = (aeroportos[i].conectados);
			indice = i;
		}
		else if (maior == (aeroportos[i].conectados)){
			if (aeroportos[i].crono < aeroportos[indice].crono){
				maior = (aeroportos[i].conectados);
				indice = i;
			}
		}
	}

	printf("Aeroporto com mais ligacoes %s:%d\n", aeroportos[indice].id, maior);
}

/******************************************************************************************
* HistogramaImprime()
*
* Arguments:	aeroportos:   		vetor que contem todos os aeroportos
*		numero_aeroportos:  	numero de aeroportos atuais
*
* Returns: void
* Description:  imprime histograma ordenado composto pelo N aeroportos com X total de voos (de cada aeroporto) diferentes
*****************************************************************************************/
void HistogramaImprime(Aeroporto aeroportos[], int numero_aeroportos){
    Histograma hist[MAXAEROPORTOS];
    int index, i;
    int n_hist = 1;

    hist[0].soma = aeroportos[0].soma;
    hist[0].n = 1;

    for (i = 1; i < numero_aeroportos; i++){

    	    //Nao e usado qsort() porque e menos eficiente a ordenar vetores ja pre-ordenados
    	    InsertionSortHistrograma(hist, n_hist); 
            index = PesquisaBinariaHistograma(hist, aeroportos[i].soma, n_hist);
            if(index == -1){
                hist[n_hist].soma = aeroportos[i].soma;
                hist[n_hist].n = 1;
                n_hist++;
            }
            else
                hist[index].n++;
    }
    InsertionSortHistrograma(hist , n_hist);

    for(i = 0; i < n_hist; i++)
        printf("%d:%d\n", hist[i].soma, hist[i].n);
}

/******************************************************************************************
* EncerraReabreAeroporto()
*
* Arguments:	grafo:   			matrix 2D que representa o grafo dos voos entre os diferentes aeroportos
* 		aeroportos:   			vetor que contem todos os aeroportos
*		numero_aeroportos:  		numero de aeroportos atuais
*		total_voos:			variavel que guarda o numero total de voos
*		encerra:			bool (true se encerra, false se reabre)
*
* Returns: void
* Description:  reabre ou encerra o aeroporto e apaga os voos e informacoes derivadas no segundo caso
*****************************************************************************************/
void EncerraReabreAeroporto(int grafo[][MAXAEROPORTOS], Aeroporto aeroportos[], int numero_aeroportos, long int total_voos[], bool encerra){
    char str1_input[MAXID];
    int index, i;

    scanf("%s", str1_input);
    index = PesquisaBinariaAeroportos(aeroportos, str1_input, numero_aeroportos);
    
    if(encerra && index!=-1){
        aeroportos[index].estado = false;
        aeroportos[index].partem = 0;
        aeroportos[index].chegam = 0;
        aeroportos[index].soma = 0;
        aeroportos[index].conectados = 0;

    	for (i = 0; i < numero_aeroportos; i++){
    		//apaga os voos que partem do aeroporto
    		if (grafo[aeroportos[i].crono][aeroportos[index].crono] != 0){
    			if (grafo[aeroportos[index].crono][aeroportos[i].crono] == 0)
    				aeroportos[i].conectados -= 1;
    			total_voos[0] -= grafo[aeroportos[i].crono][aeroportos[index].crono];
    			aeroportos[i].chegam -= grafo[aeroportos[i].crono][aeroportos[index].crono];
    			aeroportos[i].soma -= grafo[aeroportos[i].crono][aeroportos[index].crono];
    			grafo[aeroportos[i].crono][aeroportos[index].crono] = 0;
    		}
    		//apaga os voos que chegam ao aeroporto
    		if (grafo[aeroportos[index].crono][aeroportos[i].crono] != 0){
    			if (grafo[aeroportos[i].crono][aeroportos[index].crono] == 0)
    				aeroportos[i].conectados -= 1;
    			total_voos[0] -= grafo[aeroportos[index].crono][aeroportos[i].crono];
    			aeroportos[i].partem -= grafo[aeroportos[index].crono][aeroportos[i].crono];
    			aeroportos[i].soma -= grafo[aeroportos[index].crono][aeroportos[i].crono];
    			grafo[aeroportos[index].crono][aeroportos[i].crono] = 0;
    		}
    	}
    }
    else if(!(encerra) && index != -1)
        aeroportos[index].estado = true;
    else
        printf("*Aeroporto %s inexistente\n", str1_input);
}
