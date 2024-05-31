using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.GetPlayersInRoomRequest;

namespace TriviaClient
{
    internal class SubmitAnswerRequest
    {
        public string answer;
        public SubmitAnswerRequest (string answer)
        {
            this.answer = answer;
        }

        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.SUBMIT_ANSWER_RC);

            string jsonMsg = $@"{{'answer': '{this.answer}'}}";

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public SubmitAnswerResponse GetFromServer(NetworkStream clientStream)
        {
            SubmitAnswerResponse SubmitAnswerResponse = SubmitAnswerResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return SubmitAnswerResponse;
        }

        internal struct SubmitAnswerResponse
        {
            public uint status;
            public uint correctAnswerId;

            public SubmitAnswerResponse()
            {

            }

            public static SubmitAnswerResponse Deserialize(List<byte> list)
            {
                SubmitAnswerResponse response = new SubmitAnswerResponse();

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

                    response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}
