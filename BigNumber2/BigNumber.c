#include "BigNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

BigNumber* CreateBN(char* number_)
{
	if (number_ == NULL || strlen(number_) == 0 ||
		!IsIntString(number_))
		return NULL;

	BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
	if (bn == NULL)
		return NULL;

	size_t size = strlen(number_);
	if (*number_ == '-')
	{
		bn->size = size - 1;
		bn->is_negative = true;
		number_++;
	}
	else
	{
		bn->size = size;
		bn->is_negative = false;
	}

	bn->digits = (digit*)calloc(bn->size, sizeof(digit));
	if (bn->digits == NULL)
	{
		free(bn);
		return NULL;
	}

	for (size_t i = 0; i < bn->size; ++i)
		bn->digits[i] = number_[i] - '0';

	return bn;
}

void DeleteBN(BigNumber** bn_)
{
	free((*bn_)->digits);
	free(*bn_);

	*bn_ = NULL;
}

void PrintBN(BigNumber* bn_)
{
	if (bn_ == NULL)
	{
		printf("BigNumber is empty!\n");
		return;
	}

	if (bn_->is_negative)
		printf("-");

	for (size_t i = 0; i < bn_->size; ++i)
		printf("%u", bn_->digits[i]);

	printf("\n");
}

void Add(BigNumber* result,BigNumber* bn1_, BigNumber* bn2_)        
{

	BigNumber* max = NULL;
	BigNumber* min = NULL;
	if (bn1_->size >= bn2_->size)
	{
		max = bn1_;
		min = bn2_;
	}
	else
	{
		max = bn2_;
		min = bn1_;
	}

	unsigned int sub = max->size - min->size;
	unsigned int q1 = 0;

	for (int i = min->size - 1; i > -1; --i)
	{
		unsigned int sum = max->digits[i + sub] + min->digits[i] + q1;

		q1 = sum / 10;

		result->digits[i + sub + 1] = sum % 10;
	}
	int d = max->size - min->size - 1;
	for (; d > -1; --d)
	{
		result->digits[d + 1] = (max->digits[d] + q1) % 10;
		if (max->digits[d] + q1 > 9)
			q1 = (max->digits[d] + q1) / 10;
		else
			q1 = 0;
	}
	result->digits[d + 1] = q1;

}

void Sub(BigNumber* result, BigNumber* bn1_, BigNumber* bn2_)
{

	BigNumber* max = NULL;
	BigNumber* min = NULL;

	if (bn2_->size == bn1_->size)
	{
		int fl = 1;
		for (int i = 0; fl; ++i)
		{
			if (bn2_->digits[i] > bn1_->digits[i])
			{
				max = bn2_;
				min = bn1_;
				fl = 0;
			}
			else
			{
				max = bn1_;
				min = bn2_;
				fl = 0;
			}
		}

		if (max->size == min->size) {
			unsigned int sub = max->size - min->size;

			for (int i = min->size - 1; i > -1; --i)
			{
				if (max->digits[i + sub] < min->digits[i])
				{
					while (max->digits[i + sub] < min->digits[i])
					{
						int p = 1;
						for (; max->digits[i + sub - p] < 1; p++)
						{
						}
						max->digits[i + sub - p] -= 1;
						max->digits[i + sub + 1 - p] += 10;
						for (; max->digits[i + sub + 1 - p] > 9; p--)
						{
							if (max->digits[i + sub] > 9)
								break;
							max->digits[i + sub + 2 - p] += 10;
							max->digits[i + sub + 1 - p] -= 1;

						}
					}

				}
				unsigned int sub_2 = max->digits[i + sub] - min->digits[i];


				result->digits[i + sub + 1] = sub_2;
				max->digits[i + sub] = max->digits[i + sub] - min->digits[i];
			}
			for (int d = max->size - min->size; d > -1; --d)
			{

				result->digits[d + 1] = max->digits[d];
			}
		}
	}


	if (bn1_->size > bn2_->size)
	{
		max = bn1_;
		min = bn2_;
	}
	else
	{
		max = bn2_;
		min = bn1_;
	}

	if (max->size != min->size) {
		unsigned int sub = max->size - min->size;

		for (int i = min->size - 1; i > -1; --i)
		{
			if (max->digits[i + sub] < min->digits[i])
			{
				while (max->digits[i + sub] < min->digits[i])
				{
					int p = 1;
					for (; max->digits[i + sub - p] < 1; p++)
					{}
					max->digits[i + sub - p] -= 1;
					max->digits[i + sub + 1 - p] += 10;
					for (; max->digits[i + sub + 1 - p] > 9; p--)
					{
						if (max->digits[i + sub] > 9)
							break;
						max->digits[i + sub + 2 - p] += 10;
						max->digits[i + sub + 1 - p] -= 1;

					}
				}

			}
			unsigned int sub_2 = max->digits[i + sub] - min->digits[i];

			result->digits[i + sub + 1] = sub_2;
			max->digits[i + sub] = max->digits[i + sub] - min->digits[i];
		}
		for (int d = max->size - min->size; d > -1; --d)
		{
			result->digits[d + 1] = max->digits[d];
		}
	}
}


BigNumber* SumBN(BigNumber* bn1_, BigNumber* bn2_)
{
	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
		return NULL;
	result->size = max(bn1_->size, bn2_->size) + 1;


	result->digits = (digit*)calloc(result->size, sizeof(digit));
	if (result->digits == NULL)
		return NULL;

	if (bn1_->is_negative != true && bn2_->is_negative != true)
	{
		Add(result,bn1_, bn2_);
		result->is_negative = false;
	}
	if (bn1_->is_negative == true && bn2_->is_negative == true)
	{
		Add(result,bn1_, bn2_);
		result->is_negative = true;
	}
	if (bn1_->is_negative != true && bn2_->is_negative == true)
	{
		Sub(result,bn1_, bn2_);
		if (bn1_->size > bn2_->size)
			result->is_negative = false;
		else
			result->is_negative = true;
	}

	if (bn1_->is_negative == true && bn2_->is_negative != true)
	{
		Sub(result,bn1_, bn2_);
		if (bn1_->size > bn2_->size)
			result->is_negative = true;
		else
			result->is_negative = false;
	}

	while (result->digits[0] == 0)
	{
		for (size_t i = 0; i < result->size - 1; i++) 
		{
			result->digits[i] = result->digits[i + 1];
		}
		result->size--;
	}
	return result;
}

BigNumber* SubBN(BigNumber* bn1_, BigNumber* bn2_)
{
	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
		return NULL;
	result->size = max(bn1_->size, bn2_->size) + 1;


	result->digits = (digit*)calloc(result->size, sizeof(digit));
	if (result->digits == NULL)
		return NULL;

	if (bn1_->is_negative != true && bn2_->is_negative != true)
	{
		Sub(result, bn1_, bn2_);
		if (bn1_->size > bn2_->size)
			result->is_negative = false;
		else
			result->is_negative = true;
	}
	if (bn1_->is_negative == true && bn2_->is_negative == true)
	{
		Sub(result, bn1_, bn2_);
		if (bn1_->size > bn2_->size)
			result->is_negative = true;
		else
			result->is_negative = false;
	}
	if (bn1_->is_negative != true && bn2_->is_negative == true)
	{
		Add(result, bn1_, bn2_);
		result->is_negative = false;
	}

	if (bn1_->is_negative == true && bn2_->is_negative != true)
	{
		Add(result, bn1_, bn2_);
		result->is_negative = true;
	}

	while (result->digits[0] == 0)
	{
		for (size_t i = 0; i < result->size - 1; i++) {
			result->digits[i] = result->digits[i + 1];
		}
		result->size--;
	}
	return result;
}
