#include<stdio.h>
#include<unistd.h>
#include<string.h>
//低危 2019-03-18  15:38:20 W03-XDT02 10.150.73.2触发了[后台统计查询]规则。
//高危 2019-03-18  15:38:20 dh00003 10.150.73.2触发了[门诊发药统计]规则。
#define 0 EMPTY
#define -1  NOT
#define 1  FULL
struct _sms_act_list_node
{
    UINT16 iRiskLevel;                      /* 风险级别 */
    UINT32 iSrcIp;                          /* 源ip */
    UINT32 iDstIP;                          /* 目的ip */
    UINT32 iDstPort;                        /* 目的端口 */
    UINT32 iFirstTime;                      /* 第一次出现该风险的时间 */
    UINT32 iLastTime;                       /* 最后一次出现该风险的时间 */
    INT32 iIndexOfNotice;                   /* 审计对象在告警通知中的下标 */
    UINT32 iRistNum;                        /* 一定时间内触发的相同风险告警数量 */
    char strAppUser[50];                    /* 应用层账号 */
    char strSystemHost[50];                 /* 计算机名 */
    char strRuleName[200];                  /* 触发规则名称 */

    struct _sms_act_list_node *next;        /* 下一个节点 */
};

typedef struct _sms_act_head
{
    UINT16 icapacity;
    UINT16 iListLength;
    struct _sms_act_list_node *next;
};

typedef struct _sms_act_list_node stSmsActListNode;
typedef struct _sms_act_head stSmsActHead;

stSmsActHead *CreatSmsActHead();                              /* 创建链表 */
int isEmpty(stSmsActHead *head);                              /* 是否为空 */
int isFull(stSmsActHead *head);                               /* 是否满 */
int insertNoticeToSmsActList(stSmsActHead *head, const AUDIT_RECORD *record);             /* 插入告警信息 */
int findNoticeToSmsActList(stSmsActHead *head, const AUDIT_RECORD *record);               /* 查找合并告警信息 */
int delNoticeToSmsActList(stSmsActHead *head);                /* 删除处理(时间差10min) */
int destoryNoticeToSmsActList(stSmsActHead *head)             /* 销毁链表 */
void printNoticeToSmsActList(stSmsActHead *head)              /* 打印链表 */
