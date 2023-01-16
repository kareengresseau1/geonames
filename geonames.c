
//  Kareen Gresseau
//  GREK03569800
//  TP1 : geonames
//  but: afficher les villes les plus populees
//  selon la base de donnes geonames
 
#define USAGE "\
Usage: %s  <NUMBER OF CITIES>\n\
\n\
Display a table of the n most populous cities on stdout. The number of cities must not exceed 5000.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Program parameters :\n\
  NUMBER of cities         Number de cities to print (1..500)\n\
  "
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FORMAT_TITRE    "%4s   %-20.20s   %-20.20s   %s\n"
#define FORMAT_COLONNES "%4d   %-20.20s   %-20.20s   %10ld\n"

enum error {
	OK			= 0,
	ERREUR_NB_ARGS		= 1,
	ERREUR_NB_VILLES	= 2,
	ERREUR_ARGS_TYPE	= 3,
	ERREUR_FICHIER		= 4
};

struct VILLE {
	char nomVille[100];
	long int population;
	char nomPays[100];
};

struct PAYS {
	char codeASCII[2];
	char pays[100];
}; 

//Cette methode me sert a comparer le code ASCII en parametre avec les codes ASCII dans mon tableau de structure
//PAYS. Quand on trouve un code ASCII qui est pareil a celui en parametre, on peut aller cercher le pays correspondant

int trouverPaysDansListe(char code[20], struct PAYS LESPAYS[253]){
	int index = 0;
	int estPareil = 0;
	char codeA[2];
	do{
		strncat(codeA, LESPAYS[index].codeASCII, 2);
		if(strcmp(code, codeA) == 0){
			estPareil = 1;
		}
		else {
			index ++;
		}
		strcpy(codeA, "");
	}while((estPareil != 1) && index < 253);
	return index;
} 

int main(int argc, char *argv[]){
	int argument;
	int nbrVillesMax = 5000;

	int estUnNombre = 1;
	int *pointeurEstUnNombre = &estUnNombre;

	int index = 0;
	int *pointeurIndex = &index;

	long int nbrCasesOccupees = 0;
	long int *pointeurCases = &nbrCasesOccupees;

	int i = 0;
	int *pointeurI = &i;

	int estPlusGrand = 0;
	int *pointeurPlusGrand = &estPlusGrand;
	
	int tabulations = 0;

	int localisation = 0; 

	int populationTemporaire = 0;	

	char ligne[10000] = {'\0'};
	char *pointeurLigne = &ligne[1000];	
	
	char *separation; 

	FILE *cities15000;
	cities15000 = fopen("cities15000.txt", "r");

	FILE *countryInfo;
	countryInfo = fopen("countryInfo.txt", "r"); 
	
	//validation de l'argument
	if(argc != 2){
		fprintf(stderr, "nombre arguments invalide\n");
		fprintf(stderr, "Usage: ./geonames <NUMBER OF CITIES>");
		return ERREUR_NB_ARGS;
	} 

	for(int i = 0; i < strlen(argv[1]); i++){
		if((argv[1][i] > 47) && (argv[1][i] < 58)){
			*pointeurEstUnNombre = *pointeurEstUnNombre * 1;
		} else {
			*pointeurEstUnNombre = *pointeurEstUnNombre * 0;
		}
	}

	if(*pointeurEstUnNombre == 0){
		fprintf(stderr, "type argument invalide\n");
		fprintf(stderr, USAGE,argv[0]);
		return ERREUR_ARGS_TYPE;
	}

	argument = atoi(argv[1]);

	if((argument > nbrVillesMax)^(argument < 1)){
		fprintf(stderr, "nombre de ville invalide\n");
		fprintf(stderr, USAGE,argv[0]);
		return ERREUR_NB_VILLES;
	}

	if((cities15000 == NULL) || (countryInfo == NULL)){
		fprintf(stderr, "Fichier inexistant");
		fprintf(stderr, USAGE,argv[0]);
		return ERREUR_FICHIER;
	}
	
	//creation des structures
	struct VILLE VILLETAMPON;
	struct VILLE *POINTEURVILLETAMPON = &VILLETAMPON;

	struct VILLE LESVILLES[argument];
	struct VILLE *POINTEURLESVILLES = &LESVILLES[argument]; 

	struct PAYS LESPAYS[253];
	struct PAYS *POINTEURLESPAYS = &LESPAYS[253];

	//chercher les codes ASCI dans le fichier countryInfo.txt 
	
	do{
		fgets(ligne, 1000, countryInfo);
		if(ligne[0] != '#'){
			separation = strtok(ligne, "\t");
			while((separation != NULL) && tabulations < 1){
				if(tabulations == 0){
					strcpy(LESPAYS[index].codeASCII, separation);
				}
				tabulations += 1;
				separation = strtok(NULL, "\t");
			}
			index += 1;
		}
		tabulations = 0;
		strcpy(ligne, "");
	}while(!feof(countryInfo));

	rewind(countryInfo);
	index = 0;
	tabulations = 0; 

	//chercher les pays dans le fichier countryInfo.txt

	do{
		fgets(ligne, 1000, countryInfo);
		if(ligne[0] != '#'){
			separation = strtok(ligne, "\t");
			while((separation != NULL) && (tabulations < 5)){
				if(tabulations == 4){
					strcpy(LESPAYS[index].pays, separation);
				}
				tabulations += 1;
				separation = strtok(NULL, "\t");
			}
			index += 1;
		}
		tabulations = 0;
		strcpy(ligne, "");
	}while(!feof(countryInfo)); 
	

	//Chercher les noms, les populations et pays de chaque ville
	
	tabulations = 0;
	index = 0;

	do{
		fgets(ligne, 10000, cities15000);
		separation = strtok(ligne, "\t");
		char tableau[16][500] = {'\0'};
		char *pointeurTableau[16];

		pointeurTableau[0] = &tableau[0][0];
		pointeurTableau[1] = &tableau[1][0];
		pointeurTableau[2] = &tableau[2][0];
		pointeurTableau[3] = &tableau[3][0];
		pointeurTableau[4] = &tableau[4][0];
		pointeurTableau[5] = &tableau[5][0];
                pointeurTableau[6] = &tableau[6][0];
                pointeurTableau[7] = &tableau[7][0];
                pointeurTableau[8] = &tableau[8][0];
                pointeurTableau[9] = &tableau[9][0];
		pointeurTableau[10] = &tableau[10][0];
                pointeurTableau[11] = &tableau[11][0];
                pointeurTableau[12] = &tableau[12][0];
                pointeurTableau[13] = &tableau[13][0];
                pointeurTableau[14] = &tableau[14][0];
		pointeurTableau[15] = &tableau[15][0];
                

		int i = 0;

		//recuperer les elements entre chaque tabulations et les enregistrer dans tableau[16][500]

		while(separation != NULL){
			strcpy(tableau[i], separation);
			i += 1;
			separation = strtok(NULL, "\t");
		}
		
		//Les noms de ville se trouve a la case numero 2
		strcpy(VILLETAMPON.nomVille, pointeurTableau[2]);
		
		//Dependemment des lignes, les codes ASCII se trouvent a la case 7 ou 8 de tableau

		if((strlen(pointeurTableau[7]) == 2) && (atoi(pointeurTableau[7]) == 0)){
			localisation = trouverPaysDansListe(tableau[7], LESPAYS);
			strcpy(VILLETAMPON.nomPays, LESPAYS[localisation].pays);
		}
		else{
			localisation = trouverPaysDansListe(tableau[8], LESPAYS);
			strcpy(VILLETAMPON.nomPays, LESPAYS[localisation].pays);
		}

		//Les populations ne se trouvent pas toujours a la meme place d'une ligne a l'autre, mais elle se trouve
		//toujour a la 4ieme case a partir de la fin. 	
	
		if(i == 16){
			VILLETAMPON.population = atoi(pointeurTableau[12]);
		}
		
		else if(i == 15){
			VILLETAMPON.population = atoi(pointeurTableau[11]);
		}

		else {
			VILLETAMPON.population = atoi(pointeurTableau[10]);
		} 
		
		//Cette section sert a trier les villes
		
		
		if(*pointeurCases < argument){
			LESVILLES[*pointeurCases].population = VILLETAMPON.population;
			strcpy(LESVILLES[*pointeurCases].nomVille, VILLETAMPON.nomVille);
			strcpy(LESVILLES[*pointeurCases].nomPays, VILLETAMPON.nomPays);
		}

		else{
			do{
				if(VILLETAMPON.population > LESVILLES[*pointeurI].population){
					int a = argument -1;
					
					for(a; a > *pointeurI; a--){
						LESVILLES[a].population = LESVILLES[a-1].population;
						strcpy(LESVILLES[a].nomVille, LESVILLES[a-1].nomVille);
						strcpy(LESVILLES[a].nomPays, LESVILLES[a-1].nomPays);
					}

					LESVILLES[*pointeurI].population = (*POINTEURVILLETAMPON).population;
                                        strcpy(LESVILLES[*pointeurI].nomVille, (*POINTEURVILLETAMPON).nomVille);
                                        strcpy(LESVILLES[*pointeurI].nomPays, (*POINTEURVILLETAMPON).nomPays);

					estPlusGrand = 1;
				} else{
					*pointeurI += 1;
				}
			}while((*pointeurI < argument) && (estPlusGrand != 1));
		}
		
		estPlusGrand = 0;
		tabulations = 0;
		strcpy(ligne, "");
		*pointeurCases += 1;		
		VILLETAMPON.population = 0;
		strcpy(VILLETAMPON.nomVille, "");
		strcpy(VILLETAMPON.nomPays, "");
		*pointeurI = 0;
		localisation = 0;
		

	}while(!feof(cities15000));

	//Afficher le resultat final
	

	printf(FORMAT_TITRE, "Rang", "Nom", "Pays", "Population");
	printf(FORMAT_TITRE, "----", "---", "----", "----------");
	for(int i = 0; i < argument; i++){
		printf(FORMAT_COLONNES, i+1, LESVILLES[i].nomVille, LESVILLES[i].nomPays, LESVILLES[i].population);
	}
	fclose(countryInfo);
	fclose(cities15000);
	
	return OK;

}
