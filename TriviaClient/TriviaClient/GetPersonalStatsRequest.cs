using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetPersonalStatsRequest
    {
        internal struct GetPersonalStatsResponse
        {
            public GetPersonalStatsResponse(uint status, List<string> statistics)
            {
                this.status = status;
                this.statistics = statistics;
            }

            public uint status;
            public List<string> statistics;
        }
    }
}
