#ifndef DS_CHITIETHOADONNHAP_H
#define DS_CHITIETHOADONNHAP_H

#include <string.h>
#include "chitiethoadonnhap.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSChiTietHoaDonNhap
{
	ChiTietHoaDonNhap_t chitiethoadonnhap[MAX_SIZE];
	int soluong;
};
typedef struct DSChiTietHoaDonNhap DSChiTietHoaDonNhap_t;

int dscthdn_load(DSChiTietHoaDonNhap_t*, DSSach_t*);
int dscthdn_save(DSChiTietHoaDonNhap_t*);
int dscthdn_them(DSChiTietHoaDonNhap_t*, DSSach_t*, ChiTietHoaDonNhap_t*, int);
int dscthdn_sua(DSChiTietHoaDonNhap_t*, DSSach_t*, char*);
int	dscthdn_xoa(DSChiTietHoaDonNhap_t*, DSSach_t*, char*);
int dscthdn_timkiem(DSChiTietHoaDonNhap_t*, char*);
int dscthdn_hienthi(DSSach_t*, DSChiTietHoaDonNhap_t*);
int dscthdn_hienthi_index(DSSach_t*, DSChiTietHoaDonNhap_t*, int);
int dscthdn_menu();
void dscthdn_quanly(DSSach_t*, DSChiTietHoaDonNhap_t*);


/**** TRIEN KHAI ****/

int dscthdn_timkiem(DSChiTietHoaDonNhap_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->chitiethoadonnhap[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dscthdn_them(DSChiTietHoaDonNhap_t* ds, DSSach_t* dss, ChiTietHoaDonNhap_t* cthdn, int load)
{
	if (dscthdn_timkiem(ds, cthdn->id) >= 0)
	{
		printf("Hoa don nhap id=%s da ton tai\n", cthdn->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	cthdn_saochep(&ds->chitiethoadonnhap[i], cthdn);
	ds->soluong++;
	//tang so sach trong kho
	if (load == 0)
	{
		int index = dss_timkiem(dss, cthdn->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
			return 1;
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho += cthdn->soluong;
		}
	}
	return 0;
}



int dscthdn_sua(DSChiTietHoaDonNhap_t* ds, DSSach_t* dss, char* id)
{
	int index = dscthdn_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	ChiTietHoaDonNhap_t *cthdn = &ds->chitiethoadonnhap[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dscthdn_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(cthdn->id, data);
			break;
		}
	}
	
	char id_sach_danhap[8];
	strcpy(id_sach_danhap, cthdn->id_sach);
	int soluong_danhap = cthdn->soluong;
	
	printf("Nhap ID sach: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int index = dss_timkiem(dss, id_sach_danhap);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho -= soluong_danhap;
		}
		
		strcpy(cthdn->id_sach, data);
		index = dss_timkiem(dss, cthdn->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho += soluong_danhap;
		}
	}
	
	printf("Nhap ID hoa don nhap: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(cthdn->id_hoadonnhap, data);
	}
	
	printf("Nhap so luong: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int soluongcu = cthdn->soluong;
		cthdn->soluong = atoi(data);
		if (cthdn->soluong < 1)
			cthdn->soluong = 1;
			
		int index = dss_timkiem(dss, cthdn->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho -= soluongcu;
			s->soluongtonkho += cthdn->soluong;
		}
			
	}
	
	printf("Nhap don gia: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		cthdn->dongia = atoi(data);
		if (cthdn->dongia < 0)
			cthdn->dongia = 0;
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dscthdn_xoa(DSChiTietHoaDonNhap_t* ds, DSSach_t* dss, char* id)
{
	int index = dscthdn_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	
	char id_sach_danhap[8];
	strcpy(id_sach_danhap, ds->chitiethoadonnhap[index].id_sach);
	int soluong_danhap = ds->chitiethoadonnhap[index].soluong;
	int idx = dss_timkiem(dss, id_sach_danhap);
	if (idx < 0)
	{
		printf("ERROR: ID Sach khong ton tai!\n");
	}
	else
	{
		Sach_t* s = &dss->sach[idx];
		s->soluongtonkho -= soluong_danhap;
	}
	
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		cthdn_saochep(&ds->chitiethoadonnhap[i], &ds->chitiethoadonnhap[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file cthdn.data
int dscthdn_load(DSChiTietHoaDonNhap_t* ds, DSSach_t* dss)
{
	ds->soluong = 0;
	FILE* f = fopen("cthdn.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file cthdn.data\n");
		return 1;
	}
	
	ChiTietHoaDonNhap_t cthdn;
	char data[5][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 4)
		{
			strcpy(cthdn.id, data[0]);
			strcpy(cthdn.id_sach, data[1]);	
			strcpy(cthdn.id_hoadonnhap, data[2]);
			
			cthdn.soluong = atoi(data[3]);
			if (cthdn.soluong < 1)
				cthdn.soluong = 1;
			
			cthdn.dongia = atoi(data[4]);
			if (cthdn.dongia < 0)
				cthdn.dongia = 0;
				
			dscthdn_them(ds, dss, &cthdn, 1);
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

int dscthdn_save(DSChiTietHoaDonNhap_t* ds)
{
	FILE* f = fopen("cthdn.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file cthdn.data\n");
		return 1;
	}
	
	ChiTietHoaDonNhap_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->chitiethoadonnhap[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->id_sach);
		fprintf(f, "%s\n", p->id_hoadonnhap);
		fprintf(f, "%d\n", p->soluong);
		fprintf(f, "%d\n", p->dongia);
	}
	
	fclose(f);
	return 0;
}

int dscthdn_hienthi(DSSach_t* dss, DSChiTietHoaDonNhap_t* ds)
{
	cthdn_gachngang();
	cthdn_tieude();
	cthdn_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		cthdn_hienthi(dss, &ds->chitiethoadonnhap[i]);
	}
	cthdn_gachngang();
	return 0;
}

int dscthdn_hienthi_index(DSSach_t* dss, DSChiTietHoaDonNhap_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	cthdn_gachngang();
	cthdn_tieude();
	cthdn_gachngang();
	cthdn_hienthi(dss, &ds->chitiethoadonnhap[index]);
	cthdn_gachngang();
	return 0;
}

int dscthdn_menu()
{
	printf("\n\n\n");
	printf("+-------------------------------------+\n");
	printf("|   6. QUAN LY CHI TIET HOA DON NHAP  |\n");
	printf("+-------------------------------------+\n");
	printf("| 1. Them chi tiet hoa don nhap       |\n");
	printf("| 2. Sua chi tiet hoa don nhap        |\n");
	printf("| 3. Xoa chi tiet hoa don nhap        |\n");
	printf("| 4. Tim chi tiet kiem hoa don nhap   |\n");
	printf("| 5. Xem chi tiet tat ca hoa don nhap |\n");
	printf("|-1. Xoa man hinh                     |\n");
	printf("| 0. Quay lai                         |\n");
	printf("+-------------------------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dscthdn_quanly(DSSach_t* dss, DSChiTietHoaDonNhap_t* ds)
{
	int c;
	do
	{
		c = dscthdn_menu();
		switch(c) {
		case 1:
			{
				printf("THEM CHI TIET HOA DON NHAP\n");
				ChiTietHoaDonNhap_t cthdn;
				cthdn_nhap(&cthdn);
				if (!dscthdn_them(ds, dss, &cthdn, 0))
				{
					printf("\nThem thanh cong!\n\n");
					dscthdn_hienthi(dss, ds);
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
				printf("SUA CHI TIET HOA DON NHAP\n");
				dscthdn_hienthi(dss, ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dscthdn_sua(ds, dss, id))
				{
					printf("\nSua thanh cong!\n\n");
					dscthdn_hienthi(dss, ds);
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
				printf("XOA CHI TIET HOA DON NHAP\n");
				dscthdn_hienthi(dss, ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dscthdn_xoa(ds, dss, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dscthdn_hienthi(dss, ds);
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
				printf("TIM KIEM CHI TIET HOA DON NHAP\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dscthdn_timkiem(ds, id);
				if (index >= 0)
				{
					dscthdn_hienthi_index(dss, ds, index);
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
				printf("XEM TAT CA CHI TIET HOA DON NHAP\n");
				dscthdn_hienthi(dss, ds);
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
