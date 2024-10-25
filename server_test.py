import socket

UDP_IP = "255.255.255.255" # Broadcast address, usually 255.255.255.255 or fixed LAN address
SERVER_PORT = 8888 # broadcast port
CLIENT_PORT = 9999

mpack_protocol ={
    "data": [0x14],
    "crc": 0
}

server_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
server_sock.bind((UDP_IP, SERVER_PORT))

client_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
client_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
client_sock.bind((UDP_IP, CLIENT_PORT))

message = ""

while True:
    server_sock.sendto(message, (UDP_IP, CLIENT_PORT));
    data, addr = client_sock. recvfrom(1024)
    print("Received message: ", data)