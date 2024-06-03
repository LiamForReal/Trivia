using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.GetGameResultsRequest;
using static TriviaClient.SubmitAnswerRequest;

namespace TriviaClient
{
    internal class GetQuestionRequest
    {
        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_QUESTION_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public GetQuestionResponse GetFromServer(NetworkStream clientStream)
        {
            GetQuestionResponse GetQuestionResponse = GetQuestionResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetQuestionResponse;
        }
        
        internal struct GetQuestionResponse
        {
            public uint status;
            public string question;
            public List<string> answers;

            public GetQuestionResponse()
            {
                this.question = "";
                this.answers = new List<string>();
            }

            public static GetQuestionResponse Deserialize(List<byte> list)
            {
                GetQuestionResponse response = new GetQuestionResponse();

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

                    response = JsonConvert.DeserializeObject<GetQuestionResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}
