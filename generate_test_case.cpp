#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void findColumnName(int n) {
    assert(n>=1);
    --n;
    int ndigits=0, cur_pow=1, cur_sum=0;
    while(cur_sum + cur_pow*26 <=n) {
        ++ndigits, cur_pow*=26;
        cur_sum+=cur_pow;
    }
    printf("%c", (n-cur_sum)/cur_pow + 'A');
    n=(n-cur_sum)%cur_pow; cur_pow/=26;
    while(ndigits) {
        printf("%c", n/cur_pow + 'A');
        n%=cur_pow;
        --ndigits, cur_pow/=26;
    }
    printf("\n");
}

int main()
{
    findColumnName(1);
    findColumnName(26);
    findColumnName(27);
    findColumnName(52);
    findColumnName(53);
    findColumnName(26*3);
    findColumnName(26*27);
    findColumnName(26*27+1);
    return 0;
}