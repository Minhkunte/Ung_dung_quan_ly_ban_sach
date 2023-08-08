#ifndef LOAISACH_H
#define LOAISACH_H

#include <stdio.h>
#include <string.h>
#include "utils.h"

struct LoaiSach
{
	char id[8];
	char ten[20];
	char mota[40];
};
typedef struct LoaiSach LoaiSach_t;


void ls_nhap(LoaiSach_t* ls)
{
	printf("Nhap ma: ");
	gets(ls->id);
	printf("Nhap ten: ");
	gets(ls->ten);
	printf("Nhap mo ta: ");
	gets(ls->mota);
}

void ls_hienthi(LoaiSach_t* ls)
{
	printf("|%8s|%20s|%40s|\n", ls->id, ls->ten, ls->mota);
}

void ls_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(40);
	printf("+\n");
}

void ls_tieude()
{
	printf("|%8s|%20s|%40s|\n", "MA", "TEN", "MO_TA");
}

void ls_saochep(LoaiSach_t* x, LoaiSach_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->ten, y->ten);
	strcpy(x->mota, y->mota);
}


#endif
