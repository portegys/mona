# The Mona foraging ant program makefile

CC = gcc

# MONA_TRACE: tracing.
# ACTIVITY_TRACKING: tracks firing, enablement, and drive activity for network dump.
#CCFLAGS = -DUNIX -DANT_ENV -DMONA_TRACE -DACTIVITY_TRACKING
CCFLAGS = -DUNIX -DANT_ENV -DMONA_TRACE

all: ../../bin/ant

../../bin/ant: ant.o monami.o environment.o \
	../mona/mona.hpp ../mona/mona.cpp ../mona/sense.cpp ../mona/enable.cpp \
	../mona/drive.cpp ../mona/respond.cpp ../mona/utility.cpp \
	../common/pointerlist.o ../common/valueset.o ../common/random.o
	/bin/cp ../mona/mona.hpp .
	/bin/cp ../mona/mona.cpp .
	$(CC) $(CCFLAGS) -c mona.cpp
	/bin/cp ../mona/sense.cpp .
	$(CC) $(CCFLAGS) -c sense.cpp
	/bin/cp ../mona/enable.cpp .
	$(CC) $(CCFLAGS) -c enable.cpp
	/bin/cp ../mona/drive.cpp .
	$(CC) $(CCFLAGS) -c drive.cpp
	/bin/cp ../mona/respond.cpp .
	$(CC) $(CCFLAGS) -c respond.cpp
	/bin/cp ../mona/utility.cpp .
	$(CC) $(CCFLAGS) -c utility.cpp
	$(CC) -o ../../bin/ant mona.o sense.o enable.o drive.o respond.o utility.o \
		../common/pointerlist.o ../common/valueset.o ../common/random.o \
		monami.o environment.o ant.o -lstdc++
	/bin/rm -f mona.hpp mona.cpp mona.o sense.cpp sense.o enable.cpp enable.o \
		drive.cpp drive.o respond.cpp respond.o utility.cpp utility.o

monami.o: ../mona/mona.hpp environment.hpp monami.hpp monami.cpp
	$(CC) $(CCFLAGS) -c monami.cpp

environment.o: environment.hpp environment.cpp
	$(CC) $(CCFLAGS) -c environment.cpp

ant.o: ../mona/mona.hpp monami.hpp environment.hpp ant.cpp
	$(CC) $(CCFLAGS) -c ant.cpp

clean:
	/bin/rm -f *.o
