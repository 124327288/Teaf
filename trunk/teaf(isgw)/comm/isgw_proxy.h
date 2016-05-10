/******************************************************************************
* Tencent is pleased to support the open source community by making Teaf available.
* Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved. Licensed under the MIT License (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at http://opensource.org/licenses/MIT
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/
#ifndef ISGW_PROXY_H
#define ISGW_PROXY_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <map>
#include <sstream>

enum IsgwProxyErrorCode
{
    IPEC_NO_SERVER = -100,
    IPEC_SOCKET_ERROR,
    IPEC_CONNECT_FAIL,
    IPEC_SEND_FAIL,
    IPEC_RECV_FAIL,
    IPEC_TIMEOUT,
};

// �����Դ�admin serverȡip����, admin server�ĵ�ַͨ��dns�������
// ��ÿ��server�ķ��ʲ���Tcp������
// ���ַ�ʽ: tcp����ʧ��/���ʳ�ʱ"����"����һ������, ����Ϊ��server������, ��һ����������
// ���ؾ��ⷽʽ: ����ѯ, ��������������server, ����server�����������ѡ��һ��
class IsgwProxy
{
    struct ServerStat
    {
        ServerStat() : total(0), fail(0) {}
        uint32_t total;
        uint32_t fail;
    };

    enum
    {
        DEF_TIMEOUT = 50,
        DEF_INTERVAL = 300,
        DEF_MAX_FAIL_TIMES = 10,
    };

public:
    // port Ҫ����server�Ķ˿ں�
    // timeout ����server/���շ��صĳ�ʱʱ��
    // refresh_server_interval ˢ��server�б��ʱ����, ��λ��
    // max_fail_times, refresh_server_intervalʱ���������������ʧ�ܳ����ô���, ���ڱ����������ζԸ�server�ķ���
    IsgwProxy(uint16_t port, 
        uint32_t timeout = DEF_TIMEOUT, 
        uint32_t refresh_server_interval = DEF_INTERVAL, 
        uint32_t max_fail_times = DEF_MAX_FAIL_TIMES) 
            : last_refresh_time_(0), server_index_(0), port_(port), timeout_(timeout), 
            refresh_server_interval_(refresh_server_interval), max_fail_times_(max_fail_times)
    { 
        pthread_mutex_init(&mutex_, NULL); 
    }

    ~IsgwProxy() { pthread_mutex_destroy(&mutex_); }

public:
    // req ����
    // rsp ��Ӧ
    int get(const std::string& req, std::string& rsp);

    // ��admin serverȡ������ip�б�
    // servers �������IP�б�
    // port Ҫ�������Ķ˿ں�
    // timeout ����admin server�ĳ�ʱʱ��, ��λ����
    // ����ֵ 0�ɹ� ����ʧ��
    static int get_servers(uint16_t port, int32_t timeout, std::vector<std::string>& servers);

    // ָ��ip, �˿�, ��ʱ��Ϣ���ʽӿ�
    static int get(const std::string& server, uint16_t port, int32_t timeout, const std::string& req, std::string& rsp);

    static std::map<std::string, std::string> parse(const std::string& rsp);

    static std::vector<std::string> split(const std::string& items, char delim);

private:
    // ȡʹ�õķ�����ip
    int get_server(std::string& server);

private:
    // server�б�, ��ÿ��server��ʧ�ܴ���
    std::vector<std::pair<std::string, ServerStat> > servers_;
    pthread_mutex_t mutex_;
    uint32_t last_refresh_time_;
    int32_t server_index_;

private:
    uint16_t port_;
    int32_t timeout_;
    uint32_t refresh_server_interval_;
    uint32_t max_fail_times_;

private:
    static const std::string ADMIN_SERVER1;
    static const std::string ADMIN_SERVER2;
    static const uint16_t ADMIN_PORT;
};

#endif //ISGW_PROXY_H

