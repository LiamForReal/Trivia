using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.LoginRequest;
using static TriviaClient.LogOutResquest;

namespace TriviaClient
{
    internal class CreateRoomRequest
    {
        public string roomName;
        public uint maxUsers;
        public uint questionsCount;
        public uint answerTimeout;
        public bool isMatchMake;
        public CreateRoomRequest()
        {
            this.roomName = "";
            this.maxUsers = 0;
            this.questionsCount = 0;
            this.answerTimeout = 0;
            this.isMatchMake = false;
        }
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.CREATE_ROOM_RC);
            string jsonMsg = $@"{{'roomName': '{this.roomName}', 'maxUsers': {this.maxUsers}', 'questionsCount': {this.questionsCount}', 'answerTimeout': {this.answerTimeout}', 'isMatchMake': {this.isMatchMake}}}";
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
        public CreateRoomResponse GetFromServer(NetworkStream clientStream)
        {
            CreateRoomResponse CreateRoomResponse = CreateRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return CreateRoomResponse;
        }
        internal struct RoomData
        {
            public uint id;
            public string name;
            public uint maxPlayers;
            public uint numOfQuestionsInGame;
            public uint timePerQuestion;
            public uint isActive;

            public RoomData(CreateRoomRequest crr, uint isActive, uint id)
            {
                this.id = id;
                this.name = (string)crr.roomName;
                this.maxPlayers = (uint)crr.maxUsers;
                this.numOfQuestionsInGame = (uint)crr.questionsCount;
                this.timePerQuestion = (uint)crr.answerTimeout;
                this.isActive = isActive;
            }
        };
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
