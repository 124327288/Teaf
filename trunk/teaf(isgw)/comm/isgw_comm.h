/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
#ifndef _ISGW_COMM_H_
#define _ISGW_COMM_H_
#include "pp_prot.h"
#include "easyace_all.h"
#include "qmode_msg.h"
//#include "object_que.h"

#define ISGW_Object_Que ACE_Object_Que

#ifndef GUARD_DOG_WATCH 
#define GUARD_DOG_WATCH(latch) ACE_Guard<ACE_Thread_Mutex> guard(latch)
#endif

namespace EASY_UTIL //easy  �����ռ�
{

typedef struct stSOCKET_INFO
{
    unsigned int index; //����
    unsigned int sock_fd; //
    unsigned int sock_seq; //
    unsigned int sock_ip;
    unsigned int creat_time; //���Ӳ�����ʱ��
    int status; //0 ����ʹ�� 1 ���ڱ�ʹ����
}SOCKET_INFO;

///���������ַ�
char *prot_encode(char *dest, const char *src);
///���������ַ�
char *prot_strim(char *dest, const char *src);
// �ж��Ƿ��ǺϷ���uin���Ϸ���uin >10000 <int
int is_valid_uin(unsigned int uin);
unsigned int get_time();
unsigned int get_span(struct timeval *tv1, struct timeval *tv2);

};

#endif //_ISGW_COMM_H_
