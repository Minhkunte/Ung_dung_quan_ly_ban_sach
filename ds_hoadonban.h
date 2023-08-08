#ifndef DS_HOADONBAN_H
#define DS_HOADONBAN_H

#include <string.h>
#include "hoadonban.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSHoaDonBan
{
	HoaDonBan_t hoadonban[MAX_SIZE];
	int soluong;
};
typedef struct DSHoaDonBan DSHoaDonBan_t;

int dshdb_load(DSHoaDonBan_t*);
int dshdb_save(DSHoaDonBan_t*);
int dshdb_them(DSHoaDonBan_t*, HoaDonBan_t*);
int dshdb_sua(DSHoaDonBan_t*, char*);
int	dshdb_xoa(DSHoaDonBan_t*, char*);
int dshdb_timkiem(DSHoaDonBan_t*, char*);
int dshdb_hienthi(DSNhanVien_t*, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t*);
int dshdb_hienthi_index(DSNhanVien_t*, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t*, int);
int dshdb_menu();
void dshdb_quanly(DSNhanVien_t*, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t*);


/**** TRIEN KHAI ****/

int dshdb_timkiem(DSHoaDonBan_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->hoadonban[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dshdb_them(DSHoaDonBan_t* ds, HoaDonBan_t* hdb)
{
	if (dshdb_timkiem(ds, hdb->id) >= 0)
	{
		printf("Hoa don ban id=%s da ton tai\n", hdb->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	hdb_saochep(&ds->hoadonban[i], hdb);
	ds->soluong++;
	return 0;
}



int dshdb_sua(DSHoaDonBan_t* ds, char* id)
{
	int index = dshdb_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	HoaDonBan_t *hdb = &ds->hoadonban[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dshdb_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(hdb->id, data);
			break;
		}
	}
	
	printf("Nhap ID nhan vien: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdb->id_nhanvien, data);
	}
	
	printf("Nhap nhay lap (ngay/thang/nam): ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdb->ngaylap, data);
	}
	
	printf("Nhap ten khach hang: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdb->tenkhachhang, data);
	}
	
	printf("Nhap dia chi: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdb->diachi, data);
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dshdb_xoa(DSHoaDonBan_t* ds, char* id)
{
	int index = dshdb_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		hdb_saochep(&ds->hoadonban[i], &ds->hoadonban[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file hdb.data
int dshdb_load(DSHoaDonBan_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("hdb.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file hdb.data\n");
		return 1;
	}
	
	HoaDonBan_t hdb;
	char data[5][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 4)
		{
			strcpy(hdb.id, data[0]);
			strcpy(hdb.id_nhanvien, data[1]);
			strcpy(hdb.ngaylap, data[2]);	
			strcpy(hdb.tenkhachhang, data[3]);
			strcpy(hdb.diachi, data[4]);
			dshdb_them(ds, &hdb);
			i = 0;
		}
		else
		{
			i++;
		}
	}
	fclose(f);
	return 0;
}


int dshdb_save(DSHoaDonBan_t* ds)
{
	FILE* f = fopen("hdb.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file hdb.data\n");
		return 1;
	}
	
	HoaDonBan_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->hoadonban[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->id_nhanvien);
		fprintf(f, "%s\n", p->ngaylap);
		fprintf(f, "%s\n", p->tenkhachhang);
		fprintf(f, "%s\n", p->diachi);
	}
	fclose(f);
	return 0;
}

int dshdb_hienthi(DSNhanVien_t* dsnv, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t* ds)
{
	hdb_gachngang();
	hdb_tieude();
	hdb_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		hdb_hienthi(dsnv, dscthdb, &ds->hoadonban[i]);
	}
	hdb_gachngang();
	return 0;
}

int dshdb_hienthi_index(DSNhanVien_t* dsnv, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	hdb_gachngang();
	hdb_tieude();
	hdb_gachngang();
	hdb_hienthi(dsnv, dscthdb, &ds->hoadonban[index]);
	hdb_gachngang();
	return 0;
}

int dshdb_menu()
{
	printf("\n\n\n");
	printf("+---------------------------+\n");
	printf("|   7. QUAN LY HOA DON BAN  |\n");
	printf("+---------------------------+\n");
	printf("| 1. Them hoa don ban       |\n");
	printf("| 2. Sua hoa don ban        |\n");
	printf("| 3. Xoa hoa don ban        |\n");
	printf("| 4. Tim kiem hoa don ban   |\n");
	printf("| 5. Xem tat ca hoa don ban |\n");
	printf("|-1. Xoa man hinh           |\n");
	printf("| 0. Quay lai               |\n");
	printf("+---------------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dshdb_quanly(DSNhanVien_t* dsnv, DSChiTietHoaDonBan_t* dscthdb, DSHoaDonBan_t* ds)
{
	int c;
	do
	{
		c = dshdb_menu();
		switch(c) {
		case 1:
			{
				printf("THEM HOA DON BAN\n");
				HoaDonBan_t hdb;
				hdb_nhap(&hdb);
				if (!dshdb_them(ds, &hdb))
				{
					printf("\nThem thanh cong!\n\n");
					dshdb_hienthi(dsnv, dscthdb, ds);
				}
				else
				{
					printf("\nThem that bai!\n\n");
				}
				pause();
				break;
			}
		case 2:
			{
				printf("SUA HOA DON BAN\n");
				dshdb_hienthi(dsnv, dscthdb, ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dshdb_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dshdb_hienthi(dsnv, dscthdb, ds);
				}
				else
				{
					printf("\nSua that bai!\n\n");
				}
				pause();
				break;
			}
		case 3:
			{
				printf("XOA HOA DON BAN\n");
				dshdb_hienthi(dsnv, dscthdb, ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dshdb_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dshdb_hienthi(dsnv, dscthdb, ds);
				}
				else
				{
					printf("\nXoa that bai!\n\n");
				}
				pause();
				break;
			}
		case 4:
			{
				printf("TIM KIEM HOA DON BAN\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dshdb_timkiem(ds, id);
				if (index >= 0)
				{
					dshdb_hienthi_index(dsnv, dscthdb, ds, index);
				}
				else
				{
					printf("Khong tim thay id=%s\n", id);
				}
				pause();
				break;
			}
		case 5:
			{
				printf("XEM TAT CA HOA DON BAN\n");
				dshdb_hienthi(dsnv, dscthdb, ds);
				pause();
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
}


#endif
