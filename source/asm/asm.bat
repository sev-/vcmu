@ECHO OFF
IF %1==BTC GOTO DOBTC
IF %1==MSC GOTO DOMSC
GOTO BATCHERR
:DOBTC
IF %2==LARGE GOTO DOBTCL
IF %2==MEDIUM GOTO DOBTCM
IF %2==SMALL GOTO DOBTCS
GOTO BATCHERR
:DOBTCL
tasm /ml /dL vcmouse.asm,vcmousel.obj
tasm /ml /dL vctio.asm,vctiol.obj
GOTO ENDBATCH
:DOBTCM
tasm /ml /dM vcmouse.asm,vcmousem.obj
tasm /ml /dM vctio.asm,vctiom.obj
GOTO ENDBATCH
:DOBTCS
tasm /ml /dS vcmouse.asm,vcmouses.obj
tasm /ml /dS vctio.asm,vctios.obj
GOTO ENDBATCH
:DOMSC
IF %2==LARGE GOTO DOMSCL
IF %2==MEDIUM GOTO DOMSCM
IF %2==SMALL GOTO DOMSCS
GOTO BATCHERR
:DOMSCL
c:\masm\masm /ml /dL vcmouse.asm,vcmousel.obj;
c:\masm\masm /ml /dL vctio.asm,vctiol.obj;
GOTO ENDBATCH
:DOMSCM
c:\masm\masm /ml /dM vcmouse.asm,vcmousem.obj;
c:\masm\masm /ml /dM vctio.asm,vctiom.obj;
GOTO ENDBATCH
:DOMSCS
c:\masm\masm /ml /dS vcmouse.asm,vcmouses.obj;
c:\masm\masm /ml /dS vctio.asm,vctios.obj;
GOTO ENDBATCH
:BATCHERR
ECHO  MUST SPECIFY {ASSEMBLER} {MODEL}
ECHO  WHERE {ASSEMBLER} = "MSC" OR "BTC"
ECHO  AND {MODEL} = "LARGE", "MEDIUM" OR "SMALL"
ECHO  I.E. "ASM MSC LARGE" FOR LARGE MICROSOFT OBJECT
:ENDBATCH

