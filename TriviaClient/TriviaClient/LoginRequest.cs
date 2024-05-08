using System;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaClient
{
    class LoginRequest
    {
        private string username { get; set; }
        private string password { get; set; }

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }

        public List<byte> Serialize()
        {
            List<byte> list = new List<byte>();

            byte statusCode = 100;
            list.Add(statusCode);

            string message = $@"{{'username': '{this.username}', 'password': '{this.password}'}}";
            message = JsonConvert.SerializeObject(message, Formatting.Indented);
            message = message.Replace("'", "\"");
            message = message.Substring(1, message.Length - 2);

            UInt32 length = (UInt32)(message.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(message));

            return list;
        }
    }
}
