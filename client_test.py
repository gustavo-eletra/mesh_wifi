import socket

UDP_IP = "192.168.137.1" # Broadcast address, usually 255.255.255.255 or fixed LAN address
UDP_PORT = 8888 # broadcast port

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock. recvfrom(1024)
    print("Received message: ", data)