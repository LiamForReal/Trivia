using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class CloseRoomRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.CLOSE_ROOM_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public CloseRoomResponse GetFromServer(NetworkStream clientStream)
        {
            CloseRoomResponse CloseRoomResponse = CloseRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return CloseRoomResponse;
        }

        internal struct CloseRoomResponse
        {
            public uint status;
            public CloseRoomResponse(uint status)
            {
                this.status = status;
            }

            public static CloseRoomResponse Deserialize(List<byte> list)
            {
                CloseRoomResponse response = new CloseRoomResponse((uint)list[0]);
                return response;
            }
        }
    }
}
