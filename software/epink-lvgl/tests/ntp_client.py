from socket import AF_INET, SOCK_DGRAM
import sys
import socket
import struct, time

def get_ntp_time(host = "pool.ntp.org"):
    port = 123
    buf = 1024
    address = (host,port)
    msg = '\x1b' + 47 * '\0'
    # print(msg)
    
    # reference time (in seconds since 1900-01-01 00:00:00)
    TIME1970 = 2208988800 # 1970-01-01 00:00:00
    
    client = socket.socket(AF_INET, SOCK_DGRAM)
    client.sendto(msg.encode('utf-8'), address)
    msg, address = client.recvfrom(buf)
    print(struct.unpack("!12I", msg))
    t = struct.unpack("!12I", msg)[10]
    print(t)
    t -= TIME1970
    print(t)
    return time.ctime(t)#.replace("  ", " ")

if __name__ == "__main__":
    print(get_ntp_time())