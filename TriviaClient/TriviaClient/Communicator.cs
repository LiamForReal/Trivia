using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class Communicator
    {
        private NetworkStream clientStream;
        private LoginRequest loginRequest;
        private SignupRequest signupRequest;
        private LogOutResquest logOutResquest;
        private CreateRoomRequest createRoomRequest;
        private JoinRoomRequest joinRoomRequest;
        private GetHighScoreRequest getHighScoreRequest;
        private GetPersonalStatsRequest getPersonalStatsRequest;
        private GetPlayersInRoomRequest getPlayersInRoomRequest;
        private GetRoomsRequest getRoomsRequest;
        public Communicator(NetworkStream clientStream) 
        {
            this.clientStream = clientStream;
        }

        public void /*Request**/ getMsgFromServer(Cods.ResponseCode requestCode)
        {
            //make a pure class Request and all the requests will inherit 
            //from her and here you return the right msg by the code 
        }
        public void sendMsgToServer(Cods.ResponseCode requestCode)
        {
            //switch(requestCode)
            //{
            //    case Cods.ResponseCode.LOGIN_RC:
            //        loginRequest.SendLogIn(clientStream);
            //        break;
            //    case Cods.ResponseCode.SIGNUP_RC:
            //        signupRequest.SendSignUp(clientStream);
            //        break;
            //    case Cods.ResponseCode.LOGOUT_RC:
            //        logOutResquest.SendLogOut(clientStream);
            //        break;
            //    case Cods.ResponseCode.GET_ROOMS_RC:
            //        getRoomsRequest.SendGetRooms(clientStream);
            //        break;
            //    case Cods.ResponseCode.GET_PLAYERS_IN_ROOM_RC:
            //        getPlayersInRoomRequest.SendGetPlayerInRoom(clientStream);
            //        break;
            //    case Cods.ResponseCode.JOIN_ROOM_RC:
            //        joinRoomRequest.SendJoinRoom(clientStream);
            //        break;
            //    case Cods.ResponseCode.CREATE_ROOM_RC:
            //        createRoomRequest.SendCreateRoom(clientStream);
            //        break;
            //    case Cods.ResponseCode.GET_HIGH_SCORE_RC:
            //        getHighScoreRequest.SendHighScore(clientStream);
            //        break;
            //    case Cods.ResponseCode.GET_PERSONAL_STATS_RC:
            //        getPersonalStatsRequest.SendPersonalStats(clientStream);
            //        break;
            //    default:
            //        Console.WriteLine("invalid requst code not betwin 10 - 90");
            //        break;
            //}
           
        }
    }
}
