using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static TriviaClient.GetHighScoreRequest;

namespace TriviaClient
{
    internal class GetPersonalStatsRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_PERSONAL_STATS_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetPersonalStatsResponse GetFromServer(NetworkStream clientStream)
        {
            GetPersonalStatsResponse GetPersonalStatsResponse = GetPersonalStatsResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetPersonalStatsResponse;
        }
        internal struct GetPersonalStatsResponse
        {
            public uint status;
            public List<string> statistics;

            public GetPersonalStatsResponse(uint status, List<string> statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public static GetPersonalStatsResponse Deserialize(List<byte> list)
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

                GetPersonalStatsResponse response = new GetPersonalStatsResponse(status, statsList);
                return response;
            }
        }
    }
}
