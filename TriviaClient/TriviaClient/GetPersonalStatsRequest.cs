using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
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

            string jsonMsg = JsonConvert.SerializeObject(this);

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        public void SendPersonalStats(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetPersonalStatsResponse GetPersonalStats(NetworkStream clientStream)
        {
            GetPersonalStatsResponse GetPersonalStatsResponse = GetPersonalStatsResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetPersonalStatsResponse;
        }
        internal struct GetPersonalStatsResponse
        {
            private uint status;
            private string[] statistics;
            public GetPersonalStatsResponse(uint status, string[] statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public static GetPersonalStatsResponse Deserialize(List<byte> list)
            {
                uint messageLength = BitConverter.ToUInt32(list.GetRange(0, 4).ToArray(), 0);

                byte[] messageBytes = list.GetRange(4, (int)messageLength).ToArray();

                string jsonString = System.Text.Encoding.UTF8.GetString(messageBytes);

                GetPersonalStatsResponse response = new GetPersonalStatsResponse((uint)list[0], jsonString.Split('|'));
                return response;
            }

        }
    }
}
