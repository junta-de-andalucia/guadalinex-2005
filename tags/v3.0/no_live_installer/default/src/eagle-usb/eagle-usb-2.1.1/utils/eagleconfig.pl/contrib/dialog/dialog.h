/*
 *  $Id: dialog.h,v 1.1 2004/02/15 13:21:43 Tux Exp $
 *
 *  dialog.h -- common declarations for all dialog modules
 *
 *  AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  and:    Thomas Dickey
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef DIALOG_H_included
#define DIALOG_H_included 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#define RETSIGTYPE void
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>	/* fork() etc. */
#include <math.h>	/* sqrt() */

#if defined(HAVE_NCURSESW_NCURSES_H)
#include <ncursesw/ncurses.h>
#elif defined(HAVE_NCURSES_NCURSES_H)
#include <ncurses/ncurses.h>
#elif defined(HAVE_NCURSES_CURSES_H)
#include <ncurses/curses.h>
#elif defined(HAVE_NCURSES_H)
#include <ncurses.h>
#elif defined(ultrix)
#include <cursesX.h>
#else
#include <curses.h>
#endif

/* possible conflicts with <term.h> which may be included in <curses.h> */
#ifdef color_names
#undef color_names
#endif

#ifdef buttons
#undef buttons
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#include <langinfo.h>
#define _(s) gettext(s)
#else
#undef _
#define _(s) s
#endif

#ifndef GCC_NORETURN
#define GCC_NORETURN /*nothing*/
#endif

#ifndef GCC_UNUSED
#define GCC_UNUSED /*nothing*/
#endif

/*
 * Change these if you want
 */
#define USE_SHADOW TRUE
#define USE_COLORS TRUE

#ifdef HAVE_COLOR
#define SCOLS	COLS-(use_shadow ? 2 : 0)
#define SLINES	LINES-(use_shadow ? 1 : 0)
#else
#define SCOLS	COLS
#define SLINES	LINES
#endif

#define DLG_EXIT_ESC	255
#define DLG_EXIT_UNKNOWN -2	/* never return this (internal use) */
#define DLG_EXIT_ERROR	-1	/* the shell sees this as 255 */
#define DLG_EXIT_OK	0
#define DLG_EXIT_CANCEL	1
#define DLG_EXIT_HELP	2
#define DLG_EXIT_EXTRA	3

#define CHR_BACKSPACE	8
#define CHR_REPAINT	12	/* control/L */
#define CHR_DELETE	127
#define CHR_NEXT	('n' & 0x1f)
#define CHR_PREVIOUS	('p' & 0x1f)

#define ESC 27
#define TAB 9

#define MARGIN 1
#define GUTTER 2
#define SHADOW_ROWS 1
#define SHADOW_COLS 2

#define MAX_LEN 2048
#define BUF_SIZE (10*1024)

#undef  MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#undef  MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define DEFAULT_SEPARATE_STR "\t"
#define DEFAULT_ASPECT_RATIO 9
/* how many spaces is a tab long (default)? */
#define TAB_LEN 8
#define WTIMEOUT_VAL        10

#ifndef A_CHARTEXT
#define A_CHARTEXT 0xff
#endif

#define CharOf(ch)  ((ch) & A_CHARTEXT)

#ifndef ACS_ULCORNER
#define ACS_ULCORNER '+'
#endif
#ifndef ACS_LLCORNER
#define ACS_LLCORNER '+'
#endif
#ifndef ACS_URCORNER
#define ACS_URCORNER '+'
#endif
#ifndef ACS_LRCORNER
#define ACS_LRCORNER '+'
#endif
#ifndef ACS_HLINE
#define ACS_HLINE '-'
#endif
#ifndef ACS_VLINE
#define ACS_VLINE '|'
#endif
#ifndef ACS_LTEE
#define ACS_LTEE '+'
#endif
#ifndef ACS_RTEE
#define ACS_RTEE '+'
#endif
#ifndef ACS_UARROW
#define ACS_UARROW '^'
#endif
#ifndef ACS_DARROW
#define ACS_DARROW 'v'
#endif

/* these definitions really would work for ncurses 1.8.6, etc. */
#ifndef HAVE_GETPARYX
#define getparyx(win,y,x)	(y = (win)?(win)->_pary:ERR, x = (win)?(win)->_parx:ERR)
#endif

#ifndef HAVE_GETPARX
#define getparx(win)		((win)?(win)->_parx:ERR)
#endif

#ifndef HAVE_GETPARY
#define getpary(win)		((win)?(win)->_pary:ERR)
#endif

#ifndef HAVE_GETCURX
#define getcurx(win)		((win)?(win)->_curx:ERR)
#endif

#ifndef HAVE_GETCURY
#define getcury(win)		((win)?(win)->_cury:ERR)
#endif

/*
 * Attribute names
 */
#define DIALOG_ATR(n)                 color_table[n].atr

#define screen_attr                   DIALOG_ATR(0)
#define shadow_attr                   DIALOG_ATR(1)
#define dialog_attr                   DIALOG_ATR(2)
#define title_attr                    DIALOG_ATR(3)
#define border_attr                   DIALOG_ATR(4)
#define button_active_attr            DIALOG_ATR(5)
#define button_inactive_attr          DIALOG_ATR(6)
#define button_key_active_attr        DIALOG_ATR(7)
#define button_key_inactive_attr      DIALOG_ATR(8)
#define button_label_active_attr      DIALOG_ATR(9)
#define button_label_inactive_attr    DIALOG_ATR(10)
#define inputbox_attr                 DIALOG_ATR(11)
#define inputbox_border_attr          DIALOG_ATR(12)
#define searchbox_attr                DIALOG_ATR(13)
#define searchbox_title_attr          DIALOG_ATR(14)
#define searchbox_border_attr         DIALOG_ATR(15)
#define position_indicator_attr       DIALOG_ATR(16)
#define menubox_attr                  DIALOG_ATR(17)
#define menubox_border_attr           DIALOG_ATR(18)
#define item_attr                     DIALOG_ATR(19)
#define item_selected_attr            DIALOG_ATR(20)
#define tag_attr                      DIALOG_ATR(21)
#define tag_selected_attr             DIALOG_ATR(22)
#define tag_key_attr                  DIALOG_ATR(23)
#define tag_key_selected_attr         DIALOG_ATR(24)
#define check_attr                    DIALOG_ATR(25)
#define check_selected_attr           DIALOG_ATR(26)
#define uarrow_attr                   DIALOG_ATR(27)
#define darrow_attr                   DIALOG_ATR(28)
#define itemhelp_attr                 DIALOG_ATR(29)
#define form_active_text_attr         DIALOG_ATR(30)
#define form_text_attr                DIALOG_ATR(31)

/*
 * Callbacks are used to implement the "background" tailbox.
 */
typedef struct _dlg_callback {
    struct _dlg_callback *next;
    FILE *input;
    WINDOW *win;
    bool keep_bg;	/* keep in background, on exit */
    bool bg_task;	/* true if this is background task */
    bool (*handle_getc)(struct _dlg_callback *p, int ch, int fkey, int *result);
} DIALOG_CALLBACK;

typedef struct _dlg_windows {
    struct _dlg_windows *next;
    WINDOW *normal;
    WINDOW *shadow;
} DIALOG_WINDOWS;

/*
 * Global variables, which are initialized as needed
 */
typedef struct {
    DIALOG_CALLBACK *getc_callbacks;
    DIALOG_CALLBACK *getc_redirect;
    DIALOG_WINDOWS *all_windows;
} DIALOG_STATE;

extern DIALOG_STATE dialog_state;

/*
 * Global variables, which dialog resets before each widget
 */
typedef struct {
    FILE *output;		/* option "--output-fd fd" */
    bool beep_after_signal;	/* option "--beep-after" */
    bool beep_signal;		/* option "--beep" */
    bool begin_set;		/* option "--begin y x" was used */
    bool cant_kill;		/* option "--no-kill" */
    bool colors;		/* option "--colors" */
    bool cr_wrap;		/* option "--cr-wrap" */
    bool dlg_clear_screen;	/* option "--clear" */
    bool extra_button;		/* option "--extra-button" */
    bool help_button;		/* option "--help-button" */
    bool input_menu;
    bool item_help;		/* option "--item-help" */
    bool nocancel;		/* option "--no-cancel" */
    bool nocollapse;		/* option "--no-collapse" */
    bool print_siz;		/* option "--print-size" */
    bool separate_output;	/* option "--separate-output" */
    bool size_err;		/* option "--size-err" */
    bool tab_correct;		/* option "--tab-correct" */
    bool trim_whitespace;	/* option "--trim" */
    char *backtitle;		/* option "--backtitle backtitle" */
    char *cancel_label;		/* option "--cancel-label string" */
    char *default_item;		/* option "--default-item string" */
    char *exit_label;		/* option "--exit-label string" */
    char *extra_label;		/* option "--extra-label string" */
    char *help_label;		/* option "--help-label string" */
    char *input_result;
    char *ok_label;		/* option "--ok-label string" */
    char *separate_str;		/* option "--separate-widget string" */
    char *title;		/* option "--title title" */
    int aspect_ratio;		/* option "--aspect ratio" */
    int begin_x;		/* option "--begin y x" (second value) */
    int begin_y;		/* option "--begin y x" (first value) */
    int max_input;		/* option "--max-input size" */
    int output_count;		/* # of widgets that may have done output */
    int sleep_secs;		/* option "--sleep secs" */
    int tab_len;		/* option "--tab-len n" */
    int timeout_secs;		/* option "--timeout secs" */
    unsigned input_length;	/* nonzero if input_result is allocated */
} DIALOG_VARS;

#define USE_ITEM_HELP(s)        (dialog_vars.item_help && (s) != 0)
#define CHECKBOX_TAGS           (dialog_vars.item_help ? 4 : 3)
#define MENUBOX_TAGS            (dialog_vars.item_help ? 3 : 2)
#define FORMBOX_TAGS            (dialog_vars.item_help ? 9 : 8)

extern DIALOG_VARS dialog_vars;

#ifdef HAVE_COLOR
extern bool use_colors;
extern bool use_shadow;
#endif

#ifndef HAVE_TYPE_CHTYPE
#define chtype long
#endif

#define UCH(ch)			((unsigned char)(ch))

#define assert_ptr(ptr,msg) if ((ptr) == 0) exiterr("cannot allocate memory in " msg)

/*
 * Table for attribute- and color-values.
 */
typedef struct {
    chtype atr;
#ifdef HAVE_COLOR
    int fg;
    int bg;
    int hilite;
#endif
#ifdef HAVE_RC_FILE
    char *name;
    char *comment;
#endif
} DIALOG_COLORS;

extern DIALOG_COLORS color_table[];

extern FILE *pipe_fp;
extern int defaultno;
extern int screen_initialized;

/*
 * Function prototypes
 */
#ifdef HAVE_RC_FILE
extern void create_rc (const char *filename);
extern int parse_rc (void);
#endif

void attr_clear (WINDOW * win, int height, int width, chtype attr);
void dialog_clear (void);
void end_dialog (void);
void init_dialog (void);
void put_backtitle(void);

void auto_size(const char * title, const char *prompt, int *height, int *width, int boxlines, int mincols);
void auto_sizefile(const char * title, const char *file, int *height, int *width, int boxlines, int mincols);

void exiterr(const char *, ...)
#if defined(__GNUC__) && !defined(printf)
__attribute__((format(printf,1,2)))
#endif
;
void beeping(void);
void print_size(int height, int width);
void ctl_size(int height, int width);
void tab_correct_str(char *prompt);
void calc_listh(int *height, int *list_height, int item_no);
int calc_listw(int item_no, char **items, int group);
char *strclone(const char *cprompt);
int box_x_ordinate(int width);
int box_y_ordinate(int height);
void del_window(WINDOW *win);
void draw_title(WINDOW *win, const char *title);
void draw_bottom_box(WINDOW *win);
WINDOW * new_window (int height, int width, int y, int x);
WINDOW * sub_window (WINDOW *win, int height, int width, int y, int x);

#ifdef HAVE_COLOR
int dlg_color_count (void);
void color_setup (void);
void draw_shadow (WINDOW * win, int height, int width, int y, int x);
#endif

void print_autowrap(WINDOW *win, const char *prompt, int height, int width);
void draw_box (WINDOW * win, int y, int x, int height, int width, chtype boxchar,
		chtype borderchar);

int dialog_yesno (const char *title, const char *cprompt, int height, int width, int dftno);
int dialog_msgbox (const char *title, const char *cprompt, int height,
		int width, int pauseopt);
int dialog_textbox (const char *title, const char *file, int height, int width);
int dialog_menu (const char *title, const char *cprompt, int height, int width,
		int menu_height, int item_no, char **items);
int dialog_checklist (const char *title, const char *cprompt, int height,
		int width, int list_height, int item_no,
		char ** items, int flag, int separate_output);
int dialog_inputbox (const char *title, const char *cprompt, int height,
		int width, const char *init, const int password);
int dialog_gauge (const char *title, const char *cprompt, int height, int width,
		int percent);
int dialog_tailbox (const char *title, const char *file, int height, int width, int bg_task);
int dialog_fselect (const char *title, const char *path, int height, int width);
int dialog_calendar (const char *title, const char *subtitle, int height, int width, int day, int month, int year);
int dialog_timebox (const char *title, const char *subtitle, int height, int width, int hour, int minute, int second);
int dialog_form(const char *title, const char *cprompt, int height, int width, int form_height, int item_no, char **items);

/* arrows.c */
void dlg_draw_arrows(WINDOW *dialog, int top_arrow, int bottom_arrow, int x, int top, int bottom);

/* buttons.c */
extern const char ** dlg_exit_label(void);
extern const char ** dlg_ok_label(void);
extern const char ** dlg_ok_labels(void);
extern const char ** dlg_yes_labels(void);
extern int dlg_button_x_step(const char **labels, int limit, int *gap, int *margin, int *step);
extern int dlg_char_to_button(int ch, const char **labels);
extern int dlg_match_char(int ch, const char *string);
extern int dlg_next_button(const char **labels, int button);
extern int dlg_next_ok_buttonindex(int current, int extra);
extern int dlg_ok_buttoncode(int button);
extern int dlg_prev_button(const char **labels, int button);
extern int dlg_prev_ok_buttonindex(int current, int extra);
extern void dlg_button_layout(const char **labels, int *limit);
extern void dlg_button_sizes(const char **labels, int vertical, int *longest, int *length);
extern void dlg_draw_buttons(WINDOW *win, int y, int x, const char **labels, int selected, int vertical, int limit);

/* inputstr.c */
extern bool dlg_edit_string(char *string, int *offset, int key, int fkey, bool force);
extern const int * dlg_index_columns(const char *string);
extern const int * dlg_index_wchars(const char *string);
extern int dlg_count_columns(const char *string);
extern int dlg_count_wchars(const char *string);
extern int dlg_edit_offset(char *string, int offset, int x_last);
extern int dlg_limit_columns(const char *string, int limit, int offset);
extern void dlg_show_string(WINDOW *win, const char *string, int offset, chtype attr, int y_base, int x_base, int x_last, bool hidden, bool force);

/* ui_getc.c */
extern int dlg_getc(WINDOW *win, int *fkey);
extern int dlg_getc_callbacks(int ch, int fkey, int *result);
extern int dlg_last_getc(void);
extern void dlg_add_callback(DIALOG_CALLBACK *p);
extern void dlg_flush_getc(void);
extern void dlg_remove_callback(DIALOG_CALLBACK *p);
extern void killall_bg(int *retval);

/* util.c */
extern int dlg_default_item(char **items, int llen);
extern void dlg_add_result(char *string);
extern void dlg_does_output(void);
extern void dlg_exit(int code) GCC_NORETURN;
extern void dlg_item_help(char *txt);
extern void dlg_print_text(WINDOW *win, const char *txt, int len, chtype *attr);
extern void dlg_set_focus(WINDOW *parent, WINDOW *win);
extern void dlg_trim_string(char *src);

#ifdef HAVE_STRCASECMP
#define dlg_strcmp(a,b) strcasecmp(a,b)
#else
extern int dlg_strcmp(const char *a, const char *b);
#endif

/*
 * The following stuff is needed for mouse support
 */
typedef struct mseRegion {
    int x, y, X, Y, code;
    int mode, step_x, step_y;
    struct mseRegion *next;
} mseRegion;

#if defined(NCURSES_MOUSE_VERSION)

#define	mouse_open() mousemask(BUTTON1_CLICKED, (mmask_t *) 0)
#define	mouse_close() mousemask(0, (mmask_t *) 0)

void mouse_free_regions (void);
mseRegion * mouse_mkregion (int y, int x, int height, int width, int code);
void mouse_mkbigregion (int y, int x, int height, int width, int code, int step_x, int step_y, int mode);
void mouse_setbase (int x, int y);

#define USE_MOUSE 1

#else

#define	mouse_open() /*nothing*/
#define	mouse_close() /*nothing*/
#define mouse_free_regions() /* nothing */
#define	mouse_mkregion(y, x, height, width, code) /*nothing*/
#define	mouse_mkbigregion(y, x, height, width, code, step_x, step_y, mode) /*nothing*/
#define	mouse_setbase(x, y) /*nothing*/

#define USE_MOUSE 0

#endif

extern mseRegion *mouse_region (int y, int x);
extern mseRegion *mouse_bigregion (int y, int x);
extern int mouse_wgetch (WINDOW *, int *);

#define mouse_mkbutton(y,x,len,code) mouse_mkregion(y,x,1,len,code);

/*
 * This is the base for fictitious keys, which activate
 * the buttons.
 *
 * Mouse-generated keys are the following:
 *   -- the first 32 are used as numbers, in addition to '0'-'9'
 *   -- the lowercase are used to signal mouse-enter events (M_EVENT + 'o')
 *   -- uppercase chars are used to invoke the button (M_EVENT + 'O')
 */
#define M_EVENT (KEY_MAX+1)

/*
 * The `flag' parameter in checklist is used to select between
 * radiolist and checklist
 */
#define FLAG_CHECK 1
#define FLAG_RADIO 0

#endif /* DIALOG_H_included */
