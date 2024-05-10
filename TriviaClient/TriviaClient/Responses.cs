using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal struct LoginResponse
    {
        public LoginResponse(uint status)
        {
            this.status = status;
        }

        public uint status;

        // like second constructor
        public static LoginResponse Deserialize(List<byte> list)
        {
            // logic
            // this.status = status from logic;
            return new LoginResponse();
        }
    }

    internal struct SignupResponse
    {
        public SignupResponse(uint status)
        {
            this.status = status;
        }

        public uint status;
    }

    internal struct LogoutResponse
    {
        public LogoutResponse(uint status)
        {
            this.status = status;
        }

        public uint status;
    }

    internal struct GetPlayersInRoomResponse
    {
        public GetPlayersInRoomResponse(List<string> rooms)
        {
            this.rooms = rooms;
        }

        public List<string> rooms;
    }

    internal struct GetHighScoreResponse
    {
        public GetHighScoreResponse(uint status, List<string> statistics)
        {
            this.status = status;
            this.statistics = statistics;
        }

        public uint status;
        public List<string> statistics;
    }

    internal struct GetPersonalStatsResponse
    {
        public GetPersonalStatsResponse(uint status, List<string> statistics)
        {
            this.status = status;
            this.statistics = statistics;
        }

        public uint status;
        public List<string> statistics;
    }

    internal struct JoinRoomResponse
    {
        public JoinRoomResponse(uint status)
        {
            this.status = status;
        }

        public uint status;
    }

    internal struct CreateRoomResponse
    {
        public CreateRoomResponse(uint status)
        {
            this.status = status;
        }

        public uint status;
    }
}
