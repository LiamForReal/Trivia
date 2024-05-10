using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
