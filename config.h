/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */


static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps		    = 1;        /* 1 means no outer gap when there is only one window */


static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Serif:size=10:style=Bold", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "Sans:size=10:style=Bold";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#004242";
static const unsigned int baralpha  = 0x40;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "壹", "貳", "叄", "肆", "伍", "陸", "柒", "捌", "玖" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",         tile },    /* first entry is default */
	{ "TTT",      bstack },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },

	{ "H[]",      deck },
	{ "[M]",      monocle },

	{ "|M|",      centeredmaster },
	{ ">M<",      centeredfloatingmaster },

	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },

	// { "===",      bstackhoriz },
	// { "HHH",      grid },
	// { "###",      nrowgrid },
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#include <X11/XF86keysym.h>
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x25", NULL };

static Key keys[] = {
	/* modifier                     key        	function        argument */
	{ Mod1Mask,                     XK_space,	spawn,          {.v = dmenucmd} },
	{ MODKEY|ShiftMask,             XK_space,  	setlayout,	{0} },
	{ Mod1Mask,                     XK_Tab,    	zoom,		{0} },
	{ MODKEY,                       XK_Tab,    	view,           {0} },
	{ MODKEY,             		XK_Return,	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,	togglescratch,  {.v = scratchpadcmd } },

	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,                       XK_b,		togglebar,      {0} },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("killall wp_change || wp_change &") },
	{ MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("xcompmgr_toggle &") },
	{ MODKEY,			XK_f,	   	togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,      	fullscreen,  	{0} },
	{ MODKEY,                       XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,			XK_i,      	setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,      	setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_j,		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY,			XK_m,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ MODKEY,                       XK_o,      	incnmaster,  	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,      	incnmaster,  	{.i = -1 } },
	{ MODKEY,                       XK_p,      	togglefloating,	{0} },
	{ MODKEY|ShiftMask,		XK_p,		spawn,		SHCMD("killall picom || picom -b &") },
	{ MODKEY,             		XK_q,      	killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      	quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      	spawn,          SHCMD("pkill dwm") },
	{ MODKEY,			XK_s,      	togglesticky,	{0} },
	{ MODKEY|ShiftMask,		XK_s,		togglesmartgaps,{0} },
	{ MODKEY,			XK_t,		spawn,		SHCMD("toggle_cmds &") },
	{ MODKEY|ShiftMask,		XK_t,      	setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_u,      	setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,      	setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("killall clash || clash &") },
	{ MODKEY,			XK_y,      	setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,      	setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },

	{ 0,				XK_Print,	spawn,		SHCMD("maim -s | xclip -selection clipboard -t image/png") },
	{ MODKEY,			XK_Print,	spawn,		SHCMD("killall screenkey || screenkey &") },
	{ ShiftMask,			XK_Print,	spawn,		{.v = (const char*[]){ "maimpick", NULL } } },
	//{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },
	{ MODKEY,                       XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         {.i = +1 } },
	{ MODKEY, 			XK_F5,		spawn,		SHCMD("ddcutil setvcp 10 40") },
	{ MODKEY|ShiftMask,		XK_F5,		spawn,		SHCMD("ddcutil setvcp 10 80") },
	{ MODKEY, 			XK_F6,		spawn,		SHCMD("ddcutil setvcp 10 - 20") },
	{ MODKEY, 			XK_F7,		spawn,		SHCMD("ddcutil setvcp 10 + 20") },

	{ 0,XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t") },
	{ 0,XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 5") },
	{ 0,XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 5") },
	{ 0, XF86XK_AudioPrev,		spawn,		{.v = (const char*[]){ "playerctl", "previous", NULL } } },
	{ 0, XF86XK_AudioNext,		spawn,		{.v = (const char*[]){ "playerctl", "next", NULL } } },
	{ 0, XF86XK_AudioPause,		spawn,		{.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioPlay,		spawn,		{.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioStop,		spawn,		{.v = (const char*[]){ "playerctl", "stop", NULL } } },
	{ 0,XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,XF86XK_TouchpadOn,		spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0,XF86XK_TouchpadOff,		spawn,		{.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0,XF86XK_MonBrightnessUp,	spawn,		{.v = (const char*[]){ "xbacklight", "-inc", "10", NULL } } },
	{ 0,XF86XK_MonBrightnessDown,	spawn,		{.v = (const char*[]){ "xbacklight", "-dec", "10", NULL } } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("dunstctl history-pop &")},
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("killall trayer || trayer --edge top --align right --height 20 --widthtype request --SetDockType true --distance 35 --distancefrom right &")},
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("dunstctl close &")},
	{ ClkStatusText,        0,              Button4,        spawn,          SHCMD("pamixer --allow-boost -i 5")},
	{ ClkStatusText,        0,              Button5,        spawn,          SHCMD("pamixer --allow-boost -d 5")},
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
