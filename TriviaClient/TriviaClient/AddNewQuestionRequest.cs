using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class AddNewQuestionRequest
    {
        public string question;
        public string correctAnswer;
        public string wrongAnswer1;
        public string wrongAnswer2;
        public string wrongAnswer3;

        public AddNewQuestionRequest(string question, string correctAnswer, string wrongAnswer1, string wrongAnswer2, string wrongAnswer3)
        {
            this.question = question;
            this.correctAnswer = correctAnswer;
            this.wrongAnswer1 = wrongAnswer1;
            this.wrongAnswer2 = wrongAnswer2;
            this.wrongAnswer3 = wrongAnswer3;
        }

        private List<byte> Serialize()
        {
            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.ADD_NEW_QUESTION_RC);

            string jsonMsg = $@"{{'question': '{this.question}', 'correctAnswer' : '{this.correctAnswer}', 'wrongAnswer1' : '{this.wrongAnswer1}', 'wrongAnswer2' : '{this.wrongAnswer2}', 'wrongAnswer3' : '{this.wrongAnswer3}'}}";

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

        public AddNewQuestionResponse GetFromServer(NetworkStream clientStream)
        {
            AddNewQuestionResponse addNewQuestionResponse = AddNewQuestionResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return addNewQuestionResponse;
        }

        internal struct AddNewQuestionResponse
        {
            public uint status;

            public AddNewQuestionResponse(uint status)
            {
                this.status = status;
            }

            public static AddNewQuestionResponse Deserialize(List<byte> list)
            {
                AddNewQuestionResponse response = new AddNewQuestionResponse((uint)list[0]);
                return response;
            }
        }
    }
}
