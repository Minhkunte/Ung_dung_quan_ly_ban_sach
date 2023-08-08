#ifndef DS_SACH_H
#define DS_SACH_H

#include <string.h>
#include "sach.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSSach
{
	Sach_t sach[MAX_SIZE];
	int soluong;
};
typedef struct DSSach DSSach_t;

int dss_load(DSSach_t*);
int dss_save(DSSach_t*);
int dss_them(DSSach_t*, Sach_t*);
int dss_sua(DSSach_t*, char*);
int	dss_xoa(DSSach_t*, char*);
int dss_timkiem(DSSach_t*, char*);
int dss_hienthi(DSLoaiSach_t*, DSSach_t*);
int dss_hienthi_index(DSLoaiSach_t*, DSSach_t*, int);
int dss_menu();
void dss_quanly(DSLoaiSach_t*, DSSach_t*);
char* dss_query(DSSach_t*, char*);

/**** TRIEN KHAI ****/

int dss_timkiem(DSSach_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->sach[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dss_them(DSSach_t* ds, Sach_t* s)
{
	if (dss_timkiem(ds, s->id) >= 0)
	{
		printf("Sach id=%s da ton tai\n", s->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	s_saochep(&ds->sach[i], s);
	ds->soluong++;
	return 0;
}



int dss_sua(DSSach_t* ds, char* id)
{
	int index = dss_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	Sach_t *s = &ds->sach[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dss_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(s->id, data);
			break;
		}
	}
	
	printf("Nhap ten: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(s->ten, data);
	}
	printf("Nhap ID loai sach: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(s->id_loai, data);
	}
	printf("Nhap tac gia: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(s->tacgia, data);
	}
	printf("Nhap nha xuat ban: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(s->nhaxuatban, data);
	}
	printf("Nhap so luong ton kho: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		s->soluongtonkho = atoi(data);
		if (s->soluongtonkho < 0)
			s->soluongtonkho = 0;
	}
	printf("Nhap don gia: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		s->dongia = atoi(data);
		if (s->dongia < 0)
			s->dongia = 0;
	}
	fflush(stdin);
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dss_xoa(DSSach_t* ds, char* id)
{
	int index = dss_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		s_saochep(&ds->sach[i], &ds->sach[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file s.data
int dss_load(DSSach_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("s.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file s.data\n");
		return 1;
	}
	
	Sach_t s;
	char data[7][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 6)
		{
			strcpy(s.id, data[0]);
			strcpy(s.ten, data[1]);
			strcpy(s.id_loai, data[2]);
			strcpy(s.tacgia, data[3]);
			strcpy(s.nhaxuatban, data[4]);
			
			s.soluongtonkho = atoi(data[5]);
			if (s.soluongtonkho < 0)
				s.soluongtonkho = 0;
			
			s.dongia = atoi(data[6]);
			if (s.dongia < 0)
				s.dongia = 0;
			
			dss_them(ds, &s);
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


int dss_save(DSSach_t* ds)
{
	FILE* f = fopen("s.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file s.data\n");
		return 1;
	}
	
	Sach_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->sach[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->ten);
		fprintf(f, "%s\n", p->id_loai);
		fprintf(f, "%s\n", p->tacgia);
		fprintf(f, "%s\n", p->nhaxuatban);
		fprintf(f, "%d\n", p->soluongtonkho);
		fprintf(f, "%d\n", p->dongia);
	}
	fclose(f);
	return 0;
}



char* dss_query(DSSach_t* ds, char* id)
{
	int index = dss_timkiem(ds, id);
	if (index == -1)
	{
		return "unknow";
	}
	Sach_t *s = &ds->sach[index];
	return s->ten;
}


int dss_hienthi(DSLoaiSach_t* dsls, DSSach_t* ds)
{
	s_gachngang();
	s_tieude();
	s_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		s_hienthi(dsls, &ds->sach[i]);
	}
	s_gachngang();
	return 0;
}

int dss_hienthi_index(DSLoaiSach_t* dsls, DSSach_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	s_gachngang();
	s_tieude();
	s_gachngang();
	s_hienthi(dsls, &ds->sach[index]);
	s_gachngang();
	return 0;
}

int dss_menu()
{
	printf("\n\n\n");
	printf("+--------------------+\n");
	printf("|   4. QUAN LY SACH  |\n");
	printf("+--------------------+\n");
	printf("| 1. Them sach       |\n");
	printf("| 2. Sua sach        |\n");
	printf("| 3. Xoa sach        |\n");
	printf("| 4. Tim kiem sach   |\n");
	printf("| 5. Xem tat ca sach |\n");
	printf("|-1. Xoa man hinh    |\n");
	printf("| 0. Quay lai        |\n");
	printf("+--------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dss_quanly(DSLoaiSach_t* dsls, DSSach_t* ds)
{
	int c;
	do
	{
		c = dss_menu();
		switch(c) {
		case 1:
			{
				printf("THEM SACH\n");
				Sach_t s;
				s_nhap(&s);
				if (!dss_them(ds, &s))
				{
					printf("\nThem thanh cong!\n\n");
					dss_hienthi(dsls, ds);
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
				printf("SUA SACH\n");
				dss_hienthi(dsls, ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dss_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dss_hienthi(dsls, ds);
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
				printf("XOA SACH\n");
				dss_hienthi(dsls, ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dss_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dss_hienthi(dsls, ds);
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
				printf("TIM KIEM SACH\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dss_timkiem(ds, id);
				if (index >= 0)
				{
					dss_hienthi_index(dsls, ds, index);
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
				printf("XEM TAT CA SACH\n");
				dss_hienthi(dsls, ds);
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
