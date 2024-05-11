using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetRoomsRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_ROOMS_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetRoomsResponse GetFromServer(NetworkStream clientStream)
        {
            GetRoomsResponse GetRoomsResponse = GetRoomsResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetRoomsResponse;
        }

        internal struct GetRoomsResponse
        {
            private uint status;
            public GetRoomsResponse(uint status)
            {
                this.status = status;
            }

            public static GetRoomsResponse Deserialize(List<byte> list)
            {
                GetRoomsResponse response = new GetRoomsResponse((uint)list[0]);
                return response;
            }
        }
    }
}
