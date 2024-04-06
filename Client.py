import socket as s
import json

SERVER_IP = "127.0.0.1" #loop back
SERVER_PORT = 8888 #server port
AMOUNT_OF_BYTES = 5
CODS = {"Login": 100, "Sing up": 200}


def json_is_amount_of_bytes(json_msg, amount_of_bytes):
    if len(json_msg) < amount_of_bytes:
        json_msg = json_msg.ljust(amount_of_bytes)
    elif len(json_msg) > amount_of_bytes:
        json_msg = json_msg[:amount_of_bytes]
    return json_msg


def client_side():
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)
        try:
            option = int(input("choose one of the following options\n 1 - Login\n 2 - Sing up"))
            if option == 1 or option == 2:
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                if option == 1:
                    login_msg = {
                        "code": chr(CODS["Login"]),
                        "username": username,
                        "password": password
                    }
                    msg_to_send = json.dumps(login_msg).encode()
                else:
                    email = input("Enter your email: ")
                    signup_msg = {
                        "code": chr(CODS["Sing up"]),
                        "username": username,
                        "password": password,
                        "email": email
                    }
                    msg_to_send = json.dumps(signup_msg).encode()

                msg_to_send = json_is_amount_of_bytes(msg_to_send, AMOUNT_OF_BYTES)
                if len(msg_to_send) == AMOUNT_OF_BYTES:
                    sock.send(msg_to_send)
                else:
                    print("ERROR IN - json_is_amount_of_bytes")
            else:
                print("you must choose 1 or 2!")
                client_side()
            server_msg = sock.recv(AMOUNT_OF_BYTES)
            print(server_msg.decode())

        except BaseException:
            print("server crash try to conect again later\n")


def main():
    client_side()


if __name__ == "__main__":
    main()
