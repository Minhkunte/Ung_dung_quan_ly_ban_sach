#ifndef DS_LOAISACH_H
#define DS_LOAISACH_H

#include <string.h>
#include <stdlib.h>
#include "loaisach.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSLoaiSach
{
	LoaiSach_t loaisach[MAX_SIZE];
	int soluong;
};
typedef struct DSLoaiSach DSLoaiSach_t;

int dsls_load(DSLoaiSach_t*);
int dsls_save(DSLoaiSach_t*);
int dsls_them(DSLoaiSach_t*, LoaiSach_t*);
int dsls_sua(DSLoaiSach_t*, char*);
int	dsls_xoa(DSLoaiSach_t*, char*);
int dsls_timkiem(DSLoaiSach_t*, char*);
int dsls_hienthi(DSLoaiSach_t*);
int dsls_hienthi_index(DSLoaiSach_t*, int);
int dsls_menu();
void dsls_quanly(DSLoaiSach_t*);
char* dsls_query(DSLoaiSach_t*, char *);


/**** TRIEN KHAI ****/

int dsls_timkiem(DSLoaiSach_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->loaisach[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dsls_them(DSLoaiSach_t* ds, LoaiSach_t* ls)
{
	if (dsls_timkiem(ds, ls->id) >= 0)
	{
		printf("Loai sach id=%s da ton tai\n", ls->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	ls_saochep(&ds->loaisach[i], ls);
	ds->soluong++;
	return 0;
}



int dsls_sua(DSLoaiSach_t* ds, char* id)
{
	int index = dsls_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	LoaiSach_t *ls = &ds->loaisach[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dsls_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(ls->id, data);
			break;
		}
	}
	
	printf("Nhap ten: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(ls->ten, data);
	}
	
	printf("Nhap mo ta: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(ls->mota, data);
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dsls_xoa(DSLoaiSach_t* ds, char* id)
{
	int index = dsls_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		ls_saochep(&ds->loaisach[i], &ds->loaisach[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file ls.data
int dsls_load(DSLoaiSach_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("ls.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file ls.data\n");
		return 1;
	}
	
	LoaiSach_t ls;
	char data[3][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 2)
		{
			strcpy(ls.id, data[0]);
			strcpy(ls.ten, data[1]);	
			strcpy(ls.mota, data[2]);
			dsls_them(ds, &ls);
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


//load du lieu tu file ls.data
int dsls_save(DSLoaiSach_t* ds)
{
	FILE* f = fopen("ls.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file ls.data\n");
		return 1;
	}
	
	LoaiSach_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->loaisach[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->ten);
		fprintf(f, "%s\n", p->mota);
	}
	fclose(f);
	return 0;
}

char* dsls_query(DSLoaiSach_t* ds, char *id)
{
	int index = dsls_timkiem(ds, id);
	if (index == -1)
	{
		return "unknow";
	}
	LoaiSach_t *ls = &ds->loaisach[index];
	return ls->ten;
}

int dsls_hienthi(DSLoaiSach_t* ds)
{
	ls_gachngang();
	ls_tieude();
	ls_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		ls_hienthi(&ds->loaisach[i]);
	}
	ls_gachngang();
	return 0;
}

int dsls_hienthi_index(DSLoaiSach_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	ls_gachngang();
	ls_tieude();
	ls_gachngang();
	ls_hienthi(&ds->loaisach[index]);
	ls_gachngang();
	return 0;
}

int dsls_menu()
{
	printf("\n\n\n");
	printf("+-------------------------+\n");
	printf("|   3. QUAN LY LOAI SACH  |\n");
	printf("+-------------------------+\n");
	printf("| 1. Them loai sach       |\n");
	printf("| 2. Sua loai sach        |\n");
	printf("| 3. Xoa loai sach        |\n");
	printf("| 4. Tim kiem loai sach   |\n");
	printf("| 5. Xem tat ca loai sach |\n");
	printf("|-1. Xoa man hinh         |\n");
	printf("| 0. Quay lai             |\n");
	printf("+-------------------------+\n");
	printf("| Chon: ");
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void dsls_quanly(DSLoaiSach_t* ds)
{
	int c;
	do
	{
		c = dsls_menu();
		switch(c) {
		case 1:
			{
				printf("THEM LOAI SACH\n");
				LoaiSach_t ls;
				ls_nhap(&ls);
				if (!dsls_them(ds, &ls))
				{
					printf("\nThem thanh cong!\n\n");
					dsls_hienthi(ds);
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
				printf("SUA LOAI SACH\n");
				dsls_hienthi(ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dsls_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dsls_hienthi(ds);
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
				printf("XOA LOAI SACH\n");
				dsls_hienthi(ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dsls_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dsls_hienthi(ds);
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
				printf("TIM KIEM LOAI SACH\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dsls_timkiem(ds, id);
				if (index >= 0)
				{
					dsls_hienthi_index(ds, index);
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
				printf("XEM TAT CA LOAI SACH\n");
				dsls_hienthi(ds);
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
