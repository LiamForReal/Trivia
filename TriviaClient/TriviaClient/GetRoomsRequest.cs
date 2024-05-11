using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class GetRoomsRequest
    {
        public List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_ROOMS_RC);
            return list;
        }
        internal struct GetRoomsResponse
        {
            public uint status;
            public GetRoomsResponse(uint status)
            {
                this.status = status;
            }

            public static GetRoomsResponse Deserialize(List<byte> list)
            {
                GetRoomsResponse response = new GetRoomsResponse((uint)list[0]);
                return response;
            }
        }
    }
}
