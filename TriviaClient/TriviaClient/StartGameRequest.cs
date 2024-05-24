using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class StartGameRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.START_GAME_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public StartGameResponse GetFromServer(NetworkStream clientStream)
        {
            StartGameResponse StartGameResponse = StartGameResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return StartGameResponse;
        }

        internal struct StartGameResponse
        {
            public uint status;
            public StartGameResponse(uint status)
            {
                this.status = status;
            }

            public static StartGameResponse Deserialize(List<byte> list)
            {
                StartGameResponse response = new StartGameResponse((uint)list[0]);
                return response;
            }
        }
    }
}
