using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal struct LoginRequest
    {
        public string username;
        public string password;
    }
    internal struct SignupRequest
    {
        public string username;
        public string password;
        public string email;
    }

    internal struct JoinRoomRequest
    {
        public uint roomId;
    }

    internal struct GetPlayersInRoomRequest
    {
        public uint roomId;
    }
}
