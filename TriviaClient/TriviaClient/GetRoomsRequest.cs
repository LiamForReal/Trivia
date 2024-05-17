using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaClient
{
    internal class GetRoomsRequest
    {
        private List<byte> Serialize()
        {

            List<byte> list = new List<byte>();
            list.Add((byte)Cods.ResponseCode.GET_ROOMS_RC);
            return list;
        }

        public void SendToServer(NetworkStream clientStream)
        {
            SocketTools.SendToServer(Serialize(), clientStream);
        }
        public GetRoomsResponse GetFromServer(NetworkStream clientStream)
        {
            GetRoomsResponse GetRoomsResponse = GetRoomsResponse.Deserialize(SocketTools.GetMsgFromServer(clientStream));
            return GetRoomsResponse;
        }

        internal struct GetRoomsResponse
        {
            public uint status;
            public List<CreateRoomRequest.RoomData> rooms;

            public GetRoomsResponse(uint status, List<CreateRoomRequest.RoomData> rooms)
            {
                this.status = status;
                this.rooms = rooms;
            }

            public GetRoomsResponse(uint status)
            {
                this.status = status;
                this.rooms = new List<CreateRoomRequest.RoomData>();
            }

            public static GetRoomsResponse Deserialize(List<byte> list)
            {
                GetRoomsResponse response = new GetRoomsResponse((uint)list[0]);

                UInt32 length = BitConverter.ToUInt32(list.GetRange(1, 4).ToArray());

                if (length > 0)
                {
                    byte[] bytes = list.GetRange(5, (int)(length)).ToArray();
                    char[] chars = (System.Text.Encoding.UTF8.GetString(bytes).ToCharArray());
                    string jsonMessage = "";

                    foreach (char ch in chars)
                    {
                        jsonMessage += ch;
                    }

                    response = JsonConvert.DeserializeObject<GetRoomsResponse>(jsonMessage);
                }

                return response;
            }
        }
    }
}
