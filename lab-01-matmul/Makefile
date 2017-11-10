CC = gcc
CFLAGS	= -fopenmp

PERF = -O3 -g
DEBUG = -O0 -g

#CFLAGS	+= $(DEBUG)
CFLAGS += $(PERF)

INC=-I${EXTRAE_HOME}/include
EXTRAEL = -L$(EXTRAE_HOME)/lib -lomptrace

SOURCES = driver.c check.c gendat.c prtspeed.c cclock.c matmul.c
OBJECTS = driver.o check.o gendat.o prtspeed.o cclock.o matmul.o

all: matmul matmul.extrae

matmul: $(OBJECTS)
	$(CC) $(CFLAGS) -o matmul $(OBJECTS) $(LDFLAGS)

driver.o: driver.c config.h precision.h
	$(CC) $(CFLAGS) -c driver.c

check.o: check.c config.h precision.h
	$(CC) $(CFLAGS) -c check.c

gendat.o: gendat.c config.h precision.h
	$(CC) $(CFLAGS) -c gendat.c

prtspeed.o: prtspeed.c precision.h
	$(CC) $(CFLAGS) -c prtspeed.c

cclock.o: cclock.c
	$(CC) $(CFLAGS) -c cclock.c

matmul.o: matmul.c config.h precision.h
	$(CC) $(CFLAGS) -c matmul.c


matmul.extrae: $(SOURCES) $(EXTRAE_HOME)/include/extrae_user_events.h
	$(CC) -D_EXTRAE_ $(INC) $(CFLAGS) $(SOURCES) -o matmul.extrae \
             $(EXTRAEL) $(LDFLAGS)

$(EXTRAE_HOME)/include/extrae_user_events.h:
	@echo "> ERROR: Extrae RTL needed to build instrumented version."
	@echo "> Edit configure.sh file and set EXTRAE_HOME environment variable."
	@false

clean:
	rm -fr $(OBJECTS) $(COMP_FILES) \
            matmul matmul.extrae TRACE.sym TRACE.mpits set-0 \
            matmul.prv matmul.pcf matmul.row


