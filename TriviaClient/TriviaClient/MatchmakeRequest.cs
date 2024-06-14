using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.SubmitAnswerRequest;

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
            public uint amountOfQuestions;
            public uint timePerQuestion;

            public MatchmakeResponse(uint status)
            {
                this.status = status;
                this.amountOfQuestions = 0;
                this.timePerQuestion = 0;
            }

            public static MatchmakeResponse Deserialize(List<byte> list)
            {
                MatchmakeResponse response = new MatchmakeResponse((uint)list[0]);
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

                    response = JsonConvert.DeserializeObject<MatchmakeResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}
