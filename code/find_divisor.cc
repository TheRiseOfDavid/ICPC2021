int num = 某數;
for(int i = 1; i <= (int)sqrt(num); i++)
{
    if(num % i == 0)
    {
        // 得到因數 i
        // 4 = 2 * 2，只保留一個 2
        if(num / i != i)
        {
            // 12 = 3 * 4，像這樣，只要找到 3，就知道 4
            // 得到因數 num / i
        }
    }
}