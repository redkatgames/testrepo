#include <stdlib.h>
#include <dbus/dbus.h>
#include <gio/gio.h>
#include <dbus/dbus-glib.h>

int
main (int argc, char **argv)
{
  GDBusConnection *conn = NULL;
  GError *error = NULL;

  if( argc < 2 )
  {
  	g_print ("Please specify bus name as first param\n");
  	return 0;
  }  

  char* busName = argv[1];
  g_print(" busName: %s\n", busName); 

  conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
  g_assert_no_error(error);

  if (conn == NULL)
    {
      g_printerr ("Failed to open connection to bus: %s\n",
              error->message);
      g_error_free (error);
      exit (1);
    }

/*	
	// nu e nevoie de proxy daca folosesc g_dbus_connection_call_sync si nu g_dbus_proxy_call
	proxy = g_dbus_proxy_new_sync(conn,
				      G_DBUS_PROXY_FLAGS_NONE,
				      NULL,				
				      "org.freedesktop.DBus",		
				      "/org/freedesktop/DBus",	
				      "org.freedesktop.DBus",
				      NULL,		
				      &error);
*/

  GVariant *_ret;
  _ret = g_dbus_connection_call_sync(conn,
		  "org.freedesktop.DBus",           /* name */
		  "/org/freedesktop/DBus",          /* object path */
		  "org.freedesktop.DBus",           /* interface */
		  "GetConnectionUnixProcessID",
		  g_variant_new ("(s)", busName),
		  NULL,
		  G_DBUS_CALL_FLAGS_NONE,
		  -1,
		  NULL,
		  0);	

  if (_ret == NULL)
  {
  	g_print ("Error in dbus response, exiting\n");
	return 0;
  }

  int pidNum = 0;
  g_variant_get (_ret, "(u)", &pidNum);
  g_variant_unref (_ret);
  g_print ("process id for bus: %s is %d\n", busName, pidNum);

  return 0;
}
