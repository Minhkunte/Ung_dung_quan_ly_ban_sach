#ifndef CHITIETHOADONNHAP_H
#define CHITIETHOADONNHAP_H

#include <stdio.h>
#include <string.h>
#include "ds_sach.h"
#include "utils.h"

struct ChiTietHoaDonNhap
{
	char id[8];
	char id_sach[8];
	char id_hoadonnhap[8];
	int soluong;
	int dongia;
};
typedef struct ChiTietHoaDonNhap ChiTietHoaDonNhap_t;


void cthdn_nhap(ChiTietHoaDonNhap_t* cthdn)
{
	printf("Nhap ma: ");
	gets(cthdn->id);
	printf("Nhap ID sach: ");
	gets(cthdn->id_sach);
	printf("Nhap ID hoa don nhap: ");
	gets(cthdn->id_hoadonnhap);
	printf("Nhap so luong: ");
	scanf("%d", &cthdn->soluong);
	printf("Nhap don gia: ");
	scanf("%d", &cthdn->dongia);
	fflush(stdin);
}

void cthdn_hienthi(DSSach_t *dss, ChiTietHoaDonNhap_t* cthdn)
{
	printf("|%8s|%30s|%8s|%5d|%8d|\n", cthdn->id, 
		dss_query(dss, cthdn->id_sach), cthdn->id_hoadonnhap,
		cthdn->soluong, cthdn->dongia);
}

void cthdn_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(30);
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(5);
	printf("+");
	print_gachngang(8);
	printf("+\n");
}

void cthdn_tieude()
{
	printf("|%8s|%30s|%8s|%5s|%8s|\n", "MA", "TEN_SACH", "ID_HDN", "SL", "GIA");
}

void cthdn_saochep(ChiTietHoaDonNhap_t* x, ChiTietHoaDonNhap_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->id_sach, y->id_sach);
	strcpy(x->id_hoadonnhap, y->id_hoadonnhap);
	x->soluong = y->soluong;
	x->dongia = y->dongia;
}


#endif
