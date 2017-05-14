#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "Sinhvien.dat"

typedef struct SinhVien {
	char HoTen[20];
	int Tuoi;
	char Lop[20];
} SinhVien;


//Menu chinh
void menu();

void nhapDanhSachSinhVien();

void hienThiDanhSachSinhVien();

void timkiemTheoTen();

//tra ve 1 neu tim thay, 0 neu khong tim thay
int timTen(char *strHoVaTen, char *strTen);

int main(int agrc, char** argv) {
	menu();

	return 0;
}

//implement
void menu() {
	int choice;

	while (1) {
		printf("Chon lua chuc nang\n");
		printf("1. Chon 1 de Nhap danh sach sinh vien\n");
		printf("2. Chon 2 de Hien thi danh sach sinh vien\n");
		printf("3. Chon 4 de tim kiem sinh vien theo ten\n");
		printf("4. Chon 3 de Ket thuc\n");
			
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			nhapDanhSachSinhVien();
			break;
		case 2:
			hienThiDanhSachSinhVien();
			break;
		case 3: 
			exit(1);
			break;
		case 4:
			timkiemTheoTen();
			break;
		default:
			break;
		}

		//pause screen to view
		getch();
		system("cls");
	}
}

void nhapDanhSachSinhVien() {
	int i;
	int soluongSV;
	SinhVien *sv;
	FILE* file;

	printf("Nhap so luong sinh vien: ");
	scanf("%d", &soluongSV);
	
	sv = (SinhVien*)malloc(sizeof(SinhVien) * soluongSV);


	for (i = 0; i < soluongSV; i++) {
		printf("Nhap sinh vien thu %d:\n", i + 1);

		fflush(stdin);
		printf("Ho va ten: ");
		gets(sv[i].HoTen);

		printf("Tuoi: ");
		scanf("%d", &sv[i].Tuoi);
		fflush(stdin);

		printf("Lop hoc: ");
		gets(sv[i].Lop);
	}

	//write to file
	file = fopen(FILE_NAME, "wb");

	if (file != NULL) {
		fwrite(sv, sizeof(SinhVien), soluongSV, file);
		fclose(file);
	}
	else {
		printf("Can not open this file!\n");
	}

	free(sv);
}

void hienThiDanhSachSinhVien() {
	SinhVien sv;
	FILE* file;
	int cosv;

	cosv = 0;

	//read from a file
	file = fopen(FILE_NAME, "rb");

	if (file != NULL) {
		printf("-------HO TEN--------|----TUOI-----|---------LOP---------|\n");

		while (1) {
			fread(&sv, sizeof(SinhVien), 1, file);
			if (!feof(file))
			{
				cosv = 1;
				printf("%20s |%12d |%20s |\n", sv.HoTen, sv.Tuoi, sv.Lop);
			}
			else
				break;
		}

		if (cosv == 0)
			printf("Khong co sinh vien nao!\n");

		printf("----------------------------------------------------------\n");
		fclose(file);
	}
	else {
		printf("Can not open this file!\n");
	}
}

void timkiemTheoTen() {
	char strName[20];
	SinhVien sv;
	FILE* file;
	int cosv;
	cosv = 0;

	printf("Nhap ten sinh vien can tim: ");
	fflush(stdin);
	gets(strName);

	//read from a file
	file = fopen(FILE_NAME, "rb");

	if (file != NULL) {
		printf("-------HO TEN--------|----TUOI-----|---------LOP---------|\n");

		while (1) {
			fread(&sv, sizeof(SinhVien), 1, file);
			if (!feof(file))
			{
				
				if (timTen(sv.HoTen, strName) == 1) {
					cosv = 1;
					printf("%20s |%12d |%20s |\n", sv.HoTen, sv.Tuoi, sv.Lop);
				}
			}
			else
				break;
		}

		if (cosv == 0)
			printf("Khong co sinh vien nao!\n");

		printf("----------------------------------------------------------\n");
		fclose(file);
	}
	else {
		printf("Can not open this file!\n");
	}
}

int timTen(char *strHoVaTen, char *strTen) {
	int lenHoVaTen;
	int lenTen;
	int i, j;
	int minLen;
	char *strTemp;
	int lenTemp;
	int value;

	value = 1;
	lenTemp = 0;
	j = 0;

	lenHoVaTen = strlen(strHoVaTen);
	lenTen = strlen(strTen);

	minLen = lenHoVaTen <= lenTen ? lenHoVaTen : lenTen;

	//Chuyen het thanh chu hoa
	for (i = 0; i < lenHoVaTen; i++) {
		if ((strHoVaTen[i] >= 'a') && (strHoVaTen[i] <= 'z'))
			strHoVaTen[i] = strHoVaTen[i] - 32;
	}

	for (i = 0; i < lenTen; i++) {
		if ((strTen[i] >= 'a') && (strTen[i] <= 'z'))
			strTen[i] = strTen[i] - 32;
	}

	//tim kiem ten trong ho va ten
	for (i = lenHoVaTen - 1; i >= 0; i--)
	{
		if (strHoVaTen[i] == ' ')
			break;

		lenTemp++;
	}

	j = lenTemp - 1;

	if (minLen != lenTemp) {
		value = 0;
		return value;
	}

	strTemp = (char*)malloc(sizeof(char) * (lenTemp+ 1));

	for (i = lenHoVaTen - 1; i >= 0; i--)
	{
		if (strHoVaTen[i] == ' ')
			break;

		strTemp[j] = strHoVaTen[i];
		j--;
	}
	
	strTemp[lenTemp] = '\0';


	//so sanh ten va ten trong ho ten

	for (j = 0; j < lenTemp; j++)
	{
		if (strTemp[j] != strTen[j]) {
			value = 0;
			break;
		}
	}

	free(strTemp);

	return value;
	
}