using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.LoginRequest;

namespace TriviaClient
{
    internal class SignupRequest
    {

        private string username;
        private string password;
        private string email;
        public SignupRequest(string username, string password, string email)
        {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.SIGNUP_RC);

            string jsonMsg = JsonConvert.SerializeObject(this);

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }

        internal struct SignupResponse
        {
            public uint status;
            public SignupResponse(uint status)
            {
                this.status = status;
            }

            public static SignupResponse Deserialize(List<byte> list)
            {
                SignupResponse response = new SignupResponse((uint)list[0]);
                return response;
            }
        }
    }
}
