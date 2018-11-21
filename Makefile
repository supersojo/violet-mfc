#
# nmake Makefile
#
EXE = main.exe
OBJS = windows.obj direction.obj abstractnode.obj notenode.obj vcontext.obj stringutil.obj vcolor.obj
LIBS = user32.lib gdi32.lib
LFLAGS = /subsystem:windows
CFLAGS = /c /EHsc

# explicit
$(EXE) : $(OBJS)
    link $(LFLAGS) $(OBJS) $(LIBS) /OUT:$(EXE)
    
# implicit
.cpp.obj:
    @cl $(CFLAGS) $<
    
# clean
clean:
    del *.obj
    del $(EXE)