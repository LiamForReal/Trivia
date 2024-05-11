using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.LoginRequest;

namespace TriviaClient
{
    internal class CreateRoomRequest
    {
        private string roomName;
        private uint maxUsers;
        private uint questionCount;
        private uint answerTimeout;
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }
        public List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.CREATE_ROOM_RC);

            string jsonMsg = JsonConvert.SerializeObject(this);

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        internal struct CreateRoomResponse
        {
            public uint status;
            public CreateRoomResponse(uint status)
            {
                this.status = status;
            }
            public static CreateRoomResponse Deserialize(List<byte> list)
            {
                CreateRoomResponse response = new CreateRoomResponse((uint)list[0]);
                return response;
            }

        }
    }
}
