#!/bin/bash
#
# 适用于Web等服务的Linux iptables防火墙脚本。
# 根据网上的一些脚本整理而来
#
# tudaxia.com, 2014/04
#
# 注意1：该脚本需要根据实际情况修改后才能使用。
# 注意2：如果需要开发ftp服务，仅仅开放TCP20,21端口是不够的，必须加载ip_conntrack_ftp以及ip_nat_ftp。
#     方法是修改/etc/sysconfig/iptables-config, 增加/修改为以下一行内容：
# 	  IPTABLES_MODULES="ip_conntrack_ftp ip_nat_ftp"
#

##############
# 可信任的主机或者网段
##############
#TRUSTHOSTS=( "10.0.0.0/8" "xxx.xxx.xxx.xxx" )

##############
# 只开放给可信任主机的管理用端口
##############
#ADMIN_TCP_PORTS="22,3306"

##############
# 对公网开放的服务端口
##############
SERVICE_TCP_PORTS="22,21,20,25,80,443,27733,1080"
SERVICE_UDP_PORTS="53,1080"

##############
# 清空原来的iptables设置
##############
iptables -F
iptables -X

##############
# 设置默认规则
# 通常INPUT及FORWARD设为DROP,OUTPUT设置为ACCEPT就足够了
# 极端情况下，可以将OUTPUT也设置成默认DROP。然后针对OUTPUT逐条增加过滤规则
##############
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT ACCEPT

##############
# 允许lo, PING, 以及所有内部发起的访问
##############
iptables -A INPUT -i lo -j ACCEPT
iptables -A INPUT -p icmp -j ACCEPT
iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -p icmp -j ACCEPT
iptables -A FORWARD -m state --state ESTABLISHED -j ACCEPT

##############
# 允许可信任主机访问管理端口
##############
for TRUSTHOST in ${TRUSTHOSTS[@]}
do
iptables -A INPUT  -p tcp -j ACCEPT -m multiport --dport $ADMIN_TCP_PORTS -s $TRUSTHOST
done

##############
# 放开TCP及UDP服务端口
##############
iptables -A INPUT  -p tcp -j ACCEPT -m multiport --dport $SERVICE_TCP_PORTS
iptables -A INPUT  -p udp -j ACCEPT -m multiport --dport $SERVICE_UDP_PORTS

#######################
# 防止DDOS攻击：Ping of Death
#######################
iptables -N PING_OF_DEATH
iptables -A PING_OF_DEATH -p icmp --icmp-type echo-request \
         -m hashlimit \
         --hashlimit 1/s \
         --hashlimit-burst 10 \
         --hashlimit-htable-expire 300000 \
         --hashlimit-mode srcip \
         --hashlimit-name t_PING_OF_DEATH \
         -j RETURN
iptables -A PING_OF_DEATH -j LOG --log-prefix "ping_of_death_attack: "
iptables -A PING_OF_DEATH -j DROP
iptables -A INPUT -p icmp --icmp-type echo-request -j PING_OF_DEATH

#######################
# 防止DDOS攻击：SYN FLOOD
#######################
iptables -N SYN_FLOOD
iptables -A SYN_FLOOD -p tcp --syn \
         -m hashlimit \
         --hashlimit 200/s \
         --hashlimit-burst 3 \
         --hashlimit-htable-expire 300000 \
         --hashlimit-mode srcip \
         --hashlimit-name t_SYN_FLOOD \
         -j RETURN
iptables -A SYN_FLOOD -j LOG --log-prefix "syn_flood_attack: "
iptables -A SYN_FLOOD -j DROP
iptables -A INPUT -p tcp --syn -j SYN_FLOOD

#######################
# 防止DDOS攻击：stealth scan
#######################
iptables -N STEALTH_SCAN
iptables -A STEALTH_SCAN -j LOG --log-prefix "stealth_scan_attack: "
iptables -A STEALTH_SCAN -j DROP

iptables -A INPUT -p tcp --tcp-flags SYN,ACK SYN,ACK -m state --state NEW -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags ALL NONE -j STEALTH_SCAN

iptables -A INPUT -p tcp --tcp-flags SYN,FIN SYN,FIN         -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags SYN,RST SYN,RST         -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j STEALTH_SCAN

iptables -A INPUT -p tcp --tcp-flags FIN,RST FIN,RST -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags ACK,FIN FIN     -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags ACK,PSH PSH     -j STEALTH_SCAN
iptables -A INPUT -p tcp --tcp-flags ACK,URG URG     -j STEALTH_SCAN

iptables-save
service iptables save
