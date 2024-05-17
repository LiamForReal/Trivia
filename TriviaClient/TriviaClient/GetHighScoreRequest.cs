using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static TriviaClient.GetPersonalStatsRequest;
using static TriviaClient.LoginRequest;

namespace TriviaClient
{
    internal class GetHighScoreRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_HIGH_SCORE_RC);
            return list;
        }
        
        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetHighScoreResponse GetFromServer(NetworkStream clientStream)
        {
            GetHighScoreResponse GetHighScoreResponse = GetHighScoreResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetHighScoreResponse;
        }
        internal struct GetHighScoreResponse
        {
            public uint status;
            public List<string> statistics;
            public GetHighScoreResponse(uint status,List<string> statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public static GetHighScoreResponse Deserialize(List<byte> list)
            {
                uint status = list[0];
                uint messageLength = BitConverter.ToUInt32(list.GetRange(1, 4).ToArray(), 0);
                byte[] messageBytes = list.GetRange(5, (int)messageLength).ToArray();
                string jsonString = System.Text.Encoding.UTF8.GetString(messageBytes);

                var jsonDoc = System.Text.Json.JsonSerializer.Deserialize<JsonDocument>(jsonString);
                var statistics = jsonDoc.RootElement.GetProperty("statistics").EnumerateArray();
                List<string> statsList = new List<string>();
                foreach (var stat in statistics)
                {
                    statsList.Add(stat.GetString());
                }

                GetHighScoreResponse response = new GetHighScoreResponse(status, statsList);
                return response;
            }   

        }
    }
}
