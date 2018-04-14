#!/bin/sh
iptables -P INPUT ACCEPT 
iptables -F
iptables -X 
iptables -Z 
iptables -A INPUT -i lo -j ACCEPT 
iptables -A INPUT -p tcp --dport 22 -j ACCEPT 
iptables -A INPUT -p tcp --dport 21 -j ACCEPT 
iptables -A INPUT -p tcp --dport 80 -j ACCEPT 
iptables -A INPUT -p tcp --dport 443 -j ACCEPT 
iptables -A INPUT -p icmp --icmp-type 8 -j ACCEPT
iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -P INPUT DROP iptables -P OUTPUT ACCEPT 
iptables -P FORWARD DROP 
service iptables save 
systemctl restart iptables.service
