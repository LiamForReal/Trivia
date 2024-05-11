using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.GetHighScoreRequest;
using static TriviaClient.GetPlayersInRoomRequest;

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

            string jsonMsg = JsonConvert.SerializeObject(this);

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        public void GetFromServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetPlayersInRoomResponse SendToServer(NetworkStream clientStream)
        {
            GetPlayersInRoomResponse GetPlayersInRoomResponse = GetPlayersInRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetPlayersInRoomResponse;
        }

        internal struct GetPlayersInRoomResponse
        {
            private uint status;
            private string[] rooms;
            public GetPlayersInRoomResponse(uint status, string[] rooms)
            {
                this.status = status;
                this.rooms = rooms;
            }

            public static GetPlayersInRoomResponse Deserialize(List<byte> list)
            {
                uint messageLength = BitConverter.ToUInt32(list.GetRange(0, 4).ToArray(), 0);

                byte[] messageBytes = list.GetRange(4, (int)messageLength).ToArray();

                string jsonString = System.Text.Encoding.UTF8.GetString(messageBytes);

                jsonString = jsonString.Substring(1, jsonString.Length - 2);

                GetPlayersInRoomResponse response = new GetPlayersInRoomResponse((uint)list[0], jsonString.Split(','));
                return response;
            }
        }

    }
}
