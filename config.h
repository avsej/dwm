/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:size=10:bold" };
static const char dmenufont[]       = "xos4 Terminus:size=10:bold";
static const char normbordercolor[] = "#3a3a3a";
static const char normbgcolor[]     = "#dcdccc";
static const char normfgcolor[]     = "#3a3a3a";
static const char selbordercolor[]  = "#dcdccc";
static const char selbgcolor[]      = "#3a3a3a";
static const char selfgcolor[]      = "#dcdccc";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};



/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,  "gpicker",       NULL,       0,            1,        -1 },
	{ "Xchat",  NULL,       NULL,       1 << 6,       0,       -1 },
	{ "Hexchat",  NULL,       NULL,       1 << 6,       0,       -1 },
	{ "stalonetray",  NULL,       NULL,       1 << 8,       0,       -1 },
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt256c-ml", NULL };
static const char *dictcmd[]  = { "urxvt256c-ml", "-e", "sdcv", NULL };
static const char *bccmd[]  = { "emacsclient", "-c", "-a", "", NULL };
static const char *playercmd[]  = { "urxvt256c-ml", "-e", "mocp", NULL };
static const char *octavecmd[]   = { "urxvt256c-ml", "-e", "octave", "--no-gui", "--silent", "--no-history", NULL };

static const char *volumedowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *volumeupcmd[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *volumemutecmd[]   = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *mpctogglecmd[]   = { "mpc", "toggle", NULL };
static const char *mpcnextcmd[]   = { "mpc", "next", NULL };
static const char *mpcprevcmd[]   = { "mpc", "prev", NULL };

static const char *shuttercmd[]   = { "shutter", "-s", NULL };
static const char *ejectcmd[]   = { "eject", "-T", NULL };
static const char *lockcmd[]   = { "slock", NULL };
static const char *mailcmd[]   = { "claws-mail", NULL };
static const char *wwwcmd[]   = { "google-chrome", NULL };

static const char *britdown[]   = { "xbacklight", "-dec", "10", NULL };
static const char *britup[]   = { "xbacklight", "-inc", "10", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XK_F12,    spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = shuttercmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = bccmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_z,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = dictcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = playercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_c,      spawn,          {.v = octavecmd } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

/*
        { 0,   XF86XK_MonBrightnessDown,  spawn,        { .v = britdown } },
        { 0,   XF86XK_MonBrightnessUp,    spawn,        { .v = britup } },
*/

        { 0,   XF86XK_AudioLowerVolume,   spawn,        { .v = volumedowncmd } },
        { 0,   XF86XK_AudioRaiseVolume,   spawn,        { .v = volumeupcmd } },
        { 0,   XF86XK_AudioMute,          spawn,        { .v = volumemutecmd } },
        { 0,   XF86XK_AudioPlay,          spawn,        { .v = mpctogglecmd } },
        { 0,   XF86XK_AudioNext,          spawn,        { .v = mpcnextcmd } },
        { 0,   XF86XK_AudioPrev,          spawn,        { .v = mpcprevcmd } },
        /* { 0,   XF86XK_HomePage,           spawn,        { .v = wwwcmd } }, */
        /*
        { 0,   XF86XK_Mail,               spawn,        { .v = mailcmd } },
        */
        { 0,   XF86XK_Eject,              spawn,        { .v = ejectcmd } },
        { 0,   XK_Print,                  spawn,        { .v = shuttercmd } },

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
