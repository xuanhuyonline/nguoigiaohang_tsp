#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h>
#include<string.h>
#include <array>

#define MAX  100

using namespace std;

struct Dinh
{
	char ten;
	int hd, td;
};

struct Canh
{
	Dinh Dau;
	Dinh Cuoi;
	float kc;
	bool check;
};

void docFile(Dinh dsDinh[], int& nDinh, char& batdau)
{
	const char* filename = "../Data/input.txt";
	ifstream in;
	in.open(filename);
	if (in)
	{
		in >> nDinh;
		for (int i = 0; i < nDinh; i++)
		{
			in >> dsDinh[i].ten;
			in >> dsDinh[i].hd;
			in >> dsDinh[i].td;
		}
		in >> batdau;
	}
	else
	{
		printf("file loi ");
		return;
	}
	in.close();
}

void xuatFile(Dinh dsDinh[], int nDinh, char batdau)
{
	printf("\n");
	printf("Diem bat dau %c\n", batdau);
	for (int i = 0; i < nDinh; i++)
	{
		printf("%c %d %d\n", dsDinh[i].ten, dsDinh[i].hd, dsDinh[i].td);
	}
}

void taoDSCanh(Dinh dsDinh[], int nDinh, Canh dsCanh[], int &nCanh)
{
	float kc;
	nCanh = 0;
	for (int i = 0; i < nDinh; i++)
		for (int j = 0; j < nDinh; j++)
		{
			dsCanh[nCanh].Dau = dsDinh[i];
			dsCanh[nCanh].Cuoi = dsDinh[j];
			if (dsCanh[nCanh].Dau.ten != dsCanh[nCanh].Cuoi.ten)
			{
				kc = (float)sqrt(pow((double)dsDinh[j].hd - (double)dsDinh[i].hd, 2) + pow((double)dsDinh[j].td - dsDinh[i].td, 2));
				dsCanh[nCanh].kc = kc;
				dsCanh[nCanh].check = true;
				nCanh++;
			}
		}
}

void xuatDSCanh(Canh dsCanh[], int& nCanh)
{
	printf("\n\nDau\tCuoi\tKC");
	for (int i = 0; i < nCanh; i++)
	{
		printf("\n");
		printf("%c", dsCanh[i].Dau.ten);
		printf("\t%c", dsCanh[i].Cuoi.ten);
		printf("\t%.2f", dsCanh[i].kc);
	}
}

bool kiemTraTrung(char chuTrinh[], char cuoi)
{
	//int lengh = (sizeof chuTrinh / sizeof(char))-3;
	/*int lengh = strlen(chuTrinh);*/
	for (int i = 0; i < 6; i++)
	{
		if (cuoi == chuTrinh[i])
			return false;
	}
	return true;
}

int timDinhGanNhat(Dinh dsDinh[], int nDinh, Canh dsCanh[],int nCanh , char x, char chuTrinh[])
{
	bool temp = true;
	float min;
	int vt=-1;
	for (int i = 0; i < nCanh; i++)
	{
		if (dsCanh[i].check == true)
		{
			if (x == dsCanh[i].Dau.ten)
			{
				dsCanh[i].check = false;
				if (temp == true && kiemTraTrung(chuTrinh, dsCanh[i].Cuoi.ten) == true)
				{
					min = dsCanh[i].kc;
					temp = false;
					vt = i;
				}
				else if (temp == false && dsCanh[i].kc < min && kiemTraTrung(chuTrinh, dsCanh[i].Cuoi.ten) == true)
				{
					min = dsCanh[i].kc;
					vt = i;
				}
			}
			/*if (x == dsCanh[i].Dau.ten && temp == true && kiemTraTrung(chuTrinh,dsCanh[i].Cuoi.ten)==true)
			{
				min = dsCanh[i].kc;
				temp = false;
				vt = i;
				dsCanh[i].check = false;
			}
			else if (x == dsCanh[i].Dau.ten && temp == false && dsCanh[i].kc < min && kiemTraTrung(chuTrinh, dsCanh[i].Cuoi.ten) == true)
			{
				min = dsCanh[i].kc;
				vt = i;
				dsCanh[i].check = false;
			}*/
		}
	}
	return vt;
}

float taoChuTrinhVaTinhKC(Dinh dsDinh[], int nDinh, Canh dsCanh[], int nCanh, char batdau, char chuTrinh[])
{
	float s = 0;
	chuTrinh[0] = batdau;
	int tam;
	for (int i = 1; i < nDinh; i++)
	{
		tam = timDinhGanNhat(dsDinh, nDinh, dsCanh,nCanh,batdau,chuTrinh);
		chuTrinh[i] = dsCanh[tam].Cuoi.ten; //d a
		//dsCanh[tam].check = false;
		s = s + dsCanh[tam].kc;
		batdau = dsCanh[tam].Cuoi.ten;
	}

	for (int i = 0; i < nCanh; i++)
	{
		if (batdau == dsCanh[i].Dau.ten && chuTrinh[0] == dsCanh[i].Cuoi.ten && dsCanh[i].check ==true)
		{
			chuTrinh[nDinh] = dsCanh[i].Cuoi.ten;
			//dsCanh[i].check = false;
			s = s + dsCanh[i].kc;
			return s;
		}
	}
	return s;
}

void xuatChuTrinh(int nDinh, char chuTrinh[])
{
	printf("\n%c", chuTrinh[0]);
	for (int i = 1; i <= nDinh; i++)
	{
		printf("--> %c", chuTrinh[i]);
	}
}
//------------------------------------------------------------
int timVtMin(Canh dsCanh[], int nCanh)
{
	float min = dsCanh[0].kc;
	int vt = -1;
	for (int i = 1; i < nCanh; i++)
	{
		if (dsCanh[i].Dau.ten != dsCanh[i].Cuoi.ten && dsCanh[i].kc < min)
		{
			min = dsCanh[i].kc;
			vt = i;
		}
	}
	dsCanh[vt].check = false;
	return vt;
}

float chonCanhNN(Dinh dsDinh[], int nDinh, Canh dsCanh[], int nCanh,char chuTrinh1[])
{
	char xuatPhat;
	float s = 0;
	int vt = timVtMin(dsCanh, nCanh);
	/*int dinhDau = timDinhGanNhat(dsDinh, nDinh, dsCanh, nCanh, dsCanh[vt].Dau.ten, chuTrinh1);
	int dinhCuoi = timDinhGanNhat(dsDinh, nDinh, dsCanh, nCanh, dsCanh[vt].Cuoi.ten, chuTrinh1);

	if (dsCanh[dinhDau].kc > dsCanh[dinhCuoi].kc || dsCanh[dinhDau].kc == dsCanh[dinhCuoi].kc)
	{
		chuTrinh1[0] = dsCanh[vt].Dau.ten;
		chuTrinh1[1] = dsCanh[vt].Cuoi.ten;
		chuTrinh1[2] = dsCanh[dinhCuoi].Cuoi.ten;
		xuatPhat = chuTrinh1[2];
	}
	else
	{
		chuTrinh1[0] = dsCanh[vt].Cuoi.ten;
		chuTrinh1[1] = dsCanh[vt].Dau.ten;
		chuTrinh1[2] = dsCanh[dinhDau].Cuoi.ten;
		xuatPhat = chuTrinh1[2];
	}
	s = s + dsCanh[vt].kc;
	int tam;*/

	chuTrinh1[0] = dsCanh[vt].Dau.ten;
	chuTrinh1[1] = dsCanh[vt].Cuoi.ten;
	s = s + dsCanh[vt].kc;
	int tam;
	xuatPhat= chuTrinh1[1];
	for (int i = 2; i < nDinh; i++)
	{
		tam = timDinhGanNhat(dsDinh, nDinh, dsCanh, nCanh, xuatPhat, chuTrinh1);
		chuTrinh1[i] = dsCanh[tam].Cuoi.ten;
		//dsCanh[tam].check = false;
		s = s + dsCanh[tam].kc;
		xuatPhat = dsCanh[tam].Cuoi.ten;
	}

	for (int i = 0; i < nCanh; i++)
	{
		if (xuatPhat == dsCanh[i].Dau.ten && chuTrinh1[0] == dsCanh[i].Cuoi.ten && dsCanh[i].check == true)
		{
			chuTrinh1[nDinh] = dsCanh[i].Cuoi.ten;
			//dsCanh[i].check = false;
			s = s + dsCanh[i].kc;
			return s;
		}
	}
	return s;
}

void main()
{
	Dinh dsDinh[MAX];
	Canh dsCanh[MAX];
	int nDinh = 0;
	int nCanh = 0;
	char batdau;
	char chuTrinh[100];
	char chuTrinh1[100];
	float tong;

	int chon;
	do
	{
		printf("\nchon cau so: ");
		scanf_s("%d", &chon);
		switch (chon)
		{
		case 1://chon dinh bat ky
			docFile(dsDinh, nDinh, batdau);
			xuatFile(dsDinh, nDinh, batdau);
			taoDSCanh(dsDinh, nDinh, dsCanh, nCanh);
			xuatDSCanh(dsCanh, nCanh);
			tong = taoChuTrinhVaTinhKC(dsDinh, nDinh, dsCanh, nCanh, batdau, chuTrinh);
			xuatChuTrinh(nDinh, chuTrinh);
			printf("\ntong quang duong di la %f", tong);
			break;
		case 2:// tu chon canh bat ky de bat dau
			docFile(dsDinh, nDinh, batdau);
			xuatFile(dsDinh, nDinh, batdau);
			taoDSCanh(dsDinh, nDinh, dsCanh, nCanh);
			xuatDSCanh(dsCanh, nCanh);
			tong = chonCanhNN(dsDinh, nDinh, dsCanh, nCanh, chuTrinh1);
			xuatChuTrinh(nDinh, chuTrinh1);
			printf("\ntong quang duong di la %f", tong);
			break;

		}
	} while (chon > 0);

	_getch();
}
