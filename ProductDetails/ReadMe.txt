========================================================================
    CONSOLE APPLICATION : "ProductDetails" Project Overview
========================================================================
RogueWave MsSql based project using same codebase as MySql based projects.
/////////////////////////////////////////////////////////////////////////////
Includes - $(CGICC);$(RWSP_HOME);$(MYSQL)\include

Debug link dirs - $(CGICC)/win/Debug;$(RWSP_HOME)\lib;$(MYSQL)\lib\debug
Release link dirs $(CGICC)/win/Release;$(RWSP_HOME)\lib;$(MYSQL)\lib\opt

library usage: ---------------------------------------------------------
Debug: cgicc.lib;dbt15s.lib;msq15s.lib;odbc32.lib;rwmsq15s.obj;ws2_32.lib;tls15s.lib;
functor15s.lib;pointer15s.lib;sync15s.lib;itc15s.lib;threxcept15s.lib;internet15s.lib;
network15s.lib;http15s.lib
========================================================================
Release: cgicc.lib;dbt12s.lib;msq12s.lib;odbc32.lib;rwmsq12s.obj;ws2_32.lib;tls12s.lib;
functor12s.lib;pointer12s.lib;sync12s.lib;itc12s.lib;threxcept12s.lib;internet12s.lib;
network12s.lib;http12s.lib
/////////////////////////////////////////////////////////////////////////////
http://10.40.85.20/cgi-bin/rw_mssql.exe?isbn=9781401395049