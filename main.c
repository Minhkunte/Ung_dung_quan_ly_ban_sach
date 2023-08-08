#include <stdio.h>
#include <stdlib.h>
#include "ds_nhacungcap.h"
#include "ds_nhanvien.h"
#include "ds_loaisach.h"
#include "ds_sach.h"
#include "ds_hoadonnhap.h"
#include "ds_chitiethoadonnhap.h"
#include "ds_hoadonban.h"
#include "ds_chitiethoadonban.h"
#include "timkiem.h"

int menu();

int main()
{
	DSNhaCungCap_t dsncc;
	DSNhanVien_t dsnv;
	DSLoaiSach_t dsls;
	DSSach_t dss;
	DSHoaDonNhap_t dshdn;
	DSChiTietHoaDonNhap_t dscthdn;
	DSHoaDonBan_t dshdb;
	DSChiTietHoaDonBan_t dscthdb;
	
	dsncc_load(&dsncc);
	dsnv_load(&dsnv);
	dsls_load(&dsls);
	dss_load(&dss);
	dshdn_load(&dshdn);
	dscthdn_load(&dscthdn, &dss);
	dshdb_load(&dshdb);
	dscthdb_load(&dscthdb, &dss);
	
	int c;
	do
	{
		c = menu();
		switch(c) {
		case 1:
			{
				dsncc_quanly(&dsncc);
				break;
			}
		case 2:
			{
				dsnv_quanly(&dsnv);
				break;
			}
		case 3:
			{
				dsls_quanly(&dsls);
				break;
			}
		case 4:
			{
				dss_quanly(&dsls, &dss);
				break;
			}
		case 5:
			{
				dshdn_quanly(&dsncc, &dscthdn, &dshdn);
				break;
			}
		case 6:
			{
				dscthdn_quanly(&dss, &dscthdn);
				break;
			}
		case 7:
			{
				dshdb_quanly(&dsnv, &dscthdb, &dshdb);
				break;
			}
		case 8:
			{
				dscthdb_quanly(&dss, &dscthdb);
				break;
			}
		case 9:
			{
				tk_timkiem(&dss, &dsls);
				break;
			}
		case -1:
			{
				system("cls");
				break;
			}
		default:
			break;
		}
	}while (c != 0);
	
	dsncc_save(&dsncc);
	dsnv_save(&dsnv);
	dsls_save(&dsls);
	dss_save(&dss);
	dshdn_save(&dshdn);
	dscthdn_save(&dscthdn);
	dshdb_save(&dshdb);
	dscthdb_save(&dscthdb);
	
	return 0;
}

int menu()
{
	printf("\n\n\n");
	printf("+----------------------------------+\n");
	printf("|    QUAN LY HIEU SACH MINH ANH    |\n");
	printf("+----------------------------------+\n");
	printf("| 1. Quan ly nha cung cap          |\n");
	printf("| 2. Quan ly nhan vien             |\n");
	printf("| 3. Quan ly loai sach             |\n");
	printf("| 4. Quan ly sach                  |\n");
	printf("| 5. Quan ly hoa don nhap          |\n");
	printf("| 6. Quan ly chi tiet hoa don nhap |\n");
	printf("| 7. Quan ly hoa don ban           |\n");
	printf("| 8. Quan ly chi tiet hoa don ban  |\n");
	printf("| 9. Tim kiem                      |\n");
	printf("|-1. Xoa man hinh                  |\n");
	printf("| 0. Thoat                         |\n");
	printf("+----------------------------------+\n");
	printf("| Chon: ");
	
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}
