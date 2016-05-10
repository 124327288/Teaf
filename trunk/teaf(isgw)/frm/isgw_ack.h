/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
/************************************************************
  Copyright (C), 2008-2018
  FileName: isgw_ack.h
  Author: xwfang              Date: 2008-06-01
  Description:
      send msg back to client 
***********************************************************/
#ifndef _ISGW_ACK_H_
#define _ISGW_ACK_H_
#include "isgw_comm.h"
#include "../comm/pp_prot.h"

// ����С�����ֵ(1000) ��Ȼcpuռ�û�ܸ� ���׵�����ѭ��
#define DEFAULT_TIME_INTERVAL 1000 //��λ΢��
#ifndef ALARM_TIMEOUT
#define ALARM_TIMEOUT 1 //��λ��
#endif

//6.2���°汾ʹ�ö�ʱ������
#if (ACE_MAJOR_VERSION<6 ||(ACE_MAJOR_VERSION==6 && ACE_MINOR_VERSION<2)) 
#define ISGW_ACK_USE_TIMER 1
#endif

class ISGWAck : public ACE_Event_Handler
{
public:
    static ISGWAck* instance(); 
    int init(int tv);
    void putq(PPMsg* ack_msg);
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_timeout(const ACE_Time_Value& tv, const void *arg);
    unsigned int get_time();
    unsigned int get_utime();

private:
    ISGWAck() : notify_stgy_(ACE_Reactor::instance(),
        this, ACE_Event_Handler::READ_MASK)
    {
        
    }
    int process();
    uint32_t statisitc(PPMsg* ack_msg);

private:
    ACE_Reactor_Notification_Strategy notify_stgy_;
    ACE_Thread_Mutex queue_lock_;
    deque<PPMsg*> msg_queue_;

    static ISGWAck* instance_;
    static struct timeval time_; //��ǰ��ʱ�� ������ ����ʱ���Ļ��������� 
};

#endif //_ISGW_ACK_H_

