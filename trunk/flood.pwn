/*
 *
 * Anti-Flood and Anti-Repeat script
 * http://code.google.com/p/samp-anticheat
 *
*/

#include <a_samp>

#define antispam_warning_color 0xFF9900AA
#define antispam_warning_text2 "[Anti-Spam]: Don't write messages so fast!"
#define antispam_warning_text1 "[Anti-Spam]: Don't repeat yourself!"
#define antispam_throttle_msec 1000 // Time in milliseconds between two messages detected as flooding
#define antispam_show_warning // Comment this if AntiSpam should not warn users about flooding
#define antispam_block_message // Comment this if AntiSpam should not block flooded messages

enum flood_Players {
  Last_Message[128+2],
  Last_Tick,
  Last_Spamtype // 0: no spam - 1: repeating - 2: flooding
}

new floodPlayers[MAX_PLAYERS][flood_Players];

public OnFilterScriptInit()
{
  print("\nLoading flood protection - http://code.google.com/p/samp-anticheat\n");
  return 1;
}

public OnPlayerConnect(playerid)
{
  floodPlayers[playerid][Last_Tick] = 0;
  return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
  #pragma unused reason
  floodPlayers[playerid][Last_Tick] = 0;
  return 1;
}

public OnPlayerText(playerid, text[])
{
  if (IsPlayerSpamming(playerid, text))
  {
    #if defined antispam_show_warning
    switch (GetPlayerSpamType(playerid))
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
//  strcat(message, floodPlayers[playerid][Last_Message]); // This generates warning
    format(floodPlayers[playerid][Last_Message], 128+2, "%s", message); // This probably a bit slower but does not generate warning
    return 0;
  }

  if (!strcmp(message, floodPlayers[playerid][Last_Message], false))
  {
    floodPlayers[playerid][Last_Spamtype] = 1;
    return 1;
  }
  
  if (GetTickCount() - floodPlayers[playerid][Last_Tick] < antispam_throttle_msec)
  {
    floodPlayers[playerid][Last_Spamtype] = 2;
    return 1;
  }

  floodPlayers[playerid][Last_Spamtype] = 0;
//strcat(message, floodPlayers[playerid][Last_Message]); // This generates warning
  format(floodPlayers[playerid][Last_Message], 128+2, "%s", message); // This probably a bit slower but does not generate warning
  floodPlayers[playerid][Last_Tick] = GetTickCount();
  return 0;
}

stock GetPlayerSpamType(playerid)
{
  return floodPlayers[playerid][Last_Spamtype];
}
