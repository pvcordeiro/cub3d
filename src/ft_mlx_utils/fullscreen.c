
// XDisplayHeight(xvar->display, xvar->screen), XDisplayWidth(xvar->display, xvar->screen)

#include	"mlx_int.h"

#include	<unistd.h>
#include <X11/extensions/Xrandr.h>

/* global for independant extension */
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <cub3d.h>

typedef struct {
    unsigned long   flags;
    unsigned long   functions;
    unsigned long   decorations;
    long            input_mode;
    unsigned long   status;
} MotifWmHints;

#define MWM_HINTS_DECORATIONS   (1L << 1)
RRMode	saved_mode = 0;

void set_window_decorations(Display *display, Window win, int decorated)
{
    MotifWmHints hints;
    Atom prop = XInternAtom(display, "_MOTIF_WM_HINTS", False);

    hints.flags = MWM_HINTS_DECORATIONS;
    hints.decorations = decorated ? 1 : 0;

    XChangeProperty(display, win, prop, prop, 32, PropModeReplace,
                    (unsigned char *)&hints, 5);
    XFlush(display);
}

int			ft_ext_fullscreen(t_xvar *xvar, t_win_list *win)
{
  XWindowAttributes	watt;
  int			i;
  int			j;
  XRRScreenResources	*res;
  XRROutputInfo		*o_info;
  XRRCrtcInfo		*crtc;
  RRMode		mode_candidate;
  int			idx_output;
  int			idx_candidate;
  int			*fullscreen;

  fullscreen = &cub3d()->window.fullscreen;
  *fullscreen = !*fullscreen;
  set_window_decorations(xvar->display, win->window, !*fullscreen);
  if (!XGetWindowAttributes(xvar->display, win->window, &watt))
    return (0);
  res = XRRGetScreenResources(xvar->display, xvar->root);
  o_info = NULL;
  idx_output = -1;
  i = res->noutput;
  while (i--)
    {
      o_info = XRRGetOutputInfo(xvar->display, res, res->outputs[i]);
      if (o_info->connection == RR_Connected)
	{
	  idx_output = i;
	  i = 0;
	}
      else
	XRRFreeOutputInfo(o_info);
    }
  if (!o_info)
    {
      XRRFreeScreenResources(res);
      return (0);
    }
  
  idx_candidate = -1;
  i = o_info->nmode;
  while (i--)
    {
      j = res->nmode;
      while (j--)
	if (res->modes[j].id == o_info->modes[i])
	  if ((int)res->modes[j].width >= watt.width && (int)res->modes[j].height >= watt.height &&
	      (idx_candidate == -1 || res->modes[idx_candidate].width > res->modes[j].width ||
	       res->modes[idx_candidate].height > res->modes[j].height) )
	    idx_candidate = i;
    }
  if (idx_candidate < 0)
    {
      XRRFreeOutputInfo(o_info);
      XRRFreeScreenResources(res);
      return (0);
    }
  if (!*fullscreen && saved_mode == (unsigned long)-1)
    idx_candidate = 0; /* if no clue, uses first mode, usually part of npreferred */
  mode_candidate = o_info->modes[idx_candidate];
  if (!*fullscreen)
    mode_candidate = saved_mode;

  crtc = XRRGetCrtcInfo(xvar->display, res, o_info->crtc);
  saved_mode = crtc->mode;

  i = XRRSetCrtcConfig(xvar->display, res, o_info->crtc, CurrentTime, 0, 0, mode_candidate,
		       crtc->rotation, &res->outputs[idx_output], 1);
  if (*fullscreen)
    printf("found mode : %d x %d\n Status %d\n", res->modes[idx_candidate].width, res->modes[idx_candidate].height, i);
  else
    printf("back previous mode\n");
  
  XMoveWindow(xvar->display, win->window, 0, 0);
  XMapRaised(xvar->display, win->window);

  if (*fullscreen)
    {
      //      XGrabPointer(xvar->display, win->window, True, 0, GrabModeAsync, GrabModeAsync, win->window, 0L, CurrentTime);
      XGrabKeyboard(xvar->display, win->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
  else
    {
      XUngrabPointer(xvar->display, CurrentTime);
      XUngrabKeyboard(xvar->display, CurrentTime);
    }

  XSync(xvar->display, False);
  sleep(1);

  XRRFreeCrtcInfo(crtc);
  XRRFreeOutputInfo(o_info);
  XRRFreeScreenResources(res);
  return (1);
}

void	ft_restore_screen_mode(t_xvar *xvar, t_win_list *win)
{
    XWindowAttributes	watt;
    XRRScreenResources	*res;
    XRROutputInfo		*o_info = NULL;
    XRRCrtcInfo			*crtc;
    int					i, idx_output = -1;

    if (!cub3d()->window.fullscreen)
        return ;

    if (!XGetWindowAttributes(xvar->display, win->window, &watt))
        return ;

    res = XRRGetScreenResources(xvar->display, xvar->root);
    i = res->noutput;
    while (i--)
    {
        o_info = XRRGetOutputInfo(xvar->display, res, res->outputs[i]);
        if (o_info->connection == RR_Connected)
        {
            idx_output = i;
            break ;
        }
        XRRFreeOutputInfo(o_info);
    }
    if (idx_output == -1 || !o_info)
    {
        XRRFreeScreenResources(res);
        return ;
    }
    crtc = XRRGetCrtcInfo(xvar->display, res, o_info->crtc);
    XRRSetCrtcConfig(xvar->display, res, o_info->crtc, CurrentTime, 0, 0, saved_mode,
        crtc->rotation, &res->outputs[idx_output], 1);
    XRRFreeCrtcInfo(crtc);
    XRRFreeOutputInfo(o_info);
    XRRFreeScreenResources(res);
}
