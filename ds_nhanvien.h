#ifndef DS_NHANVIEN_H
#define DS_NHANVIEN_H

#include <string.h>
#include "nhanvien.h"
#include "utils.h"

#define MAX_SIZE	100

/**** KHAI BAO ****/

struct DSNhanVien
{
	NhanVien_t nhanvien[MAX_SIZE];
	int soluong;
};
typedef struct DSNhanVien DSNhanVien_t;

int dsnv_load(DSNhanVien_t*);
int dsnv_save(DSNhanVien_t*);
int dsnv_them(DSNhanVien_t*, NhanVien_t*);
int dsnv_sua(DSNhanVien_t*, char*);
int	dsnv_xoa(DSNhanVien_t*, char*);
int dsnv_timkiem(DSNhanVien_t*, char*);
int dsnv_hienthi(DSNhanVien_t*);
int dsnv_hienthi_index(DSNhanVien_t*, int);
int dsnv_menu();
void dsnv_quanly(DSNhanVien_t*);
char* dsnv_query(DSNhanVien_t*, char*);


/**** TRIEN KHAI ****/

int dsnv_timkiem(DSNhanVien_t* ds, char* id)
{
	int i, size = ds->soluong;
	for (i = 0; i < size; ++i)
	{
		if (strcmp(ds->nhanvien[i].id, id) == 0)
		{
			return i;
		}
	}
	return -1;
}


int dsnv_them(DSNhanVien_t* ds, NhanVien_t* nv)
{
	if (dsnv_timkiem(ds, nv->id) >= 0)
	{
		printf("Nhan vien id=%s da ton tai\n", nv->id);
		return 1;
	}
	int i = ds->soluong;
	//sao chep thong tin vao danh sach
	nv_saochep(&ds->nhanvien[i], nv);
	ds->soluong++;
	return 0;
}



int dsnv_sua(DSNhanVien_t* ds, char* id)
{
	int index = dsnv_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien sua
	printf("Nhap vao neu muon sua, Enter de bo qua\n\n");
	NhanVien_t *nv = &ds->nhanvien[index];
	char data[40];
	while (1)
	{
		printf("Nhap ma: ");
		if (gets(data) == 0 || data[0] == '\0' || data[0] == '\n')
		{
			break;
		}
		
		if (dsnv_timkiem(ds, data) >= 0)
		{
			printf("ID da ton tai\n\n");
			continue;
		}
		else
		{
			strcpy(nv->id, data);
			break;
		}
	}
	
	printf("Nhap ten: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(nv->ten, data);
	}
	
	printf("Nhap gioi tinh (1:nam, 0:nu): ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int gt = atoi(data);
		if (gt != 0)
			gt = 1;
		nv->gioitinh = gt;
	}
	
	printf("Nhap nam sinh (1900-2010): ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		int ns = atoi(data);
		if (ns < 1900)
			ns = 1900;
		else if (ns > 2010)
			ns = 2010;
		nv->namsinh = ns;
	}
		
	fflush(stdin);
	printf("Nhap dia chi: ");
	if (gets(data) && data[0] != '\0' && data[0] != '\n')
	{
		strcpy(nv->diachi, data);
	}
	
	return 0;
}

//Xoa bo nha cung cap khoi danh sach theo id (ds xoa bo ncc bang id)
int dsnv_xoa(DSNhanVien_t* ds, char* id)
{
	int index = dsnv_timkiem(ds, id);
	if (index == -1)
	{
		printf("Khong tim thay id=%s\n", id);
		return 1;
	}
	//Thuc hien xoa ncc
	int i, size = ds->soluong;
	for (i = index; i < size-1; ++i)
	{
		nv_saochep(&ds->nhanvien[i], &ds->nhanvien[i+1]);
	}
	ds->soluong--;
	return 0;
}



//load du lieu tu file nv.data
int dsnv_load(DSNhanVien_t* ds)
{
	ds->soluong = 0;
	FILE* f = fopen("nv.data", "r");
	if (f == NULL)
	{
		printf("ERROR: Khong doc duoc file nv.data\n");
		return 1;
	}
	
	NhanVien_t nv;
	char data[5][255];
	int i = 0;
	while (feof(f) == 0)
	{
		fgets(data[i], 255, f);
		data[i][strlen(data[i])-1] = '\0';
		if (i == 4)
		{
			strcpy(nv.id, data[0]);
			strcpy(nv.ten, data[1]);
			nv.gioitinh = atoi(data[2]);
			if (nv.gioitinh != 0)
				nv.gioitinh = 1;
				
			nv.namsinh = atoi(data[3]);
			if (nv.namsinh < 1900)
				nv.namsinh = 1900;
			else if (nv.namsinh > 2010)
				nv.namsinh = 2010;
			
			strcpy(nv.diachi, data[4]);
			dsnv_them(ds, &nv);
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


int dsnv_save(DSNhanVien_t* ds)
{
	FILE* f = fopen("nv.data", "w");
	if (f == NULL)
	{
		printf("ERROR: Khong ghi vao file nv.data\n");
		return 1;
	}
	
	NhanVien_t *p;
	int i;
	for (i = 0; i < ds->soluong; ++i)
	{
		p = &ds->nhanvien[i];
		fprintf(f, "%s\n", p->id);
		fprintf(f, "%s\n", p->ten);
		fprintf(f, "%d\n", p->gioitinh);
		fprintf(f, "%d\n", p->namsinh);
		fprintf(f, "%s\n", p->diachi);
	}
	fclose(f);
	return 0;
}



char* dsnv_query(DSNhanVien_t* ds, char *id)
{
	int index = dsnv_timkiem(ds, id);
	if (index == -1)
	{
		return "unknow";
	}
	NhanVien_t *nv = &ds->nhanvien[index];
	return nv->ten;
}

int dsnv_hienthi(DSNhanVien_t* ds)
{
	nv_gachngang();
	nv_tieude();
	nv_gachngang();
	int i, size = ds->soluong;
	if (size == 0)
	{
		printf("Khong co du lieu\n");
		return 1;
	}
	
	for (i = 0; i < size; ++i)
	{
		nv_hienthi(&ds->nhanvien[i]);
	}
	nv_gachngang();
	return 0;
}

int dsnv_hienthi_index(DSNhanVien_t* ds, int index)
{
	if (index < 0 || index >= ds->soluong)
	{
		printf("ERROR: index=%d\n", index);
		return 1;
	}
	nv_gachngang();
	nv_tieude();
	nv_gachngang();
	nv_hienthi(&ds->nhanvien[index]);
	nv_gachngang();
	return 0;
}

int dsnv_menu()
{
	printf("\n\n\n");
	printf("+-------------------------+\n");
	printf("|   2. QUAN LY NHAN VIEN  |\n");
	printf("+-------------------------+\n");
	printf("| 1. Them nhan vien       |\n");
	printf("| 2. Sua nhan vien        |\n");
	printf("| 3. Xoa nhan vien        |\n");
	printf("| 4. Tim kiem nhan vien   |\n");
	printf("| 5. Xem tat ca nhan vien |\n");
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

void dsnv_quanly(DSNhanVien_t* ds)
{
	int c;
	do
	{
		c = dsnv_menu();
		switch(c) {
		case 1:
			{
				printf("THEM NHAN VIEN\n");
				NhanVien_t nv;
				nv_nhap(&nv);
				if (!dsnv_them(ds, &nv))
				{
					printf("\nThem thanh cong!\n\n");
					dsnv_hienthi(ds);
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
				printf("SUA NHAN VIEN\n");
				dsnv_hienthi(ds);
				char id[8];
				printf("\nNhap id muon sua: ");
				gets(id);
				if (!dsnv_sua(ds, id))
				{
					printf("\nSua thanh cong!\n\n");
					dsnv_hienthi(ds);
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
				printf("XOA NHAN VIEN\n");
				dsnv_hienthi(ds);
				char id[8];
				printf("Nhap id muon xoa: ");
				gets(id);
				
				if (!dsnv_xoa(ds, id))
				{
					printf("\nXoa thanh cong!\n\n");
					dsnv_hienthi(ds);
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
				printf("TIM KIEM NHAN VIEN\n");
				char id[8];
				printf("Nhap id muon tim: ");
				gets(id);
				int index = dsnv_timkiem(ds, id);
				if (index >= 0)
				{
					dsnv_hienthi_index(ds, index);
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
				printf("XEM TAT CA NHAN VIEN\n");
				dsnv_hienthi(ds);
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
