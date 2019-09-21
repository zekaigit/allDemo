
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "cJSON.h"

#include "trace.h"


typedef struct rtk_lan_device_info{
	unsigned char hostname[64];
	unsigned int ip;
	unsigned char mac[6];
	unsigned int expires;
	unsigned char conType;
	unsigned char brand[16];
	unsigned char on_link;
	//get from proc/rtl865x/asicCounter
	unsigned int rx_bytes;
	unsigned int tx_bytes;

    unsigned char slave_flg;    //device link in mesh slave
    unsigned int rx_speed;      
    unsigned int tx_speed;
    unsigned char	rssi;
	
}RTK_LAN_DEVICE_INFO_T, *RTK_LAN_DEVICE_INFO_Tp;



#define MAX_STA_NUM 256
typedef struct mesh_sta_info{
    char mac[32];
    char ip[32];
    char rssi[32];
    char hostname[32];
    char brand[32];
    char link_time[32];
    char master[32];
}MESH_STA_INFO,*P_MESH_STA_INFO;

typedef struct mesh_neighbor_info{
    char mac[32];
	char ip[32];
    char rssi[32];
    char name[32];
    char band[32];
	char master[32];
	char link_time[32];
	struct mesh_sta_info sta_info[256];
	unsigned int sta_num; 
}MESH_NEIGHBOR_INFO,*P_MESH_NEIGHBOR_INFO;

typedef struct mesh_child_info{
	char mac[32];
	char ip[32];
	char rssi[32];
	char device_name[32];
	char link_time[32];
	char master[32];
	struct mesh_sta_info sta_info[256];
	unsigned int sta_num; 
}MESH_CHILD_INFO,*P_MESH_CHILD_INFO;

typedef struct mesh_main_info{
    char mac[32];
    char ip[32];
    char hostname[32];
    char brand[32];
	struct mesh_neighbor_info neighbor_info[12];
	unsigned int neighbor_num;
	struct mesh_sta_info sta_info[256];
	unsigned int sta_num; 
}MESH_MAIN_INFO,*P_MESH_MAIN_INFO;

typedef struct mesh_dev_info{
	MESH_MAIN_INFO main_info;
	MESH_CHILD_INFO child_info[12];
    MESH_STA_INFO sta_info[256];
    int sta_num;						//除了主节点的其他设备
    int child_num;						//MESH 子节点
}MESH_DEV_INFO,*P_MESH_DEV_INFO;


int recursion(cJSON *root,P_MESH_DEV_INFO mesh_info) 
{
	cJSON *obj;
	cJSON *ops;
	cJSON *station;
	int i;
	char *p_mac;

	int *p_sta_num = &mesh_info->sta_num;

	printf("p_sta_num = %d\n", *p_sta_num);
	obj = cJSON_GetObjectItem(root, "station_info");
	if (obj != NULL)
	{
		for(ops=obj->child; ops!=NULL; ops=ops->next)	
		{
			station = cJSON_GetObjectItem(ops, "station_mac");
			if (station==NULL)
			{
				DTRACE(DTRACE_RECURSION, "station_mac get error");
				continue;
			}
			strcpy(mesh_info->sta_info[*p_sta_num].mac, station->valuestring );
			DTRACE(DTRACE_RECURSION,"%s vs %s\n",mesh_info->sta_info[*p_sta_num].mac, station->valuestring );

			(*p_sta_num)++;
		}
				
	}
	else
		printf("station info is null\n");

	for(i=0; i<mesh_info->sta_num; i++)
	{
		printf("sta mac = %s\n", mesh_info->child_info[i].mac);
	}


	return 0;
}
int main(int argc, char *argv[])
{
	size_t  len   = 0;
	char*	line  = NULL;
	int num = 0;
	int n = 0;
	char buf[20480] = {0};
	cJSON* root;
	cJSON* obj;
	RTK_LAN_DEVICE_INFO_T devinfo[MAX_STA_NUM] = {0};

	FILE *fp = fopen("./mesh.json", "r");

	if (fp==NULL)
	{
		printf("open mesh_json error\n");
		return 0;		
	}

//	num = getline(&line, &len, fp);
	//fread(buf, 1, 2048, fp);
	while ((n = fread(buf, sizeof(char), sizeof(buf), fp)) > 0)
	{
		
	}
	fclose(fp);

	//DTRACE(DTRACE_RECURSION,"line = %s\n", buf);
	root = cJSON_Parse(buf);

	MESH_DEV_INFO mesh_info;	
	/*get all station */
	recursion(root, &mesh_info);
	obj = cJSON_GetObjectItem(root, "station_info");
	if (obj==NULL)
	{
		DTRACE(DTRACE_RECURSION,"station info get error\n");
		
	}
	cJSON *station_mac;
	cJSON *pos;
    for(pos = obj->child; pos != NULL; pos = pos->next)
    {
		station_mac = cJSON_GetObjectItem(pos, "station_mac");
        if(station_mac != NULL)
        {
			printf("station_mac=%s\n", station_mac->valuestring);
		}	
   
    }
	return 0;
}
