
#include "func.h"


int transform_str_to_min(char *p_time, unsigned int *min)
{
	char *p_tmp = NULL;
	char h[32] = {0};
	char m[32] = {0};
	unsigned int hour = 0;

	if ( strlen(p_time)<=0 )
		return -1;

	if ( (p_tmp = strstr(p_time, ":"))==NULL )
		return -1;

	strncpy(h, p_time, p_tmp-p_time);
	strcpy(m, p_tmp+1); 
	*min = atoi(h)*60 + atoi(m);
	return 0;
}

int main(int argc, char *argv[])
{
#if 0
	APP_STA_INFO sta1;
	APP_MAIN_INFO app;

	memset(&app, 0, sizeof(APP_MAIN_INFO));
		printf("000\n");

	app_init_sta(&sta1);

	printf("111\n");
	app_add_sta_to_main(&sta1, &app);


	printf("app sta num = %d\n", app.sta_num);
#endif

	int i = 0;
	char p_time[32] = {0};
	int min = 1439;
	transform_min_to_time(min, p_time);
	printf("p_time = %s\n", p_time);


	char ti[32]="12:09";
	char *hours="02";
	transform_str_to_min(ti, &min);
	printf("min = %d\n", min);

	char *p_tmp = "group2";
	sscanf(p_tmp, "group%d", &i);
	printf("i = %d\n", i);











	return 0;
}
