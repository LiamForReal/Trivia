import socket as s

SERVER_IP = "127.0.0.1" #loop back
SERVER_PORT = 8878 #server port
AMOUNT_OF_BYTES = 100


def client_side():
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)
        #server_msg = sock.recv(AMOUNT_OF_BYTES) #exception uneeded it's only get the welcome screen in the start
        while True:
            msg = input("Enter data: ")
            try:
                sock.sendall(msg.encode())  # send the message to the server
                server_msg = sock.recv(AMOUNT_OF_BYTES)
            except Exception:
                print("server crash try to conect again later\n")
                break


def main():
    client_side()


if __name__ == "__main__":
    main()
