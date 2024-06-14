using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class MatchmakeRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.MATCHMAKE_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public MatchmakeResponse GetFromServer(NetworkStream clientStream)
        {
            MatchmakeResponse MatchmakeResponse = MatchmakeResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return MatchmakeResponse;
        }

        internal struct MatchmakeResponse
        {
            public uint status;
            public MatchmakeResponse(uint status)
            {
                this.status = status;
            }

            public static MatchmakeResponse Deserialize(List<byte> list)
            {
                MatchmakeResponse response = new MatchmakeResponse((uint)list[0]);
                return response;
            }
        }
    }
}
