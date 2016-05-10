/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
//=============================================================================
/**
 *  @file    pdb_oper.h
 *
 *  ���ļ�Ϊpdb�ڲ�������ҵ������ӿڶ����ļ�
 *  ���ļ�������Ϊ��ܵ�ʹ�������ļ� 
 *  
 *  @author xwfang
 */
//=============================================================================
#ifndef _PDB_OPER_
#define _PDB_OPER_
#include "isgw_comm.h"
#include "pdb_prot.h"
#include "isgw_oper_base.h"

#include "temp_proxy.h"

class PdbOper : public IsgwOperBase
{
public:
    PdbOper();
    ~PdbOper();

/** @name process
* 
*
* @param req ��Σ�������Ϣ
* @param ack ���Σ���ŷ��ص���Ӧ��Ϣ
* @param ack_len ��μ���Σ�����Ϊackָ������ռ䣬
*                          ����Ϊackʵ�ʴ�ŵ���Ϣ����
*
* @retval 0 �ɹ�
* @retval ����ֵ��ʾ�� �ɹ�
*/
    int process(QModeMsg& req, char* ack, int& ack_len);
    
private:
    
private:
        
};

#endif //_PDB_OPER_
