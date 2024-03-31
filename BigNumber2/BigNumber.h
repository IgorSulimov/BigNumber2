#pragma once
#include <stdbool.h>

typedef unsigned char digit;
typedef struct BigNumber BigNumber;
// ��� �������� ����� (>10 ������)
struct BigNumber
{
	unsigned int size;		// ������ �����
	digit* digits;  	// ������ �� ���� �����
	bool is_negative;	// ���� �����
};

/*
* @brief �������� �������� �����
* @param number_ : ������ � ������� ������
* @return ��������� �� ���������� ������ � ������� ������
*/
BigNumber* CreateBN(char* number_);

/*
* @brief ������� ��������� ������� �����
* @param bn_ : ��������� �� ������� �����
*/
void DeleteBN(BigNumber** bn_);

/*
* @brief ������ �������� �����
* @param bn_ : ��������� �� ������� �����
*/
void PrintBN(BigNumber* bn_);

/*
* @brief ����� ���� ������� �����
* @param bn1_, bn2_ : ������� �����
* @return ������� ����� �� ����� ���� �������
*/
void Sub(BigNumber* result, BigNumber* bn1_, BigNumber* bn2_);

void Add(BigNumber* result, BigNumber* bn1_, BigNumber* bn2_);

BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_);

BigNumber* SubBN(BigNumber* bn1_, BigNumber* bn2_);


