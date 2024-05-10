using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetHighScoreRequest
    {
        internal struct GetHighScoreResponse
        {
            public GetHighScoreResponse(uint status, List<string> statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public uint status;
            public List<string> statistics;
        }
    }
}
