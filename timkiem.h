#ifndef TIMKIEM_H
#define TIMKIEM_H

#include <ctype.h>
#include "ds_sach.h"
#include "ds_loaisach.h"

int is_found(char* key, char* content)
{
	char lower_key[40];
	char lower_content[40];
	strcpy(lower_key, key);
	strcpy(lower_content, content);
	
	int i;
	for (i = 0; i < 40 && lower_key[i] != 0; ++i)
		lower_key[i] = tolower(lower_key[i]);
	for (i = 0; i < 40 && lower_content[i] != 0; ++i)
		lower_content[i] = tolower(lower_content[i]);
	
	if (strstr(lower_content, lower_key))
		return 1;
	return 0;
}

int tk_menu()
{
	printf("\n\n\n");
	printf("+---------------------+\n");
	printf("|    9. TIM KIEM      |\n");
	printf("+---------------------+\n");
	printf("| 1. Tim ten sach     |\n");
	printf("| 2. Tim loai sach    |\n");
	printf("| 3. Tim tac gia      |\n");
	printf("| 4. Tim nha xuat ban |\n");
	printf("|-1. Xoa man hinh     |\n");
	printf("| 0. Thoat            |\n");
	printf("+---------------------+\n");
	printf("| Chon: ");
	
	int c;
	scanf("%d",&c);
	fflush(stdin);
	printf("\n");
	return c;
}

void tk_theoten(DSSach_t *dss, DSLoaiSach_t *dsls)
{
	char data[40];
	printf("Nhap ten sach muon tim: ");
	gets(data);
	
	s_gachngang();
	s_tieude();
	s_gachngang();
	int i, found = 0;
	for (i = 0; i < dss->soluong; ++i)
	{
		if (is_found(data, dss->sach[i].ten))
		{
			s_hienthi(dsls, &dss->sach[i]);
			found = 1;
		}
	}
	
	if (found == 0)
	{
		printf("Khong tim thay ket qua nao!\n");
	}
	s_gachngang();
}

void tk_theoloai(DSSach_t *dss, DSLoaiSach_t *dsls)
{
	char data[40];
	printf("Nhap ten loai sach muon tim: ");
	gets(data);
	
	s_gachngang();
	s_tieude();
	s_gachngang();
	int i, found = 0;
	for (i = 0; i < dss->soluong; ++i)
	{
		int index = dsls_timkiem(dsls, dss->sach[i].id_loai);
		if (index >= 0)
		{
			LoaiSach_t* ls = &dsls->loaisach[index];
			if (is_found(data, ls->ten))
			{
				s_hienthi(dsls, &dss->sach[i]);
				found = 1;
			}
		}
	}
	
	if (found == 0)
	{
		printf("Khong tim thay ket qua nao!\n");
	}
	s_gachngang();
}

void tk_theotacgia(DSSach_t *dss, DSLoaiSach_t *dsls)
{
	char data[40];
	printf("Nhap ten tac gia muon tim: ");
	gets(data);
	
	s_gachngang();
	s_tieude();
	s_gachngang();
	int i, found = 0;
	for (i = 0; i < dss->soluong; ++i)
	{
		if (is_found(data, dss->sach[i].tacgia))
		{
			s_hienthi(dsls, &dss->sach[i]);
			found = 1;
		}
	}
	
	if (found == 0)
	{
		printf("Khong tim thay ket qua nao!\n");
	}
	s_gachngang();
}

void tk_theonhaxuatban(DSSach_t *dss, DSLoaiSach_t *dsls)
{
	char data[40];
	printf("Nhap ten nha xuat ban muon tim: ");
	gets(data);
	
	s_gachngang();
	s_tieude();
	s_gachngang();
	int i, found = 0;
	for (i = 0; i < dss->soluong; ++i)
	{
		if (is_found(data, dss->sach[i].nhaxuatban))
		{
			s_hienthi(dsls, &dss->sach[i]);
			found = 1;
		}
	}
	
	if (found == 0)
	{
		printf("Khong tim thay ket qua nao!\n");
	}
	s_gachngang();
}

void tk_timkiem(DSSach_t *dss, DSLoaiSach_t *dsls)
{
	int c;
	do
	{
		c = tk_menu();
		switch(c) {
		case 1:
			{
				tk_theoten(dss, dsls);
				break;
			}
		case 2:
			{
				tk_theoloai(dss, dsls);
				break;
			}
		case 3:
			{
				tk_theotacgia(dss, dsls);
				break;
			}
		case 4:
			{
				tk_theonhaxuatban(dss, dsls);
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
