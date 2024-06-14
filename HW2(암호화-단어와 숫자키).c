#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void makeCaesar(char k[], char n[]) {
	int crc;
	int i;
	int p = 1;
	n[0] = k[0];
	for (i = 1; k[i] != '\0'; i++) {
		crc = 0;
		for (int j = 0; j < i; j++) {
			if (k[i] == k[j]) {
				crc = 1;
				break;
			}
		}
		if (crc == 0) {
			n[p++] = k[i];
		}
	}
	n[p] = '\0';
}
void encoded(int dist, char n[], char a[]) {
	int idx = dist;
	char start = 'A';
	int i;
	int nLen = strlen(n);
	/*
	for (i = 0; i < 26; i++) {
		if (idx >= dist && idx < nLen + dist)
			a[idx++] = n[i];
	}
	*/
	for (i = 0; i < strlen(n); i++) {
		if (idx >= dist && idx < nLen + dist)
			a[idx++] = n[i];
	}

	for (i = 0; i < 26 - strlen(n); i++) {
		for (int j = 0; j < strlen(n); j++) {
			if (start == n[j])
				start++;
		}
		a[idx++] = start++;
		if (idx == 26)
			idx = 0;
	}
	a[26] = '\0';
}

void encodedSentence(char a[], char o[], char e[]) {
	int i;
	for (i = 0; o[i] != '\0'; i++) {
		if (o[i] >= 'A' && o[i] <= 'Z') {
			e[i] = a[o[i] - 'A'];
		}
		else {
			e[i] = o[i];
		}
	}
	e[i] = '\0';
}
int main(void) {
	char caesarKey[30];
	int caesarDist;	// 0 ~ 25
	char alphabet[27];
	char newKey[30];

	printf("Enter a key to use for encoding(대문자로 된 단어입력): ");
	scanf("%s", caesarKey);
	printf("Enter a distance for encoding: ");
	scanf("%d", &caesarDist);
	makeCaesar(caesarKey, newKey);

	encoded(caesarDist, newKey, alphabet);
	printf("----------------------------------------------------\n");
	printf("alphabet: \t");

	for (int i = 'A'; i <= 'Z'; i++) {
		printf("%c", i);
	}
	printf("\nencoded: \t");
	printf("%s", alphabet);

	FILE* fp1;
	FILE* fp2;
	char fp1Name[30];
	char fp2Name[30];

	printf("\n입력파일: ");
	getchar();
	fgets(fp1Name, 30, stdin);
	
	printf("출력파일: ");
	fgets(fp2Name, 30, stdin);

	fp1Name[strlen(fp1Name) - 1] = '\0';	// fgets 널문자 제거
	fp2Name[strlen(fp2Name) - 1] = '\0';

	if ((fp1 = fopen(fp1Name, "r")) == NULL) {
		printf("파일 오픈 에러1");
		exit(1);
	}

	if ((fp2 = fopen(fp2Name, "w")) == NULL) {
		printf("파일 오픈 에러2");
		exit(2);
	}

	char origin[256];
	char encoded[256];

	while (fgets(origin, sizeof(origin), fp1) != NULL) {
		encodedSentence(alphabet, origin, encoded);
		fputs(encoded, fp2);
	}
	fclose(fp1);
	fclose(fp2);

	return 0;
}
