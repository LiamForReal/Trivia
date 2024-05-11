using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.TextFormatting;

namespace TriviaClient
{
    internal class LoginRequest
    {
        private string username;
        private string password;

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
        public List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.LOGIN_RC);

            // example:
            //LoginResponse loginResponse = LoginResponse.Deserialize(list);
            string jsonMsg = JsonConvert.SerializeObject(this);

            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }
        internal struct LoginResponse
        {
            public uint status;
            public LoginResponse(uint status)
            {
                this.status = status;
            }
            public static LoginResponse Deserialize(List<byte> list)
            {
                LoginResponse response = new LoginResponse((uint)list[0]);
                return response;
            }
        }
    }
}
