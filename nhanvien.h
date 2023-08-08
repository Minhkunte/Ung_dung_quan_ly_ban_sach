#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <stdio.h>
#include <string.h>
#include "utils.h"

struct NhanVien
{
	char id[8];
	char ten[20];
	int gioitinh;
	int namsinh;
	char diachi[40];
};
typedef struct NhanVien NhanVien_t;


void nv_nhap(NhanVien_t* nv)
{
	printf("Nhap ma: ");
	gets(nv->id);
	printf("Nhap ten: ");
	gets(nv->ten);
	
	printf("Nhap gioi tinh (1:nam, 0:nu): ");
	scanf("%d",&nv->gioitinh);
	if (nv->gioitinh != 0)
		nv->gioitinh = 1;
	
	printf("Nhap nam sinh (1900-2010): ");
	scanf("%d",&nv->namsinh);
	if (nv->namsinh < 1900)
		nv->namsinh = 1900;
	else if (nv->namsinh > 2010)
		nv->namsinh = 2010;
		
	fflush(stdin);
	printf("Nhap dia chi: ");
	gets(nv->diachi);
}

void nv_hienthi(NhanVien_t* nv)
{
	printf("|%8s|%20s|%6d|%6d|%40s|\n", nv->id, nv->ten, nv->gioitinh, nv->namsinh, nv->diachi);
}

void nv_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(6);
	printf("+");
	print_gachngang(6);
	printf("+");
	print_gachngang(40);
	printf("+\n");
}

void nv_tieude()
{
	printf("|%8s|%20s|%6s|%6s|%40s|\n", "MA", "TEN", "GT", "NS", "DIA_CHI");
}

void nv_saochep(NhanVien_t* x, NhanVien_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->ten, y->ten);
	x->gioitinh = y->gioitinh;
	x->namsinh = y->namsinh;
	strcpy(x->diachi, y->diachi);
}


#endif
