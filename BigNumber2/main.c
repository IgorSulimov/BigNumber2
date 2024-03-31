#include "BigNumber.h"
#include <stdio.h>
int main()
{
    char* str = "66";
    char* str2 = "322";

    BigNumber* bn1_ = CreateBN(str);
    if (bn1_ == NULL)
        printf("bn == NULL!\n");

    BigNumber* bn2_ = CreateBN(str2);
    if (bn1_ == NULL)
        printf("bn == NULL!\n");
    PrintBN(bn1_);
    PrintBN(bn2_);

    BigNumber* sum = SubBN(bn1_, bn2_);
    PrintBN(sum);

    free(bn1_);
    free(bn2_);
    free(sum);
    return 0;

}