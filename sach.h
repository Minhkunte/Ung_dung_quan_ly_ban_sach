#ifndef SACH_H
#define SACH_H

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "ds_loaisach.h"

struct Sach
{
	char id[8];
	char ten[30];
	char id_loai[8];
	char tacgia[20];
	char nhaxuatban[20];
	int soluongtonkho;
	int dongia;
};
typedef struct Sach Sach_t;


void s_nhap(Sach_t* s)
{
	printf("Nhap ma: ");
	gets(s->id);
	printf("Nhap ten: ");
	gets(s->ten);
	printf("Nhap ID loai sach: ");
	gets(s->id_loai);
	printf("Nhap tac gia: ");
	gets(s->tacgia);
	printf("Nhap nha xuat ban: ");
	gets(s->nhaxuatban);
	
	printf("Nhap so luong ton kho: ");
	scanf("%d",&s->soluongtonkho);
	if (s->soluongtonkho < 0)
		s->soluongtonkho = 0;
		
	printf("Nhap don gia: ");
	scanf("%d",&s->dongia);
	if (s->dongia < 0)
		s->dongia = 0;
		
	fflush(stdin);
}

void s_hienthi(DSLoaiSach_t* dsls, Sach_t* s)
{
	printf("|%8s|%30s|%15s|%20s|%20s|%5d|%8d|\n",
		s->id, s->ten, dsls_query(dsls, s->id_loai), s->tacgia,
		s->nhaxuatban, s->soluongtonkho, s->dongia);
}

void s_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(30);
	printf("+");
	print_gachngang(15);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(5);
	printf("+");
	print_gachngang(8);
	printf("+\n");
}

void s_tieude()
{
	printf("|%8s|%30s|%15s|%20s|%20s|%5s|%8s|\n",
		"MA", "TEN", "LOAI_SACH", "TAC_GIA", "NSB", "SL", "GIA");
}

void s_saochep(Sach_t* x, Sach_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->ten, y->ten);
	strcpy(x->id_loai, y->id_loai);
	strcpy(x->tacgia, y->tacgia);
	strcpy(x->nhaxuatban, y->nhaxuatban);
	x->soluongtonkho = y->soluongtonkho;
	x->dongia = y->dongia;
}


#endif
