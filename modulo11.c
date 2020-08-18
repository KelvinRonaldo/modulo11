#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "modulo11.h"

int subString(char *input, char *output, int initIndex, int size){

	int i = 0;

	if(size > strlen(input)){
		return false;
	}

	for(i = 0; i < size; i++){
		output[i] = input[initIndex+i];
	}

	return true;
}

int verifyCpf(char *cpf){
	int multiplier = 10;

	char cpfWithoutDigit[20] = {0x00};
	char originalDigit[4] = {0x00};
	char finalDigit[4] = {0x00};

	int numChars[32];
	int multiplied[32];
	int sum = 0;
	int sums[30];

	double divRemainder = 0.0;

	if(strcmp(cpf, "00000000000") == 0){
		return false;
	}

	
	subString(cpf, originalDigit, 9, 2);
	subString(cpf, cpfWithoutDigit, 0, strlen(cpf) - 2);

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < strlen(cpfWithoutDigit); j++){
			numChars[j] = cpf[j] - '0';
			multiplied[j] = numChars[j] * multiplier;
			multiplier--;
			sum += multiplied[j];

		}

		divRemainder = fmod(sum, 11);
		if(divRemainder < 2){
			if(strlen(finalDigit) < 1){
				strcpy(finalDigit, "0");
			}else{
				strcat(finalDigit, "0");
			}
		}else{
			sprintf(finalDigit, "%s%d", finalDigit, (int)(11 - divRemainder));
		}

		sum = 0;
		memset(numChars, 0x00, sizeof(numChars));
		memset(multiplied, 0x00, sizeof(multiplied));
		sprintf(cpfWithoutDigit, "%s%d", cpfWithoutDigit, (int)(11 - divRemainder));
		multiplier = 11;

	}

	if(strcmp(finalDigit, originalDigit) != 0){
		return false;
	}

	return true;
}

int verifyCnpj(char *cnpj){
	
	int multiplier = 2;
	int sum = 0;

	int numChars[32];
	int multiplied[32];

	char cnpjWithoutDigit[32];
    char originalDigit[4] = {0x00};
	char finalDigit[4] = {0x00};
	double divRemainder = 0.0;

	if(strcmp(cnpj, "00000000000000") == 0){
		return false;
	}

	subString(cnpj, originalDigit, strlen(cnpj) - 2, 2);
	subString(cnpj, cnpjWithoutDigit, 0, strlen(cnpj) - 2);

	for(int i = 0; i < 2; i++){
		for(int j = strlen(cnpjWithoutDigit) - 2, k = 0; j >= 0; j--, k++){
			numChars[k] = cnpj[j] - '0';
			multiplied[k] = numChars[k] * multiplier;
			multiplier++;
			if(multiplier > 9){
				multiplier = 2;
			}
			sum += multiplied[k];			

		}

		divRemainder = fmod(sum, 11);
		if(divRemainder < 2){
			if(strlen(finalDigit) < 1){
				strcpy(finalDigit, "0");
			}else{
				strcat(finalDigit, "0");
			}
		}else{
			sprintf(finalDigit, "%s%d", finalDigit, (int)(11 - divRemainder));
		}

		sum = 0;
		memset(numChars, 0x00, sizeof(numChars));
		memset(multiplied, 0x00, sizeof(multiplied));
		sprintf(cnpjWithoutDigit, "%s%d", cnpjWithoutDigit, (int)(11 - divRemainder));
		multiplier = 2;

		
	}

	if(strcmp(finalDigit, originalDigit) != 0){
		return false;
	}

	return true;
}


int main(void){

	char cpf[] = "00000000000";
	char cnpj[] = "33333333333328";

	if(verifyCpf(cpf)){
		printf("CPF VÁLIDO\n");
	}else{
		printf("CPF INVÁLIDO\n");
	}

	if(verifyCnpj(cnpj)){
		printf("CNPJ VÁLIDO\n");
	}else{
		printf("CNPJ INVÁLIDO\n");
	}

	return 0;
}