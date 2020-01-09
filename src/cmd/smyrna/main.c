/* $Id: main.c,v 1.58 2009/12/09 23:45:26 erg Exp $Revision: */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
//windows.h for win machines
#if defined(_WIN32) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <windowsx.h>
#endif
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <glade/glade.h>
#include "gui.h"
#include "viewport.h"
#include "support.h"
#include "menucallbacks.h"
#include "gltemplate.h"
#include "memory.h"
#include "gvprpipe.h"
#include "frmobjectui.h"
#ifdef ENABLE_NLS
#include "libintl.h"
#endif
#include <assert.h>

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#else
#include "compat_getopt.h"
#endif

#ifdef G_OS_WIN32
gchar *package_prefix;
gchar *package_data_dir;
#endif
gchar *package_locale_dir;
static char *smyrnaDir;		/* path to directory containin smyrna data files */
char *smyrnaGlade;
unsigned char SmyrnaVerbose;


/* smyrnaPath:
 * Construct pathname for smyrna data file.
 * Base file name is given as suffix.
 * The function resolves the directory containing the data files,
 * and constructs a complete pathname.
 * The returned string is malloced, so the application should free
 * it later.
 * Returns NULL on error.
 */
char *smyrnaPath(char *suffix)
{
    char *buf;
    static int baselen;
    int slen;
#ifdef WIN32
    char *pathSep = "\\";
#else
    char *pathSep = "/";
#endif
    assert(smyrnaDir);

    if (baselen == 0) {
	baselen = (int)strlen(smyrnaDir) + 2;
    }
    slen = (int)strlen(suffix);
    buf = N_NEW(baselen+slen, char);
    sprintf(buf, "%s%s%s", smyrnaDir, pathSep, suffix);
    return buf;
}

static char *useString = "Usage: smyrns [-v?] <file>\n\
  -v         - verbose\n\
  -?         - print usage\n";

static void usage(int v)
{
    printf(useString);
    exit(v);
}


static char *parseArgs(int argc, char *argv[], ViewInfo * view)
{
    unsigned int c;

    while ((c = getopt(argc, argv, ":K:txv?")) != -1) {
	switch (c) {
	case 'v':
	    SmyrnaVerbose = 1;
	    break;
#if 0
	case 't':
	    view->dfltViewType = VT_TOPVIEW;
	    break;
	case 'x':
	    view->dfltViewType = VT_XDOT;
	    break;
	case 'K':
	    view->dfltEngine = s2layout(optarg);
	    break;
#endif
	case '?':
	    if (optopt == '?')
		usage(0);
	    else
		fprintf(stderr,
			"smyrna: option -%c unrecognized - ignored\n",
			optopt);
	    break;
	}
    }

    if (optind < argc)
	return argv[optind];
    else
	return NULL;
}

#ifdef UNUSED
static void close_cgraph(Agraph_t * g)
{
    Agnode_t *v;
    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	agdelrec(v, "temp_node_record");
    }
    agclose(g);
}

#endif

int main(int argc, char *argv[])
{
    GdkGLConfig *glconfig;
    char *initFileName;
    /*combo box to show loaded graphs */
    GtkComboBox *graphComboBox;



    smyrnaDir = getenv("SMYRNA_PATH");
    if (!smyrnaDir) {
#ifdef _WIN32
	int sz =
	    GetCurrentDirectory(0,
				NULL) +
	    strlen("\\share\\graphviz\\smyrna") + 1;
	smyrnaDir = N_NEW(sz, char);
	GetCurrentDirectory(sz, smyrnaDir);
	smyrnaDir[strlen(smyrnaDir) - 4] = (char) 0;
	strcat(smyrnaDir, "\\share\\graphviz\\smyrna");
#else
	smyrnaDir = SMYRNA_PATH;
#endif
    }
    load_attributes();

#ifdef G_OS_WIN32
    package_prefix =
	g_win32_get_package_installation_directory(NULL, NULL);
    package_data_dir = g_build_filename(package_prefix, "share", NULL);
    package_locale_dir =
	g_build_filename(package_prefix, "share", "locale", NULL);
#else
    package_locale_dir = g_build_filename(smyrnaDir, "locale", NULL);
#endif				/* # */
#ifdef ENABLE_NLS
    bindtextdomain(GETTEXT_PACKAGE, package_locale_dir);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
#endif
    view = NEW(ViewInfo);

    init_viewport(view);
    gtk_set_locale();
    gtk_init(&argc, &argv);
    initFileName = parseArgs(argc, argv, view);
    if (!(smyrnaGlade))
	smyrnaGlade = smyrnaPath("smyrna.glade");
    xml = glade_xml_new(smyrnaGlade, NULL, NULL);

    gladewidget = glade_xml_get_widget(xml, "frmMain");
    gtk_widget_show(gladewidget);
    g_signal_connect((gpointer) gladewidget, "destroy",
		     G_CALLBACK(mQuitSlot), NULL);
    glade_xml_signal_autoconnect(xml);
    if (initFileName) {
	view->initFile = 1;
	view->initFileName = strdup(initFileName);
    }
    gtk_gl_init(0, 0);
    /* Configure OpenGL framebuffer. */
    glconfig = configure_gl();
//      gladewidget = glade_xml_get_widget(xml, "vbox2");
    gladewidget = glade_xml_get_widget(xml, "hbox11");

    gtk_widget_hide(glade_xml_get_widget(xml, "vbox13"));
    gtk_window_set_deletable ((GtkWindow*)glade_xml_get_widget(xml, "dlgSettings"),0);
    gtk_window_set_deletable ((GtkWindow*)glade_xml_get_widget(xml, "dlgTVFilter"),0);
    gtk_window_set_deletable ((GtkWindow*)glade_xml_get_widget(xml, "frmTVNodes"),0);


    create_window(glconfig, gladewidget);

    change_cursor(GDK_TOP_LEFT_ARROW);

#ifndef WIN32
    glutInit(&argc, argv);
#endif

    gladewidget = glade_xml_get_widget(xml, "hbox13");
    graphComboBox = (GtkComboBox *) gtk_combo_box_new_text();
    gtk_box_pack_end((GtkBox*)gladewidget, (GtkWidget*)graphComboBox, 1, 1, 10);
    gtk_widget_show((GtkWidget*)graphComboBox);
    view->graphComboBox = graphComboBox;
    gtk_main();



#ifdef G_OS_WIN32
    g_free(package_prefix);
    g_free(package_data_dir);
#endif
    g_free(package_locale_dir);
    return 0;
}
