#include <stdio.h>
#include <iostream>
#include <fstream>
#define M 9999
using namespace std;

int nl, ns, linetrash, nts; 
int transl, transs; 
int *strans; 
int *etrans;
int *num; 
int **D;
int data; 
int *transt; 
int *startst; 
int *endst; 
int start_transl, start_transs; 
int desti_transl, desti_transs;

ifstream f("input.txt");

int dijkstra(int data_num){

	int *length = new int[ns + 1];
	int *result = new int[ns + 1];
	int vnear,min;
	int start, desti, duration;
	int repeat = 0;

	start = startst[data_num];
	desti = endst[data_num];

	for (int i = 0; i <= ns; i++){
		length[i] = D[start][i];
		result[i] = D[start][i];
	}

	while (repeat <= (ns-1)){
		min = M;
		for (int i = 0; i <= ns; i++){
			if ((i != start) && (0 <= length[i]) && (length[i] < min)){ // 시작점이 아니면서
				min = length[i];
				vnear = i;
				min = result[i];
			}
		}
		for (int i = 0; i <= ns; i++){
			if (length[vnear] + D[vnear][i] < length[i]){
				length[i] = length[vnear] + D[vnear][i];
				result[i] = result[vnear] + D[vnear][i];
			}
		}
		length[vnear] = -1;
		repeat++;
	}
	duration = result[desti];
	delete[] length;
	delete[] result;
	return duration;
}
int addstationnumber(int transl, int transs)
{
	for (int m = 0; m <= (transl-1); m++){
		int temp = num[m];
		transs = temp + transs;
	}
	return transs;
}
int main(){

	f >> nl;
	num = new int[nl + 1];

	num[0] = 0;
	for (int i = 1; i <= nl; i++){
		f >> linetrash;
		f >> num[i];
		ns += num[i];
	}

	D = new int *[ns + 1];
	for (int i = 0; i <= ns; i++){
		D[i] = new int[ns + 1];
	}

	f >> nts;
	int *strans = new int[nts];
	int *etrans = new int[nts];

	for (int i = 0; i <= (nts -1) ; i++){
		f >> transl;
		f >> transs;
		strans[i] = addstationnumber(transl, transs);

		f >> transl;
		f >> transs;
		etrans[i] = addstationnumber(transl, transs);
	}

	f >> data;
	transt = new int[data];
	startst = new int[data];
	endst = new int[data];

	for (int i = 0; i <= (data-1); i++){
		f >> transt[i];
		f >> start_transl;
		f >> start_transs;
		startst[i] = addstationnumber(start_transl, start_transs);

		f >> desti_transl;
		f >> desti_transs;
		endst[i] = addstationnumber(desti_transl, desti_transs);
	}

	for (int j = 0; j <= (data-1); j++){

		for (int a = 0; a <= ns; a++){
			for (int b = 0; b <= ns; b++){
				D[a][b] =  M ;
			}
		}

		for (int i = 1; i <= ns; i++){
			
			D[i][i] = 0;

			if (i < ns)
				D[i][i + 1] = 1;

			if (i > 1)
				D[i][i - 1] = 1;
		}

		for (int i = 0; i <= (nts-1); i++){
			D[strans[i]][etrans[i]] = transt[j];
			D[etrans[i]][strans[i]] = transt[j];
		}

		int remove = 0;
		for (int m = 1; m <= (nl-1); m++){
			int temp = num[m];
			remove = temp + remove;
			D[remove][remove + 1] = M;
			D[remove + 1][remove] = M;
		}
		cout << dijkstra(j) << endl;
	}
	
	for (int k = 0; k < (ns + 1); k++){
		delete[] D[k];
	}
	delete[] D;
	delete[] num;
	delete[] transt;
	delete[] startst;
	delete[] endst;
	delete[] strans;
	delete[] etrans;

	return 0;
}
