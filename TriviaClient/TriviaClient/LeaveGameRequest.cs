using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class LeaveGameRequest
    {
        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.LEAVE_GAME_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public LeaveGameResponse GetFromServer(NetworkStream clientStream)
        {
            LeaveGameResponse LeaveRoomResponse = LeaveGameResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return LeaveRoomResponse;
        }

        internal struct LeaveGameResponse
        {
            public uint status;
            public LeaveGameResponse(uint status)
            {
                this.status = status;
            }

            public static LeaveGameResponse Deserialize(List<byte> list)
            {
                LeaveGameResponse response = new LeaveGameResponse((uint)list[0]);
                return response;
            }
        }
    }
}
