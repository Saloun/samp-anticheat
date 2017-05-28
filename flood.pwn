/*
 *
 * Anti-Flood and Anti-Repeat script
 * 
 *
*/

#include <a_samp>

#define antispam_warning_color 0xff9900aa
#define antispam_warning_text2 "[Anti-Spam]: Don't write messages so fast!" // The message when the player floods
#define antispam_warning_text1 "[Anti-Spam]: Don't repeat yourself!" // The message when the player repeats
#define antispam_throttle_msec 1500 // Time in milliseconds between two messages detected as flooding (1000 milliseconds = 1 seconds)
#define antispam_show_warning // Comment this if AntiSpam should not warn users about flooding
#define antispam_block_message // Comment this if AntiSpam should not block flooded messages ( not recommended to comment out )
#define antispam_behavior_doublecheck true // If true, it checks the time between flood messages, too ( recommended ) [added in r6]
#define antispam_behavior_ignorecaps true // if true, it does not check the case of messages ( example will be same as ExAmplE ) [added in r13]
//#define antispam_admins_can_spam // Uncomment this to allow RCON admins spam

enum flood_Players {
  Last_Message[128],
  Last_Tick,
  Last_Spamtype // 0: no spam - 1: repeating - 2: flooding
}

new floodPlayers[MAX_PLAYERS][flood_Players];

public OnFilterScriptInit()
{
  print("\nLoading flood protection\n");
  return 1;
}

public OnPlayerConnect(playerid)
{
  floodPlayers[playerid][Last_Tick] = 0;
  floodPlayers[playerid][Last_Message][0] = 0;
  floodPlayers[playerid][Last_Spamtype] = 0;
  return 1;
}

public OnPlayerText(playerid, text[])
{
  if (IsPlayerSpamming(playerid, text))
  {
    #if defined antispam_admins_can_spam
      if (IsPlayerAdmin(playerid)) return 1;
    #endif
    #if defined antispam_show_warning
    switch (floodPlayers[playerid][Last_Spamtype])
    {
      case 1:
      {
        SendClientMessage(playerid, antispam_warning_color, antispam_warning_text1);
      }
      case 2:
      {
        SendClientMessage(playerid, antispam_warning_color, antispam_warning_text2);
      }
    }
    #endif
    #if defined antispam_block_message
    return 0;
    #else
    return 1;
    #endif
  }
  return 1;
}

stock IsPlayerSpamming(playerid, message[])
{
  if (!floodPlayers[playerid][Last_Tick])
  {
    floodPlayers[playerid][Last_Tick] = GetTickCount();
    floodPlayers[playerid][Last_Spamtype] = 0;
    floodPlayers[playerid][Last_Message][0] = 0;
    strcat(floodPlayers[playerid][Last_Message], message);
    return 0;
  }

  if (strcmp(message, floodPlayers[playerid][Last_Message], antispam_behavior_ignorecaps) == 0)
  {
    floodPlayers[playerid][Last_Spamtype] = 1;
    return 1;
  }
  
  if (GetTickCount() - floodPlayers[playerid][Last_Tick] < antispam_throttle_msec)
  {
    #if antispam_behavior_doublecheck
      floodPlayers[playerid][Last_Tick] = GetTickCount();
    #endif
    floodPlayers[playerid][Last_Spamtype] = 2;
    return 1;
  }

  floodPlayers[playerid][Last_Spamtype] = 0;
  floodPlayers[playerid][Last_Message][0] = 0;
  strcat(floodPlayers[playerid][Last_Message], message);
  floodPlayers[playerid][Last_Tick] = GetTickCount();
  return 0;
}
