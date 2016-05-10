/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
/********************************************************************************
  Copyright (C), 2008-2018
  FileName: stat.h
  Author: jinglin xwfang              Date: 2009-12-10
  Description:
    ����ͳ��ģ�飬֧�ְ�ͳ����Ϣ��¼��mem_map�У�ͳ�������˵������:
    1-100 Ϊϵͳ�ڲ������ָ�� ��ҵ��Ҫʹ��
    101-10000 Ϊ��ͨ��ҵ��ָ�cmd) ͳ����
    10001-10240  ��������ҵ���Զ����ͳ��������쳣���У�
    20241 - 20480  Ϊ����ڲ����쳣ͳ����� 
********************************************************************************/
#ifndef _STAT_H_
#define _STAT_H_
#include <ace/Mem_Map.h> 
#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <string>

#define USE_RW_THREAD_MUTEX 1

//const int STAT_DESC_MAX_LEN = 60; 
const int MAX_DESC_MSGLEN = 50; 
const int MAX_STAT_INDEX = 10239;  //��������ͳ����(�±��0��ʼ)������ͳ����� 10240 ��ʼ 
const int MAX_ISGW_FAILED_ITEM = 1024;   //isgw��ܵ�������ͳ����

//��������ͳ�ƶ��� 
typedef enum _STAT_CODE
{
    STAT_CODE_SVC_ENQUEUE = 20241, // �ӿ��߳���ӵ������̶߳���ʧ�� 
    STAT_CODE_SVC_TIMEOUT = 20242, // �����̴߳���ʱ������Ϣ��ʱ
    STAT_CODE_SVC_NOMEM = 20243, //  �����̴߳���ʱ�����ڴ�ľ� 
    STAT_CODE_IBCSVC_ENQUEUE = 20244, //�� ibc ��Ϣ����ʧ�� 
    STAT_CODE_SVC_OVERLOAD = 20245, // �����̴߳���ʱ����ϵͳ����
    STAT_CODE_SVC_REJECT = 20246, // ָ����������ʧ�����쳣
    STAT_CODE_IBCSVC_TIMEOUT = 20247, //ibc �����̴߳���ʱ������Ϣ��ʱ
    STAT_CODE_SVC_FORWARD = 20248, //
    STAT_CODE_IBCSVC_FAC = 20249, // ibc fac �쳣
    
    STAT_CODE_PUT_ACK_TIMEOUT = 20250, // �����̷߳�����Ӧģ����г�ʱ(���)
    STAT_CODE_ACK_NOOWNER = 20251, // ��Ӧʱû���ҵ���Ӧ�Ŀͻ���
    STAT_CODE_ACK_DISCONN = 20252, // ������Ϣʱ�Զ˹ر�
    STAT_CODE_ACK_BLOCK = 20253, // ������Ϣʱ�Զ�����
    STAT_CODE_ACK_ABNOR = 20254, // ������Ϣʱ�쳣
    STAT_CODE_ACK_UNCOMP = 20255, // ������Ϣʱ����ȫ
    STAT_CODE_CONN_FAIL = 20256, // ����˵�����ʧ��
    STAT_CODE_SEND_FAIL = 20257, // ������Ϣ�����ʧ��
    STAT_CODE_RECV_FAIL = 20258, // �Ӻ�˽�����Ϣʧ��(ֻ��ͬ���ķ�ʽ֧��) 
    STAT_CODE_DB_CONN_RUNOUT = 20259, //��ǰû�п��õ�DB����
    STAT_CODE_TCP_CONN_RUNOUT = 20260, //��ǰû�п��õ�tcp����

    STAT_CODE_ISGWC_ENQUEUE = 20261, //  isgwcintf ģ����������Ϣ����ʧ��
    STAT_CODE_ASYNC_ENQUEUE = 20262, //  �첽�߳����ʧ��
    STAT_CODE_DB_CRITICAL_ERROR = 20263, // mysql�ؼ�������2014��1146��

    STAT_CODE_RDS_SEL_DB = 20270, //redis select db failed
    STAT_CODE_RDS_RESET = 20271, //redis reset
    
    STAT_CODE_END
}STAT_CODE;

typedef struct ReprtInfo
{
    ReprtInfo(unsigned a=0, int b=0, int c=0, unsigned d=0, unsigned e=0):
    cmd(a),total_count(b),failed_count(c),total_span(d),procss_span(e)
        {}
    unsigned cmd;
    int total_count;
    int failed_count;
    unsigned total_span;
    unsigned procss_span;
    
}ReprtInfo;

//#define offsetof(TYPE,MEMBER)  ((int)&(((TYPE *)0)->MEMBER))

class Stat
{
public:
    ~Stat();
    static Stat* instance(); 
    int init(const char* file_name="./.stat", int flag=0);
    int init_check(const char* file_name="./.stat");
    void incre_stat(int index, int incre=1);
    void add_stat(ReprtInfo *info);
    int* get_stat();
    void reset_stat();
    void get_statstr(const char *stat_cfg, std::string &statstr);
    
private:
    Stat()
    {
        state_ = 0;
        
        //stat�ļ���ǰ4���ֽ���һ��magic ����(ͳ��������),����check�ļ���ʽ�Ƿ���ȷ
        //�����ǵ���ָ����Ϣͳ��,ÿ��ͳ������Ҫ4��int�ֶ�,�����10240��ͳ����
        //ָ��ͳ����Ϣ������1024������ͳ����,����ͳ�Ƶ�ƫ�ƴ�20241��ʼ
        //ÿ��ͳ������Ҫ1��int�ֶ�        
        isgw_failed_offset_ = (sizeof(ReprtInfo)-sizeof(int)) * (MAX_STAT_INDEX+1) + sizeof(int);
        file_size_ = (sizeof(ReprtInfo)-sizeof(int)) * (MAX_STAT_INDEX+1) + sizeof(int) +1024*sizeof(int);
    }
    
private:
    
    ACE_Mem_Map stat_file_;
    int file_size_;
    int isgw_failed_offset_;
    char file_name_[128];
    static ACE_Thread_Mutex lock_;
    int state_; //�Ƿ��ʼ���ı�־ 
    static Stat* instance_; 
};

#endif /* _STAT_H_ */
