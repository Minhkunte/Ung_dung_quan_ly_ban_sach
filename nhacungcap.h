#ifndef NHACUNGCAP_H
#define NHACUNGCAP_H
#include "utils.h"

struct NhaCungCap
{
	char id[8];
	char ten[40];
	char diachi[40];
	char sodienthoai[12];
};
typedef struct NhaCungCap NhaCungCap_t;

void ncc_nhap(NhaCungCap_t* ncc)
{
	printf("Nhap ma: ");
	gets(ncc->id);
	printf("Nhap ten: ");
	gets(ncc->ten);
	printf("Nhap dia chi: ");
	gets(ncc->diachi);
	printf("Nhap so dien thoai: ");
	gets(ncc->sodienthoai);
}

void ncc_hienthi(NhaCungCap_t* ncc)
{
	printf("|%8s|%40s|%40s|%12s|\n", ncc->id, ncc->ten, ncc->diachi, ncc->sodienthoai);
}

void ncc_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(40);
	printf("+");
	print_gachngang(40);
	printf("+");
	print_gachngang(12);
	printf("+\n");
}

void ncc_tieude()
{
	printf("|%8s|%40s|%40s|%12s|\n", "MA", "TEN", "DIA_CHI", "SDT");
}

void ncc_saochep(NhaCungCap_t* x, NhaCungCap_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->ten, y->ten);
	strcpy(x->diachi, y->diachi);
	strcpy(x->sodienthoai, y->sodienthoai);
}

#endif
