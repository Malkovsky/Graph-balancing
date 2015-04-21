all: balancing flows flows2 gauss
	
balancing:
	g++ -O2 balancing.cpp -obalancing.exe

flows:
	g++ -O2 flows.cpp -oflows.exe

flows2:
	g++ -O2 flows2.cpp -oflows2.exe

gauss:
	g++ -O2 gauss.cpp -ogauss.exe

	