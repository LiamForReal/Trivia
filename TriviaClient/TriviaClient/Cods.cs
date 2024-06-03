using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public class Cods
    {
        public enum ResponseCode
        {
            LOGIN_RC = 10,
            SIGNUP_RC = 20,
            LOGOUT_RC = 30,
            GET_ROOMS_RC = 40,
            GET_PLAYERS_IN_ROOM_RC = 50,
            JOIN_ROOM_RC = 60,
            CREATE_ROOM_RC = 70,
            GET_HIGH_SCORE_RC = 80,
            GET_PERSONAL_STATS_RC = 90,
            CLOSE_ROOM_RC = 100,
            START_GAME_RC = 110,
            GET_ROOM_STATE_RC = 120,
            LEAVE_ROOM_RC = 130,
            GET_GAME_RESULTS_RC = 140,
            SUBMIT_ANSWER_RC = 150,
            GET_QUESTION_RC = 160,
            LEAVE_GAME_RC = 170,
        }

        public enum Status
        {
            LOGIN_STATUS = 11,
            SIGNUP_STATUS = 21,
            LOGOUT_STATUS = 31,
            GET_ROOMS_STATUS = 41,
            GET_PLAYERS_IN_ROOM_STATUS = 51,
            JOIN_ROOM_STATUS = 61,
            CREATE_ROOM_STATUS = 71,
            GET_HIGH_SCORE_STATUS = 81,
            GET_PERSONAL_STATS_STATUS = 91,
            CLOSE_ROOM_STATUS = 101,
            START_GAME_STATUS = 111,
            GET_ROOM_STATE_STATUS = 121,
            LEAVE_ROOM_STATUS = 131,
            GET_GAME_RESULTS_STATUS = 141,
            SUBMIT_ANSWER_CORRECT = 151,
            SUBMIT_ANSWER_WRONG = 152,
            GET_QUESTION_STATUS = 161,
            LEAVE_GAME_STATUS = 171,
        }

        public enum Errors
        {
            LOGIN_ERROR = 15,
            SIGNUP_ERROR = 25,
            PASSWORD_WEAK = 26,
            LOGOUT_ERROR = 35,
            GET_ROOMS_ERROR = 45,
            GET_PLAYERS_IN_ROOM_ERROR = 55,
            JOIN_ROOM_ERROR = 65,
            CREATE_ROOM_ERROR = 75,
            GET_HIGH_SCORE_ERROR = 85,
            THERE_IS_NO_SCORES = 86,
            GET_PERSONAL_STATS_ERROR = 95,
            CLOSE_ROOM_ERROR = 105,
            START_GAME_ERROR = 115,
            GET_ROOM_STATE_SERVER_ERROR = 125,
            GET_ROOM_STATE_ROOM_ERROR = 126,
            LEAVE_ROOM_ERROR = 135,
            GET_GAME_RESULTS_ERROR = 145,
            SUBMIT_ANSWER_ERROR = 155,
            GET_QUESTION_ERROR = 165,
            LEAVE_GAME_ERROR = 175,
        }
    }
}

