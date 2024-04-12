import socket as s

SERVER_IP = "127.0.0.1" #loop back
SERVER_PORT = 8888 #server port
AMOUNT_OF_BYTES = 5


def client_side():
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)
        try:
            server_msg = sock.recv(AMOUNT_OF_BYTES)
            print(server_msg.decode())
            msg = input("Enter data: ")
            if msg == "Hello":
                sock.sendall(msg.encode())  # send the message to the server
                print("Hello")
            elif msg != "EXIT":
                print("you must enter Hello to talk with server next time")
        except BaseException:
            print("server crash try to conect again later\n")


def main():
    client_side()


if __name__ == "__main__":
    main()
