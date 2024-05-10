using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class CreateRoomRequest
    {
        private string roomName;
        private uint maxUsers;
        private uint questionCount;
        private uint answerTimeout;
        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }

        internal struct CreateRoomResponse
        {
            public CreateRoomResponse(uint status)
            {
                this.status = status;
            }

            public uint status;
        }
    }
}
