/*
 *
 * High ping kicker script
 * http://code.google.com/p/samp-anticheat
 *
*/

#define PING_MAX_PING 160 // The maximum of allowed latency in milliseconds
#define PING_PROBES 5 // If the player's latency is more than the maximum allowed {PING_PROBES} times in a row he gets kicked (to avoid packet loss)
#define PING_KICK_MESSAGE "[High Ping Checker] You have been kicked due to high ping." // The message shown to user when gets kicked
#define PING_KICK_MESSAGE_TO_ALL "[High Ping Checker] %s have been kicked due to high ping." // The message shown to all users when player gets kicked
#define PING_KICK_COLOR #FF0000 // The color of the messages


#include <a_samp>

new pingPlayers[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
  pingPlayers[playerid] = 0;
  return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
  #pragma unused reason
  pingPlayers[playerid] = 0;
  return 1;
}

public OnPlayerUpdate(playerid)
{
  if (GetPlayerPing(playerid) > PING_MAX_PING && GetPlayerPing(playerid) != 65535)
  {
    pingPlayers[playerid] = pingPlayers[playerid] + 1;
    if (pingPlayers[playerid] > PING_PROBES)
    {
      pingPlayers[playerid] = 0;
      SendClientMessage(playerid, PING_KICK_COLOR, PING_KICK_MESSAGE);
      Kick(playerid);
      new msg[256];
      format(msg, 256, PING_KICK_MESSAGE_TO_ALL, playerid);
      SendClientMessageToAll(PING_KICK_COLOR, msg);
    }
  }
  else
  {
    pingPlayers[playerid] = 0;
  }
  return 1;
}