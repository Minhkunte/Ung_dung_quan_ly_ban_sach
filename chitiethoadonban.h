#ifndef CHITIETHOADONBAN_H
#define CHITIETHOADONBAN_H

#include <stdio.h>
#include <string.h>
#include "ds_sach.h"
#include "utils.h"

struct ChiTietHoaDonBan
{
	char id[8];
	char id_sach[8];
	char id_hoadonban[8];
	int soluong;
	int dongia;
};
typedef struct ChiTietHoaDonBan ChiTietHoaDonBan_t;


void cthdb_nhap(DSSach_t* dss, ChiTietHoaDonBan_t* cthdb)
{
	printf("Nhap ma: ");
	gets(cthdb->id);
	printf("Nhap ID sach: ");
	gets(cthdb->id_sach);
	
	int index = dss_timkiem(dss, cthdb->id_sach);
	if (index < 0)
	{
		printf("ERROR: ID sach khong ton tai\n");
		cthdb->dongia = 0;
	}
	else
	{
		cthdb->dongia = dss->sach[index].dongia;
	}
	
	printf("Nhap ID hoa don ban: ");
	gets(cthdb->id_hoadonban);
	printf("Nhap so luong: ");
	scanf("%d", &cthdb->soluong);
	fflush(stdin);
}

void cthdb_hienthi(DSSach_t *dss, ChiTietHoaDonBan_t* cthdb)
{
	printf("|%8s|%30s|%8s|%5d|%8d|%14d|\n", cthdb->id, 
		dss_query(dss, cthdb->id_sach), cthdb->id_hoadonban,
		cthdb->soluong, cthdb->dongia,
		cthdb->soluong*cthdb->dongia);
}

void cthdb_gachngang()
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
	printf("+");
	print_gachngang(14);
	printf("+\n");
}

void cthdb_tieude()
{
	printf("|%8s|%30s|%8s|%5s|%8s|%14s|\n", "MA", "TEN_SACH", "ID_HDB", "SL", "GIA", "THANH_TIEN");
}

void cthdb_saochep(ChiTietHoaDonBan_t* x, ChiTietHoaDonBan_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->id_sach, y->id_sach);
	strcpy(x->id_hoadonban, y->id_hoadonban);
	x->soluong = y->soluong;
	x->dongia = y->dongia;
}


#endif
