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
* ���ļ�Ϊ PDB ������Э���ʽ�����ļ�
* 
******************************************************************************/
#ifndef _PDB_PROT_H_
#define _PDB_PROT_H_

//��Ϣ����ָ���
typedef enum _PDB_CMD
{
    // 100 �����ڲ����� 

    // 100 - 200 ������ 
    CMD_QUERY_VIP = 101, //��ѯvip
    CMD_TEST_CINTF = 102, 
    CMD_TEST_COMM = 103,
    CMD_TEST_ADMIN_STT = 104, 
    
    CMD_IBC_TEST = 999,
    
    CMD_PDB_END
}PDB_CMD;

#endif //_PDB_PROT_H_
