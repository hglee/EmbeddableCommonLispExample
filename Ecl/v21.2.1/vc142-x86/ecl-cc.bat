@ECHO OFF
REM Script to compile/link a C file with ECL
REM (Michael Goffioul)

set CMDTYPE=%1
set CMDARGS=
:LOOP
shift
IF NOT "%1" == "" (
	set CMDARGS=%CMDARGS% %1
	goto LOOP
)

IF %CMDTYPE% == --compile (
	cl /EHsc /DGC_DLL /DGC_BUILD /nologo /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG /MD /O2 /arch:SSE2 -IC:/Workspace/ecl-21.2.1/msvc/package/ecl %CMDARGS%
	GOTO END
) ELSE IF %CMDTYPE% == --link (
	cl %CMDARGS% /link /incremental:no /nologo  /STACK:1048576 C:/Workspace/ecl-21.2.1/msvc/package/ecl.lib
	GOTO END
)

ECHO Usage: %0 [OPTIONS] [ARGS*]
ECHO Options:
ECHO      [--compile]
ECHO      [--link]

:END
