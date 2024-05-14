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
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionsCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionsCount = questionsCount;
            this.answerTimeout = answerTimeout;
        }
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.CREATE_ROOM_RC);
            string jsonMsg = $@"{{'roomName': '{this.roomName}', 'maxUsers' : '{this.maxUsers}', ' 'questionsCount': '{this.questionsCount}', 'answerTimeout' : '{this.answerTimeout}'}}";

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        internal struct RoomData
        {
            uint _id;
            string _name;
            uint _maxPlayers;
            uint _numOfQuestionsInGame;
            uint _timePerQuestion;
            uint _isActive;

            public RoomData(CreateRoomRequest crr,uint isActive, uint id)
            {
                _id = id;
                _name = crr.roomName;
                _maxPlayers = crr.maxUsers;
                _numOfQuestionsInGame = crr.questionsCount;
                _timePerQuestion = crr.answerTimeout;
                _isActive = isActive;
            }
        };
        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public CreateRoomResponse GetFromServer(NetworkStream clientStream)
        {
            CreateRoomResponse CreateRoomResponse = CreateRoomResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return CreateRoomResponse;
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
