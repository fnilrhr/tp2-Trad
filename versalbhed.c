#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inf301.h"

// Size of the alphabets
#define ALPHABET_SIZE 26

// French alphabet
const char french_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
			'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Al Bhed alphabet
const char albhed_alphabet[] = {'Y', 'P', 'L', 'T', 'A', 'V', 'K', 'R', 'E',
			'Z', 'G', 'M', 'S', 'H', 'U', 'B', 'X', 'N', 'C', 'D',
			'I', 'J', 'F', 'Q', 'O', 'W'};

int index_french_alphabet(char character) {
	int indice=-1;
	for(int i=0;i<ALPHABET_SIZE;i++){
		if (french_alphabet[i]==character){
			//charactere trouve
			indice=i;
		}
	}
	return indice;
}

void albhed_to_french(char * french, char * albhed) {
	for(int i=0;i<strlen(french);i++){
		int index = index_french_alphabet(french[i]);
		if(index==-1){
			//charactere non alph
			albhed[i]=french[i];
		}
		else{
			albhed[i]=albhed_alphabet[index];
		}
	}
	printf("%s", albhed);			
}

int main(int argc, char ** argv) {
	// Tests of index_albhed_alphabet()
	printf("Index of 'Y' - Expected : 0 - Found : %d\n", index_french_alphabet('Y'));
	printf("Index of 'Z' - Expected : 9 - Found : %d\n", index_french_alphabet('Z'));
	printf("Index of 'W' - Expected : 25 - Found : %d\n", index_french_alphabet('W'));
	printf("Index of '5' - Expected : -1 - Found : %d\n", index_french_alphabet('5'));

	// Tests albhed_to_french()
	// creation of strings to receive translations
	char * test_albhed1 = "IMT C'EST ECLATE";
	char * test_albhed_to_french1 = new_1D_char_array(strlen(test_albhed1)+1);
	albhed_to_french(test_albhed1, test_albhed_to_french1);
	printf("Translation of IMT C'EST ECLATE - Expected : ALGORITHME - Found : %s\n", test_albhed_to_french1);
	destroy_1D_array(test_albhed_to_french1);

	char * test_albhed2 = "TA GROSSE MERE A CHARLIN CAR ELLE M'INVTE PAS CETTE PUTE.";
	char * test_albhed_to_french2 = new_1D_char_array(strlen(test_albhed2)+1);
	albhed_to_french(test_albhed2, test_albhed_to_french2);
	printf("Translation of TA GROSSE MERE A CHARLIN CAR ELLE M'INVTE PAS CETTE PUTE. - Expected : C'EST UN EXEMPLE. - Found : %s\n", test_albhed_to_french2);
	destroy_1D_array(test_albhed_to_french2);

	char * test_albhed3 = "";
	char * test_albhed_to_french3 = new_1D_char_array(strlen(test_albhed3)+1);
	albhed_to_french(test_albhed3, test_albhed_to_french3);
	printf("Translation of empty string - Expected : - Found : %s\n", test_albhed_to_french3);
	destroy_1D_array(test_albhed_to_french3);

	return 0;
}
