using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static TriviaClient.SignupRequest;

namespace TriviaClient
{
    internal class LogOutResquest
    {
        public List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.LOGOUT_RC);

            return list;
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
                LogoutResponse lr = new LogoutResponse();
                lr.status = (uint)list[0];
                return lr;
            }
        }
    }
}
