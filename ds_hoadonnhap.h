#ifndef DS_HOADONNHAP_H
#define DS_HOADONNHAP_H

#include <string.h>
#include "hoadonnhap.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSHoaDonNhap
{
	HoaDonNhap_t hoadonnhap[MAX_SIZE];
	int soluong;
};
typedef struct DSHoaDonNhap DSHoaDonNhap_t;

int dshdn_load(DSHoaDonNhap_t*);
int dshdn_save(DSHoaDonNhap_t*);
int dshdn_them(DSHoaDonNhap_t*, HoaDonNhap_t*);
int dshdn_sua(DSHoaDonNhap_t*, char*);
int	dshdn_xoa(DSHoaDonNhap_t*, char*);
int dshdn_timkiem(DSHoaDonNhap_t*, char*);
int dshdn_hienthi(DSNhaCungCap_t*, DSChiTietHoaDonNhap_t*, DSHoaDonNhap_t*);
int dshdn_hienthi_index(DSNhaCungCap_t*, DSChiTietHoaDonNhap_t*, DSHoaDonNhap_t*, int);
int dshdn_menu();
void dshdn_quanly(DSNhaCungCap_t*, DSChiTietHoaDonNhap_t*, DSHoaDonNhap_t*);


/**** TRIEN KHAI ****/

int dshdn_timkiem(DSHoaDonNhap_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->hoadonnhap[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dshdn_them(DSHoaDonNhap_t* ds, HoaDonNhap_t* hdn)
{
	if (dshdn_timkiem(ds, hdn->id) >= 0)
	{
		printf("Hoa don nhap id=%s da ton tai\n", hdn->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	hdn_saochep(&ds->hoadonnhap[i], hdn);
	ds->soluong++;
	return 0;
}



int dshdn_sua(DSHoaDonNhap_t* ds, char* id)
{
	int index = dshdn_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	HoaDonNhap_t *hdn = &ds->hoadonnhap[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dshdn_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(hdn->id, data);
			break;
		}
	}
	
	printf("Nhap nhay nhap (ngay/thang/nam): ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdn->ngaynhap, data);
	}
	
	printf("Nhap ID nha cung cap: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(hdn->id_nhacungcap, data);
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dshdn_xoa(DSHoaDonNhap_t* ds, char* id)
{
	int index = dshdn_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		hdn_saochep(&ds->hoadonnhap[i], &ds->hoadonnhap[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file hdn.data
int dshdn_load(DSHoaDonNhap_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("hdn.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file hdn.data\n");
		return 1;
	}
	
	HoaDonNhap_t hdn;
	char data[3][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 2)
		{
			strcpy(hdn.id, data[0]);
			strcpy(hdn.ngaynhap, data[1]);	
			strcpy(hdn.id_nhacungcap, data[2]);
			dshdn_them(ds, &hdn);
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


int dshdn_save(DSHoaDonNhap_t* ds)
{
	FILE* f = fopen("hdn.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file hdn.data\n");
		return 1;
	}
	
	HoaDonNhap_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->hoadonnhap[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->ngaynhap);
		fprintf(f, "%s\n", p->id_nhacungcap);
	}
	fclose(f);
	return 0;
}


int dshdn_hienthi(DSNhaCungCap_t* dsncc, DSChiTietHoaDonNhap_t* dscthdn, DSHoaDonNhap_t* ds)
{
	hdn_gachngang();
	hdn_tieude();
	hdn_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		hdn_hienthi(dsncc, dscthdn, &ds->hoadonnhap[i]);
	}
	hdn_gachngang();
	return 0;
}

int dshdn_hienthi_index(DSNhaCungCap_t* dsncc, DSChiTietHoaDonNhap_t* dscthdn, DSHoaDonNhap_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	hdn_gachngang();
	hdn_tieude();
	hdn_gachngang();
	hdn_hienthi(dsncc, dscthdn, &ds->hoadonnhap[index]);
	hdn_gachngang();
	return 0;
}

int dshdn_menu()
{
	printf("\n\n\n");
	printf("+----------------------------+\n");
	printf("|   5. QUAN LY HOA DON NHAP  |\n");
	printf("+----------------------------+\n");
	printf("| 1. Them hoa don nhap       |\n");
	printf("| 2. Sua hoa don nhap        |\n");
	printf("| 3. Xoa hoa don nhap        |\n");
	printf("| 4. Tim kiem hoa don nhap   |\n");
	printf("| 5. Xem tat ca hoa don nhap |\n");
	printf("|-1. Xoa man hinh            |\n");
	printf("| 0. Quay lai                |\n");
	printf("+----------------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dshdn_quanly(DSNhaCungCap_t* dsncc, DSChiTietHoaDonNhap_t* dscthdn, DSHoaDonNhap_t* ds)
{
	int c;
	do
	{
		c = dshdn_menu();
		switch(c) {
		case 1:
			{
				printf("THEM HOA DON NHAP\n");
				HoaDonNhap_t hdn;
				hdn_nhap(&hdn);
				if (!dshdn_them(ds, &hdn))
				{
					printf("\nThem thanh cong!\n\n");
					dshdn_hienthi(dsncc, dscthdn, ds);
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
				printf("SUA HOA DON NHAP\n");
				dshdn_hienthi(dsncc, dscthdn, ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dshdn_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dshdn_hienthi(dsncc, dscthdn, ds);
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
				printf("XOA HOA DON NHAP\n");
				dshdn_hienthi(dsncc, dscthdn, ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dshdn_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dshdn_hienthi(dsncc, dscthdn, ds);
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
				printf("TIM KIEM HOA DON NHAP\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dshdn_timkiem(ds, id);
				if (index >= 0)
				{
					dshdn_hienthi_index(dsncc, dscthdn, ds, index);
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
				printf("XEM TAT CA HOA DON NHAP\n");
				dshdn_hienthi(dsncc, dscthdn, ds);
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
