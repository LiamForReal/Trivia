using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{

    internal class JoinRoomRequest
    {
        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }

        public uint roomId;

        internal struct JoinRoomResponse
        {
            public JoinRoomResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
        }
    }

}
