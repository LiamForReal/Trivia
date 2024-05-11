using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

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
            byte[] response = new byte[4096];
            clientStream.Read(response, 0, 4096);

            foreach (byte b in response)
            {
                Console.Write((char)b);
            }
            Console.WriteLine();
        }

        public static List<byte> GetMsgFromServer(NetworkStream clientStream)
        {
            List<byte> responseData = new List<byte>();
            byte[] responseBuffer = new byte[4096];
            int bytesRead;

            do
            {
                bytesRead = clientStream.Read(responseBuffer, 0, responseBuffer.Length);
                for (int i = 0; i < bytesRead; i++)
                {
                    responseData.Add(responseBuffer[i]);
                }
            } while (bytesRead == responseBuffer.Length);

            return responseData;
        }

    }
}
