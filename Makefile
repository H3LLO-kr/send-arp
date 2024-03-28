NAME	= send-arp
LDLIBS	=-lpcap
RM		= rm -rf
OBJS	= main.o \
		  arphdr.o \
		  ethhdr.o \
		  ip.o \
		  mac.o \
		  _send-arp_func.o

all: $(NAME)


main.o: mac.h ip.h ethhdr.h arphdr.h main.cpp

arphdr.o: mac.h ip.h arphdr.h arphdr.cpp

ethhdr.o: mac.h ethhdr.h ethhdr.cpp

ip.o: ip.h ip.cpp

mac.o : mac.h mac.cpp

_send-arp_func.o : _send-arp_func.cpp

$(NAME): main.o arphdr.o ethhdr.o ip.o mac.o _send-arp_func.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	$(RM) $(NAME)
	$(RM) $(OBJS)
