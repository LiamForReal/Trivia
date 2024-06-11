using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class PlayerResults
    {
        public string username;
        public uint correctAnswerCount;
        public uint wrongAnswerCount;
        public double averageAnswerTime;

        public PlayerResults(string username, uint correctAnswerCount, uint wrongAnswerCount, double averageAnswerTime) 
        {
            this.username = username;
            this.correctAnswerCount = correctAnswerCount;
            this.wrongAnswerCount = wrongAnswerCount;
            this.averageAnswerTime = averageAnswerTime;
        }
    }
}
