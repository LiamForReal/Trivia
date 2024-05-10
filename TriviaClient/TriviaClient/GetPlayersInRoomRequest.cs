using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetPlayersInRoomRequest
    {
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }

        public uint roomId;

        internal struct GetPlayersInRoomResponse
        {
            public GetPlayersInRoomResponse(List<string> rooms)
            {
                this.rooms = rooms;
            }

            public List<string> rooms;
        }

    }
}
