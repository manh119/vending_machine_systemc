OBJEXT = o
TARGET_ARCH = linux

CXX_FILES = \
    control.cpp \
	main.cpp \
	supply.cpp \
	tester.cpp \

H_FILES = \
	control.h \
	supply.h \
	tester.h \
	definition.h \

control_OBJECTS = control.$(OBJEXT) main.$(OBJEXT) supply.$(OBJEXT) tester.$(OBJEXT)
control_DEPENDENCIES =

all: control

control_LDFLAGS =
control_LDADD = -L/usr/local/system-2.3.4/lib-linux64 -lsystemc-2.3.4 -lm
LIBS = 
LDFLAGS = 
CXXLD = $(CXX)
CXXLINK = $(CXXLD) $(CXXFLAGS) $(LDFLAGS) \
	-o $@

control: $(control_OBJECTS) $(control_DEPENDENCIES) 
	@rm -f control
	$(CXXLINK) $(control_LDFLAGS) $(control_OBJECTS) $(control_LDADD) $(LIBS)

.SUFFIXES:
.SUFFIXES: .cpp .o .obj
srcdir = .
prefix = /usr/local/system-2.3.4
CXX = g++
DEFS = -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" 
DEFAULT_INCLUDES = -I. -I$(srcdir)
INCLUDES = -I$(prefix)/include
CPPFLAGS = 
# CXXFLAGS = -Wall -DSC_INCLUDE_FX -O3
CXXFLAGS = -DSC_INCLUDE_FX -O3 $(INCLUDES)

CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(CPPFLAGS) $(CXXFLAGS)

.cpp.o:
	$(CXXCOMPILE) -c -o $@ `test -f '$<' || echo '$(srcdir)/'`$<

debug: CXXFLAGS += -g
debug: control

.PHONY: debug

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise, a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

clean: 
	rm -f *.o control control.vcd
