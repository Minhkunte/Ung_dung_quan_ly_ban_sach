#ifndef HOADONBAN_H
#define HOADONBAN_H

#include <stdio.h>
#include <string.h>
#include "ds_chitiethoadonban.h"
#include "utils.h"

struct HoaDonBan
{
	char id[8];
	char id_nhanvien[8];
	char ngaylap[12];
	char tenkhachhang[20];
	char diachi[40];
	int tongsotien;
};
typedef struct HoaDonBan HoaDonBan_t;

void hdb_tinhtien(HoaDonBan_t* hdb, DSChiTietHoaDonBan_t* dscthdb)
{
	int i, size = dscthdb->soluong;
	int sotien = 0;
	for (i = 0; i < size; ++i)
	{
		ChiTietHoaDonBan_t *cthdb = &dscthdb->chitiethoadonban[i];
		if (strcmp(cthdb->id_hoadonban, hdb->id) == 0)
		{
			sotien += cthdb->soluong * cthdb->dongia;
		}
	}
	hdb->tongsotien = sotien;
}

void hdb_nhap(HoaDonBan_t* hdb)
{
	char id[8];
	char id_nhanvien[8];
	char ngaylap[12];
	char tenkhachhang[20];
	char diachi[40];
	int tongsotien;
	
	printf("Nhap ma: ");
	gets(hdb->id);
	printf("Nhap ID nhan vien: ");
	gets(hdb->id_nhanvien);
	printf("Nhap ngay lap (ngay/thang/nam): ");
	gets(hdb->ngaylap);
	printf("Nhap ten khach hang: ");
	gets(hdb->tenkhachhang);
	printf("Nhap dia chi: ");
	gets(hdb->diachi);
	hdb->tongsotien = 0;
}

void hdb_hienthi(DSNhanVien_t* dsnv, DSChiTietHoaDonBan_t* dscthdb, HoaDonBan_t* hdb)
{
	hdb_tinhtien(hdb, dscthdb);
	printf("|%8s|%20s|%12s|%20s|%34s|%14d|\n", hdb->id,
		dsnv_query(dsnv, hdb->id_nhanvien), hdb->ngaylap,
		hdb->tenkhachhang, hdb->diachi, hdb->tongsotien);
}

void hdb_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(12);
	printf("+");
	print_gachngang(20);
	printf("+");
	print_gachngang(34);
	printf("+");
	print_gachngang(14);
	printf("+\n");
}

void hdb_tieude()
{
	printf("|%8s|%20s|%12s|%20s|%34s|%14s|\n",
		"MA", "NHAN_VIEN", "NGAY_LAP", "KHACH_HANG", "DIA_CHI", "TONG_SO_TIEN");
}

void hdb_saochep(HoaDonBan_t* x, HoaDonBan_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->id_nhanvien, y->id_nhanvien);
	strcpy(x->ngaylap, y->ngaylap);
	strcpy(x->tenkhachhang, y->tenkhachhang);
	strcpy(x->diachi, y->diachi);
	x->tongsotien = y->tongsotien;
}

#endif
