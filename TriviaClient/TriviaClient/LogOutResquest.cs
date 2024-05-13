using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.SignupRequest;

namespace TriviaClient
{
    internal class LogOutResquest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.LOGOUT_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public LogoutResponse GetFromServer(NetworkStream clientStream)
        {
            LogoutResponse LogOutResponse = LogoutResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return LogOutResponse;
        }
        internal struct LogoutResponse
        {
            public uint status;
            public LogoutResponse(uint status)
            {
                this.status = status;
            }

            public static LogoutResponse Deserialize(List<byte> list)
            {
                LogoutResponse response = new LogoutResponse((uint)list[0]);
                return response;
            }
        }
    }
}
