using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace TriviaClient
{
    internal static class SocketTools
    {
        public static void SendToServer(List<byte> list, NetworkStream clientStream)
        {
            byte[] buffer = list.ToArray();
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();

            // FOR DEBUG:
/*            byte[] response = new byte[4096];
            clientStream.Read(response, 0, 4096);

            foreach (byte b in response)
            {
                Console.Write((char)b);
            }
            Console.WriteLine();*/
        }

        public static List<byte> GetMsgFromServer(NetworkStream clientStream)
        {
            List<byte> responseData = new List<byte>();
            byte statusCode = (byte)clientStream.ReadByte();
            MessageBox.Show(statusCode.ToString());
            responseData.Add(statusCode);
            byte[] lengthBytes = new byte[4];
            int result =  clientStream.Read(lengthBytes, 0, 4);
            responseData.AddRange(lengthBytes);

            UInt32 length = BitConverter.ToUInt32(lengthBytes);

            if (result != -1 && length != 0)
            {
                byte[] jsonData = new byte[length];
                clientStream.Read(jsonData, 0, (int)length);
                responseData.AddRange(jsonData);
            }

            clientStream.Flush();

            return responseData;
        }

    }
}
