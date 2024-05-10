using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class SocketTools
    {
        private NetworkStream clientStream;
        public void SendToServer(List<byte> list)
        {
            byte[] buffer = list.ToArray();
            this.clientStream.Write(buffer, 0, buffer.Length);
            this.clientStream.Flush();

            // FOR DEBUG:
            byte[] response = new byte[4096];
            this.clientStream.Read(response, 0, 4096);

            foreach (byte b in response)
            {
                Console.Write((char)b);
            }
            Console.WriteLine();
        }

        public List<byte> GetMsgFromServer()
        {
            List<byte> responseData = new List<byte>();
            byte[] responseBuffer = new byte[4096];
            int bytesRead;

            do
            {
                bytesRead = this.clientStream.Read(responseBuffer, 0, responseBuffer.Length);
                for (int i = 0; i < bytesRead; i++)
                {
                    responseData.Add(responseBuffer[i]);
                }
            } while (bytesRead == responseBuffer.Length);

            return responseData;
        }

    }
}
