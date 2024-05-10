using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal struct LoginRequest
    {
        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }

        public string username;
        public string password;
    }
    internal struct SignupRequest
    {
        public SignupRequest(string username, string password, string email)
        {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public string username;
        public string password;
        public string email;
    }

    internal struct JoinRoomRequest
    {
        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }

        public uint roomId;
    }

    internal struct GetPlayersInRoomRequest
    {
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }

        public uint roomId;
    }

    internal struct CreateRoomRequest
    {
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }

        public string roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint answerTimeout;
    }
}
