using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class LogOutResquest
    {
        internal struct LogoutResponse
        {
            public LogoutResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
        }
    }
}
