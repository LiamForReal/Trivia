import socket as s
import json

SERVER_IP = "127.0.0.1"  # loop back
SERVER_PORT = 8888  # server port
AMOUNT_OF_BYTES = 5
CODES = {"Login": 100, "Signup": 200}


def client_side():
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)
        try:
            option = int(input("Choose one of the following options:\n1 - Login\n2 - Sign Up\n"))
            if option == 1 or option == 2:
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                if option == 1:
                    login_msg = {
                        "username": username,
                        "password": password
                    }
                    to_send = json.dumps(login_msg)

                    length = len(to_send)

                    # Send status code
                    sock.sendall(CODES["Login"].to_bytes(1, byteorder='big'))
                    # Send message length in little-endian format
                    sock.sendall(length.to_bytes(4, byteorder='little', signed=False))
                    # Send message data
                    sock.sendall(to_send.encode())

                else:
                    email = input("Enter your email: ")
                    signup_msg = {
                        "username": username,
                        "password": password,
                        "email": email
                    }
                    to_send = json.dumps(signup_msg)

                    # Send status code
                    sock.sendall(CODES["Signup"].to_bytes(1, byteorder='big'))
                    # Send message length in little-endian format
                    sock.sendall(len(to_send).to_bytes(4, byteorder='little', signed=False))
                    # Send message data
                    sock.sendall(to_send.encode())

                server_msg = sock.recv(1024)
                print("Server response:", server_msg.decode())

            elif option == 3:
                return
            else:
                print("You must choose 1 or 2!")

        except Exception as e:
            print("Error:", e)
            print("Server crashed. Try to connect again later.")


def main():
    client_side()


if __name__ == "__main__":
    main()
