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
    internal class GetGameResultsRequest
    {
        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_GAME_RESULTS_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }

        public GetGameResultsResponse GetFromServer(NetworkStream clientStream)
        {
            GetGameResultsResponse GetGameResultsResponse = GetGameResultsResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetGameResultsResponse;
        }

        internal struct GetGameResultsResponse
        {
            public uint status;
            public List<PlayerResults> results;

            public GetGameResultsResponse()
            {
                results = new List<PlayerResults>();
            }

            public static GetGameResultsResponse Deserialize(List<byte> list)
            {
                GetGameResultsResponse response = new GetGameResultsResponse();

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

                    response = JsonConvert.DeserializeObject<GetGameResultsResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}
