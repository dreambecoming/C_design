#include"global.h"

/**
 *
 *  \brief ���ļ���Ҫ���ڱ����������ļ�����ĺ���
 *
 */



/**
 * ��������: LoadData
 * ��������: �������������������ݴ������ļ����뵽�ڴ滺������ʮ��������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ���ܺ����г��˺���ExitSys�ķ���ֵ����ΪFALSE��,
 *           ���������ķ���ֵ����ΪTRUE.
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    int Re = 0;

    if(MakeDir())
    {
        printf("�ļ��д����ɹ���\n");
    }
    else
    {
        printf("�ļ��д���ʧ�ܣ�\n");
    }

    Re = CreatList(&gp_head);
    gul_station_count = LoadCode();
    if(gul_station_count<1)
    {
        printf("\n վ����������ʧ�� ��\n");
    }
    else
    {
        printf("\n վ���������سɹ��� \n");
    }

    if(Re<60) //60��ʾ������������Ѽ���
    {
        printf("\n ϵͳ�������ݲ����� ��\n");
        printf("\n ����ϵͳ�ر�ǰ�������ݣ� ��\n");
    }

    printf("\n�����������...\n");
    getch();
    return TRUE;
}

/**
 * ��������: MakeDir
 * ��������: �����ļ���
 * �������:
 * �������:
 * �� �� ֵ:  TRUE FALSE
 *
 * ����˵��:
 */
BOOL MakeDir(void)
{

    if(access("data",0) == EOF)   //access�����ж��ļ����Ƿ��Ѵ��ڣ�����0��ʾ�ж�
    {
        if( mkdir("data") == EOF)
        {
            return FALSE;
        }
    }
    if( access("data\\road",0) == EOF)
    {
        if( mkdir("data\\road") == EOF)
        {
            return FALSE;
        }
    }
    if (access("data\\station",0) == EOF)
    {
        if (mkdir("data\\station") == EOF)
        {
            return FALSE;
        }
    }
    if( access("data\\truck",0) == EOF)
    {
        if( mkdir("data\\truck") == EOF)
        {
            return FALSE;
        }
    }

    return TRUE;

}

/**
 * ��������: LoadCode
 * ��������: ��������������ļ����뵽һ������������
 * �������: FileName ��Ŵ�����������ļ���.
 * �������:
 * �� �� ֵ: ��Ŵ�������ڴ滺������С(���ֽ�Ϊ��λ).
 *
 * ����˵��:
 */
int LoadCode(void)
{
    STATION_CODE *phead, *tail;
    FILE *pFile = NULL;
    int re = 0,temp;
    char ch[50];

    pFile = fopen(gp_station_code_filename , "r");

    if(pFile == NULL)
    {
        printf("\nվ��������ʧ��\n");
        if(fopen(gp_station_code_filename,"w") == NULL)
        {
            printf("վ�������ļ�����ʧ�ܣ� \n");
        }
        else
        {
            printf("վ�������ļ������ɹ��� \n");
        }
        return re;
    }


    phead = (STATION_CODE*)malloc(sizeof(STATION_CODE));
    tail = phead;

    if(fscanf(pFile,"%d%s",&temp,ch) != EOF)
    {
        tail->station_num = temp;
        strcpy(tail->station_name,ch);
    }

    while(fscanf(pFile,"%d%s",&temp,ch) != EOF)
    {
        tail->next = (STATION_CODE*)malloc(sizeof(STATION_CODE));
        tail = tail->next;
        tail->station_num = temp;
        strcpy(tail->station_name,ch);
    }

    tail -> next = NULL;

    gp_station_code = phead;
    re = temp;

    return temp;

}

/**
 * ��������: CreatList
 * ��������: �������ļ���ȡ��������, ����ŵ���������ʮ��������.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ, ����������������ʮ����.
 * �� �� ֵ: int����ֵ, ��ʾ�������������.
 *           0  ����, ������
 *           4  �Ѽ���·����Ϣ���ݣ���վ�������Ϣ�ͳ�����Ϣ���ݼ������嵥����
 *           12 �Ѽ���·����Ϣ��վ����Ϣ���ݣ��޳�����Ϣ���ݼ������嵥����
 *           28 ������������Ѽ��أ��޻����嵥����
 *           60 ����������ݶ��Ѽ���
 * ����˵��:
 */

int CreatList(ROAD_DATA **phead)
{
    ROAD_DATA *hd = NULL, *pRoadData, tmp1;
    STATION_DATA *pStationData, tmp2;
    TRUCK_DATA *pTruckData, tmp3;
    GOODS_DATA *pGoodsData, tmp4;
    FILE *pFile;
    int find;
    int re = 0;

    if((pFile = fopen(gp_road_filename,"rb"))== NULL)
    {
        printf("·�����������Ϣ��ʧ�ܣ� \n");
        return re;
    }
    printf("·�����������Ϣ�򿪳ɹ���\n");

    //�������ļ��ж�����¥��Ϣ���ݣ������Ժ���ȳ���ʽ������������

    while(fread(&tmp1, sizeof(ROAD_DATA),1,pFile)==1)
    {
        pRoadData = (ROAD_DATA*)malloc( sizeof(ROAD_DATA));
        *pRoadData= tmp1;
        pRoadData->station = NULL;
        pRoadData->next = hd;
        hd = pRoadData;
    }
    fclose(pFile);

    //�ж��Ƿ�ɹ���ȡ
    if (hd == NULL)
    {
        printf("·�����������Ϣ����ʧ�ܣ�\n");
        return re;
    }
    printf("·�����������Ϣ���سɹ���");
    *phead = hd;
    re += 4;

    if((pFile = fopen(gp_station_filename,"rb"))==NULL)
    {
        printf("վ�������Ϣ�����ļ���ʧ�ܣ�\n");
        return re;
    }
    printf("վ�������Ϣ�����ļ��򿪳ɹ���\n");
    re +=8;

        /*�������ļ��ж�ȡѧ��������Ϣ���ݣ�����������Ӧ����ѧ��������Ϣ֧����*/
    while(fread(&tmp2,sizeof(STATION_DATA),1,pFile) == 1)
    {
        //�����ڵ�
        pStationData = (STATION_DATA*)malloc(sizeof(STATION_DATA));
        *pStationData = tmp2 ;
        pStationData->truck=NULL;

        //�������ϲ��Ҷ�Ӧ�Ľڵ�
        pRoadData = hd ;
        while(pRoadData != NULL
              && strcmp(pRoadData->road,pStationData->road)!= 0)//�������ͬ
        {
            pRoadData = pRoadData ->next; //������һ���ڵ�
        }
        if(pRoadData != NULL) //����ҵ�����������
        {
            pStationData->next = pRoadData->station;
            pRoadData->station = pStationData;
        }
        else //û�ҵ��ͷſռ�
        {
            free(pStationData);
        }
        fclose(pFile);//�ǵùر��ļ�
    }

    if ((pFile = fopen(gp_truck_filename,"rb"))==NULL)
    {
        printf("����������Ϣ��ʧ�ܣ�\n");
        return re;
    }
    printf("����������Ϣ�򿪳ɹ���\n");
    re += 16;

    //���ؽ���ڵ���
    while(fread(&tmp3,sizeof(TRUCK_DATA),1,pFile))
    {
        //�����ڵ�
        pTruckData = (TRUCK_DATA*)malloc(sizeof(TRUCK_DATA));
        *pTruckData = tmp3;

        //����վ��֧���϶�Ӧ�ĳ����ڵ�
        pRoadData=hd;
        find = 0;
        while(pRoadData != NULL &&find == 0)
        {
            pStationData = pRoadData->station;
            while(pStationData!= NULL && find ==0)
            {
                if(strcmp(pStationData->road,pTruckData->road) == 0 )//�ҵ���ͬ;
                {
                    find =1;
                    break;
                }
                pStationData=pStationData->next;
            }
            pRoadData= pRoadData->next;
        }
        if(find)//1Ϊ�ҵ�
        {
            pStationData->truck = pTruckData;
        }
        else//û�ҵ��ͷ�
        {
            free(pTruckData);
        }
        fclose(pFile);//�ǵùر��ļ�
    }


    //����·���ϵĻ����嵥
    if((pFile = fopen(gp_goods_filename,"rb"))==NULL)
    {
        printf("�����嵥��Ϣ�����ļ���ʧ�ܣ�\n");
        return re;
    }
    printf("�����嵥��Ϣ�����ļ��򿪳ɹ���\n");
    re += 32;

    while(fread(&tmp4,sizeof(GOODS_DATA),1,pFile)==1)
    {
        //�����ڵ�
        pGoodsData = (GOODS_DATA*)malloc(sizeof(GOODS_DATA));
        *pGoodsData = tmp4;

        //���Ҷ�Ӧ�ĳ�����վ��
        pRoadData = hd ;
        find = 0;
        while(pRoadData !=NULL && find == 0 )
        {
            pStationData = pRoadData->station;
            while(pStationData != NULL && find == 0)
            {
                pTruckData = pStationData->truck;
                if(pTruckData != NULL && find ==0)
                {
                    if(strcmp(pStationData->road,pGoodsData->road)==0 //ͬʱ����վ���·��������������
                       && pStationData ->station_num == pGoodsData->station_num)
                    {
                        find = 1;
                        break;
                    }
                }
                pStationData=pStationData->next;
            }
            pRoadData = pRoadData->next;
        }
        if(find)//����ҵ�
        {
            //pGoodsData->next = pTruckData ->goods;
            pGoodsData->next = pGoodsData;
            pTruckData->goods = pGoodsData;
        }
        else//δ�ҵ��ͷſռ�
        {
            free(pGoodsData);
        }
    }
    fclose(pFile); //�ر��ļ�

    return re;
}