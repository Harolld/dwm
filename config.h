/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */

static const int statusallmon       = 1;        /* 1 to display status on all monitor, 0 for just selected monitor */

#define ICONSIZE 12   /* icon size */
#define ICONSPACING 10 /* space between icon and title */

static const char *fonts[]          = { "RobotoMono Nerd Font:size=12","JoyPixels:size=12" };
static const char dmenufont[]       = "RobotoMono Nerd Font:size=12";

static const char databaseLocation[]= "/home/harold/mainKeePass.kdbx";

static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff5555";
static const char col_green[]       = "#50fa7b";
static const char col_yellow[]      = "#f1fa8c";
static const char col_blue[]        = "#bd93f9";
static const char col_magenta[]     = "#ff79c6";
static const char col_cyan[]        = "#8be9fd";
static const char col_white[]       = "#bbbbbb";

static const char col_bg[]          = "#282a36";
static const char col_fg[]          = "#f8f8f2";

static const char *colors[][3]      = {
	/*                   fg         bg         border   */
	[SchemeStatus] = { col_white, col_bg,    col_blue  },
	[SchemeNorTag] = { col_white, col_bg,    col_blue  },
	[SchemeSelTag] = { col_cyan,  col_bg,    col_blue  },
    [SchemeWinTag] = { col_yellow,col_bg,    col_blue  },
	[SchemeNorTit] = { col_white, col_bg,    col_blue  },
	[SchemeSelTit] = { col_fg,    col_bg,    col_blue  },
    [SchemeLtsymb] = { col_white, col_bg,    col_blue  },
	[SchemeNorm]   = { col_fg,    col_bg,    col_blue  },
	[SchemeSel]    = { col_fg,    col_bg,    col_magenta  },
};

static const char *barcolors[] = {
	"#000000",
	"#7f0000",
	"#007f00",
	"#7f7f00",
	"#00007f",
	"#7f007f",
	"#007f7f",
	"#cccccc",
	"#333333",
	"#ff0000",
	"#00ff00",
	"#ffff00",
	"#0000ff",
	"#ff00ff",
	"#00ffff",
	"#ffffff",
};

/* tagging */
static const char *tags[]       = { "???", "???", "???", "???", "???", "???", "???", "???", "???" };
static const char *alttags[]    = { "???", "???", "???", "???", "???", "???", "???", "???", "???" };

static const unsigned int ulinepad	= 3;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "librewolf",NULL,       NULL,       1 << 2,       0,           -1 },
    { NULL,       "vlc",      NULL,       1 << 8,       0,           -1 },
    { NULL,       NULL,       "Spotify",  1 << 7,       0,           -1 },
    { NULL,       "discord",  NULL,       1 << 6,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *screencmd[]  = { "screengrab", "-r", NULL };
static const char *keepmcmd[]   = { "keepmenu", "-d", databaseLocation, NULL };

static const char *blup[]       = { "xbacklight", "-inc", "5", NULL };
static const char *bldown[]     = { "xbacklight", "-dec", "5", NULL };

static const char *volup[]      = { "pactl", "set-sink-volume", "0", "+5%", NULL};
static const char *voldown[]    = { "pactl", "set-sink-volume", "0", "-5%", NULL};
static const char *volmute[]    = { "pactl", "set-sink-mute", "0", "toggle", NULL}; 

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

    { MODKEY,                       XK_g,      spawn,          {.v = keepmcmd } },

    { 0,                            XK_Print,  spawn,          {.v = screencmd } },

    { 0,                            XF86XK_MonBrightnessUp,     spawn,      {.v = blup } },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,      {.v = bldown } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,      {.v = volup } },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,      {.v = voldown } },
    { 0,                            XF86XK_AudioMute,           spawn,      {.v = volmute } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
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

