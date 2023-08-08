#ifndef HOADONNHAP_H
#define HOADONNHAP_H

#include <stdio.h>
#include <string.h>
#include "ds_nhacungcap.h"
#include "ds_chitiethoadonnhap.h"
#include "utils.h"

struct HoaDonNhap
{
	char id[8];
	char ngaynhap[12];
	char id_nhacungcap[8];
	int tongsotien;
};
typedef struct HoaDonNhap HoaDonNhap_t;

void hdn_tinhtien(HoaDonNhap_t* hdn, DSChiTietHoaDonNhap_t* dscthdn)
{
	int i, size = dscthdn->soluong;
	int sotien = 0;
	for (i = 0; i < size; ++i)
	{
		ChiTietHoaDonNhap_t *cthdn = &dscthdn->chitiethoadonnhap[i];
		if (strcmp(cthdn->id_hoadonnhap, hdn->id) == 0)
		{
			sotien +=  cthdn->soluong * cthdn->dongia;
		}
	}
	hdn->tongsotien = sotien;
}

void hdn_nhap(HoaDonNhap_t* hdn)
{
	printf("Nhap ma: ");
	gets(hdn->id);
	printf("Nhap ngay nhap (ngay/thang/nam): ");
	gets(hdn->ngaynhap);
	printf("Nhap ID nha cung cap: ");
	gets(hdn->id_nhacungcap);
	hdn->tongsotien = 0;
}

void hdn_hienthi(DSNhaCungCap_t* dsncc, DSChiTietHoaDonNhap_t* dscthdn, HoaDonNhap_t* hdn)
{
	hdn_tinhtien(hdn, dscthdn);
	printf("|%8s|%12s|%40s|%14d|\n", hdn->id, hdn->ngaynhap,
		dsncc_query(dsncc, hdn->id_nhacungcap), hdn->tongsotien);
}

void hdn_gachngang()
{
	printf("+");
	print_gachngang(8);
	printf("+");
	print_gachngang(12);
	printf("+");
	print_gachngang(40);
	printf("+");
	print_gachngang(14);
	printf("+\n");
}

void hdn_tieude()
{
	printf("|%8s|%12s|%40s|%14s|\n", "MA", "NGAY_NHAP", "NHA_CUNG_CAP", "TONG_SO_TIEN");
}

void hdn_saochep(HoaDonNhap_t* x, HoaDonNhap_t* y)
{
	strcpy(x->id, y->id);
	strcpy(x->ngaynhap, y->ngaynhap);
	strcpy(x->id_nhacungcap, y->id_nhacungcap);
	x->tongsotien = y->tongsotien;
}

#endif
