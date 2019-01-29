#include <stdlib.h>
#include <stdio.h>
#include <dbus/dbus.h>
#include <gio/gio.h>
#include <dbus/dbus-glib.h>

char* get_process_name_by_pid(const int pid)
{
    char* name = (char*)calloc(1024,sizeof(char));

    if(name)
    {
        sprintf(name, "/proc/%d/status",pid);
        FILE* f = fopen(name,"r");
        if(f)
	{
            fgets(name, 1024, f);
            fclose(f);
        }
    }
    return name;
}

char* getObjNameForBus(char* busName)
{
  GError *error = NULL;
  GDBusConnection *conn = NULL;

  conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
  g_assert_no_error(error);

  if (conn == NULL)
    {
      g_printerr ("Failed to open connection to bus: %s\n",
              error->message);
      g_error_free (error);
      exit (1);
    }

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

  g_printf("pid = %d\n", pidNum);

  char* processName = get_process_name_by_pid(pidNum);

  return processName;	

}


int
main (int argc, char **argv)
{

  if( argc < 2 )
  {
  	g_print ("Please specify bus name as first param\n");
  	return 0;
  }  
	

  char* busName = argv[1];
  g_print(" busName: %s\n", busName); 

  char objName[128] = {0};

  char* processName = getObjNameForBus(busName);


  g_print ("process id for bus: %s is %s\n", busName, processName);

  return 0;
}
