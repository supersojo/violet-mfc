#
# nmake Makefile
#
EXE = main.exe
OBJS = application.obj vcomponent.obj workspace.obj workspacepanel.obj sidebar.obj sidebarpanel.obj direction.obj abstractnode.obj abstractedge.obj \
       abstractgraph.obj notenode.obj vcontext.obj stringutil.obj \
       vcolor.obj linestyle.obj bentstyle.obj lineedge.obj \
       linestylechoicelist.obj bentstylechoicelist.obj arrowhead.obj \
       arrowheadchoicelist.obj labeledlineedge.obj separator.obj

LIBS = user32.lib gdi32.lib 
LFLAGS = /subsystem:windows
CFLAGS = /c /EHsc /Zi /I./../include

# explicit
$(EXE) : $(OBJS)
    link $(LFLAGS) $(OBJS) $(LIBS) /OUT:$(EXE)
    
# implicit
.cpp.obj:
    cl $(CFLAGS) $<
    
# clean
clean:
    del *.obj
    del $(EXE)
