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



/* ALS allocate variable */
new
  ADH_hasOnDialogResponse[1 char];

/* ALS forwards */
forward ADH_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
forward ADH_OnFilterScriptInit();
forward ADH_OnGameModeInit();

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
  static
    iDialogID,
    iReturnValue,
    szDummy[2] = { 1, 0 };                                 /* empty inputtext */
  
  iDialogID = GetPVarInt(playerid, "dId1");
 
  if (iDialogID < 1 || iDialogID > 32767) return 1;     /* illegal dialog ids */
  
  if (ADH_hasOnDialogResponse{0} & 1)      /* ADH_OnDialogResponse is present */
  {
    iReturnValue = CallLocalFunction("ADH_OnDialogResponse",
    "iiiis",                               /* we pass 4 integers and 1 string */
    playerid, iDialogID, response, listitem,             /* pass the integers */
    inputtext[0] == 0 ?                    /* is the string completely empty? */
    szDummy :                       /* pass a dummy value to prevent crashing */
    inputtext                                  /* pass inputtext if not empty */
    );
    
    if (iReturnValue == 1)           /* the current script handled the dialog */
    {
      SetPVarInt(playerid, "dId1", 0); /* we use PVar for cross-compatibility */
      return 1;
    }
    else   /* the current script did not handle the dialog, pass it to others */
    {
      return 0;
    }
  }
  else /* the current script doesn't have OnDialogResponse, pass it to others */
  {
    return 0;
  }
}

public OnFilterScriptInit()
{
  if (funcidx("ADH_OnDialogResponse") != -1) ADH_hasOnDialogResponse{0} |= 1;
  return (funcidx("ADH_OnFilterScriptInit") == -1) ? 1 : CallLocalFunction("ADH_OnFilterScriptInit", "");
}

public OnGameModeInit()
{
  if (funcidx("ADH_OnDialogResponse") != -1) ADH_hasOnDialogResponse{0} |= 1;
  return (funcidx("ADH_OnGameModeInit") == -1) ? 1 : CallLocalFunction("ADH_OnGameModeInit", "");
}

stock ADH_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
  SetPVarInt(playerid, "dId1", dialogid);
  return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

stock GetPlayerDialogID(playerid)
  return GetPVarInt(playerid, "dId1");

/* ALS hooks */

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit ADH_OnFilterScriptInit

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit ADH_OnGameModeInit

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse ADH_OnDialogResponse

#if defined _ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog ADH_ShowPlayerDialog


native GetPlayerDialogID(playerid) = ADH_GetPlayerDialog;