/*
 *
 * Anti-DialogHack [Include]
 * http://samp-anticheat.googlecode.com
 *
 * (C) KoczkaHUN 2011 @ samp-anticheat
 */

#if defined _saADH_included
  #endinput
#endif
#define _saADH_included

#if !defined _samp_included
  #tryinclude "a_samp.inc"
#endif
#if !defined _samp_included
  #error Anti-Dialog Hack: a_samp.inc could not be included
#endif

#define SA_ADH_cODR(%0,%1,%2,%3,%4) CallLocalFunction("SA_ADH_ODR","iiiis",%0,%1,%2,%3,%4)

/* ALS allocate variable */
new bool:SA_ADH_DR;

/* ALS forwards */
forward SA_ADH_ODR(playerid, dialogid, response, listitem, inputtext[]);
forward SA_ADH_OFI();
forward SA_ADH_OGI();

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
  new SA_ADH_ODR_dialogid = GetPVarInt(playerid, "dId1");
  if (SA_ADH_ODR_dialogid < 1 || SA_ADH_ODR_dialogid > 32767) return 1; /* illegal dialog ids */
  if (SA_ADH_DR)
  {
    if (SA_ADH_cODR(playerid, SA_ADH_ODR_dialogid, response, listitem, inputtext) == 1) /* the current script handled the dialog */
    {
      SetPVarInt(playerid, "dId1", 0);
      return 1;
    }
    else /* the current script is not responsible for the dialog, pass it to others */
    {
      return 0;
    }
  }
  else /* the current script doesn't have OnDialogResponse, pass it to others */
  {
    return 0;
  }
  
  return 0; /* ignores warning */
}

public OnFilterScriptInit()
{
  SA_ADH_DR = bool:(funcidx("SA_ADH_ODR") != -1);
  return (funcidx("SA_ADH_OFI") == -1) ? 1 : CallLocalFunction("SA_ADH_OFI", "");
}

public OnGameModeInit()
{
  SA_ADH_DR = bool:(funcidx("SA_ADH_ODR") != -1);
  return (funcidx("SA_ADH_OGI") == -1) ? 1 : CallLocalFunction("SA_ADH_OGI", "");
}

stock SA_ADH_SPD(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
  SetPVarInt(playerid, "dId1", dialogid);
  return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

stock GetPlayerDialogID(playerid) return GetPVarInt(playerid, "dId1");

/* ALS hooks */

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SA_ADH_OFI

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SA_ADH_OGI

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse SA_ADH_ODR

#if defined _ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog SA_ADH_SPD

/*
native GetPlayerDialogID(playerid);
*/
