using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            // logic
            return new List<byte>();
        }

        internal struct LoginResponse
        {
            public LoginResponse(uint status)
            {
                this.status = status;
            }

            public uint status;

            // like second constructor
            public static LoginResponse Deserialize(List<byte> list)
            {
                // logic
                // this.status = status from logic;
                return new LoginResponse();
            }
        }
    }
}
