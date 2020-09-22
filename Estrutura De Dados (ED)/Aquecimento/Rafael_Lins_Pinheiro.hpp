#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <stdio.h>
#include <algorithm> 

using namespace std;

int exercicio0(const char* cstr) {
	return 0;
}

int exercicio1(const char* cstr) {
	int num1, num2, sum = 0;
	sscanf_s(cstr, "%d %d", &num1, &num2);


	for (int i = num1; i <= num2; i++) {
		sum += i;
	}

	return sum;
}

int exercicio2(const char* cstr) {
	int numvot, cand1 = 0, cand2 = 0, cand3 = 0, voto;
	sscanf_s(cstr, "%d", &numvot);
	//scanf_s("%d", &numvot);
	for (int i = 0; i < numvot; i++) {
		sscanf_s(cstr, "%d", &voto);
		//scanf_s("%d", &voto);
		if (voto == 1) {
			cand1 += 1;
		}
		if (voto == 2) {
			cand2 += 1;
		}
		if (voto == 3) {
			cand3 += 1;
		}
		voto = 0;
	}
	if (cand1 > cand2 && cand1 > cand3) {
		return 1;
	}

	else if (cand2 > cand1 && cand2 > cand3) {
		return 2;
	}
	else if (cand3 > cand2 && cand3 > cand1) {
		return 3;
	}
	else {
		return 0;
	}
}

auto exercicio3(const char* cstr) {
	float soma = 0.0, media = 0.0, max = -99999.0, min = 99999.0, num;
	int cont;

	sscanf_s(cstr, "%d", &cont);
	//scanf_s("%d", &cont);
	for (int i = 0; i < cont; i++) {
		scanf_s("%f", &num);
		soma += num;
		if (num > max) {
			max = num;
		}
		if (num < min) {
			min = num;
		}

	}
	media = soma / cont;
	return std::make_tuple(soma, media, max, min);
}

int exercicio4(const char* cstr) {
	int cont, aluno;
	float nota[100];
	std::string name(100, ' ');;
	sscanf_s(cstr, "%d", &cont);
	//scanf_s("%d", &cont);
	for (int i = 1; i <= cont; i++) {
		sscanf_s(cstr, "%f", &nota[i]);
		sscanf_s(cstr, "%*s", &name[i]);
		//scanf_s("%f ", &nota[i]);
		//scanf_s("%*s", &name[i]);

	}
	sscanf_s(cstr, "%d", &aluno);
	//scanf_s("%d", &aluno);
	if (nota[aluno] >= 6.0) {
		return 1;
	}
	else {
		return 0;
	}
}

int exercicio5(const char* cstr) {
	int num, fat = 1;
	sscanf_s(cstr, "%d", &num);
	//scanf_s("%d", &num);
	for (int i = 1; i <= num; i++) {
		fat *= i;
	}
	return fat;
}

int exercicio6(const char* cstr) {
	int num;
	sscanf_s(cstr, "%d", &num);
	//scanf_s("%d", &num);
	int a = 1, b = 1, x;
	if (num == 1) {
		x = a;
	}
	if (num == 2) {
		x = b;
	}
	for (int i = 3;i <= num;i++) {
		x = a + b;
		a = b;
		b = x;
	}
	return x;
}

char exercicio7(const char* cstr) {
	int cont;
	int contM = 0, contJ = 0;
	char maria;
	char joao;
	sscanf_s(cstr, "%d", &cont);
	//scanf_s("%d", &cont);
	for (int i = 0; i < cont; i++) {
		sscanf_s(cstr, "%d", &maria);
		sscanf_s(cstr, "%d", &joao);
		//cin >> maria;
		//cin >> joao;

		if ((maria == 'd') && (joao == 't')) {
			contM += 1;
		}
		else if (maria == 'p' && joao == 'd') {
			contM += 1;
		}
		else if (maria == 't' && joao == 'p') {
			contM += 1;
		}
		else if (maria == 't' && joao == 'd') {
			contJ += 1;
		}
		else if (maria == 'd' && joao == 'p') {
			contJ += 1;
		}
		else if (maria == 'p' && joao == 't') {
			contJ += 1;
		}
		else {}
	}
	if (contM >= contJ) {
		return 'M';
	}
	else {
		return 'J';
	}

}

auto exercicio8(const char* cstr) {
	int A, B, aux;
	int* p = &A, * b = &B;
	sscanf_s(cstr, "%d %d", &A, &B);
	//scanf_s(" %d %d", &A, &B);
	aux = A;
	*p = B;
	*b = aux;
	return std::make_tuple(A,B);
}

float exercicio9(const char* cstr) {
	int cont;
	float num;
	float* arr;
	float mediana;
	sscanf_s(cstr, "%d", &cont);
	//scanf_s("%d", &cont);
	arr = new float[cont];
	for (int i = 0; i < cont; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + (cont));
	if (cont % 2 != 0) {
		mediana = arr[(cont / 2)];
	}
	else {
		mediana = ((arr[cont / 2]) + (arr[((cont / 2) - 1)])) / 2;
	}
	return mediana;

}
