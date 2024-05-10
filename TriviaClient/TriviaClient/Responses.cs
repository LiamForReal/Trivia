using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class Responses
    {
        internal struct LoginResponse
        {
            public LoginResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
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
    }
}
