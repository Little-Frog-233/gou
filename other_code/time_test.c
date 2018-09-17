#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t timer = -1;
    printf("ctime is %s\n",ctime(&timer));//输出标准日历时间

    struct tm *local_time = NULL;
    struct tm *gm_time = NULL;
    timer;

    timer = 10000000.00;
    printf("ctime is %s\n",ctime(&timer));//输出标准日历时间

    local_time = localtime(&timer);

    gm_time = gmtime(&timer);

    //printf("%d %d-%d %d:00:00", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday);
    printf("%d %d-%d %d\t%d\n\n", local_time->tm_year , local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_yday, local_time->tm_hour);
    printf("%d %d-%d %d\t%d\n", gm_time->tm_year , gm_time->tm_mon + 1, gm_time->tm_mday, gm_time->tm_yday, gm_time->tm_hour);
    printf("\n\n");

    local_time->tm_year = 10;

    printf("10/4 = %lf\n",10/4.0);
    

    return 0;
}
