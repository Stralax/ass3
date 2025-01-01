#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

char** struktura[100];

char* ISPIS[100];

char* R[100];
int dolzinaR = 0;

char* M[100];
int dolzinaM = 0;

char END[15];

char* name[100];
int value[100];
int equ[100];
int endic = 0;

int velikostTabele = 0;
int BASE = 0;

int LS = 0;
int sum = 0; // koliko LS rabimo pocevaci brez ukaza formata 4

int retZnak(char znak){
	if(znak>=48 && znak<=57){
		return znak - 48;
	}
	return znak - 55;
} 

char* decToHex(int stevilo, int velicina){ // velicina je duzina zapisa broja v HEX
	int j = 0;
	int index = 0;
	char* hex = calloc(50, sizeof(char));
	char* rez = calloc(velicina, sizeof(char));
	while (velicina--) {
		int r = stevilo % 16;
		if (r < 10) {
		    hex[index] = r + 48;
		} 
		else{
		    hex[index] = r + 55;
		}
		
		index++;
		stevilo = stevilo / 16;
	}
	for (int i = index - 1; i >= 0; i--) {
	    rez[j++] = hex[i];
	}
	return rez;
}

int hexToDec(char* niz){
	int cifra = 0;
	int broj = 0;
	int stepen = 1;
	for(int i=strlen(niz)-1; i>=0; i--){
		 cifra = retZnak(niz[i]);
		 broj += cifra * stepen;
		 stepen *= 16; 
	}
	return broj;
}

int registri(char* niz){
	if(strcmp(niz, "A") == 0){
		return 0;
	}
	else if(strcmp(niz, "X") == 0){
		return 1;
	}
	else if(strcmp(niz, "L") == 0){
		return 2;
	}
	else if(strcmp(niz, "B") == 0){
		return 3;
	}
	else if(strcmp(niz, "S") == 0){
		return 4;
	}
	else if(strcmp(niz, "T") == 0){
		return 5;
	}
	else if(strcmp(niz, "F") == 0){
		return 6;
	}
	return -1;
}


int ukaz(char* niz, int* tip){

	//UKAZI iz formata 1
	if(strcmp(niz, "FIX") == 0){
		sum = 1;
		tip[0] = 1;
		return 196; 
	}
	else if(strcmp(niz, "FLOAT") == 0){
		sum = 1;
		tip[0] = 1;
		return 192; 
	}
	else if(strcmp(niz, "HIO") == 0){
		sum = 1;
		tip[0] = 1;
		return 244; 
	}
	else if(strcmp(niz, "NORM") == 0){
		sum = 1;
		tip[0] = 1;
		return 200; 
	}
	else if(strcmp(niz, "SIO") == 0){
		sum = 1;
		tip[0] = 1;
		return 240; 
	}
	else if(strcmp(niz, "TIO") == 0){
		sum = 1;
		tip[0] = 1;
		return 248; 
	}
	//UKAZI iz formata 2
	else if(strcmp(niz, "ADDR") == 0){
		sum = 2;
		tip[0] = 2;
		return 144; 
	}
	else if(strcmp(niz, "CLEAR") == 0){
		sum = 2;
		tip[0] = 2;
		return 180; 
	}
	else if(strcmp(niz, "DIVR") == 0){
		sum = 2;
		tip[0] = 2;
		return 156; 
	}
	else if(strcmp(niz, "COMPR") == 0){
		sum = 2;
		tip[0] = 2;
		return 160; 
	}
	else if(strcmp(niz, "MULR") == 0){
		sum = 2;
		tip[0] = 2;
		return 152; 
	}
	else if(strcmp(niz, "RMO") == 0){
		sum = 2;
		tip[0] = 2;
		return 172; 
	}
	else if(strcmp(niz, "SHIFTL") == 0){
		sum = 2;
		tip[0] = 2;
		return 164; 
	}
	else if(strcmp(niz, "SHITFR") == 0){
		sum = 2;
		tip[0] = 2;
		return 168; 
	}
	else if(strcmp(niz, "SUBR") == 0){
		sum = 2;
		tip[0] = 2;
		return 148; 
	}
	else if(strcmp(niz, "SVC") == 0){
		sum = 2;
		tip[0] = 2;
		return 176; 
	}
	else if(strcmp(niz, "TIXR") == 0){
		sum = 2;
		tip[0] = 2;
		return 184; 
	}
	//UKAZI iz formata 3 ili 4
	else if(strcmp(niz, "ADD") == 0){
		sum = 3;
		tip[0] = 3;
		return 24; 
	}
	else if(strcmp(niz, "ADDF") == 0){
		sum = 3;
		tip[0] = 3;
		return 88; 
	}
	else if(strcmp(niz, "AND") == 0){
		sum = 3;
		tip[0] = 3;
		return 64; 
	}
	else if(strcmp(niz, "COMP") == 0){
		sum = 3;
		tip[0] = 3;
		return 40; 
	}
	else if(strcmp(niz, "COMPF") == 0){
		sum = 3;
		tip[0] = 3;
		return 136; 
	}
	else if(strcmp(niz, "DIV") == 0){
		sum = 3;
		tip[0] = 3;
		return 36; 
	}
	else if(strcmp(niz, "DIVF") == 0){
		sum = 3;
		tip[0] = 3;
		return 100; 
	}
	else if(strcmp(niz, "J") == 0){
		sum = 3;
		tip[0] = 3;
		return 60; 
	}
	else if(strcmp(niz, "JEQ") == 0){
		sum = 3;
		tip[0] = 3;
		return 48; 
	}
	else if(strcmp(niz, "JGT") == 0){
		sum = 3;
		tip[0] = 3;
		return 52; 
	}
	else if(strcmp(niz, "JLT") == 0){
		sum = 3;
		tip[0] = 3;
		return 56; 
	}
	else if(strcmp(niz, "JSUB") == 0){
		sum = 3;
		tip[0] = 3;
		return 72; 
	}
	else if(strcmp(niz, "LDA") == 0){
		sum = 3;
		tip[0] = 3;
		return 0; 
	}
	else if(strcmp(niz, "LDB") == 0){
		sum = 3;
		tip[0] = 3;
		return 104; 
	}
	else if(strcmp(niz, "LDCH") == 0){
		sum = 3;
		tip[0] = 3;
		return 80; 
	}
	else if(strcmp(niz, "LDF") == 0){
		sum = 3;
		tip[0] = 3;
		return 112; 
	}
	else if(strcmp(niz, "LDL") == 0){
		sum = 3;
		tip[0] = 3;
		return 8; 
	}
	else if(strcmp(niz, "LDS") == 0){
		sum = 3;
		tip[0] = 3;
		return 108; 
	}
	else if(strcmp(niz, "LDT") == 0){
		sum = 3;
		tip[0] = 3;
		return 116; 
	}
	else if(strcmp(niz, "LDX") == 0){
		sum = 3;
		tip[0] = 3;
		return 4; 
	}
	else if(strcmp(niz, "LPS") == 0){
		sum = 3;
		tip[0] = 3;
		return 208; 
	}
	else if(strcmp(niz, "MUL") == 0){
		sum = 3;
		tip[0] = 3;
		return 32; 
	}
	else if(strcmp(niz, "MULF") == 0){
		sum = 3;
		tip[0] = 3;
		return 96; 
	}
	else if(strcmp(niz, "OR") == 0){
		sum = 3;
		tip[0] = 3;
		return 68; 
	}
	else if(strcmp(niz, "RD") == 0){
		sum = 3;
		tip[0] = 3;
		return 216; 
	}
	else if(strcmp(niz, "RSUB") == 0){
		sum = 3;
		tip[0] = 3;
		return 76; 
	}
	else if(strcmp(niz, "SSK") == 0){
		sum = 3;
		tip[0] = 3;
		return 236; 
	}
	else if(strcmp(niz, "STA") == 0){
		sum = 3;
		tip[0] = 3;
		return 12; 
	}
	else if(strcmp(niz, "STB") == 0){
		sum = 3;
		tip[0] = 3;
		return 120; 
	}
	else if(strcmp(niz, "STCH") == 0){
		sum = 3;
		tip[0] = 3;
		return 84; 
	}
	else if(strcmp(niz, "STF") == 0){
		sum = 3;
		tip[0] = 3;
		return 128; 
	}
	else if(strcmp(niz, "STI") == 0){
		sum = 3;
		tip[0] = 3;
		return 212; 
	}
	else if(strcmp(niz, "STL") == 0){
		sum = 3;
		tip[0] = 3;
		return 20; 
	}
	else if(strcmp(niz, "STS") == 0){
		sum = 3;
		tip[0] = 3;
		return 124; 
	}
	else if(strcmp(niz, "STSW") == 0){
		sum = 3;
		tip[0] = 3;
		return 232; 
	}
	else if(strcmp(niz, "STT") == 0){
		sum = 3;
		tip[0] = 3;
		return 132; 
	}
	else if(strcmp(niz, "STX") == 0){
		sum = 3;
		tip[0] = 3;
		return 16; 
	}
	else if(strcmp(niz, "SUB") == 0){
		sum = 3;
		tip[0] = 3;
		return 28; 
	}
	else if(strcmp(niz, "SUBF") == 0){
		sum = 3;
		tip[0] = 3;
		return 92; 
	}
	else if(strcmp(niz, "TD") == 0){
		sum = 3;
		tip[0] = 3;
		return 224; 
	}
	else if(strcmp(niz, "TIX") == 0){
		sum = 3;
		tip[0] = 3;
		return 44; 
	}
	else if(strcmp(niz, "WD") == 0){
		sum = 3;
		tip[0] = 3;
		return 220; 
	}
	// dodatek
	else if(strcmp(niz, "WORD")){
		sum = 3;
		tip[0] = 4;
		return 0;
	}
	else if(strcmp(niz, "RESW")){
		sum = 3;
		tip[0] = 4;
		return 0;
	}
	else if(strcmp(niz, "BYTE")){
		sum = 1;
		sum = 4;
		return 0;
	}
	else if(strcmp(niz, "RESB")){
		sum = 1;
		sum = 4;
		return 0;
	}
	/*else if(strcmp(niz, "START")){
		sum = 0;
		return -1;
	}*/
	else if(strcmp(niz, "EQU")){  // Razmisli--------------------------------------------------------------
		sum = 0;
		sum = 4;
		return -1;
	}/*
	else if(strcmp(niz, "ORG")){  // Razmisli--------------------------------------------------------------
		sum = 0;
		return -1;
	}
	else if(strcmp(niz, "END")){  // Razmisli
		sum = 0;
		return -1;
	}*/
	
	return -1;
}

void print(int index){
	for(int i=0; i<index; i++){
		int j=0;
		while(strcmp(struktura[i][j], "KONEC") != 0){
			printf("%s ",struktura[i][j]);
			j++;
		}
		printf("\n");
	}
}

int searchPlus(char** niz){
	int j=0;
	while(strcmp(niz[j], "KONEC") != 0){
		if(strcmp(niz[j], "+") == 0){
			return 1;
		}
		j++;
	}
	return 0;
}

//funkcija za ucitavanje iz fajla v pomnilnk
int ucitaj(FILE *fptr){

	char tre;
	int prviznak = 0;
	int index = 0;
	
	char* beseda = calloc(8, sizeof(char));
	int b = 0;
	char** stavek = calloc(15, sizeof(beseda));
	int s = 0;

	while((tre = fgetc(fptr)) != EOF) {
  		
  		if(tre == '{' && prviznak == 0){		// Ucitavamo naslov (adresu)
  			prviznak++;
  			while((tre = fgetc(fptr)) != '}'){
  				beseda[b++] = tre;
  			}
  			stavek[s++] = beseda;
  			//printf("%s ", beseda);
  			beseda = calloc(8, sizeof(char));
  			b = 0;
  		}
  		else if(tre == ' ' && prviznak == 0){	// Stavljamo da prvi naslov ne obstaja
  			stavek[s++] = "COFFEE";
  			//printf("COFFEE ");
  			prviznak++;
  		}
  		else if(tre == '{') {	// Ucitavanje ukaza
  	
  			while((tre = fgetc(fptr)) != '}'){
  				beseda[b++] = tre;
  			}
  			
  			//printf("%s\n", beseda);
  			if(strcmp(beseda, "+") == 0){
  				stavek[s++] = "+";
  			}
  			else{
  				stavek[s++] = beseda;
  			}
  			beseda = calloc(8, sizeof(char));
  			b = 0;
  			
  		}
  		else if(tre == '\n'){
  			//printf("\n");
  			//printf("ad;akdjadk\n");
  			stavek[s++] = "KONEC";
  			struktura[index++] = stavek;
  			stavek = calloc(5, sizeof(beseda));;
  			s = 0;
  			//printf("ad;akdjadk\n");
  			prviznak = 0;
  		}
 		
  		//printf("tre = %c\n", tre);
  		
	}
	return index;
}

int dec(char* niz){
	if(niz[0] == '0' && niz[1] == 'x'){
		return hexToDec(&niz[2]);
	}
	else{
		return atoi(niz);
	}
}

void prviPrehod(int index){
	int tip;
	for(int i=0; i<index; i++){
		if(strcmp(struktura[i][0], "COFFEE") == 0){
			if(strcmp(struktura[i][1], "ORG") == 0){
				if(struktura[i][2][0] == '0' && struktura[i][2][1] == 'x'){
					LS = hexToDec(&struktura[i][2][2]) - 3;
				}
				else{
					LS = atoi(struktura[i][2]) - 3;
				}
			}
		}
		else if(strcmp(struktura[i][0], "COFFEE") != 0){
			// DVA NIZA name[] in value[] globalne promenljive in dostop name[0] in value[0] 
			name[velikostTabele] = struktura[i][0];
			if(strcmp(struktura[i][1], "EQU") == 0){
				if(struktura[i][2][0] == '0' && struktura[i][2][1] == 'x'){
					value[velikostTabele] = hexToDec(&struktura[i][2][2]);
					equ[velikostTabele] = 1;
				}
				else{
					value[velikostTabele] = atoi(struktura[i][2]);
					equ[velikostTabele] = 1;
				}
			}
			else{
				value[velikostTabele] = LS;
			}
			velikostTabele++;
		}
		
		if(strcmp(struktura[i][1], "+") == 0){
			LS += 1;
			ukaz(struktura[i][2], &tip);
			LS += sum;
			sum = 0;
		
		}
		else if(strcmp(struktura[i][1], "START") != 0 && strcmp(struktura[i][1], "EQU") != 0){
			ukaz(struktura[i][1], &tip);
			if(strcmp(struktura[i][1], "RESW") == 0 || strcmp(struktura[i][1], "RESB") == 0){
				int num = atoi(struktura[i][2]);
				LS += sum * num;
			}
			else {
				LS += sum;
			}
			sum = 0;
		}
	}
}

void printTable(){
	for(int i=0; i<velikostTabele; i++){
		printf("Name: %s, %d\n", name[i], value[i]);
	}

}

void printISPIS(){
	for(int i=0; i<1; i++){
		printf("%s\n", R[i]);
	}
}

int isX(char** besede){
	int x = 0;
	int vejica = 0;
	int konec = 0;
	int i =0;
	while(1){
		if(strcmp(besede[i], "KONEC") == 0){
			konec = i;
			break;
		}
		if(strcmp(besede[i], ",") == 0){
			vejica = i;
		}
		if(strcmp(besede[i], "X") == 0){
			x = i;
		}
		i++;
	}
	//printf("k = %d, v = %d, x = %d\n", konec, vejica, x);
	return (konec - vejica) - (konec - x);
}

int getValue(char* niz){
	//printf("ime = %s\n", niz);
	for(int i=0; i<velikostTabele;i++){
		if(strcmp(niz, name[i]) == 0){
			//printf("i = %s\n", name[i]);
			return i;
		}
	}
	//fprintf(stderr, "NAPAKA NASLOV NI DEFINIRAN\n");
	return -1;
}


int naslov(char** niz,int e, int* n){

	

	// Kodiranje naslova	
	int x = 0;
	int b = 0;
	int p = 0;
	int hash = 0;
	if(isX(niz) == 1){
		x = 8;
	}	
	//printf("x = %d\n", x);
	
	char* m;
	int pozicija = 0; 
	if(e == 1){
		pozicija = 3;
	}
	else{
		pozicija = 2;
	}
	if(strcmp(niz[pozicija], "#") == 0){
		pozicija++;
		//hash = 1;
	}
	else if(strcmp(niz[pozicija], "@") == 0){
		pozicija++;
	}
	
	int v = getValue(niz[pozicija]);
	int naslov = value[v];
	
	//printf("%s = %d\n", niz[pozicija], naslov);
	//printf("razlika = %d\n", naslov - LS);
	
	if(v == -1){
		naslov = atoi(niz[pozicija]);
		hash = 1;
	}
	
	if(equ[v] == 1){
		hash = 1;
	}
	
	//printf("vrednost = %d\n", naslov);
	if(hash != 1 && naslov-LS>=-2048 && naslov-LS<2048){	//PC-relativno
		n[0] = naslov - LS;
		//printf("%d\n",n[0]);
		if(n[0]<0 && e==0){
			n[0] += 4096;
		}
		else if(n[0]<0 && e==1){
			n[0] += 1048576;
		}
		p = 2; 
	}
	else if(hash != 1 && BASE == 1 && naslov>=0 && naslov<4096){	// Bazno relativno
		n[0] = naslov;
		b = 4;
	}
	else{ 	// neposredno
		n[0] = naslov;
		//printf("neposredno = %d\n", naslov);
		if(hash == 0 && endic != 1){
			char* modi = calloc(15, sizeof(char));
			for(int m=0; m<15; m++){
				modi[m] = ' ';
			}
			modi[0] = 'M';
			
			int y = 2;
			if(e == 1){
				y = 3;
			}
			char* lok = decToHex(LS-y, 6);
			int j = 1;
			for(int m=0; m<strlen(lok);m++){
				modi[j++] = lok[m];
			}
			modi[7] = '0';
			if(e == 1){
				modi[8] = '5';
			}
			else if(e == 0){
				modi[8] = '3';
			}
			//printf("%s\n", modi);
			M[dolzinaM++] = modi;
		}
	}
	/*else{
		//NAPAKA
	}*/
	return x + e + b + p;
}

int naslavljanje(char* niz){
	int brojUkaza = 0;
	if(strcmp(niz, "@") == 0){	//posredno naslavljanje
		brojUkaza += 2;
	}
	else if(strcmp(niz, "#") == 0){	//takojsnje
		brojUkaza += 1;
	}
	else{	//enostavno
		brojUkaza += 3;
	}
	return brojUkaza;
}

void drugiPrehod(int index){
	int kreiraj = 0;
	LS = 0;
	int indexEND = 0;
	int duzinaT = 9;
	char* T = calloc(80, sizeof(char));
	for(int m=0; m<80; m++){
		T[m] = ' ';
	}
	T[0] = 'T';
	int res = 0;
	int stariRes = 0;
	for(int i=0; i<index; i++){
		res = 0;
		if(strcmp(struktura[i][1], "ORG") == 0){
			if(struktura[i][2][0] == '0' && struktura[i][2][1] == 'x'){
				LS = hexToDec(&struktura[i][2][2]) - 3;
			}
			else{
				LS = atoi(struktura[i][2]) - 3;
			} 
		}
		else if(strcmp(struktura[i][1], "BASE") == 0){
			BASE = 1;
		}
		else if(strcmp(struktura[i][1], "NOBASE") == 0){
			BASE = 0;
		}
		else if(strcmp(struktura[i][1], "START") == 0){
			char* prviRed = calloc(22,sizeof(char));
			prviRed[0] = 'H';
			int j = 1;
			for(int k=0; k<strlen(struktura[i][0]); k++){
				prviRed[j++] = struktura[i][0][k];
			}
			if(j<7){
				for(int k=j; k<7; k++){
					prviRed[k] = ' ';
				}	
			}
			int d = dec(struktura[i][2]);
			
			char* stevilo = decToHex(d, 6);
			j = 7;
			for(int k=0; k<strlen(stevilo); k++){
				prviRed[j++] = stevilo[k];
				
			}
			// MANJKA DUZINA PROGRAMA
			R[0] = prviRed;
			dolzinaR++;
			
			char* stevilo2 = decToHex(LS, 6);
			j = 1;
			for(int k=0; k<strlen(stevilo2); k++){
				T[j++] = stevilo2[k];
			}
			//printf("%s\n", T);
		}
		else if(strcmp(struktura[i][1], "END") == 0){
			for(int m=0; m<15; m++){
				END[m] = ' ';
			}
			END[0] = 'E';
			indexEND = 1;
			endic = 1;
			int nas;
			naslov(struktura[i], 0, &nas);
			char* zapis = decToHex(nas, 6);
			int j = 1;
			for(int k=0; k<strlen(zapis); k++){
				END[j++] = zapis[k];
			}
		}
		
		
		if(strcmp(struktura[i][1], "+") == 0){
			LS += 1;
			int tip;
			int brojUkaza = ukaz(struktura[i][2], &tip);
			LS += sum;
			sum = 0;
			
			
			brojUkaza += naslavljanje(struktura[i][3]);
			int nas = 0;
			int n = naslov(struktura[i], 1, &nas);
			
			char* zapis = decToHex(brojUkaza, 2);
			for(int k=0; k<strlen(zapis); k++){
				T[duzinaT++] = zapis[k];
				if(duzinaT >= 69){	// DODATEK
					T[7] = '1';
					T[8] = 'E';
					R[dolzinaR++] = T;
					//printf("%s\n", T);
					T = calloc(80, sizeof(char));
					for(int m=0; m<80; m++){
						T[m] = ' ';
					}
					T[0] = 'T';
					duzinaT = 9;
					char* stevilo2 = decToHex(LS - ((strlen(zapis) - k + 1)/2), 6);
					int j = 1;
					for(int k=0; k<strlen(stevilo2); k++){
						T[j++] = stevilo2[k];
					}
				}	// KRAJ DODATKA
			}
			T[duzinaT++] = decToHex(n, 1)[0];
			////// RADI  MORAS RAZMISLITI KAKO RAZLIKOVATI 1 format, 2 format, 3-4 fromat nije
			
			zapis = decToHex(nas, 5);
			for(int k=0; k<strlen(zapis); k++){
				T[duzinaT++] = zapis[k];
				if(duzinaT >= 69){	// DODATEK
					T[7] = '1';
					T[8] = 'E';
					R[dolzinaR++] = T;
					//printf("%s\n", T);
					T = calloc(80, sizeof(char));
					for(int m=0; m<80; m++){
						T[m] = ' ';
					}
					T[0] = 'T';
					duzinaT = 9;
					char* stevilo2 = decToHex(LS - ((strlen(zapis) - k + 1)/2), 6);
					int j = 1;
					for(int k=0; k<strlen(stevilo2); k++){
						T[j++] = stevilo2[k];
					}
				}	// KRAJ DODATKA
				else if(res && T[9] != ' '){	// pogoj2
					res = 0;
					int t = 9;
					while(T[t] != ' '){
						t++;
					}
					char* dol = decToHex((t-9)/2, 2);
					int q = 7;
					for(int k=0; k<strlen(dol); k++){
						T[q++] = dol[k];
					}
					
					if(T[8] != '0'){
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS, 6);
						kreiraj = 1;
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}
					else{
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						kreiraj = 1;
						char* stevilo2 = decToHex(LS, 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}
				}	//kraj pogoj2
			}
			
			//printf("%s\n", T);
			/*T = calloc(80, sizeof(char));
			for(int m=0; m<80; m++){
				T[m] = ' ';
			}
			T[0] = 'T';
			duzinaT = 9;*/
			
		}
		else if(strcmp(struktura[i][1], "START") != 0 && strcmp(struktura[i][1], "EQU") != 0 && strcmp(struktura[i][1], "END") != 0){
			int tip = 0;
			int brojUkaza = ukaz(struktura[i][1], &tip);
			if(strcmp(struktura[i][1], "RESW") == 0 || strcmp(struktura[i][1], "RESB") == 0){
				int num = atoi(struktura[i][2]);
				LS += sum * num;
				res = 1;
				stariRes = 1;
			}
			else {
				LS += sum;
			}
			sum = 0;
			
			if(tip == 3 && strcmp(struktura[i][2], "KONEC") != 0){
				brojUkaza += naslavljanje(struktura[i][2]);
				int nas = 0;
				//printf("a = %s\n", struktura[i][1]);
				int n = naslov(struktura[i], 0, &nas);
				
				char* zapis = decToHex(brojUkaza, 2);
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS - (strlen(zapis) - k + 1), 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
				}
				T[duzinaT++] = decToHex(n, 1)[0];
				////// RADI  MORAS RAZMISLITI KAKO RAZLIKOVATI 1 format, 2 format, 3-4 fromat nije
				
				zapis = decToHex(nas, 3);
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS - ((strlen(zapis) - k)/2), 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
				}
				//printf("ime = %s\n",struktura[i][1]);
				//printf("%s\n", T);
				/*T = calloc(80, sizeof(char));
				for(int m=0; m<80; m++){
					T[m] = ' ';
				}
				T[0] = 'T';
				duzinaT = 9;*/
			}
			else if(strcmp(struktura[i][1], "WORD") == 0 || strcmp(struktura[i][1], "BYTE") == 0){
				int broj = 0;
				if(struktura[i][2][0] == '0' && struktura[i][2][1] == 'x'){
					 broj = hexToDec(&struktura[i][2][2]);
				}
				else{
					broj = atoi(struktura[i][2]);
				}
				char* zapis;
				if(strcmp(struktura[i][1], "BYTE") == 0){
					zapis = decToHex(broj, 2);
				}
				else if(strcmp(struktura[i][1], "WORD") == 0){
					zapis = decToHex(broj, 6);
				}
				
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS - ((strlen(zapis) - k)/2), 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
					
				}
				//printf("ime = %s\n",struktura[i][1]);
				//printf("%s\n", T);
				/*T = calloc(80, sizeof(char));
				for(int m=0; m<80; m++){
					T[m] = ' ';
				}
				T[0] = 'T';
				duzinaT = 9;*/
				
			}
			else if(strcmp(struktura[i][1], "RSUB") == 0){
				brojUkaza += naslavljanje(struktura[i][2]);
				char* zapis = decToHex(brojUkaza, 2);
				int nas = 0;
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
				}
				int n = 0;
				T[duzinaT++] = decToHex(n, 1)[0];
				zapis = decToHex(0, 3);
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS - (strlen(zapis) - k + 1), 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
				}
				//printf("ime = %s\n",struktura[i][1]);
				//printf("%s\n", T);
				/*T = calloc(80, sizeof(char));
				for(int m=0; m<80; m++){
					T[m] = ' ';
				}
				T[0] = 'T';
				duzinaT = 9;*/	
			}
			else if(tip == 2){
				char* zapis = decToHex(brojUkaza, 2);
				int r1;
				int r2;
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS, 6);
						kreiraj = 1;
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
				}
				r1 = registri(struktura[i][2]);
				zapis = decToHex(r1, 1);
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS - ((strlen(zapis) - k)/2), 6);
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
					else if(res && T[9] != ' '){	// pogoj2
						res = 0;
						int t = 9;
						while(T[t] != ' '){
							t++;
						}
						char* dol = decToHex((t-9)/2, 2);
						int q = 7;
						for(int k=0; k<strlen(dol); k++){
							T[q++] = dol[k];
						}
						
						if(T[8] != '0'){
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS, 6);
							kreiraj = 1;
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
						else{
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							kreiraj = 1;
							char* stevilo2 = decToHex(LS, 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}
					}	//kraj pogoj2
				}
				///printf("l = %s\n", struktura[i][4]);
				if(struktura[i][4] != NULL && (r2 = registri(struktura[i][4])) != -1){
					
					zapis = decToHex(r2, 1);
					for(int k=0; k<strlen(zapis); k++){
						T[duzinaT++] = zapis[k];
						if(duzinaT >= 69){	// DODATEK
							T[7] = '1';
							T[8] = 'E';
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS - ((strlen(zapis) - k)/2), 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}	// KRAJ DODATKA*/
						else if(res && T[9] != ' '){	// pogoj2
							res = 0;
							int t = 9;
							while(T[t] != ' '){
								t++;
							}
							char* dol = decToHex((t-9)/2, 2);
							int q = 7;
							for(int k=0; k<strlen(dol); k++){
								T[q++] = dol[k];
							}
							
							if(T[8] != '0'){
								R[dolzinaR++] = T;
								//printf("%s\n", T);
								T = calloc(80, sizeof(char));
								for(int m=0; m<80; m++){
									T[m] = ' ';
								}
								T[0] = 'T';
								duzinaT = 9;
								char* stevilo2 = decToHex(LS, 6);
								kreiraj = 1;
								int j = 1;
								for(int k=0; k<strlen(stevilo2); k++){
									T[j++] = stevilo2[k];
								}
							}
							else{
								T = calloc(80, sizeof(char));
								for(int m=0; m<80; m++){
									T[m] = ' ';
								}
								T[0] = 'T';
								duzinaT = 9;
								kreiraj = 1;
								char* stevilo2 = decToHex(LS, 6);
								int j = 1;
								for(int k=0; k<strlen(stevilo2); k++){
									T[j++] = stevilo2[k];
								}
							}
						}	//kraj pogoj2
					}
				}
				else{
					int broj = 0;
					if(struktura[i][4] != NULL){
						broj = atoi(struktura[i][4]);
					}
					zapis = decToHex(broj, 1);
					for(int k=0; k<strlen(zapis); k++){
						T[duzinaT++] = zapis[k];
						if(duzinaT >= 69){	// DODATEK
							T[7] = '1';
							T[8] = 'E';
							R[dolzinaR++] = T;
							//printf("%s\n", T);
							T = calloc(80, sizeof(char));
							for(int m=0; m<80; m++){
								T[m] = ' ';
							}
							T[0] = 'T';
							duzinaT = 9;
							char* stevilo2 = decToHex(LS - ((strlen(zapis) - k)/2), 6);
							int j = 1;
							for(int k=0; k<strlen(stevilo2); k++){
								T[j++] = stevilo2[k];
							}
						}	// KRAJ DODATKA
						else if(res && T[9] != ' '){	// pogoj2
							res = 0;
							int t = 9;
							while(T[t] != ' '){
								t++;
							}
							char* dol = decToHex((t-9)/2, 2);
							int q = 7;
							for(int k=0; k<strlen(dol); k++){
								T[q++] = dol[k];
							}
							
							if(T[8] != '0'){
								R[dolzinaR++] = T;
								//printf("%s\n", T);
								T = calloc(80, sizeof(char));
								for(int m=0; m<80; m++){
									T[m] = ' ';
								}
								T[0] = 'T';
								duzinaT = 9;
								char* stevilo2 = decToHex(LS, 6);
								kreiraj = 1;
								int j = 1;
								for(int k=0; k<strlen(stevilo2); k++){
									T[j++] = stevilo2[k];
								}
							}
							else{
								T = calloc(80, sizeof(char));
								for(int m=0; m<80; m++){
									T[m] = ' ';
								}
								T[0] = 'T';
								duzinaT = 9;
								kreiraj = 1;
								char* stevilo2 = decToHex(LS, 6);
								int j = 1;
								for(int k=0; k<strlen(stevilo2); k++){
									T[j++] = stevilo2[k];
								}
							}
						}	//kraj pogoj2
					}
				}
				
				//printf("ime = %s\n",struktura[i][1]);
				//printf("%s\n", T);
				/*T = calloc(80, sizeof(char));
				for(int m=0; m<80; m++){
					T[m] = ' ';
				}
				T[0] = 'T';
				duzinaT = 9;*/
			}
			else if(tip == 1){
				char* zapis = decToHex(brojUkaza, 2);
				for(int k=0; k<strlen(zapis); k++){
					T[duzinaT++] = zapis[k];
					if(duzinaT >= 69){	// DODATEK
						T[7] = '1';
						T[8] = 'E';
						R[dolzinaR++] = T;
						//printf("%s\n", T);
						T = calloc(80, sizeof(char));
						for(int m=0; m<80; m++){
							T[m] = ' ';
						}
						T[0] = 'T';
						duzinaT = 9;
						char* stevilo2 = decToHex(LS, 6);
						kreiraj = 1;
						int j = 1;
						for(int k=0; k<strlen(stevilo2); k++){
							T[j++] = stevilo2[k];
						}
					}	// KRAJ DODATKA
				}
			}
			
			if(duzinaT >= 69){	// DODATEK
				T[7] = '1';
				T[8] = 'E';
				R[dolzinaR++] = T;
				//printf("%s\n", T);
				T = calloc(80, sizeof(char));
				for(int m=0; m<80; m++){
					T[m] = ' ';
				}
				T[0] = 'T';
				duzinaT = 9;
				char* stevilo2 = decToHex(LS, 6);
				kreiraj = 1;
				int j = 1;
				for(int k=0; k<strlen(stevilo2); k++){
					T[j++] = stevilo2[k];
				}
			}	// KRAJ DODATKA
			
			else if(res){	// pogoj2
				
				res = 0;
				stariRes = 0;
				int t = 9;
				while(T[t] != ' '){
					t++;
				}
				char* dol = decToHex((t-9)/2, 2);
				int q = 7;
				for(int k=0; k<strlen(dol); k++){
					T[q++] = dol[k];
				}
				
				if(T[8] != '0'){
					R[dolzinaR++] = T;
					//printf("%s\n", T);
					T = calloc(80, sizeof(char));
					for(int m=0; m<80; m++){
						T[m] = ' ';
					}
					T[0] = 'T';
					duzinaT = 9;
					kreiraj = 1;
					char* stevilo2 = decToHex(LS, 6);
					int j = 1;
					for(int k=0; k<strlen(stevilo2); k++){
						T[j++] = stevilo2[k];
					}
				}
				else{
					T = calloc(80, sizeof(char));
					for(int m=0; m<80; m++){
						T[m] = ' ';
					}
					T[0] = 'T';
					duzinaT = 9;
					kreiraj = 1;
					char* stevilo2 = decToHex(LS, 6);
					int j = 1;
					for(int k=0; k<strlen(stevilo2); k++){
						T[j++] = stevilo2[k];
					}
				}
			}	//kraj pogoj2
		}
	}
	if(T[10] != ' '){
		int t = 9;
		while(T[t] != ' '){
			t++;
		}
		char* dol = decToHex((t-9)/2, 2);
		int q = 7;
		for(int k=0; k<strlen(dol); k++){
			T[q++] = dol[k];
		}
		
		
		R[dolzinaR++] = T;
		//printf("%s\n", T);
		T = calloc(80, sizeof(char));
		for(int m=0; m<80; m++){
			T[m] = ' ';
		}
		T[0] = 'T';
		duzinaT = 9;
		char* stevilo2 = decToHex(LS, 6);
		int j = 1;
		for(int k=0; k<strlen(stevilo2); k++){
			T[j++] = stevilo2[k];
		}
	
	}
	
	if(indexEND == 0){
		strcpy(END, "E000000");
	}
	
}

void createFile(char* name){

	int i = 0;
	char* name2 = calloc(25, sizeof(char));
	while(name[i] != '.'){
		name2[i] = name[i];
		i++;
	}
	name2[i++] = name[i];
	name2[i++] = 's';
	name2[i++] = 'o';
	name2[i++] = 'b';
	name2[i++] = 'j';
	
	FILE* fptr = fopen(name2, "w");
	char* broj = decToHex(LS, 6);
	int j = 13;
	for(int m=0; m<strlen(broj); m++){
		R[0][j++] = broj[m];
	}
	//printf("%s\n", R[0]);
	
	fprintf(fptr, "%s\n", R[0]);
	for(int i=1; i<dolzinaR; i++){
		for(int j=0; j<70; j++){
			if(R[i][j] != ' '){
				fprintf(fptr, "%c", R[i][j]);
			}			
		}
		fprintf(fptr, "\n");
	}
	
	/*for(int i=0; i<dolzinaM; i++){
		fprintf(fptr, "%s\n", R[i]);
	}*/
	
	/*for(int i=0; i<dolzinaM; i++){
		fprintf(fptr, "%s\n", M[i]);
	}*/
	
	for(int i=0; i<dolzinaM; i++){
		for(int j=0; j<10; j++){
			if(M[i][j] != ' '){
				fprintf(fptr, "%c", M[i][j]);
			}			
		}
		fprintf(fptr, "\n");
	}
	
	for(int i=0; i<7; i++){
		if(END[i] != ' '){
			fprintf(fptr, "%c", END[i]);
		}	
	}
	fprintf(fptr, "\n");
	
	//fprintf(fptr, "%s\n", END);
}

int main(int argc, char *argv[]){


	
	FILE *fptr;
	fptr = fopen("Koda.txt", "r"); 
	
	int index = ucitaj(fptr);
	//printf("velikost = %d\n", index);
	//print(index);
	
	prviPrehod(index);
	
	//printTable();
	
	drugiPrehod(index);

	
	//printf("%s\n", END);
	
	createFile(argv[1]);
	
	//printISPIS();
	
	//printf("broj = %s\n", decToHex(68, 2));
	
	//printf("dec = %d\n", hexToDec("1248"));
	
	return 0;
}



























