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

    internal class JoinRoomRequest
    {

        private uint roomId;
        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }

        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.JOIN_ROOM_RC);

            string jsonMsg = JsonConvert.SerializeObject(this);

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
        public JoinRoomResponse GetFromServer(NetworkStream clientStream)
        {
            JoinRoomResponse JoinRoomResponse = JoinRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return JoinRoomResponse;
        }

        internal struct JoinRoomResponse
        {
            private uint status;
            public JoinRoomResponse(uint status)
            {
                this.status = status;
            }

            public static JoinRoomResponse Deserialize(List<byte> list)
            {
                JoinRoomResponse response = new JoinRoomResponse((uint)list[0]);
                return response;
            }
        }
    }

}
