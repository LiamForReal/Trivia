import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8888
CODES = {
    "Login": 100,
    "Signup": 200
}
BUFFER_SIZE = 1024

def client_side():
    option = input("Choose one of the following options:\n1 - Login\n2 - Sign Up\n")
    if not option.isnumeric():
        print ("Invalid option!")
        return
    
    option = int(option)
    
    try:
        if option in [1, 2]:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                server_address = (SERVER_IP, SERVER_PORT)
                sock.connect(server_address)
                username = input("Enter your username: ")
                password = input("Enter your password: ")
            
                if option == 1:
                    login_msg = {"username": username, "password": password}
                    to_send = json.dumps(login_msg).encode()
                    length = len(to_send).to_bytes(4, byteorder='little', signed=False)

                    sock.sendall(CODES["Login"].to_bytes(1, byteorder='big') + length + to_send)

                else:
                    email = input("Enter your email: ")
                    signup_msg = {"username": username, "password": password, "email": email}
                    to_send = json.dumps(signup_msg).encode()
                    length = len(to_send).to_bytes(4, byteorder='little', signed=False)

                    sock.sendall(CODES["Signup"].to_bytes(1, byteorder='big') + length + to_send) 
                    
                status_code = int.from_bytes(sock.recv(1))
                length = int.from_bytes(sock.recv(4), byteorder='little', signed=False)
                json_data = json.loads(sock.recv(length).decode())
                print(json_data)
        else:
            print("You must choose 1 or 2!")

    except (ValueError, socket.error) as e:
        print("Error:", e)
        print("Failed to connect to the server.")

if __name__ == "__main__":
    client_side()
