/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
/******************************************************************************
 *  @file    ibc_oper_base.h
 *
 *  ���ļ�Ϊ�ڲ���������ҵ���߼��Ļ�����
 *  ʹ��������չ��ʵ�ִ��� 
 ******************************************************************************/
#ifndef _IBC_OPER_BASE_H_
#define _IBC_OPER_BASE_H_
#include "easyace_all.h"
#include "qmode_msg.h"
#include "ibc_prot.h"

class IBCOperBase
{
public:
    IBCOperBase() {};
    virtual ~IBCOperBase() {}; 
    virtual int process(QModeMsg& req, char* ack, int& ack_len); 
    //���Ϊ����ϲ����߼�������Ҫ���ķǳ������� ����������߳���Ӱ�� 
    virtual int merge(IBCRValue& rvalue, const char* new_item); 

	//�ϲ�������ջص���ע�����ֻ����ȫ������������ʱ��������һ��
	virtual int end(IBCRValue& rvalue); 

private:

};

#endif // _IBC_OPER_BASE_H_
