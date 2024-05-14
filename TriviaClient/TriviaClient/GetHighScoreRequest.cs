using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
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
            public string[] statistics;
            public GetHighScoreResponse(uint status, string[] statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public static GetHighScoreResponse Deserialize(List<byte> list)
            {
                uint messageLength = BitConverter.ToUInt32(list.GetRange(0, 4).ToArray(), 0);
                
                byte[] messageBytes = list.GetRange(4, (int)messageLength).ToArray();

                string jsonString = System.Text.Encoding.UTF8.GetString(messageBytes);

                jsonString = jsonString.Substring(1, jsonString.Length - 2);

                GetHighScoreResponse response = new GetHighScoreResponse((uint)list[0], jsonString.Split(','));
                return response;
            }   

        }
    }
}
