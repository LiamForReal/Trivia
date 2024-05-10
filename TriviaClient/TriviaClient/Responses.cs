using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class Responses
    {
        internal struct LoginResponse
        {
            public LoginResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
        }

        internal struct SignupResponse
        {
            public SignupResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
        }


    }
}
