/*
 * A PDFViewer deam
 * Build from  WebKitGTK+ and pdf.js
 * 
 * author:yilei <yilei108@gmail.com>
 *
 */

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>


static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    // Create a browser instance
	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

	/* Create a new websettings and disable java script */
	WebKitSettings *settings = webkit_web_view_get_settings(webView);
	
	webkit_settings_set_allow_file_access_from_file_urls(settings, TRUE);
	
	/* Apply the result */
	webkit_web_view_set_settings (webView, settings);

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

    // Load a web page into the browser instance
    //webkit_web_view_load_uri(webView, "file:///home/kylin/work/pdf/web/viewer.html#disableWorker=true");
    webkit_web_view_load_uri(webView, "file:///home/kylin/work/pdf/learning/helloworld.html");
    // Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(main_window);

    // Run the main GTK+ event loop
    gtk_main();

    return 0;
}


static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
{
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
{
    gtk_widget_destroy(window);
    return TRUE;
}
