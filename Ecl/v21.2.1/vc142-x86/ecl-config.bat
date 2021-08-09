@ECHO OFF
REM Script converted from ecl-config
REM (Michael Goffioul)

IF %1 == --cflags (
	ECHO /EHsc /DGC_DLL /DGC_BUILD /nologo /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG /MD /O2 /arch:SSE2 -IC:/Workspace/ecl-21.2.1/msvc/package/ecl
	GOTO END
) ELSE IF %1 == --libs (
	ECHO /link /incremental:no /nologo  /STACK:1048576 /link /LIBPATH:C:/Workspace/ecl-21.2.1/msvc/package ecl.lib 
	GOTO END
)

ECHO Usage: ecl-config [OPTIONS]
ECHO Options:
ECHO      [--cflags]
ECHO      [--libs]

:END
