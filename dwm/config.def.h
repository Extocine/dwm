/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222"; /* The grey behind the Icons */
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb"; /*Icon Colors*/ /*bbbbbb*/
static const char col_gray4[]       = "#222222"; /*Window Title Text Color*/
static const char col_cyan[]        = "#46c8c0"; /*Main Color*/
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "discord",     NULL,       NULL,       1 << 2,             0,       -1 },
	{ "TelegramDesktop",     NULL,       NULL,       1 << 2,             0,       -1 },
	{ "Google-chrome",  NULL,    NULL,       1 << 1,             0,       -1 },
	{ "Google Chrome",  NULL,    NULL,       1 << 1,             0,       -1 },
	{ "Nemo",	NULL,	NULL,		 1 << 4,		0,	 -1 },
	{ "Nautilus",	NULL,	NULL,		 1 << 4,		0,	 -1 },
	{ "steam", NULL,	NULL,		 1 << 3,		0,	 -1 },
	{ "Spotify", "spotify",	"Spotify",	 1 << 5,		0,	 -1 },
	{ "Pavucontrol", NULL,	NULL,		 1 << 8,		0,	 -1 },
	{ "KeePassXC", NULL,	NULL,		 1 << 8,		0,	 -1 },
	{ "Minecraft Launcher", NULL,	NULL,	 1 << 3,		0,	 -1 },
 	{ "yuzu", NULL,    NULL,          	 1 << 3,                0,       -1 },
	{ "Timeshift-gtk", NULL,    NULL,        1 << 7,                0,       -1 },
        { "Timeshift-launcher", NULL,    NULL,   1 << 7,                0,       -1 },
        { "dolphin-emu", NULL,    NULL,          1 << 3,                0,       -1 },



};

/* layout(s) */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define XF86XK_AudioRaiseVolume	0x1008FF13

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,    		        XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,	        XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY,             	        XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrogaps,      {.i = -1 } },
/*	{ MODKEY,                       XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY,                       XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY,                       XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY,                       XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_9,      incrovgaps,     {.i = -1 } }, */
	{ MODKEY|ShiftMask,  	        XK_0,      togglegaps,     {0} },
	{ MODKEY,		        XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,			XK_Super_L, spawn,	  SHCMD("ulauncher") },
	{ MODKEY|ShiftMask, 		XK_p, 	   spawn, 	  SHCMD("flameshot gui") },
        { MODKEY|ShiftMask,             XK_m,      spawn,         SHCMD("killall Discord") },
	{ MODKEY,                       XK_F5,     spawn,         SHCMD("setxkbmap us") },
        { MODKEY,                       XK_F6,     spawn,         SHCMD("setxkbmap ru -variant phonetic") },
        { ControlMask|ShiftMask,        XK_Escape, spawn,         SHCMD("gnome-system-monitor") },
        {MODKEY|ShiftMask|ControlMask,  XK_c,      spawn,         SHCMD("xkill") },
        {MODKEY|ShiftMask|ControlMask,  XK_Return, spawn,         SHCMD("cool-retro-term -p ~/.config/cool-retro-term/custom.json") },
        {Mod4Mask,                      XK_e,      spawn,         SHCMD("nemo") },
        {Mod4Mask,                      XK_period, spawn,         SHCMD("gnome-characters") },
	{0, XF86XK_AudioRaiseVolume,          	   spawn,         SHCMD("amixer set Master 5%+") },
        {0, XF86XK_AudioMute,          		   spawn,         SHCMD("amixer set Master mute") },
        {0, XF86XK_AudioLowerVolume,          	   spawn,         SHCMD("amixer set Master 5%-") },
	{0, XF86XK_Calculator,          	   spawn,         SHCMD("gnome-calculator") },
        {0, XF86XK_Explorer,                     spawn,         SHCMD("arandr") },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
