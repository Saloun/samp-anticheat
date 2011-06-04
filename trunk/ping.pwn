/*
 *
 * High ping kicker filterscript
 * http://code.google.com/p/samp-anticheat
 *
*/

#define PING_MAX_PING 160 // The maximum of allowed latency in milliseconds
#define PING_PROBES 5 // If the player's latency is more than the maximum allowed {PING_PROBES} times in a row he gets kicked (to avoid packet loss)
#define PING_KICK_MESSAGE "[High Ping Checker] You have been kicked due to high ping." // The message shown to user when gets kicked
#define PING_KICK_MESSAGE_TO_ALL "[High Ping Checker] %s have been kicked due to high ping." // The message shown to all users when player gets kicked
#define PING_KICK_COLOR #ff0000ff // The color of the messages


#include <a_samp>

new pingPlayers[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
  pingPlayers[playerid] = 0;
  return 1;
}

public OnPlayerUpdate(playerid)
{
  pPing = GetPlayerPing(playerid);
  if (pPing < PING_MAX_PING)
  {
    pingPlayers[playerid] = 0;
    return 1;
  }
  if (pPing > 65534) return 1;
  pingPlayers[playerid] = pingPlayers[playerid] + 1;
  if (pingPlayers[playerid] > PING_PROBES)
  {
    pingPlayers[playerid] = 0;
    new msg[128], pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, MAX_PLAYER_NAME);
    format(msg, sizeof(msg), PING_KICK_MESSAGE_TO_ALL, pName);
    SendClientMessage(playerid, PING_KICK_COLOR, PING_KICK_MESSAGE);
    SendClientMessageToAll(PING_KICK_COLOR, msg);
    Kick(playerid);
  }
  return 1;
}