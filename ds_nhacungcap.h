#ifndef DS_NHACUNGCAP_H
#define DS_NHACUNGCAP_H

#include <string.h>
#include "nhacungcap.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSNhaCungCap
{
	NhaCungCap_t nhacungcap[MAX_SIZE];
	int soluong;
};
typedef struct DSNhaCungCap DSNhaCungCap_t;

int dsncc_load(DSNhaCungCap_t*);
int dsncc_save(DSNhaCungCap_t*);
int dsncc_them(DSNhaCungCap_t*, NhaCungCap_t*);
int dsncc_sua(DSNhaCungCap_t*, char*);
int	dsncc_xoa(DSNhaCungCap_t*, char*);
int dsncc_timkiem(DSNhaCungCap_t*, char*);
int dsncc_hienthi(DSNhaCungCap_t*);
int dsncc_hienthi_index(DSNhaCungCap_t*, int);
int dsncc_menu();
void dsncc_quanly(DSNhaCungCap_t*);
char* dsncc_query(DSNhaCungCap_t*, char *);



/**** TRIEN KHAI ****/

//tim kiem nha cung cap trong danh sach bang id (tim ncc trong ds theo id)
//return index neu tim thay, return -1 neu KHONG tim thay
int dsncc_timkiem(DSNhaCungCap_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->nhacungcap[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}



//Ghi them nha cung cap vao danh sach (ds them ncc)
int dsncc_them(DSNhaCungCap_t* ds, NhaCungCap_t* ncc)
{
	if (dsncc_timkiem(ds, ncc->id) >= 0)
	{
		printf("Nha cung cap id=%s da ton tai\n", ncc->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	ncc_saochep(&ds->nhacungcap[i], ncc);
	ds->soluong++;
	return 0;
}



int dsncc_sua(DSNhaCungCap_t* ds, char* id)
{
	int index = dsncc_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	NhaCungCap_t *ncc = &ds->nhacungcap[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dsncc_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(ncc->id, data);
			break;
		}
	}
	
	
	printf("Nhap ten: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(ncc->ten, data);
	}
	
	printf("Nhap dia chi: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(ncc->diachi, data);
	}
	
	printf("Nhap so dien thoai: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(ncc->sodienthoai, data);
	}
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dsncc_xoa(DSNhaCungCap_t* ds, char* id)
{
	int index = dsncc_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		ncc_saochep(&ds->nhacungcap[i], &ds->nhacungcap[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file ncc.data
int dsncc_load(DSNhaCungCap_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("ncc.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file ncc.data\n");
		return 1;
	}
	
	NhaCungCap_t ncc;
	char data[4][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 3)
		{
			strcpy(ncc.id, data[0]);
			strcpy(ncc.ten, data[1]);
			strcpy(ncc.diachi, data[2]);
			strcpy(ncc.sodienthoai, data[3]);
			dsncc_them(ds, &ncc);
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


int dsncc_save(DSNhaCungCap_t* ds)
{
	FILE* f = fopen("ncc.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file ncc.data\n");
		return 1;
	}
	
	NhaCungCap_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->nhacungcap[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->ten);
		fprintf(f, "%s\n", p->diachi);
		fprintf(f, "%s\n", p->sodienthoai);
	}
	fclose(f);
	return 0;
}


char* dsncc_query(DSNhaCungCap_t* ds, char *id)
{
	int index = dsncc_timkiem(ds, id);
	if (index == -1)
	{
		return "unknow";
	}
	NhaCungCap_t *ncc = &ds->nhacungcap[index];
	return ncc->ten;
}


int dsncc_hienthi(DSNhaCungCap_t* ds)
{
	ncc_gachngang();
	ncc_tieude();
	ncc_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		ncc_hienthi(&ds->nhacungcap[i]);
	}
	ncc_gachngang();
	return 0;
}

int dsncc_hienthi_index(DSNhaCungCap_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	ncc_gachngang();
	ncc_tieude();
	ncc_gachngang();
	ncc_hienthi(&ds->nhacungcap[index]);
	ncc_gachngang();
	return 0;
}

int dsncc_menu()
{
	printf("\n\n\n");
	printf("+----------------------------+\n");
	printf("|   1. QUAN LY NHA CUNG CAP  |\n");
	printf("+----------------------------+\n");
	printf("| 1. Them nha cung cap       |\n");
	printf("| 2. Sua nha cung cap        |\n");
	printf("| 3. Xoa nha cung cap        |\n");
	printf("| 4. Tim kiem nha cung cap   |\n");
	printf("| 5. Xem tat ca nha cung cap |\n");
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

void dsncc_quanly(DSNhaCungCap_t* ds)
{
	int c;
	do
	{
		c = dsncc_menu();		
		switch(c) {
		case 1:
			{
				printf("THEM NHA CUNG CAP\n");
				NhaCungCap_t ncc;
				ncc_nhap(&ncc);
				if (!dsncc_them(ds, &ncc))
				{
					printf("\nThem thanh cong!\n\n");
					dsncc_hienthi(ds);
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
				printf("SUA NHA CUNG CAP\n");
				dsncc_hienthi(ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dsncc_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dsncc_hienthi(ds);
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
				printf("XOA NHA CUNG CAP\n");
				dsncc_hienthi(ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dsncc_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dsncc_hienthi(ds);
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
				printf("TIM KIEM NHA CUNG CAP\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dsncc_timkiem(ds, id);
				if (index >= 0)
				{
					dsncc_hienthi_index(ds, index);
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
				printf("XEM TAT CA NHA CUNG CAP\n");
				dsncc_hienthi(ds);
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
