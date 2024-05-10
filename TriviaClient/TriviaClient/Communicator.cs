using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal static class Communicator
    {
        public static List<byte> Serialize(string jsonMsg, byte status)
        {
        
            List<byte> list = new List<byte>();
            list.Add(status);

            // example:
            // LoginResponse loginResponse = LoginResponse.Deserialize(list);


            jsonMsg = JsonConvert.SerializeObject(jsonMsg, Formatting.Indented);
            jsonMsg = jsonMsg.Replace("'", "\"");
            jsonMsg = jsonMsg.Substring(1, jsonMsg.Length - 2);

            UInt32 length = (UInt32)(jsonMsg.Length);
            list.AddRange(BitConverter.GetBytes(length));

            list.AddRange(Encoding.ASCII.GetBytes(jsonMsg));

            return list;
        }
    }
}
