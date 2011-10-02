/*
 *
 * SetMaxPing include
 * http://code.google.com/p/samp-anticheat
 *
 */

/* PAWNO stuff */
/*
native SetMaxPing(playerid = -1, ping = 160, max_probes = 5);
native GetMaxPing(playerid = -1);
native GetMaxProbes(playerid = -1);
native SetPingKickMessageForPlayer(message[], color = 0xff0000ff);
native SetPingKickMessageForAll(message[], color = 0xff0000ff);
native GetPingKickMessageForPlayer(message[], color = 0);
native GetPingKickMessageForAll(message[], color = 0);
*/

#if defined _kHPK_included
  #endinput
#endif
#define _kHPK_included

#if !defined _samp_included
  #tryinclude "a_samp.inc"
#endif
#if !defined _samp_included
  #error SetMaxPing: a_samp.inc could not be included
#endif

/* Allocate variables */
enum SetMaxPing_bitEnum (<<=1)
{
  SetMaxPing_hasOPC,
  SetMaxPing_hasOPDC,
  SetMaxPing_hasOPU,
  SetMaxPing_hasGMI,
  SetMaxPing_hasFSI
}
new
 SetMaxPing_maxping[MAX_PLAYERS][2],
 SetMaxPing_probes[MAX_PLAYERS],
 SetMaxPing_gmaxping[2],
 SetMaxPing_messagetoplayer[128],
 SetMaxPing_messagetoall[128];

forward SMP_OnPlayerConnect(playerid);
forward SMP_OnPlayerDisconnect(playerid, reason);
forward SMP_OnPlayerUpdate(playerid);
forward SMP_GMInit();
forward SMP_FSInit();
forward OnPlayerPingKick(playerid, ping);



#define PING_KICK_MESSAGE "[High Ping Checker] You have been kicked due to high ping." // The message shown to user when gets kicked
#define PING_KICK_MESSAGE_TO_ALL "[High Ping Checker] %s have been kicked due to high ping." // The message shown to all users when player gets kicked
#define PING_KICK_COLOR #ff0000ff // The color of the messages


#include <a_samp>

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