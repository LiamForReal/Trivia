using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetRoomStateRequest
    {
        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_ROOM_STATE_RC);

            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public GetRoomStateResponse GetFromServer(NetworkStream clientStream)
        {
            GetRoomStateResponse getRoomStateResponse = GetRoomStateResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return getRoomStateResponse;
        }

        internal struct GetRoomStateResponse
        {
            public uint status;
            public bool hasGameBegun;
            public List<string> players;
            public uint questionCount;
            public uint answerTimeout;

            public GetRoomStateResponse(uint status, bool hasGameBegun, List<string> players, uint questionCount, uint answerTimeout)
            {
                this.status = status;
                this.hasGameBegun = hasGameBegun;
                this.players = players;
                this.questionCount = questionCount;
                this.answerTimeout = answerTimeout;
            }

            public static GetRoomStateResponse Deserialize(List<byte> list)
            {
                GetRoomStateResponse response = new GetRoomStateResponse();

                UInt32 length = BitConverter.ToUInt32(list.GetRange(1, 4).ToArray());

                if (length > 0)
                {
                    byte[] bytes = list.GetRange(5, (int)(length)).ToArray();
                    char[] chars = (System.Text.Encoding.UTF8.GetString(bytes).ToCharArray());
                    string jsonMessage = "";

                    foreach (char ch in chars)
                    {
                        jsonMessage += ch;
                    }

                    response = JsonConvert.DeserializeObject<GetRoomStateResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}