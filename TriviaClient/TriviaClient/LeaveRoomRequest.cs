using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class LeaveRoomRequest
    {
        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.LEAVE_ROOM_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public LeaveRoomResponse GetFromServer(NetworkStream clientStream)
        {
            LeaveRoomResponse LogOutResponse = LeaveRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return LogOutResponse;
        }

        internal struct LeaveRoomResponse
        {
            public uint status;
            public LeaveRoomResponse(uint status)
            {
                this.status = status;
            }

            public static LeaveRoomResponse Deserialize(List<byte> list)
            {
                LeaveRoomResponse response = new LeaveRoomResponse((uint)list[0]);
                return response;
            }
        }
    }
}
