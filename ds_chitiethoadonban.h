#ifndef DS_CHITIETHOADONBAN_H
#define DS_CHITIETHOADONBAN_H

#include <string.h>
#include "chitiethoadonban.h"
#include "ds_sach.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSChiTietHoaDonBan
{
	ChiTietHoaDonBan_t chitiethoadonban[MAX_SIZE];
	int soluong;
};
typedef struct DSChiTietHoaDonBan DSChiTietHoaDonBan_t;

int dscthdb_load(DSChiTietHoaDonBan_t*, DSSach_t*);
int dscthdb_save(DSChiTietHoaDonBan_t*);
int dscthdb_them(DSChiTietHoaDonBan_t*, DSSach_t*, ChiTietHoaDonBan_t*, int);
int dscthdb_sua(DSChiTietHoaDonBan_t*, DSSach_t*, char*);
int	dscthdb_xoa(DSChiTietHoaDonBan_t*, DSSach_t*, char*);
int dscthdb_timkiem(DSChiTietHoaDonBan_t*, char*);
int dscthdb_hienthi(DSSach_t*, DSChiTietHoaDonBan_t*);
int dscthdb_hienthi_index(DSSach_t*, DSChiTietHoaDonBan_t*, int);
int dscthdb_menu();
void dscthdb_quanly(DSSach_t*, DSChiTietHoaDonBan_t*);


/**** TRIEN KHAI ****/

int dscthdb_timkiem(DSChiTietHoaDonBan_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->chitiethoadonban[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dscthdb_them(DSChiTietHoaDonBan_t* ds, DSSach_t *dss, ChiTietHoaDonBan_t* cthdb, int load)
{
	if (dscthdb_timkiem(ds, cthdb->id) >= 0)
	{
		printf("Hoa don ban id=%s da ton tai\n", cthdb->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	cthdb_saochep(&ds->chitiethoadonban[i], cthdb);
	ds->soluong++;
	
	//giam so sach trong kho
	if (load == 0)
	{
		int index = dss_timkiem(dss, cthdb->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
			return 1;
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho -= cthdb->soluong;
		}
	}
	return 0;
}



int dscthdb_sua(DSChiTietHoaDonBan_t* ds, DSSach_t* dss, char* id)
{
	int index = dscthdb_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	ChiTietHoaDonBan_t *cthdb = &ds->chitiethoadonban[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dscthdb_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(cthdb->id, data);
			break;
		}
	}
	
	char id_sach_daban[8];
	strcpy(id_sach_daban, cthdb->id_sach);
	int soluong_daban = cthdb->soluong;
	
	printf("Nhap ID sach: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int index = dss_timkiem(dss, id_sach_daban);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho += soluong_daban;
		}

		strcpy(cthdb->id_sach, data);
		index = dss_timkiem(dss, cthdb->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			s->soluongtonkho -= soluong_daban;
		}
	}
	
	printf("Nhap ID hoa don ban: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(cthdb->id_hoadonban, data);
	}
	
	printf("Nhap so luong: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int soluongcu = cthdb->soluong;
		cthdb->soluong = atoi(data);
		if (cthdb->soluong < 1)
			cthdb->soluong = 1;
		
		int index = dss_timkiem(dss, cthdb->id_sach);
		if (index < 0)
		{
			printf("ERROR: ID Sach khong ton tai!\n");
		}
		else
		{
			Sach_t* s = &dss->sach[index];
			if (cthdb->soluong > s->soluongtonkho)
				cthdb->soluong = s->soluongtonkho;
			s->soluongtonkho += soluongcu;
			s->soluongtonkho -= cthdb->soluong;
		}
	}
	
	printf("Nhap don gia: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		cthdb->dongia = atoi(data);
		if (cthdb->dongia < 0)
			cthdb->dongia = 0;
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dscthdb_xoa(DSChiTietHoaDonBan_t* ds, DSSach_t *dss, char* id)
{
	int index = dscthdb_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	
	char id_sach_daban[8];
	strcpy(id_sach_daban, ds->chitiethoadonban[index].id_sach);
	int soluong_daban = ds->chitiethoadonban[index].soluong;
	int idx = dss_timkiem(dss, id_sach_daban);
	if (idx < 0)
	{
		printf("ERROR: ID Sach khong ton tai!\n");
	}
	else
	{
		Sach_t* s = &dss->sach[idx];
		s->soluongtonkho += soluong_daban;
	}
			
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		cthdb_saochep(&ds->chitiethoadonban[i], &ds->chitiethoadonban[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file cthdb.data
int dscthdb_load(DSChiTietHoaDonBan_t* ds, DSSach_t* dss)
{
	ds->soluong = 0;
	FILE* f = fopen("cthdb.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file cthdb.data\n");
		return 1;
	}
	
	ChiTietHoaDonBan_t cthdb;
	char data[5][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 4)
		{
			strcpy(cthdb.id, data[0]);
			strcpy(cthdb.id_sach, data[1]);	
			strcpy(cthdb.id_hoadonban, data[2]);
			
			cthdb.soluong = atoi(data[3]);
			if (cthdb.soluong < 1)
				cthdb.soluong = 1;
			
			cthdb.dongia = atoi(data[4]);
			if (cthdb.dongia < 0)
				cthdb.dongia = 0;
				
			dscthdb_them(ds, dss, &cthdb, 1);
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

int dscthdb_save(DSChiTietHoaDonBan_t* ds)
{
	FILE* f = fopen("cthdb.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file cthdb.data\n");
		return 1;
	}
	
	ChiTietHoaDonBan_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->chitiethoadonban[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->id_sach);
		fprintf(f, "%s\n", p->id_hoadonban);
		fprintf(f, "%d\n", p->soluong);
		fprintf(f, "%d\n", p->dongia);
	}
	fclose(f);
	return 0;
}

int dscthdb_hienthi(DSSach_t* dss, DSChiTietHoaDonBan_t* ds)
{
	cthdb_gachngang();
	cthdb_tieude();
	cthdb_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		cthdb_hienthi(dss, &ds->chitiethoadonban[i]);
	}
	cthdb_gachngang();
	return 0;
}

int dscthdb_hienthi_index(DSSach_t* dss, DSChiTietHoaDonBan_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	cthdb_gachngang();
	cthdb_tieude();
	cthdb_gachngang();
	cthdb_hienthi(dss, &ds->chitiethoadonban[index]);
	cthdb_gachngang();
	return 0;
}

int dscthdb_menu()
{
	printf("\n\n\n");
	printf("+------------------------------------+\n");
	printf("|   8. QUAN LY CHI TIET HOA DON BAN  |\n");
	printf("+------------------------------------+\n");
	printf("| 1. Them chi tiet hoa don ban       |\n");
	printf("| 2. Sua chi tiet hoa don ban        |\n");
	printf("| 3. Xoa chi tiet hoa don ban        |\n");
	printf("| 4. Tim chi tiet kiem hoa don ban   |\n");
	printf("| 5. Xem chi tiet tat ca hoa don ban |\n");
	printf("|-1. Xoa man hinh                    |\n");
	printf("| 0. Quay lai                        |\n");
	printf("+------------------------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dscthdb_quanly(DSSach_t* dss, DSChiTietHoaDonBan_t* ds)
{
	int c;
	do
	{
		c = dscthdb_menu();
		switch(c) {
		case 1:
			{
				printf("THEM CHI TIET HOA DON BAN\n");
				ChiTietHoaDonBan_t cthdb;
				cthdb_nhap(dss, &cthdb);
				if (!dscthdb_them(ds, dss, &cthdb, 0))
				{
					printf("\nThem thanh cong!\n\n");
					dscthdb_hienthi(dss, ds);
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
				printf("SUA CHI TIET HOA DON BAN\n");
				dscthdb_hienthi(dss, ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dscthdb_sua(ds, dss, id))
				{
					printf("\nSua thanh cong!\n\n");
					dscthdb_hienthi(dss, ds);
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
				printf("XOA CHI TIET HOA DON BAN\n");
				dscthdb_hienthi(dss, ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dscthdb_xoa(ds, dss, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dscthdb_hienthi(dss, ds);
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
				printf("TIM KIEM CHI TIET HOA DON BAN\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dscthdb_timkiem(ds, id);
				if (index >= 0)
				{
					dscthdb_hienthi_index(dss, ds, index);
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
				printf("XEM TAT CA CHI TIET HOA DON BAN\n");
				dscthdb_hienthi(dss, ds);
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
