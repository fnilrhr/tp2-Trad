#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inf301.h"

/*

PAS FINIS MANQUE DES TRUCS 

*/



// Character to display blocks in terminal
#define CHAR_FULL 219

// Size of image characters
#define CHAR_SIZE 7

// Size of the alphabets
#define ALPHABET_SIZE 40

/**
 * \struct struct SheikahCharacter
 * \brief Structure representing a character of the Sheikah alphabet
 *
 * \var character The (french) character represented.
 * \var image The graphical representation of the character.
 */
struct SheikahCharacter {
	char character;
	char image[CHAR_SIZE][CHAR_SIZE];
};

// End-of-string character for the Sheikah alphabet
const struct SheikahCharacter SHEIKAH_NULL = {'\0'};

// Space caracter for the Sheikah alphabet
const struct SheikahCharacter SHEIKAH_SPACE = {' '};

// French alphabet
const char french_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
	'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	 'X', 'Y', 'Z', '-', '!', '.', '?', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

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

void french_to_sheikah(char * french, struct SheikahCharacter * sheikah, struct SheikahCharacter * sheikah_alphabet, int alphaSize){
	for(int i=0; i<strlen(french); i++){
		int index = index_french_alphabet(french[i]);
		if(index==-1){
			//sheikah->character = french[i];
			sheikah[i] = SHEIKAH_SPACE;
		}else{
			sheikah[i] = sheikah_alphabet[index];
		}
	}
	sheikah[strlen(french)] = SHEIKAH_NULL;
}

void sheikah_vers_image(struct SheikahCharacter * sheikah){
	const int taille_caractere = 7;

	char * image;

	int largeur_image = strlen(sheikah->character) * (taille_caractere + 2);

	for(int i =0; i < strlen(sheikah->character); i++){
		for(int k = 0; k < taille_caractere; k++){
			int position = i * (taille_caractere + 2);
			for(int j =0; j < (taille_caractere -1); j++){
				image[i][position + j] = sheikah[i].image[k][j];
			}
			image[i][position + taille_caractere] = " ";
			image[i][position + taille_caractere + 1] = " ";
		}
	}
}

struct SheikahCharacter read_character(char * line) {
	struct SheikahCharacter c;
	char * current_value = NULL;
	int i, j;

	for ( i = 0 ; i < CHAR_SIZE ; i++ ) {
		for( int j = 0 ; j < CHAR_SIZE ; j++ ) {
			c.image[i][j] = ' ';
		}
	}

	current_value = strtok(line, " ");
	c.character = *current_value;
	current_value = strtok(NULL, " ");
	while( current_value != NULL ) {
		i = atoi(current_value);
		current_value = strtok(NULL, " ");
		j = atoi(current_value);
		c.image[i][j] = CHAR_FULL;
		current_value = strtok(NULL, " ");
	}
	return c;
}

/**
 * \fn load_alphabet
 * \brief Loads the Sheikah alphabet from a file.
 *
 * \param file_name The path of the file containing the alphabet data.
 *
 * \return The (address of the) array of struct SheikahCharacter created from
 *         the file.
 */
struct SheikahCharacter * load_alphabet(char * file_name) {
	char line[1024];
	int nb_lines;
	struct SheikahCharacter * alphabet;
	FILE * file = fopen(file_name, "r");
	if( file == NULL ) {
		fprintf(stderr, "Error: cannot load file %s.\n", file_name);
		exit(EXIT_FAILURE);
	}
	nb_lines = 0;
	while( fgets(line, sizeof(line), file) != NULL ) {
		nb_lines++;
	}
	alphabet = (struct SheikahCharacter *)malloc(sizeof(struct SheikahCharacter) * nb_lines);
	rewind(file);
	nb_lines = 0;
	while( fgets(line, sizeof(line), file ) != NULL ) {
		alphabet[nb_lines] = read_character(line);
		nb_lines++;
	}
	fclose(file);
	return alphabet;
}

/**
 * \fn new_1D_int_array
 * \brief Creates a regular (1-dimensional) array of struct SheikahCharacter of
 *        size array_size.
 *
 * \param array_size The size (number of cells) in the array.
 *
 * \return The (address of the) array created.
 */
struct SheikahCharacter * new_1D_sheikahcharacter_array(int array_size) {
	return new_1D_array(array_size, sizeof(struct SheikahCharacter));
}

int main(int argc, char ** argv) {
	// load Sheikah alphabet
	struct SheikahCharacter * sheikah_alphabet = load_alphabet("sheikah_alphabet.dat");

	// TEST french_to_sheikah()
	int i;
	char * test_french1 = "ALGORITHME";
	struct SheikahCharacter * test_french_to_sheikah1 = new_1D_sheikahcharacter_array(strlen(test_french1) + 1);
	french_to_sheikah(test_french1, test_french_to_sheikah1, sheikah_alphabet, ALPHABET_SIZE);
	printf("Translation of %s - Found : ", test_french1);
	for( i = 0 ; test_french_to_sheikah1[i].character != '\0'; i++ ) {
		printf("%c", test_french_to_sheikah1[i].character);
	}
	printf("\n");

	char * test_french2 = "C'EST UN EXEMPLE.";
	struct SheikahCharacter * test_french_to_sheikah2 = new_1D_sheikahcharacter_array(strlen(test_french2) + 1);
	french_to_sheikah(test_french2, test_french_to_sheikah2, sheikah_alphabet, ALPHABET_SIZE);
	printf("Translation of %s - Found : ", test_french2);
	for( i = 0 ; test_french_to_sheikah2[i].character != '\0'; i++ ) {
		printf("%c", test_french_to_sheikah2[i].character);
	}
	printf("\n");

	char * test_french3 = "";
	struct SheikahCharacter * test_french_to_sheikah3 = new_1D_sheikahcharacter_array(strlen(test_french3) + 1);
	french_to_sheikah(test_french3, test_french_to_sheikah3, sheikah_alphabet, ALPHABET_SIZE);
	printf("Translation of %s - Found : ", test_french3);
	for( i = 0 ; test_french_to_sheikah3[i].character != '\0'; i++ ) {
		printf("%c", test_french_to_sheikah3[i].character);
	}
	printf("\n");

	return 0;
}
