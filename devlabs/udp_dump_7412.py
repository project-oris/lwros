import socket

# 수신할 IP 주소 및 포트 설정
UDP_IP = "0.0.0.0"  # 모든 인터페이스에서 수신
UDP_PORT = 7412    # 수신할 포트 번호

# 소켓 생성
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Listening on {UDP_IP}:{UDP_PORT}")

# 4바이트 간격으로 데이터를 헥사로 출력하는 함수
def print_data_in_hex(data):
    for i in range(0, len(data), 4):
        chunk = data[i:i+4]  # 4바이트씩 데이터 슬라이스
        hex_chunk = ' '.join(f"{byte:02x}" for byte in chunk)  # 헥사 형식으로 변환
        print(f"{i:04x}: {hex_chunk}")

# 메시지 수신 대기
while True:
    data, addr = sock.recvfrom(1024)  # 1024는 수신 버퍼 크기
    print(f"Received {len(data)} bytes from {addr}")
    print_data_in_hex(data)
