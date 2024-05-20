using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.GetHighScoreRequest;
using static TriviaClient.GetPlayersInRoomRequest;
using static TriviaClient.GetRoomsRequest;

namespace TriviaClient
{
    internal class GetPlayersInRoomRequest
    {
        public uint roomId;
        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_PLAYERS_IN_ROOM_RC);

            string jsonMsg = $@"{{'roomId': {this.roomId}}}";

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

        public GetPlayersInRoomResponse GetFromServer(NetworkStream clientStream)
        {
            GetPlayersInRoomResponse GetPlayersInRoomResponse = GetPlayersInRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetPlayersInRoomResponse;
        }

        internal struct GetPlayersInRoomResponse
        {
            public uint status;
            public string[] players;

            public GetPlayersInRoomResponse(uint status, string[] players)
            {
                this.status = status;
                this.players = players;
            }

            public static GetPlayersInRoomResponse Deserialize(List<byte> list)
            {
                GetPlayersInRoomResponse response = new GetPlayersInRoomResponse();

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

                    response = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(jsonMessage);
                }

                return response;
            }
        }

    }
}
